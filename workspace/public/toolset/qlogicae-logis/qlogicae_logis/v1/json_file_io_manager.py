import json
from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import json_manager
from qlogicae_logis.v1.json_file_io_manager_configurations import (
    JsonFileIoManagerConfigurations,
)


class JsonFileIoManager(AbstractManager[JsonFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(JsonFileIoManagerConfigurations())

    def read_file(self, file: Any) -> Any:
        return json.load(file) or {}

    def write_file(self, file: Any, data: Any) -> bool:
        json.dump(
            data,
            file,
            indent=json_manager.singleton.indent_count,
            ensure_ascii=json_manager.singleton.is_ascii_format_enabled,
        )

        return True


singleton = JsonFileIoManager()
