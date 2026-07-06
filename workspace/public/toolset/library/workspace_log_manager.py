from library import (
    log_manager,
    file_log_manager,
    value_cache_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceLogManager:
    def setup(self) -> bool:
        is_override_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",                
                "is-override-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)
        is_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",                
                "is-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)
        is_file_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",      
                "file",
                "is-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)
        is_console_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",      
                "console",
                "is-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)
        file_targets = (
            item["name"]
            for item in (value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/configuration/workspace.yaml-raw",
                    "data",
                    "log",      
                    "file",
                    "targets",
                ],
                output_type=TargetCacheValue.ANY,
            ) or {})
        )

        for full_path in value_cache_manager.singleton.get_one_value(
            ["log-targets"]
        ):
            file_log_manager.singleton.add_file_output(full_path)

        return True

    def shutdown(self) -> bool:
        log_manager.singleton.shutdown()

        return True


singleton = WorkspaceLogManager()
