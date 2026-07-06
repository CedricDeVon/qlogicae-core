from library import (
    system_manager,
    filesystem_manager,
    value_cache_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceSystemManager:
    def setup(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["current-root-full-path"],
            filesystem_manager.singleton.get_root_workspace_folder(),
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        value_cache_manager.singleton.set_one_value(
            ["original-console-executed-full-path"],
            filesystem_manager.singleton.get_cli_folder(),
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        value_cache_manager.singleton.set_one_value(
            ["current-console-executed-full-path"],
            value_cache_manager.singleton.get_one_value(
                ["current-root-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            ),
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        self.navigate_console_executed_to_root()

        return True

    def navigate_console_executed_to_root(self) -> bool:
        self.navigate_console_executed(
            value_cache_manager.singleton.get_one_value(
                ["current-root-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            )
        )

        return True

    def navigate_console_executed(self, target: str) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["previous-console-executed-full-path"],
            value_cache_manager.singleton.get_one_value(
                ["current-console-executed-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            ),
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        value_cache_manager.singleton.set_one_value(
            ["current-console-executed-full-path"],
            target,
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        system_manager.singleton.change_cli_filesystem_path(
            target
        )

        return True

    def shutdown(self) -> bool:
        return True


singleton = WorkspaceSystemManager()
