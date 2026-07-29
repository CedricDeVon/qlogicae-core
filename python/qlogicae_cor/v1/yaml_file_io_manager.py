from pathlib import Path
from typing import Any

import yaml

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.text_encoding_manager import TextEncodingManager
from qlogicae_cor.v1.yaml_file_io_manager_configurations import (
    YamlFileIoManagerConfigurations,
)
from qlogicae_cor.v1.yaml_manager import (
    YamlManager,
)


class YamlFileIoManager(AbstractManager[YamlFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(YamlFileIoManagerConfigurations())

    def read_file(self, file_path: str) -> Any:
        path = Path(file_path)

        output_data: Any = {}
        with path.open(
            mode="r",
            encoding=SingletonManager.get_singleton(
                TextEncodingManager
            ).selected_encoding,
        ) as file:
            output_data = yaml.safe_load(file) or {}

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
            yaml.safe_dump(
                data,
                file,
                sort_keys=SingletonManager.get_singleton(
                    YamlManager,
                ).is_key_sorting_enabled,
                default_flow_style=SingletonManager.get_singleton(
                    YamlManager,
                ).is_default_flow_state_enabled,
                allow_unicode=SingletonManager.get_singleton(
                    YamlManager,
                ).is_unicode_enabled,
                indent=SingletonManager.get_singleton(
                    YamlManager,
                ).indent_count,
            )

        return True

    def format_to_string(self, value: str) -> Any:
        return (
            yaml.dump(
                value,
                sort_keys=SingletonManager.get_singleton(
                    YamlManager,
                ).is_key_sorting_enabled,
                default_flow_style=SingletonManager.get_singleton(
                    YamlManager,
                ).is_default_flow_state_enabled,
                allow_unicode=SingletonManager.get_singleton(
                    YamlManager,
                ).is_unicode_enabled,
                indent=SingletonManager.get_singleton(
                    YamlManager,
                ).indent_count,
            )
            or ""
        )
