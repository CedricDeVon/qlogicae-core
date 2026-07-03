import argparse

from library import (
    log_manager,
    macros_manager,
    workspace_manager,
    filesystem_manager,
    value_cache_manager,
)
from library.target_cache_value import TargetCacheValue


def handler_manager_callback():
    cli_parser = argparse.ArgumentParser(
        description="'filesystem.clean' command",
        epilog="...",
    )
    cli_parser.add_argument(
        "-t",
        "--target",
        help="combination target",
        dest="target",
        choices=(
            value_cache_manager.singleton.get_one_value(
                ["clean-include-selections"],
                output_type=TargetCacheValue.DEFINED,
            )
            or {}
        ),
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

    for include_path in (
        value_cache_manager.singleton.get_one_value(
            [
                f"workspace/public/configuration/workspace.yaml-raw",
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
    ):
        parsed_include_path = macros_manager.singleton.parse_one(
            include_path,
            (
                value_cache_manager.singleton.get_one_value(
                    ["workspace-macros"],
                    output_type=TargetCacheValue.DEFINED,
                )
                or {}
            ),
        )

        if parsed_include_path in (
            value_cache_manager.singleton.get_one_value(
                ["clean-exclude-selections"],
                output_type=TargetCacheValue.DEFINED,
            )
            or {}
        ):
            log_manager.singleton.log_info(
                f"filesystem '{parsed_include_path}' ignored for cleaning"
            )
            continue

        if cli_arguments.display_target:
            log_manager.singleton.log_info(parsed_include_path)
            continue

        filesystem_manager.singleton.clean_filesystem_path(parsed_include_path)
        log_manager.singleton.log_info(
            f"filesystem '{parsed_include_path}' cleaned"
        )


workspace_manager.singleton.handle(handler_manager_callback)
