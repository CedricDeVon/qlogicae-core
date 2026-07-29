import json
from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.json_manager import (
    JsonManager,
)
from qlogicae_cor.v1.json_text_manager_configurations import (
    JsonTextManagerConfigurations,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)


class JsonTextManager(AbstractManager[JsonTextManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(JsonTextManagerConfigurations())

    def is_valid(self, value: str) -> bool:
        json.loads(value)
        return True

    def convert_to_object(self, value: str) -> Any:
        return json.loads(value)

    def convert_to_string(self, value: Any) -> str:
        return json.dumps(
            value,
            indent=SingletonManager.get_singleton(
                JsonManager
            ).indent_count,
            ensure_ascii=SingletonManager.get_singleton(
                JsonManager
            ).is_ascii_format_enabled,
        )
