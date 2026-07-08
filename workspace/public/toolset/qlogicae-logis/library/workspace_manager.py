from datetime import UTC
from pathlib import Path
from collections.abc import Callable

from library import (
    log_manager,
    time_manager,
    system_manager,
    macros_manager,
    file_io_manager,
    file_log_manager,
    timestamp_manager,
    console_log_manager,
    value_cache_manager,
    workspace_log_manager,
    time_zone_enum_manager,
    workspace_system_manager,
    workspace_macros_manager,
    workspace_script_manager,
    workspace_filesystem_manager,
    workspace_value_cache_manager,
)
from library.log_options import LogOptions
from library.target_cache_value import TargetCacheValue


class WorkspaceManager:
    def handle(self, callback: Callable[[void], void]) -> bool:
        self.setup()

        callback()

        self.shutdown()

        return True

    def setup(self) -> bool:
        self.setup_timestamp_console_execution_start()
        self.setup_filesystem_paths()
        self.setup_executing_console()
        self.setup_file_data_extraction()
        self.setup_macros_targets()
        self.setup_parsing_macros()
        self.setup_workspace_selections()
        self.setup_clean_scripts()
        self.setup_script_selections()
        self.setup_script_commands()
        self.setup_logs()

        return True

    def setup_script_commands(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["script-command-epilogue"],
            f"For more information, visit: '{
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/tooling/qlogicae-logis/project/configuration/about.yaml-raw",
                        "data",
                        "repository"
                    ],
                    output_type=TargetCacheValue.DEFINED,
                )
            }'",
            output_type=TargetCacheValue.DEFINED,
        )

        return True

    def setup_executing_console(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["original-executing-console-full-path"],
            system_manager.singleton.current_executing_console_filesystem_path,
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        value_cache_manager.singleton.set_one_value(
            ["current-executing-console-full-path"],
            value_cache_manager.singleton.get_one_value(
                ["current-root-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            ),
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        workspace_system_manager.singleton.navigate_to_root()

        return True

    def setup_filesystem_paths(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["current-root-full-path"],
            workspace_filesystem_manager.singleton.root_workspace_filesystem_path,
            output_type=TargetCacheValue.FOLDER_PATH,
        )

        return True

    def setup_file_data_extraction(self) -> bool:
        current_root_full_path = value_cache_manager.singleton.get_one_value(
            ["current-root-full-path"],
            output_type=TargetCacheValue.FOLDER_PATH,
        )
        original_executing_console_full_path = (
            value_cache_manager.singleton.get_one_value(
                ["original-executing-console-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            )
        )
        scope_selecions = workspace_filesystem_manager.singleton.scope_selections or {}
        for current_scope_selection in scope_selecions:
            target_filesystem_paths = (
                Path(
                    f"{current_root_full_path}/workspace/{current_scope_selection}/configuration"
                ).iterdir()
                or {}
            )

            for current_configuration_file in target_filesystem_paths:
                if not current_configuration_file.is_file():
                    continue

                with open(
                    current_configuration_file.resolve(),
                    encoding=file_io_manager.singleton.file_encoding,
                ) as current_file:
                    raw_data = workspace_filesystem_manager.singleton.read_file(
                        current_file
                    )

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

        target_filesystem_paths = (
            Path(
                f"{original_executing_console_full_path}/project/configuration"
            ).iterdir()
            or {}
        )
        for current_configuration_file in target_filesystem_paths:
            if not current_configuration_file.is_file():
                continue

            with open(
                current_configuration_file.resolve(),
                encoding=file_io_manager.singleton.file_encoding,
            ) as current_file:
                raw_data = workspace_filesystem_manager.singleton.read_file(
                    current_file
                )

                value_cache_manager.singleton.set_one_value(
                    [
                        f"workspace/public/tooling/qlogicae-logis/project/configuration/{current_configuration_file.name}-raw"
                    ],
                    (({} if raw_data is None else raw_data) or {}),
                    output_type=TargetCacheValue.DEFINED,
                )
                value_cache_manager.singleton.set_one_value(
                    [
                        f"workspace/public/tooling/qlogicae-logis/project/configuration/{current_configuration_file.name}-full-path"
                    ],
                    current_configuration_file.resolve(),
                    output_type=TargetCacheValue.FILE_PATH,
                )

    def setup_macros_targets(self) -> bool:
        time_manager.singleton.current_time_zone = (
            time_zone_enum_manager.singleton.convert_from_string_to_timezone(
                (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "time",
                            "zone",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or "local"
                )
            )
        )

        value_cache_manager.singleton.set_one_value(
            ["current-date"], time_manager.singleton.current_iso8601_date
        )

        value_cache_manager.singleton.set_one_value(
            ["current-year"], time_manager.singleton.current_year
        )

        return True

    def setup_timestamp_console_execution_start(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["timestamp-console-execution-start"],
            timestamp_manager.singleton.current_standard_timestamp,
        )

        return True

    def setup_timestamp_console_execution_end(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["timestamp-console-execution-end"],
            timestamp_manager.singleton.current_standard_timestamp,
        )

        return True

    def setup_workspace_selections(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["default-workspace-selections"],
            set(
                key
                for key, value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "selection",
                            "default",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                ).items()
            ),
        )

        value_cache_manager.singleton.set_one_value(
            ["project-workspace-selections"],
            set(
                key
                for key, value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "selection",
                            "project",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                ).items()
            ),
        )

        value_cache_manager.singleton.set_one_value(
            ["workspace-selections"],
            set(
                value_cache_manager.singleton.get_one_value(
                    ["default-workspace-selections"],
                    output_type=TargetCacheValue.ANY,
                )
                or {}
            )
            | set(
                value_cache_manager.singleton.get_one_value(
                    ["project-workspace-selections"],
                    output_type=TargetCacheValue.ANY,
                )
                or {}
            ),
        )

        return True

    def setup_clean_scripts(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["clean-include-selections"],
            {
                value
                for value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "script",
                            "clean",
                            "include",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                )
            },
        )

        value_cache_manager.singleton.set_one_value(
            ["clean-exclude-selections"],
            {
                macros_manager.singleton.parse_one(
                    item["name"],
                    (
                        value_cache_manager.singleton.get_one_value(
                            ["workspace-macros"],
                            output_type=TargetCacheValue.ANY,
                        )
                        or {}
                    ),
                )
                for item in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "script",
                            "clean",
                            "exclude",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or []
                )
            },
        )

        return True

    def setup_script_selections(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["script-selections"],
            {
                key
                for key, value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "script",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                ).items()
            },
        )

        return True

    def setup_parsing_macros(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["workspace-macros"],
            macros_manager.singleton.resolve_many(
                {
                    item["name"]: f"{
                        value_cache_manager.singleton.get_one_value(
                            [item['name']],
                            output_type=TargetCacheValue.ANY,
                        )
                    }"
                    for item in (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/private/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "value-cache",
                                "targets",
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    )
                    + (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/public/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "value-cache",
                                "targets",
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    )
                }
                | {
                    item["name"]: f"{item['value']}"
                    for item in (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/private/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "file",
                                "targets",
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    )
                    + (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/public/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "file",
                                "targets",
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    )
                }
            )
            or {},
            output_type=TargetCacheValue.ANY,
        )

        return True

    def setup_logs(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["log-file-targets"],
            {
                macros_manager.singleton.parse_one(
                    item["name"],
                    (
                        value_cache_manager.singleton.get_one_value(
                            ["workspace-macros"],
                            output_type=TargetCacheValue.ANY,
                        )
                        or {}
                    ),
                )
                for item in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "log",
                            "file",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or []
                )
            },
        )

        is_logging_enabled = (
            value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/configuration/workspace.yaml-raw",
                    "data",
                    "log",
                    "is-enabled",
                ],
                output_type=TargetCacheValue.ANY,
            )
            or False
        )
        is_logging_verbose_enabled = (
            value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/configuration/workspace.yaml-raw",
                    "data",
                    "log",
                    "is-verbose-enabled",
                ],
                output_type=TargetCacheValue.ANY,
            )
            or False
        )
        is_logging_override_enabled = (
            value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/configuration/workspace.yaml-raw",
                    "data",
                    "log",
                    "is-override-enabled",
                ],
                output_type=TargetCacheValue.ANY,
            )
            or False
        )
        is_logging_verbose_override_enabled = (
            value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/configuration/workspace.yaml-raw",
                    "data",
                    "log",
                    "is-verbose-override-enabled",
                ],
                output_type=TargetCacheValue.ANY,
            )
            or False
        )

        file_log_manager.singleton.options = LogOptions(
            is_enabled=is_logging_enabled
            if is_logging_override_enabled
            else (
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "log",
                        "file",
                        "is-enabled",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or False
            ),
            is_verbose_enabled=is_logging_verbose_enabled
            if is_logging_verbose_override_enabled
            else (
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "log",
                        "file",
                        "is-verbose-enabled",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or False
            ),
        )

        console_log_manager.singleton.options = LogOptions(
            is_enabled=is_logging_enabled
            if is_logging_override_enabled
            else (
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "log",
                        "console",
                        "is-enabled",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or False
            ),
            is_verbose_enabled=is_logging_verbose_enabled
            if is_logging_verbose_override_enabled
            else (
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "log",
                        "console",
                        "is-verbose-enabled",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or False
            ),
        )

        if (
            is_logging_enabled
            if is_logging_override_enabled
            else (
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "log",
                        "file",
                        "is-enabled",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or False
            )
            or False
        ):
            for full_path in value_cache_manager.singleton.get_one_value(
                ["log-file-targets"]
            ):
                file_log_manager.singleton.add_file_output(full_path)

        return True

    def shutdown(self) -> bool:
        log_manager.singleton.shutdown()

        return True

    def handle_cli_argument_set_invalid(self, cli_arguments: Any) -> bool:
        log_manager.singleton.log_info(
            f"'{cli_arguments}' is not an existing cli option set"
        )

        return True


singleton = WorkspaceManager()
