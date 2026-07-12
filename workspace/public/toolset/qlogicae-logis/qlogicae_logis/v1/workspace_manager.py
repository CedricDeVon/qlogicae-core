from collections.abc import Callable
from pathlib import Path
from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import (
    console_log_manager,
    file_io_manager,
    file_log_manager,
    filesystem_manager,
    log_manager,
    macros_manager,
    system_manager,
    time_manager,
    time_zone_enum_manager,
    timestamp_manager,
    value_cache_manager,
    workspace_filesystem_manager,
    workspace_system_manager,
)
from qlogicae_logis.v1.filesystem_manager import (
    FileEntityFileSystemTreeSetupOptions,
    FolderEntityFileSystemTreeSetupOptions,
)
from qlogicae_logis.v1.log_options import LogOptions
from qlogicae_logis.v1.target_cache_value import TargetCacheValue
from qlogicae_logis.v1.workspace_manager_configurations import WorkspaceManagerConfigurations


class WorkspaceManager(AbstractManager[WorkspaceManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(WorkspaceManagerConfigurations())

    def debug_value_cache(self) -> bool:
        self.setup()

        self.handle_toolset_configuration_file_data_extraction_setup()
        self.handle_toolset_configuration_data_setup()
        self.handle_workspace_selections_setup()
        self.handle_cutsom_script_selections_setup()
        self.handle_clean_scripts_setup()

        value_cache_manager.singleton.display_all_items()

        return True

    def handle(self, callback: Callable[[None], None]) -> bool:
        self.setup()

        callback()

        self.shutdown()

        return True

    def setup(self) -> bool:
        self.handle_timestamp_console_execution_start_setup()
        self.handle_executing_console_filesystem_paths_setup()
        self.handle_root_filesystem_replenishment_setup()
        self.handle_workspace_configuration_file_data_extraction_setup()
        self.handle_value_cache_macros_setup()
        self.handle_macros_parsing_setup()
        self.handle_logs_setup()

        return True

    def handle_root_filesystem_replenishment_setup(self) -> bool:
        current_root_full_path = value_cache_manager.singleton.get_one_value(
            ["current-root-full-path"],
            output_type=TargetCacheValue.FOLDER_PATH,
        )

        gitignore_file = FileEntityFileSystemTreeSetupOptions(
            name=".gitignore", content="*"
        )

        configuration_workspace_file = FileEntityFileSystemTreeSetupOptions(
            name="workspace.yaml", content="data:\n\nmetadata:\n"
        )

        configuration_sub_tree = FolderEntityFileSystemTreeSetupOptions(
            name="configuration",
            entities=[configuration_workspace_file],
        )

        target_selection_filesystem_sub_tree = FolderEntityFileSystemTreeSetupOptions(
            name="filesystem",
            entities=[],
        )

        target_sub_tree = FolderEntityFileSystemTreeSetupOptions(
            name="target",
            entities=[
                FolderEntityFileSystemTreeSetupOptions(
                    name="all",
                    entities=[target_selection_filesystem_sub_tree],
                ),
                FolderEntityFileSystemTreeSetupOptions(
                    name="project",
                    entities=[
                        target_selection_filesystem_sub_tree,
                        FolderEntityFileSystemTreeSetupOptions(
                            name="selection",
                            entities=[],
                        ),
                    ],
                ),
                FolderEntityFileSystemTreeSetupOptions(
                    name="root",
                    entities=[
                        target_selection_filesystem_sub_tree,
                    ],
                ),
            ],
        )

        temporary_sub_tree = FolderEntityFileSystemTreeSetupOptions(
            name="temporary",
            entities=[
                FolderEntityFileSystemTreeSetupOptions(
                    name="log",
                    entities=[],
                ),
                FolderEntityFileSystemTreeSetupOptions(
                    name="intermediate",
                    entities=[],
                ),
            ],
        )

        root_filesystem_tree = FolderEntityFileSystemTreeSetupOptions(
            entities=[
                FolderEntityFileSystemTreeSetupOptions(
                    name="workspace",
                    entities=[
                        FolderEntityFileSystemTreeSetupOptions(
                            name="private",
                            entities=[
                                configuration_sub_tree,
                                target_sub_tree,
                                temporary_sub_tree,
                                gitignore_file,
                            ],
                        ),
                        FolderEntityFileSystemTreeSetupOptions(
                            name="public",
                            entities=[configuration_sub_tree, target_sub_tree],
                        ),
                    ],
                ),
                FolderEntityFileSystemTreeSetupOptions(
                    name="project",
                    entities=[],
                ),
                FolderEntityFileSystemTreeSetupOptions(
                    name="selection",
                    entities=[],
                ),
            ]
        )

        filesystem_manager.singleton.setup_filesystem_tree(
            current_root_full_path, root_filesystem_tree
        )

    def handle_timestamp_console_execution_start_setup(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["timestamp-console-execution-start"],
            timestamp_manager.singleton.current_standard_timestamp,
        )

        return True

    def handle_timestamp_console_execution_end_setup(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["timestamp-console-execution-end"],
            timestamp_manager.singleton.current_standard_timestamp,
        )

        return True

    def handle_executing_console_filesystem_paths_setup(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["current-root-full-path"],
            workspace_filesystem_manager.singleton.root_workspace_filesystem_path,
            output_type=TargetCacheValue.FOLDER_PATH,
        )
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

    def handle_workspace_configuration_file_data_extraction_setup(self) -> bool:
        current_root_full_path = value_cache_manager.singleton.get_one_value(
            ["current-root-full-path"],
            output_type=TargetCacheValue.FOLDER_PATH,
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

                with Path.open(
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

    def handle_toolset_configuration_file_data_extraction_setup(self) -> bool:
        original_executing_console_full_path = (
            value_cache_manager.singleton.get_one_value(
                ["original-executing-console-full-path"],
                output_type=TargetCacheValue.FOLDER_PATH,
            )
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

            with Path.open(
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

    def handle_toolset_configuration_data_setup(self) -> bool:
        toolset_about_raw_data = (
            value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/tooling/qlogicae-logis/project/configuration/about.json-raw",
                    "data",
                ],
                output_type=TargetCacheValue.DEFINED,
            )
            or {}
        )

        toolset_about = {}
        toolset_about_table = {}
        for key, item in toolset_about_raw_data.items():
            if "name" not in item:
                continue

            if "value" not in item:
                toolset_about[key] = item
                toolset_about[key]["value"] = "None"

            else:
                toolset_about[key] = item

                if "is-tabular" not in item or item["is-tabular"]:
                    toolset_about_table[key] = item

        value_cache_manager.singleton.set_one_value(
            ["toolset-about"],
            toolset_about,
            output_type=TargetCacheValue.DEFINED,
        )
        value_cache_manager.singleton.set_one_value(
            ["toolset-about-table"],
            toolset_about_table,
            output_type=TargetCacheValue.DEFINED,
        )

        return True

    def handle_value_cache_macros_setup(self) -> bool:
        time_zone = (
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

        time_manager.singleton.current_time_zone = (
            time_zone_enum_manager.singleton.convert_from_string_to_timezone(time_zone)
        )

        value_cache_manager.singleton.set_one_value(
            ["current-date"], time_manager.singleton.current_iso8601_date
        )

        value_cache_manager.singleton.set_one_value(
            ["current-year"], time_manager.singleton.current_year
        )

        return True

    def handle_workspace_selections_setup(self) -> bool:
        default_workspace_selections = (
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

        project_workspace_selections = (
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

        default_workspace_selection_set = set(
            key for key, value in default_workspace_selections
        )
        project_workspace_selection_set = set(
            key for key, value in project_workspace_selections
        )

        value_cache_manager.singleton.set_one_value(
            ["default-workspace-selections"], default_workspace_selection_set
        )

        value_cache_manager.singleton.set_one_value(
            ["project-workspace-selections"], project_workspace_selection_set
        )

        value_cache_manager.singleton.set_one_value(
            ["workspace-selections"],
            default_workspace_selection_set | project_workspace_selection_set,
        )

        return True

    def handle_clean_scripts_setup(self) -> bool:
        workspace_macros = (
            value_cache_manager.singleton.get_one_value(
                ["workspace-macros"],
                output_type=TargetCacheValue.ANY,
            )
            or {}
        )

        clean_include_targets = (
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

        clean_exclude_targets = (
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

        value_cache_manager.singleton.set_one_value(
            ["clean-include-selections"], {value for value in clean_include_targets}
        )

        value_cache_manager.singleton.set_one_value(
            ["clean-exclude-selections"],
            {
                macros_manager.singleton.parse_one(item["name"], workspace_macros)
                for item in clean_exclude_targets
            },
        )

        return True

    def handle_cutsom_script_selections_setup(self) -> bool:
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

    def handle_macros_parsing_setup(self) -> bool:
        private_value_cache_macros = (
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
        public_value_cache_macros = (
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
        private_file_macros = (
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
        public_file_macros = (
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

        resolved_macros = (
            macros_manager.singleton.resolve_many(
                {
                    item["name"]: f"{
                        value_cache_manager.singleton.get_one_value(
                            [item['name']],
                            output_type=TargetCacheValue.ANY,
                        )
                    }"
                    for item in private_value_cache_macros + public_value_cache_macros
                }
                | {
                    item["name"]: f"{item['value']}"
                    for item in private_file_macros + public_file_macros
                }
            )
            or {}
        )

        value_cache_manager.singleton.set_one_value(
            ["workspace-macros"],
            resolved_macros,
            output_type=TargetCacheValue.ANY,
        )

        return True

    def handle_logs_setup(self) -> bool:
        workspace_macros = (
            value_cache_manager.singleton.get_one_value(
                ["workspace-macros"],
                output_type=TargetCacheValue.ANY,
            )
            or {}
        )

        log_file_targets = (
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

        value_cache_manager.singleton.set_one_value(
            ["log-file-targets"],
            {
                macros_manager.singleton.parse_one(
                    item["name"],
                    workspace_macros,
                )
                for item in log_file_targets
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
