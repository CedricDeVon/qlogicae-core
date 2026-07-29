from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.data_file_io_manager_configurations import (
    DataFileIoManagerConfigurations,
)
from qlogicae_cor.v1.file_io_manager import (
    FileIoManager,
)
from qlogicae_cor.v1.json_file_io_manager import (
    JsonFileIoManager,
)
from qlogicae_cor.v1.json_manager import (
    JsonManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.toml_file_io_manager import (
    TomlFileIoManager,
)
from qlogicae_cor.v1.toml_manager import (
    TomlManager,
)
from qlogicae_cor.v1.yaml_file_io_manager import (
    YamlFileIoManager,
)
from qlogicae_cor.v1.yaml_manager import (
    YamlManager,
)


class DataFileIoManager(AbstractManager[DataFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(DataFileIoManagerConfigurations())

    def e(self, file_path: str) -> Any:
        if SingletonManager.get_singleton(
            YamlManager
        ).is_valid(file_path):
            return SingletonManager.get_singleton(
                YamlFileIoManager
            ).read_file(file_path)

        elif SingletonManager.get_singleton(
            JsonManager
        ).is_valid(file_path):
            return SingletonManager.get_singleton(
                JsonFileIoManager
            ).read_file(file_path)

        elif SingletonManager.get_singleton(
            TomlManager
        ).is_valid(file_path):
            return SingletonManager.get_singleton(
                TomlFileIoManager
            ).read_file(file_path)

        else:
            return SingletonManager.get_singleton(
                FileIoManager
            ).read_file(file_path)


    def write_file(self, file_path: str, data: Any) -> Any:
        if SingletonManager.get_singleton(
            YamlManager
        ).is_valid(file_path):
            return SingletonManager.get_singleton(
                YamlFileIoManager
            ).write_file(file_path, data)

        elif SingletonManager.get_singleton(
            JsonManager
        ).is_valid(file_path):
            return SingletonManager.get_singleton(
                JsonFileIoManager
            ).write_file(file_path, data)

        elif SingletonManager.get_singleton(
            TomlManager
        ).is_valid(file_path):
            return SingletonManager.get_singleton(
                TomlFileIoManager
            ).write_file(file_path, data)

        else:
            return SingletonManager.get_singleton(
                FileIoManager
            ).write_file(file_path, data)


