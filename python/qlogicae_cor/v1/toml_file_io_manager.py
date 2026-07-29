import tomllib
from typing import Any

import tomli_w

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.toml_file_io_manager_configurations import (
    TomlFileIoManagerConfigurations,
)


class TomlFileIoManager(AbstractManager[TomlFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TomlFileIoManagerConfigurations())

    def read_file(self, file_path: Any) -> Any:
        output_data = {}

        with file_path.open("rb") as file:
            output_data = tomllib.load(file)

        return output_data

    def write_file(self, file_path: Any, data: Any) -> bool:
        file_path.parent.mkdir(
            parents=True,
            exist_ok=True,
        )

        with file_path.open("wb") as file:
            tomli_w.dump(
                data,
                file,
            )

        return True
