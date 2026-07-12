from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.yaml_manager_configurations import YamlManagerConfigurations


class YamlManager(AbstractManager[YamlManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(YamlManagerConfigurations())

        self._valid_suffixes: set[str] = {".yaml", ".yml"}
        self._is_key_sorting_enabled: bool = False
        self._is_default_flow_state_enabled: bool = False
        self._is_unicode_enabled: bool = True
        self._indent_count: int = 4

    @property
    def valid_suffixes(self) -> set[str]:
        return self._valid_suffixes

    def is_valid_file_extensions(self, file: Any) -> bool:
        return any(suffix in self._valid_suffixes for suffix in self._valid_suffixes)

    @property
    def is_key_sorting_enabled(self) -> bool:
        return self._is_key_sorting_enabled

    @is_key_sorting_enabled.setter
    def is_key_sorting_enabled(self, value: bool) -> bool:
        self._is_key_sorting_enabled = value

        return True

    @property
    def is_default_flow_state_enabled(self) -> bool:
        return self._is_default_flow_state_enabled

    @is_default_flow_state_enabled.setter
    def is_default_flow_state_enabled(self, value: bool) -> bool:
        self._is_default_flow_state_enabled = value

        return True

    @property
    def is_unicode_enabled(self) -> bool:
        return self._is_unicode_enabled

    @is_unicode_enabled.setter
    def is_unicode_enabled(self, value: bool) -> bool:
        self._is_unicode_enabled = value

        return True

    @property
    def indent_count(self) -> int:
        return self._indent_count

    @indent_count.setter
    def indent_count(self, value: int) -> bool:
        if value < 0:
            raise Exception("indent_count must be non-negative.")

        self._indent_count = value

        return True


singleton = YamlManager()
