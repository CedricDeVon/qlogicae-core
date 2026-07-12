from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.workspace_log_manager_configurations import (
    WorkspaceLogManagerConfigurations,
)


class WorkspaceLogManager(AbstractManager[WorkspaceLogManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(WorkspaceLogManagerConfigurations())

        self._log_targets = {"file", "console"}

    @property
    def log_targets(self):
        return self._log_targets


singleton = WorkspaceLogManager()
