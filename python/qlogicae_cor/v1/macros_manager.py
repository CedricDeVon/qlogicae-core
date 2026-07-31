from __future__ import annotations

from typing import Any

_re: Any = None
_Path: Any = None
_Mapping: Any = None
_singleton_manager: Any = None
_text_encoding_manager: Any = None


def _handle_dynamic_imports() -> None:
    global _handle_dynamic_imports
    global _re
    global _Path
    global _Mapping
    global _singleton_manager
    global _text_encoding_manager

    import re
    from collections.abc import Mapping
    from pathlib import Path

    import qlogicae_cor.v1.singleton_manager
    import qlogicae_cor.v1.text_encoding_manager

    _re = re
    _Path = Path
    _Mapping = Mapping
    _singleton_manager = qlogicae_cor.v1.singleton_manager.SingletonManager
    _text_encoding_manager = qlogicae_cor.v1.text_encoding_manager.TextEncodingManager

    _handle_dynamic_imports = lambda: None


class MacrosManager:
    __slots__ = (
        "_selected_identifier_pattern",
        "_selected_macros_pattern",
    )

    def __init__(self) -> None:
        _handle_dynamic_imports()

        self._selected_identifier_pattern: _re.Pattern[str] = (
            _re.compile(r"^[A-Za-z0-9._-]+$")
        )
        self._selected_macros_pattern: _re.Pattern[str] = (
            _re.compile(r"\$\{\{\s*([A-Za-z0-9._-]+)\s*\}\}")
        )

    @property
    def selected_identifier_pattern(self) -> _re.Pattern[str]:
        return self._selected_identifier_pattern

    @selected_identifier_pattern.setter
    def selected_identifier_pattern(self, value: str) -> None:
        self._selected_identifier_pattern = _re.compile(value)

    @property
    def selected_macros_pattern(self) -> _re.Pattern[str]:
        return self._selected_macros_pattern

    @selected_macros_pattern.setter
    def selected_macros_pattern(self, value: str) -> None:
        self._selected_macros_pattern = _re.compile(value)

    def resolve_many(
        self,
        values: object,
    ) -> _Mapping[str, object]:
        if not isinstance(values, _Mapping):
            raise TypeError("'values' must be a mapping")

        for key in values:
            if not isinstance(key, str):
                raise TypeError("macro names must be strings")

            if not self._selected_identifier_pattern.fullmatch(key):
                raise ValueError(f"invalid macro name: '{key}'")

        cache: dict[str, object] = {}

        for root in values:
            if root in cache:
                continue

            stack: list[str] = [root]
            visiting: set[str] = set()

            while stack:
                key = stack[-1]

                if key in cache:
                    stack.pop()
                    visiting.discard(key)
                    continue

                if key not in values:
                    raise ValueError(
                        f"key path '{key}' is an unknown macros",
                    )

                value = values[key]

                if not isinstance(value, str):
                    cache[key] = value
                    stack.pop()
                    visiting.discard(key)
                    continue

                if key not in visiting:
                    visiting.add(key)

                unresolved: list[str] = []

                for match in self._selected_macros_pattern.finditer(value):
                    dependency = match.group(1)

                    if dependency in cache:
                        continue

                    if dependency in visiting:
                        raise ValueError(
                            f"key path '{dependency}' is a circular reference",
                        )

                    unresolved.append(dependency)

                if unresolved:
                    stack.extend(reversed(unresolved))
                    continue

                def replace(
                    match: _re.Match[str],
                ) -> str:
                    dependency = match.group(1)
                    return str(cache[dependency])

                cache[key] = self._selected_macros_pattern.sub(
                    replace,
                    value,
                )

                stack.pop()
                visiting.remove(key)

        return cache

    def resolve_one(
        self,
        key: object,
        values: object,
        cache: dict[object, object],
        stack: set[object],
    ) -> object:
        if not isinstance(key, str):
            raise TypeError("'key' must be a string")

        if not isinstance(values, _Mapping):
            raise TypeError("'values' must be a mapping")

        if not isinstance(cache, dict):
            raise TypeError("'cache' must be a dictionary")

        if not isinstance(stack, set):
            raise TypeError("'stack' must be a set")

        if key not in values:
            raise KeyError(f"unknown macro '{key}'")

        if key in cache:
            return cache[key]

        frames: list[tuple[object, bool]] = [(key, False)]

        while frames:
            current_key, expanded = frames.pop()

            if current_key in cache:
                continue

            if not expanded:
                if current_key in stack:
                    raise ValueError(
                        f"key path '{current_key}' is a circular reference",
                    )

                if current_key not in values:
                    raise ValueError(
                        f"key path '{current_key}' is an unknown macros",
                    )

                value = values[current_key]

                if not isinstance(value, str):
                    cache[current_key] = value
                    continue

                stack.add(current_key)

                frames.append((current_key, True))

                for match in self._selected_macros_pattern.finditer(value):
                    dependency = match.group(1)

                    if dependency not in values:
                        raise KeyError(
                            f"macro '{current_key}' references unknown macro "
                            f"'{dependency}'",
                        )

                    if dependency in stack:
                        raise ValueError(
                            f"circular macro reference: "
                            f"'{current_key}' -> '{dependency}'",
                        )

                    if dependency not in cache:
                        frames.append((dependency, False))

            else:
                value = values[current_key]

                cache[current_key] = self._selected_macros_pattern.sub(
                    lambda match: str(cache[match.group(1)]),
                    value,
                )

                stack.remove(current_key)

        return cache[key]

    def parse_many(
        self,
        values: object,
        resolved: _Mapping[str, object],
    ) -> object:
        return self.parse_one(values, resolved)

    def parse_one(
        self,
        value: object,
        resolved: _Mapping[str, object],
    ) -> object:
        if isinstance(value, str):
            return self._selected_macros_pattern.sub(
                lambda match: resolved.get(
                    match.group(1),
                    match.group(0),
                ),
                value,
            )

        if isinstance(value, dict):
            return {
                key: self.parse_one(child, resolved)
                for key, child in value.items()
            }

        if isinstance(value, list):
            return [
                self.parse_one(child, resolved)
                for child in value
            ]

        if isinstance(value, tuple):
            return tuple(
                self.parse_one(child, resolved)
                for child in value
            )

        if isinstance(value, set):
            return {
                self.parse_one(child, resolved)
                for child in value
            }

        return value

    def parse_filesystem(
        self,
        filesystem_path: str | _Path,
        workspace_macros: object,
    ) -> bool:
        encoding = (
            _singleton_manager.get_singleton(
                _text_encoding_manager,
            ).selected_encoding
        )

        root = _Path(filesystem_path)

        for current_root, directories, files in root.walk(
            top_down=False,
        ):
            current_root = _Path(current_root)

            for file_name in files:
                current_path = current_root / file_name

                try:
                    file_data = current_path.read_text(
                        encoding=encoding,
                    )
                except UnicodeDecodeError:
                    pass
                else:
                    parsed_file_data = self.parse_one(
                        file_data,
                        workspace_macros,
                    )

                    if parsed_file_data != file_data:
                        current_path.write_text(
                            parsed_file_data,
                            encoding=encoding,
                        )

                parsed_name = self.parse_one(
                    current_path.name,
                    workspace_macros,
                )

                if parsed_name != current_path.name:
                    current_path = current_path.rename(
                        current_path.with_name(
                            parsed_name,
                        ),
                    )

            for directory_name in directories:
                current_path = current_root / directory_name

                parsed_name = self.parse_one(
                    current_path.name,
                    workspace_macros,
                )

                if parsed_name != current_path.name:
                    current_path.rename(
                        current_path.with_name(
                            parsed_name,
                        ),
                    )

        return True
