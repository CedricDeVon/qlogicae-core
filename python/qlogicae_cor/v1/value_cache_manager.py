from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.filesystem_manager import (
    FilesystemManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.target_cache_value import (
    TargetCacheValue,
)
from qlogicae_cor.v1.value_cache_manager_configurations import (
    ValueCacheManagerConfigurations,
)
from qlogicae_cor.v1.value_cache_storage_manager import ValueCacheStorageManager


class ValueCacheManager(AbstractManager[ValueCacheManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(ValueCacheManagerConfigurations())

    def is_key_found(self, keys: list[str]) -> bool:
        return SingletonManager.get_singleton(
            ValueCacheStorageManager,
        ).is_key_found(keys)

    def get_one_value(
        self,
        keys: list[str],
        output_type: TargetCacheValue = TargetCacheValue.DEFINED,
    ) -> Any:
        value = SingletonManager.get_singleton(
            ValueCacheStorageManager,
        ).get_one_value(keys)
        self.throw_if_value_is_explicitly_invalid(value, output_type)

        return value

    def set_one_value(
        self,
        keys: list[str],
        value: Any,
        output_type: TargetCacheValue = TargetCacheValue.DEFINED,
    ) -> bool:
        self.throw_if_value_is_explicitly_invalid(value, output_type)

        return SingletonManager.get_singleton(
            ValueCacheStorageManager,
        ).set_one_value(keys, value)

    def remove_one_value(self, keys: list[str]) -> bool:
        self.throw_if_key_not_found(keys)

        return SingletonManager.get_singleton(
            ValueCacheStorageManager,
        ).remove_one_value(keys)

    def clear_all_values(self) -> bool:
        return SingletonManager.get_singleton(
            ValueCacheStorageManager,
        ).clear_all_values()

    def display_all_items(self) -> bool:
        return SingletonManager.get_singleton(
            ValueCacheStorageManager,
        ).display_all_items()

    def throw_if_value_is_explicitly_invalid(
        self,
        value: Any,
        output_type: TargetCacheValue = TargetCacheValue.DEFINED,
    ) -> bool:
        match output_type:
            case TargetCacheValue.FILESYSTEM_PATH:
                SingletonManager.get_singleton(
                    FilesystemManager,
                ).throw_if_filesystem_path_invalid(
                    value
                )

                return True

            case TargetCacheValue.FILE_PATH:
                SingletonManager.get_singleton(
                    FilesystemManager,
                ).throw_if_file_path_invalid(value)

                return True

            case TargetCacheValue.FOLDER_PATH:
                SingletonManager.get_singleton(
                    FilesystemManager,
                ).throw_if_folder_path_invalid(value)

                return True

            case TargetCacheValue.DEFINED:
                self.throw_if_undefined(value)

                return True

            case _:
                return False

        return False

    def throw_if_key_not_found(self, keys: list[str]) -> bool:
        if not SingletonManager.get_singleton(
            ValueCacheStorageManager,
        ).is_key_found(keys):
            raise KeyError(f"key path '{keys}' does not exist")

        return False

    def throw_if_undefined(self, value: Any) -> bool:
        if value is None:
            raise KeyError("value is not defined")

        return False
