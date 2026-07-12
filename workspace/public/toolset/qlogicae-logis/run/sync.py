import argparse
from pathlib import Path

from qlogicae_logis.v1 import (
    file_io_manager,
    file_log_manager,
    filesystem_manager,
    macros_manager,
    value_cache_manager,
    workspace_filesystem_manager,
    workspace_manager,
)
from qlogicae_logis.v1.target_cache_value import TargetCacheValue


def handle_manager_callback():
    workspace_manager.singleton.handle_workspace_selections_setup()

    workspace_selections = (
        value_cache_manager.singleton.get_one_value(
            ["workspace-selections"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    is_enabled = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "selection",
                "is-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or False
    )

    project_workspace_selections = (
        value_cache_manager.singleton.get_one_value(
            ["project-workspace-selections"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    cli_parser = argparse.ArgumentParser(
        description="'run.sync' command",
    )
    cli_parser.add_argument(
        "-t",
        "--target",
        help="workspace target",
        dest="target",
        default="all",
        choices=workspace_selections,
    )
    cli_arguments = cli_parser.parse_args()

    if not is_enabled:
        file_log_manager.singleton.log_warning(
            "'run.sync' - setup execution is disabled"
        )

        return False

    if cli_arguments.target == "all":
        handle_target_root()
        handle_target_project()

    elif cli_arguments.target == "root":
        handle_target_root()

    elif cli_arguments.target == "project":
        handle_target_project()

    elif cli_arguments.target in project_workspace_selections:
        handle_target_project_selection(cli_arguments.target)

    else:
        workspace_manager.singleton.handle_cli_argument_set_invalid(cli_arguments)

    return True


def handle_target_root():
    file_log_manager.singleton.log_info("'run.sync' - 'root' setup execution start")

    current_root_full_path = value_cache_manager.singleton.get_one_value(
        ["current-root-full-path"],
        output_type=TargetCacheValue.FOLDER_PATH,
    )

    selections_default_targets_root_full_path = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "selection",
                "default",
                "targets",
                "root",
                "full-path",
            ],
            output_type=TargetCacheValue.DEFINED,
        )
        or []
    )

    workspace_macros = (
        value_cache_manager.singleton.get_one_value(
            ["workspace-macros"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    parsed_filesystem_path = macros_manager.singleton.parse_one(
        selections_default_targets_root_full_path,
        workspace_macros,
    )

    filesystem_manager.singleton.clean_filesystem_path(
        f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/root"
    )

    for current_scope_name in workspace_filesystem_manager.singleton.scope_selections:
        filesystem_manager.singleton.copy_filesystem_path(
            f"{current_root_full_path}/workspace/{current_scope_name}/target/all/filesystem",
            f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/root",
        )
        filesystem_manager.singleton.copy_filesystem_path(
            f"{current_root_full_path}/workspace/{current_scope_name}/target/root/filesystem",
            f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/root",
        )

    handle_filesystem_parsing(
        f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/root"
    )
    filesystem_manager.singleton.copy_filesystem_path(
        f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/root",
        parsed_filesystem_path,
    )
    file_log_manager.singleton.log_info("'run.sync' - 'root' setup execution complete")

    return True


def handle_filesystem_parsing(
    filesystem_path,
):
    workspace_macros = (
        value_cache_manager.singleton.get_one_value(
            ["workspace-macros"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    root = Path(filesystem_path)

    for current_root, directories, files in root.walk(
        top_down=False,
    ):
        current_root = Path(current_root)

        for file_name in files:
            current_path = current_root / file_name

            try:
                file_data = current_path.read_text(
                    encoding=file_io_manager.singleton.file_encoding,
                )
            except UnicodeDecodeError:
                continue

            parsed_file_data = macros_manager.singleton.parse_one(
                file_data,
                workspace_macros,
            )

            current_path.write_text(
                parsed_file_data,
                encoding=file_io_manager.singleton.file_encoding,
            )

            parsed_name = macros_manager.singleton.parse_one(
                current_path.name,
                workspace_macros,
            )

            if parsed_name != current_path.name:
                current_path.rename(
                    current_path.with_name(
                        parsed_name,
                    )
                )

        for directory_name in directories:
            current_path = current_root / directory_name

            parsed_name = macros_manager.singleton.parse_one(
                current_path.name,
                workspace_macros,
            )

            if parsed_name != current_path.name:
                current_path.rename(
                    current_path.with_name(
                        parsed_name,
                    )
                )

    return True


def handle_target_project():
    file_log_manager.singleton.log_info("'run.sync' - 'project' setup execution start")

    project_workspace_selections = (
        value_cache_manager.singleton.get_one_value(
            ["project-workspace-selections"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    for project_name in project_workspace_selections:
        handle_target_project_selection(project_name)

    file_log_manager.singleton.log_info(
        "'run.sync' - 'project' setup execution complete"
    )

    return True


def handle_target_project_selection(project_name):
    file_log_manager.singleton.log_info(
        f"'run.sync' - '{project_name}' setup execution start"
    )

    current_root_full_path = value_cache_manager.singleton.get_one_value(
        ["current-root-full-path"],
        output_type=TargetCacheValue.FOLDER_PATH,
    )

    selection_project_target_full_paths = value_cache_manager.singleton.get_one_value(
        [
            "workspace/public/configuration/workspace.yaml-raw",
            "data",
            "selection",
            "project",
            "targets",
            project_name,
            "full-path",
        ],
        output_type=TargetCacheValue.DEFINED,
    )

    workspace_macros = (
        value_cache_manager.singleton.get_one_value(
            ["workspace-macros"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    parsed_filesystem_path = macros_manager.singleton.parse_one(
        selection_project_target_full_paths,
        workspace_macros,
    )

    filesystem_manager.singleton.clean_filesystem_path(
        f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/{project_name}"
    )

    for current_scope_name in workspace_filesystem_manager.singleton.scope_selections:
        filesystem_manager.singleton.copy_filesystem_path(
            f"{current_root_full_path}/workspace/{current_scope_name}/target/all/filesystem",
            f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/{project_name}",
        )
        filesystem_manager.singleton.copy_filesystem_path(
            f"{current_root_full_path}/workspace/{current_scope_name}/target/project/filesystem",
            f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/{project_name}",
        )
        filesystem_manager.singleton.copy_filesystem_path(
            f"{current_root_full_path}/workspace/{
                current_scope_name
            }/target/project/selection/{project_name}/filesystem",
            f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/{project_name}",
        )

    handle_filesystem_parsing(
        f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/{project_name}"
    )
    filesystem_manager.singleton.copy_filesystem_path(
        f"{current_root_full_path}/workspace/private/temporary/intermediate/filesystem/{project_name}",
        parsed_filesystem_path,
    )

    file_log_manager.singleton.log_info(
        f"'run.sync' - '{project_name}' setup execution complete"
    )

    return True


workspace_manager.singleton.handle(handle_manager_callback)
