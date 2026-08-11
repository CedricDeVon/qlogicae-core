from __future__ import annotations

from typing import Any

_json: Any = None
_SingletonManager: Any = None
_JsonManager: Any = None


def _handle_dynamic_imports() -> None:
    global _handle_dynamic_imports
    global _json
    global _SingletonManager
    global _JsonManager

    import json

    from .json_manager import JsonManager
    from .singleton_manager import SingletonManager

    _json = json
    _SingletonManager = (
        SingletonManager
    )
    _JsonManager = (
        JsonManager
    )

    _handle_dynamic_imports = lambda: None


class JsonTextManager:
    def __init__(self) -> None:
        _handle_dynamic_imports()

    def is_valid(
        self,
        value: str,
    ) -> bool:
        _json.loads(value)

        return True

    def convert_to_object(
        self,
        value: str,
    ) -> Any:
        return _json.loads(value)

    def convert_to_string(
        self,
        value: Any,
    ) -> str:
        manager: _JsonManager = (
            _SingletonManager.get_singleton(
                _JsonManager,
            )
        )

        result: str = _json.dumps(
            value,
            indent=manager.indent_count,
            ensure_ascii=manager.is_ascii_format_enabled,
        )

        return result
