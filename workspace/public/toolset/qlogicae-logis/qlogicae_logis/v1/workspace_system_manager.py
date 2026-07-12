from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import (
    system_manager,
    value_cache_manager,
)
from qlogicae_logis.v1.target_cache_value import TargetCacheValue
from qlogicae_logis.v1.workspace_system_manager_configurations import (
    WorkspaceSystemManagerConfigurations,
)


class WorkspaceSystemManager(AbstractManager[WorkspaceSystemManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(WorkspaceSystemManagerConfigurations())

    def navigate_to_root(self) -> bool:
        self.navigate(
            value_cache_manager.singleton.get_one_value(
                ["current-root-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            )
        )

        return True

    def navigate(self, target: str) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["previous-executing-console-full-path"],
            value_cache_manager.singleton.get_one_value(
                ["current-executing-console-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            ),
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        value_cache_manager.singleton.set_one_value(
            ["current-executing-console-full-path"],
            target,
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        system_manager.singleton.current_executing_console_filesystem_path = target

        return True


singleton = WorkspaceSystemManager()
