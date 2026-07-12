from pathlib import Path
from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import (
    json_file_io_manager,
    json_manager,
    text_file_io_manager,
    yaml_file_io_manager,
    yaml_manager,
)
from qlogicae_logis.v1.workspace_filesystem_manager_configurations import (
    WorkspaceFilesystemManagerConfigurations,
)


class WorkspaceFilesystemManager(
    AbstractManager[WorkspaceFilesystemManagerConfigurations]
):
    def __init__(self) -> None:
        super().__init__(WorkspaceFilesystemManagerConfigurations())

        self._scope_selections: set[str] = {"private", "public"}

    @property
    def scope_selections(self) -> set[str]:
        return self._scope_selections

    @property
    def root_workspace_filesystem_path(self) -> str:
        return Path(__file__).resolve().parent.parent.parent.parent.parent.parent.parent

    def read_file(self, file: Any) -> Any:
        if yaml_manager.singleton.is_valid_file_extensions(file):
            return yaml_file_io_manager.singleton.read_file(file)

        elif json_manager.singleton.is_valid_file_extensions(file):
            return json_file_io_manager.singleton.read_file(file)

        else:
            return text_file_io_manager.singleton.read_file(file)


singleton = WorkspaceFilesystemManager()
