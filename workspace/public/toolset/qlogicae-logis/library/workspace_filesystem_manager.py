from pathlib import Path

from library import (
    yaml_file_io_manager,
    json_file_io_manager,
    text_file_io_manager,
)


class WorkspaceFilesystemManager:
    def __init__(self) -> None:
        self._scope_selections: set[str] = {"private", "public"}

    @property
    def scope_selections(self) -> set[str]:
        return self._scope_selections

    @property
    def root_workspace_filesystem_path(self) -> str:
        return Path(__file__).resolve().parent.parent.parent.parent.parent.parent

    def read_file(self, file: Any) -> Any:
        if yaml_file_io_manager.singleton.is_valid(file):
            return yaml_file_io_manager.singleton.read_file(file)

        elif json_file_io_manager.singleton.is_valid(file):
            return json_file_io_manager.singleton.read_file(file)

        else:
            return text_file_io_manager.singleton.read_file(file)


singleton = WorkspaceFilesystemManager()
