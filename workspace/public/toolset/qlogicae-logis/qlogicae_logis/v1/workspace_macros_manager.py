from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.workspace_macros_manager_configurations import (
    WorkspaceMacrosManagerConfigurations,
)


class WorkspaceMacrosManager(AbstractManager[WorkspaceMacrosManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(WorkspaceMacrosManagerConfigurations())

    @property
    def current_root_full_path(self) -> str:
        return "${{ current-root-full-path }}"


singleton = WorkspaceMacrosManager()
