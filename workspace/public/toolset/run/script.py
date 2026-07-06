import argparse

from library import (
    system_manager,
    workspace_manager,
    macros_manager,
    file_log_manager,
    console_log_manager,
    value_cache_manager,
)
from library.log_options import LogOptions
from library.target_cache_value import TargetCacheValue
from library.script_command import ScriptCommand


def handler_manager_callback():
    cli_parser = argparse.ArgumentParser(
        description="'script' command",
        epilog="...",
    )
    cli_parser.add_argument(
        "-t",
        "--target",
        help="target",
        dest="target",
        choices=(
            value_cache_manager.singleton.get_one_value(
                ["script-selections"],
                output_type=TargetCacheValue.DEFINED,
            )
            or {}
        ),
    )
    cli_arguments = cli_parser.parse_args()

    if not value_cache_manager.singleton.get_one_value(
        [
            f"workspace/public/configuration/workspace.yaml-raw",
            "data",
            "script",
            "is-enabled",
        ],
        output_type=TargetCacheValue.ANY,
    ):
        file_log_manager.singleton.log_warning(
            "'run.script' - check 'data.script.is-enabled' property within your 'workspace.yaml' file - disabled"
        )

        return False

    handle_targets(cli_arguments.target)

    return True


def handle_targets(target_name):
    file_log_manager.singleton.log_info(
        f"'run.script' - '{target_name}' execution - start"
    )

    for current_item in (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "script",
                "targets",
                target_name,
                "commands",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or []
    ):                
        system_manager.singleton.change_cli_filesystem_path(
            macros_manager.singleton.parse_one(
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "script",
                        "targets",
                        target_name,
                        "enter-full-path",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or "${{ current-root-full-path }}",
                (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace-macros"
                        ],
                        output_type=TargetCacheValue.DEFINED,
                    )
                    or {}
                ),
            )
        )

        if current_item["run"] in value_cache_manager.singleton.get_one_value(
            [
                "script-selections",
            ],
            output_type=TargetCacheValue.ANY,
        ):
            handle_targets(current_item["run"])

        else:
            cli_output = system_manager.singleton.execute_command(
                macros_manager.singleton.parse_one(
                    current_item["run"],
                    (
                        value_cache_manager.singleton.get_one_value(
                            ["workspace-macros"],
                            output_type=TargetCacheValue.DEFINED,
                        )
                        or {}
                    ),
                ),
            )

            file_log_manager.singleton.log_info(
                cli_output
            )
            console_log_manager.singleton.log_info(
                cli_output.stdout or cli_output.stderr,
                options=LogOptions(
                    is_verbose=False
                )
            )

    file_log_manager.singleton.log_info(
        f"'run.script' - '{target_name}' execution - complete"
    )


workspace_manager.singleton.handle(handler_manager_callback)
