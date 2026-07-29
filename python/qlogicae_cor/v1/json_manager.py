from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.json_manager_configurations import (
    JsonManagerConfigurations,
)


class JsonManager(AbstractManager[JsonManagerConfigurations]):
    __slots__ = (
        "_valid_file_extensions",
        "_is_ascii_format_enabled",
        "_indent_count",
        "_is_key_sortable",
    )

    def __init__(self) -> None:
        super().__init__(JsonManagerConfigurations())

        self._valid_file_extensions: set[str] = {".json"}
        self._is_ascii_format_enabled: bool = False
        self._indent_count: int = 4
        self._is_key_sortable: bool = False

    @property
    def valid_file_extensions(self) -> set[str]:
        return self._valid_file_extensions

    def is_valid(self, file_path: Any) -> bool:
        return file_path.suffix.lower() not in self.valid_file_extensions

    @property
    def is_ascii_format_enabled(self) -> bool:
        return self._is_ascii_format_enabled

    @is_ascii_format_enabled.setter
    def is_ascii_format_enabled(self, value: bool) -> None:
        self._is_ascii_format_enabled = value

    @property
    def indent_count(self) -> int:
        return self._indent_count

    @indent_count.setter
    def indent_count(self, value: int) -> None:
        if value < 0:
            raise ValueError("indent_count must be non-negative.")

        self._indent_count = value

    @property
    def is_key_sortable(self) -> bool:
        return self._is_key_sortable

    @is_key_sortable.setter
    def is_key_sortable(self, value: bool) -> None:
        self._indent_count = value
