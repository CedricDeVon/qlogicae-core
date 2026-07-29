from typing import Any

import yaml

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.yaml_manager import YamlManager
from qlogicae_cor.v1.yaml_text_manager_configurations import (
    YamlTextManagerConfigurations,
)


class YamlTextManager(AbstractManager[YamlTextManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(YamlTextManagerConfigurations())

    def is_valid(self, value: str) -> bool:
        yaml.safe_load(value)

        return True

    def convert_to_object(self, value: str) -> Any:
        return yaml.safe_load(value)

    def convert_to_string(self, value: Any) -> str:
        return yaml.safe_dump(
            value,
            sort_keys=SingletonManager.get_singleton(
                YamlManager
            ).is_key_sorting_enabled,
            default_flow_style=SingletonManager.get_singleton(
                YamlManager
            ).is_default_flow_state_enabled,
            allow_unicode=SingletonManager.get_singleton(
                YamlManager
            ).is_unicode_enabled,
            indent=SingletonManager.get_singleton(
                YamlManager
            ).indent_count,
        )
