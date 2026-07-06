from library import (
    log_manager,
    file_log_manager,
    value_cache_manager,
)
from library.log_options import LogOptions
from library.target_cache_value import TargetCacheValue


class WorkspaceLogManager:
    def __init__(self) -> None:
        self._log_targets = { "file", "console" }

    @property
    def log_targets(self):
        return self._log_targets

    def setup(self) -> bool:
        is_logging_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",                
                "is-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)
        is_logging_verbose_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",                
                "is-verbose-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)
        is_logging_override_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",                
                "is-override-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)
        is_logging_verbose_override_enabled = (value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "log",                
                "is-verbose-override-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        ) or False)

        log_manager.singleton.file_options = LogOptions(
            is_enabled = is_logging_enabled
                if is_logging_override_enabled else (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "log",      
                            "file",
                            "is-enabled",
                        ],
                        output_type=TargetCacheValue.ANY,
                    ) or False
                ),
            is_verbose_enabled = is_logging_verbose_enabled
                if is_logging_verbose_override_enabled else (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "log",      
                            "file",
                            "is-verbose-enabled",
                        ],
                        output_type=TargetCacheValue.ANY,
                    ) or False
                )
        )
        log_manager.singleton.console_options = LogOptions(
            is_enabled = is_logging_enabled
                if is_logging_override_enabled else (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "log",      
                            "console",
                            "is-enabled",
                        ],
                        output_type=TargetCacheValue.ANY,
                    ) or False
                ),
            is_verbose_enabled = is_logging_verbose_enabled
                if is_logging_verbose_override_enabled else (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "log",      
                            "console",
                            "is-verbose-enabled",
                        ],
                        output_type=TargetCacheValue.ANY,
                    ) or False
                )
        )
             
        if (is_logging_enabled if is_logging_override_enabled else (
            value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/configuration/workspace.yaml-raw",
                    "data",
                    "log",      
                    "file",
                    "is-enabled",
                ],
                output_type=TargetCacheValue.ANY,
            ) or False
        ) or False):
            for full_path in value_cache_manager.singleton.get_one_value(
                ["log-file-targets"]
            ):
                file_log_manager.singleton.add_file_output(full_path)

        return True

    def shutdown(self) -> bool:
        log_manager.singleton.shutdown()

        return True


singleton = WorkspaceLogManager()

