from pathlib import Path

from library import (
    file_io_manager,
    value_cache_manager,
    yaml_file_io_manager,
    json_file_io_manager,
    text_file_io_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceFilesystemManager:
    def __init__(self) -> None:
        self._scope_selections: set[str] = {"private", "public"}

    @property
    def scope_selections(self) -> set[str]:
        return self._scope_selections

    def setup(self) -> bool:
        for current_scope_selection in (
            self.scope_selections or {}
        ):
            for current_configuration_file in (Path(
                    f"{
                        value_cache_manager.singleton.get_one_value(
                            ['current-root-full-path'],
                            output_type=TargetCacheValue.FOLDER_PATH,
                        ) 
                    }/workspace/{current_scope_selection}/configuration"
                ).iterdir() or {}
            ):
                if not current_configuration_file.is_file():
                    continue

                with open(
                    current_configuration_file.resolve(),
                    encoding=file_io_manager.singleton.file_encoding,
                ) as current_file:
                    raw_data = self.read_file(current_file)

                    value_cache_manager.singleton.set_one_value(
                        [
                            f"workspace/{current_scope_selection}/configuration/{current_configuration_file.name}-raw"
                        ],
                        (({} if raw_data is None else raw_data) or {}),
                        output_type=TargetCacheValue.DEFINED,
                    )
                    value_cache_manager.singleton.set_one_value(
                        [
                            f"workspace/{current_scope_selection}/configuration/{current_configuration_file.name}-full-path"
                        ],
                        current_configuration_file.resolve(),
                        output_type=TargetCacheValue.FILE_PATH,
                    )

    def shutdown(self) -> bool:
        return True

    def read_file(self, file: Any) -> Any:
        if yaml_file_io_manager.singleton.is_valid(file):
            return yaml_file_io_manager.singleton.read_file(file)

        elif json_file_io_manager.singleton.is_valid(file):
            return json_file_io_manager.singleton.read_file(file)

        else:
            return text_file_io_manager.singleton.read_file(file)


singleton = WorkspaceFilesystemManager()
