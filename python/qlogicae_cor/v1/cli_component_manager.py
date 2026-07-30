from typing import Any

from pyfiglet import Figlet
from rich.console import Console, RenderableType
from rich.padding import Padding
from rich.progress import (
    BarColumn,
    Progress,
    SpinnerColumn,
    TextColumn,
    TimeElapsedColumn,
)
from rich.rule import Rule
from rich.table import Table

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.cli_component_manager_configurations import (
    CliComponentManagerConfigurations,
)


class CliComponentManager(AbstractManager[CliComponentManagerConfigurations]):
    __slots__ = ("_console")

    def __init__(self) -> None:
        super().__init__(CliComponentManagerConfigurations())

        self._console: Console = Console()

    @property
    def console(self) -> Console:
        return self._console

    @property
    def table(self) -> Table:
        return Table(
            show_header=False,
            box=None,
            pad_edge=False,
            padding=(0, 4, 1, 4),
        )

    @property
    def progress_bar(self) -> Progress:
        return Progress(
            SpinnerColumn("dots", style="bold bright_green"),
            TextColumn("[green]{task.description}"),
            BarColumn(
                bar_width=80,
                complete_style="green",
            ),
            TextColumn("[green]{task.percentage:>6.2f}%"),
            TimeElapsedColumn(),
        )

    def setup_table(self, data: dict[str, Any] | None = None) -> Padding:
        if not data:
            return self.setup_padding()

        cli_table = self.table
        cli_table_headers = (data["headers"] if "headers" in data else []) or []

        for cli_table_header in cli_table_headers:
            cli_table_header_name = (
                cli_table_header["name"] if "name" in cli_table_header else "name"
            )
            cli_table_header_style = (
                cli_table_header["style"] if "style" in cli_table_header else "white"
            )
            cli_table_header_no_wrap = (
                cli_table_header["no_wrap"] if "no_wrap" in cli_table_header else True
            )

            cli_table.add_column(
                cli_table_header_name,
                style=cli_table_header_style,
                no_wrap=cli_table_header_no_wrap,
            )

        cli_table_rows = (data["rows"] if "rows" in data else []) or []
        for cli_table_row in cli_table_rows:
            cli_table.add_row(*cli_table_row)

        return self.setup_padding(cli_table)

    def setup_horizontal_rule(self) -> Padding:
        return Padding(Rule(style="bold green"), (0, 2))

    def setup_branding(
        self,
        brand_name: str,
        brand_description: str,
    ) -> Padding:
        brand_name = brand_name or "Brand"
        brand_description = brand_description or "Description"

        return self.setup_padding(
            f"[white]{Figlet(font='slant').renderText(brand_name)}[/]\n[white]{brand_description}[/]"
        )

    def setup_duration_text(self, text: str="") -> Padding:
        return self.setup_padding(f"[dim]{text} seconds[/]")

    def setup_end_padding(self) -> Padding:
        return self.setup_padding("", 0, 4)

    def setup_padding(self,
        text: RenderableType = "",
        vertical: int=1,
        horizontal: int=4
    ) -> Padding:
        return Padding(
            text,
            (vertical, horizontal),
        )
