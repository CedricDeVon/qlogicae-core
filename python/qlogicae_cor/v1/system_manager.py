import os
import platform
from pathlib import Path

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.system_manager_configurations import (
    SystemManagerConfigurations,
)


class SystemManager(AbstractManager[SystemManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(SystemManagerConfigurations())

    @property
    def current_executing_script_filesystem_path(
        self,
    ) -> str:
        return f"{Path(__file__).resolve()}"

    @property
    def current_executing_console_filesystem_path(
        self,
    ) -> str:
        return f"{Path.cwd().resolve()}"

    @current_executing_console_filesystem_path.setter
    def current_executing_console_filesystem_path(
        self,
        filesystem_path: str,
    ) -> None:
        path = Path(filesystem_path).expanduser().resolve()

        if not path.exists():
            raise ValueError(
                f"directory '{path}' does not exist",
            )

        if not path.is_dir():
            raise ValueError(
                f"'{path}' is not a directory",
            )

        os.chdir(path)

    @property
    def operating_system_name(self) -> str:
        return platform.system()

    @property
    def operating_system_architecture(
        self,
    ) -> str:
        return platform.machine()

