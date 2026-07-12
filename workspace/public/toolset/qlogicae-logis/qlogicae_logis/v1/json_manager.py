from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.json_manager_configurations import JsonManagerConfigurations


class JsonManager(AbstractManager[JsonManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(JsonManagerConfigurations())

        self._valid_file_extensions: set[str] = {".json"}
        self._is_ascii_format_enabled: bool = False
        self._indent_count: int = 4

    @property
    def valid_file_extensions(self) -> set[str]:
        return self._valid_file_extensions

    def is_valid_file_extension(self, file: Any) -> bool:
        return any(
            suffix in self._valid_file_extensions
            for suffix in self._valid_file_extensions
        )

    @property
    def is_ascii_format_enabled(self) -> bool:
        return self._is_ascii_format_enabled

    @is_ascii_format_enabled.setter
    def is_ascii_format_enabled(self, value: bool) -> bool:
        self._is_ascii_format_enabled = value

        return True

    @property
    def indent_count(self) -> int:
        return self._indent_count

    @indent_count.setter
    def indent_count(self, value: int) -> bool:
        if value < 0:
            raise Exception("indent_count must be non-negative.")

        self._indent_count = value

        return True


singleton = JsonManager()
