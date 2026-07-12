from typing import Any

import yaml
from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import yaml_manager
from qlogicae_logis.v1.yaml_file_io_manager_configurations import (
    YamlFileIoManagerConfigurations,
)


class YamlFileIoManager(AbstractManager[YamlFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(YamlFileIoManagerConfigurations())

    def read_file(self, file: Any) -> Any:
        return yaml.safe_load(file) or {}

    def write_file(self, file: Any, data: Any) -> bool:
        yaml.safe_dump(
            data,
            file,
            sort_keys=yaml_manager.singleton.is_key_sorting_enabled,
            default_flow_style=yaml_manager.singleton.is_default_flow_state_enabled,
            allow_unicode=yaml_manager.singleton.is_unicode_enabled,
            indent=yaml_manager.singleton.indent_count,
        )

        return True

    def format_to_string(self, value: str) -> Any:
        return (
            yaml.dump(
                value,
                sort_keys=yaml_manager.singleton.is_key_sorting_enabled,
                default_flow_style=yaml_manager.singleton.is_default_flow_state_enabled,
                allow_unicode=yaml_manager.singleton.is_unicode_enabled,
                indent=yaml_manager.singleton.indent_count,
            )
            or ""
        )


singleton = YamlFileIoManager()
