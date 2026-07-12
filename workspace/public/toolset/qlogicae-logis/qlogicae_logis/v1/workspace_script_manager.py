from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.workspace_script_manager_configurations import (
    WorkspaceScriptManagerConfigurations,
)


class WorkspaceScriptManager(AbstractManager[WorkspaceScriptManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(WorkspaceScriptManagerConfigurations())


singleton = WorkspaceScriptManager()
