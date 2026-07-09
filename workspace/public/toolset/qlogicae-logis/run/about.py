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
    workspace_manager.singleton.handle_toolset_configuration_file_data_extraction_setup()
    workspace_manager.singleton.handle_toolset_configuration_data_setup()

    toolset_about = (
        value_cache_manager.singleton.get_one_value(
            [
                "toolset-about",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or {}
    )
    toolset_about_table = (
        value_cache_manager.singleton.get_one_value(
            [
                "toolset-about-table",
            ],
            output_type=TargetCacheValue.ANY,
        )
        or {}
    )
    toolset_about_company_name = toolset_about["company-name"]["value"]
    toolset_about_project_name = toolset_about["project-name"]["value"]
    toolset_about_brand_name = toolset_about["brand-name"]["value"]
    toolset_about_project_description = toolset_about["project-description"]["value"]

    cli_parser = argparse.ArgumentParser(
        description="'run.about' command",
    )
    cli_arguments = cli_parser.parse_args()

    console = Console()
    logo = Figlet(font="slant").renderText(toolset_about_brand_name)

    table = Table(
        show_header=False,
        box=None,
        pad_edge=False,
        padding=(0, 4, 1, 4),
    )
    table.add_column("Key", style="bold white", no_wrap=True)
    table.add_column("Value", style="white")
    for key, item in toolset_about_table.items():
        item_name = item["name"]
        item_value = str(item["value"])

        table.add_row(item_name, item_value)


    file_log_manager.singleton.log_info(f"'run.about' - about execution start")
    console.print(
        Padding(
            f"[white]{logo}[/]\n[white]{toolset_about_project_description}[/]",
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
