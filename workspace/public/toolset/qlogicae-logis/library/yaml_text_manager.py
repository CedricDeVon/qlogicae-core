import yaml
from typing import Any

from library import yaml_manager


class YamlTextManager:
    def is_valid(self, value: str) -> bool:
        try:
            yaml.safe_load(
                value
            )

            return True

        except yaml.YAMLError:
            return False

    def convert_to_object(self, value: str) -> Any:
        return yaml.safe_load(
            value
        )

    def convert_to_string(self, value: Any) -> str:
        return yaml.safe_dump(
            value,
            sort_keys=yaml_manager.singleton.is_key_sorting_enabled,
            default_flow_style=yaml_manager.singleton.is_default_flow_state_enabled,
            allow_unicode=yaml_manager.singleton.is_unicode_enabled,
            indent=yaml_manager.singleton.indent_count,
        )


singleton = YamlTextManager()
