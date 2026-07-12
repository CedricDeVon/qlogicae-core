import json
from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import json_manager
from qlogicae_logis.v1.json_text_manager_configurations import JsonTextManagerConfigurations


class JsonTextManager(AbstractManager[JsonTextManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(JsonTextManagerConfigurations())

    def is_valid(self, value: str) -> bool:
        try:
            json.loads(value)
            return True

        except json.JSONDecodeError:
            return False

    def convert_to_object(self, value: str) -> Any:
        return json.loads(value)

    def convert_to_string(self, value: Any) -> str:
        return json.dumps(
            value,
            indent=json_manager.singleton.indent_count,
            ensure_ascii=json_manager.singleton.is_ascii_format_enabled,
        )


singleton = JsonTextManager()
