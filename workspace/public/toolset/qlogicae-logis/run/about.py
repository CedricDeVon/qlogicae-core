import argparse

from library import (
    log_manager,
    file_log_manager,
    workspace_manager,
    value_cache_manager,
    yaml_file_io_manager,
)
from library.target_cache_value import TargetCacheValue
from library.enum_conversion_output import EnumConversionOutput


def handler_manager_callback() -> bool:
    cli_parser = argparse.ArgumentParser(
        description="'run.about' command",
        epilog="...",
    )
    cli_arguments = cli_parser.parse_args()

    file_log_manager.singleton.log_info(f"'run.about' - about execution start")

    log_manager.singleton.log_info(f"{
        yaml_file_io_manager.singleton.format(
            (
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/tooling/qlogicae-logis/project/configuration/about.yaml-raw",
                        "data"                    
                    ],
                    output_type=TargetCacheValue.ANY,
                ) or {}
            ),            
        )}"
    )

    file_log_manager.singleton.log_info(f"'run.about' - about execution complete")

    return True


workspace_manager.singleton.handle(handler_manager_callback)
