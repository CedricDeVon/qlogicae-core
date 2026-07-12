import argparse

from qlogicae_logis.v1 import (
    file_log_manager,
    filesystem_manager,
    log_manager,
    macros_manager,
    value_cache_manager,
    workspace_manager,
)
from qlogicae_logis.v1.target_cache_value import TargetCacheValue


def handler_manager_callback():
    workspace_manager.singleton.handle_workspace_selections_setup()
    workspace_manager.singleton.handle_clean_scripts_setup()

    target_selections = (
        value_cache_manager.singleton.get_one_value(
            ["clean-include-selections"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    cli_parser = argparse.ArgumentParser(
        description="'run.clean' command",
    )
    cli_parser.add_argument(
        "-t",
        "--target",
        help="combination target",
        dest="target",
        choices=target_selections,
    )
    cli_parser.add_argument(
        "-dt",
        "--display-target",
        dest="display_target",
        help="displays target filesystem paths",
        action=argparse.BooleanOptionalAction,
        default=False,
    )
    cli_arguments = cli_parser.parse_args()

    is_enabled = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "script",
                "clean",
                "is-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or False
    )

    if not is_enabled:
        file_log_manager.singleton.log_warning(
            "'run.clean' - cleaning execution is disabled"
        )

        return False

    clean_include_targets = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "script",
                "clean",
                "include",
                "targets",
                cli_arguments.target,
            ],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    workspace_macros = (
        value_cache_manager.singleton.get_one_value(
            ["workspace-macros"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    clean_exclude_selections = (
        value_cache_manager.singleton.get_one_value(
            ["clean-exclude-selections"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    for current_item in clean_include_targets:
        parsed_include_path = macros_manager.singleton.parse_one(
            current_item["name"],
            workspace_macros,
        )

        file_log_manager.singleton.log_info(
            f"'run.clean' - '{parsed_include_path}' cleaning execution start"
        )

        if parsed_include_path in clean_exclude_selections:
            file_log_manager.singleton.log_warning(
                f"'run.clean' - '{parsed_include_path}' cleaning execution ignored"
            )
            continue

        if cli_arguments.display_target:
            log_manager.singleton.log_info(parsed_include_path)
            continue

        filesystem_manager.singleton.clean_filesystem_path(parsed_include_path)

    file_log_manager.singleton.log_info(
        f"'run.clean' - '{parsed_include_path}' cleaning execution complete"
    )

    return True


workspace_manager.singleton.handle(handler_manager_callback)
