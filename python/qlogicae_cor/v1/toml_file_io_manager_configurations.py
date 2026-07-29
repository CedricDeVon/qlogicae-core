from qlogicae_cor.v1.abstract_manager_configurations import (
    AbstractManagerConfigurations,
)


class TomlFileIoManagerConfigurations(
    AbstractManagerConfigurations,
):
    def __init__(self) -> None:
        super().__init__()
