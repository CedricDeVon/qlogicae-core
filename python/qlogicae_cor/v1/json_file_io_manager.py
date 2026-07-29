import json
from pathlib import Path
from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.json_file_io_manager_configurations import (
    JsonFileIoManagerConfigurations,
)
from qlogicae_cor.v1.json_manager import (
    JsonManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.text_encoding_manager import TextEncodingManager


class JsonFileIoManager(AbstractManager[JsonFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(JsonFileIoManagerConfigurations())

    def read_file(self, file_path: str) -> Any:
        path = Path(file_path)

        output_data: Any = {}
        with path.open(
            mode="r",
            encoding=SingletonManager.get_singleton(
                TextEncodingManager
            ).selected_encoding,
        ) as file:
            output_data = json.load(file) or {}

        return output_data

    def write_file(self, file_path: str, data: Any) -> bool:
        path = Path(file_path)

        path.parent.mkdir(
            parents=True,
            exist_ok=True,
        )
        with path.open(
            mode="w",
            encoding=SingletonManager.get_singleton(
                TextEncodingManager
            ).selected_encoding,
        ) as file:
            json.dump(
                data,
                file,
                indent=SingletonManager.get_singleton(
                    JsonManager
                ).indent_count,
                ensure_ascii=SingletonManager.get_singleton(
                    JsonManager
                ).is_ascii_format_enabled,
                sort_keys=SingletonManager.get_singleton(
                    JsonManager
                ).is_key_sortable,
            )

        return True
