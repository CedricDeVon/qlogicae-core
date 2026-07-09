import time
import random
import argparse

from rich.live import Live
from rich.rule import Rule
from pyfiglet import Figlet
from rich.panel import Panel
from rich.table import Table
from rich.padding import Padding
from rich.console import Console
from rich.progress import (
    Progress,
    SpinnerColumn,
    BarColumn,
    TextColumn,
    TaskProgressColumn,
    TimeElapsedColumn,
    TimeRemainingColumn,
)

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
    script_command_epilogue = (
        value_cache_manager.singleton.get_one_value(
            [
                "script-command-epilogue",
            ],
            output_type=TargetCacheValue.DEFINED,
        )
        or ""
    )

    cli_parser = argparse.ArgumentParser(
        description="'run.about' command",
        epilog=script_command_epilogue,
    )
    cli_arguments = cli_parser.parse_args()

    file_log_manager.singleton.log_info(f"'run.about' - about execution start")
    logo = Figlet(font="slant").renderText("QLogicae Logis")
    console = Console()
    outputs = (
        value_cache_manager.singleton.get_one_value(
            [
                "workspace/public/tooling/qlogicae-logis/project/configuration/about.yaml-raw",
                "data",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or {}
    )
    include_outputs = [
        "version",
        "company-name",
        "project-name",
        "author-full-name",
        "author-email",
        "repository",
        "keywords",
    ]

    outputs = {key: outputs[key] for key in include_outputs if key in outputs}

    table = Table(
        show_header=False,
        box=None,
        pad_edge=False,
        padding=(0, 4, 1, 4),
    )

    table.add_column("Key", style="bold white", no_wrap=True)
    table.add_column("Value", style="white")

    for index, (key, value) in enumerate(outputs.items()):
        table.add_row(key.replace("-", " ").title(), str(value))

    console.print(
        Padding(
            f"[white]{logo}[/]\n[white]The project management tool for QLogicae projects[/]",
            (2, 4),
        )
    )
    console.print(Rule(style="white"))

    console.print(
        Padding(
            table,
            (2, 4),
        )
    )

    file_log_manager.singleton.log_info(f"'run.about' - about execution complete")

    return True


workspace_manager.singleton.handle(handler_manager_callback)
