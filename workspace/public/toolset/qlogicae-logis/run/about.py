import argparse

from pyfiglet import Figlet
from rich.console import Console
from rich.padding import Padding
from rich.rule import Rule
from rich.table import Table

from qlogicae_logis.v1 import (
    file_log_manager,
    value_cache_manager,
    workspace_manager,
)
from qlogicae_logis.v1.target_cache_value import TargetCacheValue


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
    toolset_about_company_name = (
        toolset_about["company-name"]["value"]
        if "company-name" in toolset_about and "value" in toolset_about["company-name"]
        else "QLogicae"
    )
    toolset_about_project_name = (
        toolset_about["project-name"]["value"]
        if "project-name" in toolset_about and "value" in toolset_about["project-name"]
        else "Logis"
    )
    toolset_about_brand_name = (
        toolset_about["brand-name"]["value"]
        if "brand-name" in toolset_about and "value" in toolset_about["brand-name"]
        else f"{toolset_about_company_name} {toolset_about_project_name}"
    )
    toolset_about_project_description = (
        toolset_about["project-description"]["value"]
        if "project-description" in toolset_about
        and "value" in toolset_about["project-description"]
        else "The project management tool for QLogicae projects"
    )

    cli_console = Console()
    cli_logo = Figlet(font="slant").renderText(toolset_about_brand_name)
    cli_table = Table(
        show_header=False,
        box=None,
        pad_edge=False,
        padding=(0, 4, 1, 4),
    )
    cli_table.add_column("Key", style="bold white", no_wrap=True)
    cli_table.add_column("Value", style="white")
    for _key, item in toolset_about_table.items():
        item_name = item["name"] if "name" in item else "None"
        item_value = str(item["value"]) if "value" in item else "None"
        cli_table.add_row(item_name, item_value)

    cli_parser = argparse.ArgumentParser(
        description="'run.about' command",
    )
    cli_parser.parse_args()
    # cli_arguments = cli_parser.parse_args()

    # cli_progress_items = [
    #     ("Loading", "white"),
    # ]
    # cli_progress_bar = Progress(
    #     SpinnerColumn("dots", style="bold bright_white"),
    #     TextColumn("[white]{task.description}"),
    #     BarColumn(bar_width=80, complete_style="white"),
    #     TextColumn("[white]{task.percentage:>6.2f}%"),
    #     TimeElapsedColumn(),
    # )
    # cli_progress_bar_task = cli_progress_bar.add_task("", total=100)
    # with Live(
    #     cli_progress_bar,
    #     console=cli_console,
    #     refresh_per_second=60,
    #     transient=True,
    # ):
    #     start = time.perf_counter()
    #     for index, (message, color) in enumerate(cli_progress_items):
    #         cli_progress_bar.update(cli_progress_bar_task, description=message)

    #         cli_progress_bar.update(
    #             cli_progress_bar_task,
    #             completed=min(index / len(cli_progress_items) * 100, 100),
    #             elapsed=f"{(time.perf_counter() - start):.2f}s",
    #         )
    #         time.sleep(0.5)
    #         cli_progress_bar.update(
    #             cli_progress_bar_task,
    #             completed=min(index / len(cli_progress_items) * 100, 100),
    #             elapsed=f"{(time.perf_counter() - start):.2f}s",
    #         )
    #         time.sleep(0.5)
    #         cli_progress_bar.update(
    #             cli_progress_bar_task,
    #             completed=min(index / len(cli_progress_items) * 100, 100),
    #             elapsed=f"{(time.perf_counter() - start):.2f}s",
    #         )
    #         time.sleep(0.5)
    # cli_console.print(f"[dim]Completed in {} seconds[/]")

    file_log_manager.singleton.log_info("'run.about' - about execution start")
    cli_console.print(
        Padding(
            f"[white]{cli_logo}[/]\n[white]{toolset_about_project_description}[/]",
            (2, 4),
        )
    )
    cli_console.print(Rule(style="bold green"))
    cli_console.print(
        Padding(
            cli_table,
            (2, 4),
        )
    )
    file_log_manager.singleton.log_info("'run.about' - about execution complete")

    return True


workspace_manager.singleton.handle(handler_manager_callback)
