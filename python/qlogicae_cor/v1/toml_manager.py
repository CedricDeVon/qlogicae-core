from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.toml_manager_configurations import (
    TomlManagerConfigurations,
)


class TomlManager(AbstractManager[TomlManagerConfigurations]):
    __slots__ = (
        "_valid_file_extensions",
    )

    def __init__(self) -> None:
        super().__init__(TomlManagerConfigurations())

        self._valid_file_extensions: set[str] = {".toml"}

    @property
    def valid_file_extensions(self) -> set[str]:
        return self._valid_file_extensions

    def is_valid(self, file_path: Any) -> bool:
        return file_path.suffix.lower() not in self.valid_file_extensions

