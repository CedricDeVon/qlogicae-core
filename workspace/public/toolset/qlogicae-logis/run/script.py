import argparse

from qlogicae_logis.v1 import (
    console_log_manager,
    file_log_manager,
    log_manager,
    macros_manager,
    script_process_enum_manager,
    script_process_manager,
    system_manager,
    value_cache_manager,
    workspace_manager,
)
from qlogicae_logis.v1.enum_conversion_output import EnumConversionOutput
from qlogicae_logis.v1.target_cache_value import TargetCacheValue


def handler_manager_callback() -> bool:
    workspace_manager.singleton.handle_cutsom_script_selections_setup()

    script_selections = (
        value_cache_manager.singleton.get_one_value(
            ["script-selections"],
            output_type=TargetCacheValue.DEFINED,
        )
        or {}
    )

    cli_parser = argparse.ArgumentParser(
        description="'run.script' command",
    )
    cli_parser.add_argument(
        "-t",
        "--target",
        help="target",
        dest="target",
        choices=script_selections,
    )
    cli_arguments = cli_parser.parse_args()

    handle_targets(cli_arguments.target)

    return True


def handle_targets(target_name: str) -> bool:
    file_log_manager.singleton.log_info(
        f"'run.script' - '{target_name}' script execution start"
    )

    is_enabled_found = (
        value_cache_manager.singleton.is_key_found(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "script",
                "is-enabled",
            ]
        )
        or False
    )
    is_enabled = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "script",
                "is-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or False
    )
    is_enabled = is_enabled if is_enabled_found else True
    if not is_enabled:
        log_manager.singleton.log_warning(
            f"'run.script' - '{target_name}' script execution is disabled"
        )
        return True

    is_process_override_enabled = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "script",
                "is-process-override-enabled",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or False
    )
    default_script_process = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/configuration/workspace.yaml-raw",
                "data",
                "script",
                "process",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or "subprocess"
    )

    script_commands = (
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
    )
    if not len(script_commands):
        log_manager.singleton.log_warning(
            f"'run.script' - '{target_name}' script does not have commands to execute"
        )
        return False

    script_selections = (
        value_cache_manager.singleton.get_one_value(
            [
                "script-selections",
            ],
            output_type=TargetCacheValue.ANY,
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

    for current_script_command in script_commands:
        if "run" not in current_script_command:
            log_manager.singleton.log_warning(
                f"'run.script' - a command within the '{target_name}'"
                "script does not have a 'run' property"
            )
            continue

        is_current_script_command_enabled = (
            current_script_command["is-enabled"]
            if "is-enabled" in current_script_command
            else True
        )
        if not is_current_script_command_enabled:
            log_manager.singleton.log_warning(
                f"'run.script' - '{target_name}' script execution is disabled"
            )
            continue

        current_script_process = (
            default_script_process
            if is_process_override_enabled
            else (
                current_script_command["process"]
                if "process" in current_script_command
                else "subprocess"
            )
        )
        current_script_process_enum = (
            script_process_enum_manager.singleton.convert_value(
                current_script_process, EnumConversionOutput.ENUM
            )
        )

        current_script_target_full_path = (
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
            or "${{ current-root-full-path }}"
        )

        system_manager.singleton.current_executing_console_filesystem_path = (
            macros_manager.singleton.parse_one(
                current_script_target_full_path, workspace_macros
            )
        )

        if current_script_command["run"] in script_selections:
            handle_targets(current_script_command["run"])

        else:
            cli_output = script_process_manager.singleton.execute_command(
                macros_manager.singleton.parse_one(
                    current_script_command["run"],
                    workspace_macros,
                ),
                script_process_type=current_script_process_enum,
            )

            file_log_manager.singleton.log_info(cli_output)
            console_log_manager.singleton.log_info(
                cli_output.stdout or cli_output.stderr or ""
            )

    file_log_manager.singleton.log_info(
        f"'run.script' - '{target_name}' script execution complete"
    )

    return True


workspace_manager.singleton.handle(handler_manager_callback)
