import random
from math import sqrt
import time


# pytest \
#     -vv \
#     --benchmark-only \
#     --benchmark-disable-gc \
#     --benchmark-verbose \
#     --benchmark-sort=mean \
#     --benchmark-columns=min,max,mean,stddev,median,iqr,outliers,rounds,iterations,ops \
#     --benchmark-json=benchmark.json \
#     --benchmark-histogram=benchmark \
#     --benchmark-save=latest \
#     --benchmark-disable-gc \
#     demo.py


# def builtin_sort(data: list[int]) -> list[int]:
#     return sorted(data)

# def list_comprehension(data: list[int]) -> list[int]:
#     return [x * 2 for x in data]


# def sum_squares(data: list[int]) -> float:
#     return sum(sqrt(x) for x in data)

# def setup():
#     pass

# def teardown(result):
#     pass

# def test_sort_100(benchmark):
#     data = [random.randint(0, 1_000_000) for _ in range(100)]

#     result = benchmark.pedantic(
#         builtin_sort,
#         args=(data,),
#         rounds=100,
#         iterations=100,
#         warmup_rounds=10,
#         # setup=setup,
#         # teardown=teardown,
#     )

#     assert len(result) == len(data)

# def test_sort_1000(benchmark):
#     data = [random.randint(0, 1_000_000) for _ in range(1000)]

#     result = benchmark.pedantic(
#         builtin_sort,
#         args=(data,),
#         rounds=100,
#         iterations=100,
#         warmup_rounds=10,
#         # setup=setup,
#         # teardown=teardown,
#     )

#     assert len(result) == len(data)

# def test_sort_10000(benchmark):
#     data = [random.randint(0, 1_000_000) for _ in range(10000)]

#     result = benchmark.pedantic(
#         builtin_sort,
#         args=(data,),
#         rounds=10,
#         iterations=1000,
#         warmup_rounds=10,
#         # setup=setup,
#         # teardown=teardown,
#     )

#     assert len(result) == len(data)


# def test_sort_100(benchmark):
#     data = [random.randint(0, 1_000_000) for _ in range(100)]

#     result = benchmark.pedantic(
#         builtin_sort,
#         args=(data,),
#         rounds=1000,
#         iterations=10,
#         warmup_rounds=100,
#         # setup=setup,
#         teardown=teardown,
#     )

#     assert len(result) == len(data)


# def test_sort_1000(benchmark):
#     data = [random.randint(0, 1_000_000) for _ in range(1_000)]

#     result = benchmark.pedantic(
#         builtin_sort,
#         args=(data,),
#         rounds=1000,
#         iterations=10,
#         warmup_rounds=100,
#         # setup=setup,
#         teardown=teardown,
#     )

#     assert len(result) == len(data)


# def test_sort_10000(benchmark):
#     data = [random.randint(0, 1_000_000) for _ in range(10_000)]

#     result = benchmark.pedantic(
#         builtin_sort,
#         args=(data,),
#         rounds=100,
#         iterations=10,
#         warmup_rounds=100,
#         # setup=setup,
#         teardown=teardown,
#     )

#     assert len(result) == len(data)


# def test_list_comprehension(benchmark):
#     data = list(range(100_000))

#     result = benchmark(list_comprehension, data)

#     assert result[0] == 0


# def test_math_generator(benchmark):
#     data = list(range(100_000))

#     result = benchmark(sum_squares, data)

#     assert result > 0


# ---------------------------------------------------------------------
# Pedantic Benchmark
# ---------------------------------------------------------------------

# def test_pedantic_sort(benchmark):
#     data = [random.randint(0, 1_000_000) for _ in range(5_000)]

#     benchmark.pedantic(
#         builtin_sort,
#         args=(data,),
#         rounds=1000,
#         iterations=100,
#         warmup_rounds=10
#     )


# from library import (
#     workspace_manager,
#     value_cache_manager,
# )


# def handle_manager_callback():
#     value_cache_manager.singleton.display_all_items()


# workspace_manager.singleton.handle(handle_manager_callback)

# from pympler import asizeof


# items = [True, 1, 1.1, {}, "", "hello"]

# print('Objsize: ')
# for item in items:
#     print(objsize.get_deep_size(item))
#     # print(asizeof.asizeof(item))


# print('Pympler: ')
# for item in items:
#     # print(objsize.get_deep_size(item))
#     print(asizeof.asizeof(item))


# import os
# import psutil

# process = psutil.Process(os.getpid())

# print(f"CPU        : {process.cpu_percent(interval=1.0):.1f}%")
# print(f"RSS        : {process.memory_info().rss / 1024 / 1024:.2f} MB")
# print(f"VMS        : {process.memory_info().vms / 1024 / 1024:.2f} MB")
# print(f"Threads    : {process.num_threads()}")
# print(f"Open Files : {len(process.open_files())}")


# DATA = b"x" * (1024 * 1024)  # 1 MB


# def write_file():
#     path = Path("benchmark.bin")

#     with path.open("wb") as file:
#         file.write(DATA)

#     path.unlink()


# def benchmark():


# def system_metrics():
#     process = psutil.Process(os.getpid())

#     print("=== Memory ===")

#     memory = process.memory_info()

#     print(f"RSS        : {memory.rss / 1024 / 1024:.2f} MB")
#     print(f"VMS        : {memory.vms / 1024 / 1024:.2f} MB")

#     print()

#     print("=== CPU ===")

#     print(f"CPU %      : {process.cpu_percent(interval=1.0):.1f}%")
#     print(f"Threads    : {process.num_threads()}")

#     print()

#     print("=== Process ===")

#     print(f"PID        : {process.pid}")


# if __name__ == "__main__":
#     # benchmark()
#     system_metrics()

# import random


# def bubble_sort(values: list[int]) -> list[int]:
#     values = values.copy()

#     n = len(values)

#     for i in range(n):
#         for j in range(n - i - 1):
#             if values[j] > values[j + 1]:
#                 values[j], values[j + 1] = (
#                     values[j + 1],
#                     values[j],
#                 )

#     return values


# def main():
#     data = [
#         random.randint(0, 100000)
#         for _ in range(50000)
#     ]

#     bubble_sort(data)


# if __name__ == "__main__":
#     main()

# import random

# from pathlib import Path

# import os
# import psutil
# import pyperf


# def create_list_1():
#     return [random.random() for _ in range(1_000_000)]


# def create_dict_1():
#     return {
#         i: random.random()
#         for i in range(1_000_000)
#     }


# def create_list_2():
#     return [random.random() for _ in range(1_000)]


# def create_dict_2():
#     return {
#         i: random.random()
#         for i in range(1_000)
#     }

# def main():
#     numbers1 = create_list_1()

#     del numbers1

#     numbers1 = create_list_1()
#     numbers2 = create_list_1()

#     del numbers1

#     numbers2 = create_list_1()

#     # runner = pyperf.Runner()
#     # runner.bench_func(
#     #     "Write 1 MB",
#     #     create_list_1,
#     # )


# if __name__ == "__main__":
#     main()

# rm memray.bin && memray run -o memray.bin demo.py && memray table memray.bin

# memray summary memray1.bin
# memray table memray1.bin
# memray stats memray1.bin


#!/usr/bin/env python3

# import random
# import time

# from rich.console import Console
# from rich.live import Live
# from rich.progress import (
#     Progress,
#     SpinnerColumn,
#     BarColumn,
#     TextColumn,
#     TaskProgressColumn,
#     TimeElapsedColumn,
# )

# console = Console()

# items = [
#     ("📥", "Downloading metadata", "cyan"),
#     ("📦", "Resolving dependencies", "yellow"),
#     ("🔍", "Checking package cache", "bright_blue"),
#     ("⚙", "Preparing build environment", "blue"),
#     ("🛠", "Compiling C extensions", "magenta"),
#     ("📦", "Downloading numpy", "cyan"),
#     ("📦", "Downloading pandas", "cyan"),
#     ("📦", "Downloading scipy", "cyan"),
#     ("📦", "Downloading matplotlib", "cyan"),
#     ("📦", "Downloading rich", "cyan"),
#     ("🔧", "Installing numpy", "green"),
#     ("🔧", "Installing pandas", "green"),
#     ("🔧", "Installing scipy", "green"),
#     ("🔧", "Installing matplotlib", "green"),
#     ("🔧", "Installing rich", "green"),
#     ("📝", "Generating entry points", "bright_magenta"),
#     ("📄", "Writing configuration files", "bright_white"),
#     ("🔗", "Linking shared libraries", "bright_yellow"),
#     ("🧹", "Cleaning temporary files", "bright_black"),
#     ("🛡", "Running integrity checks", "bright_cyan"),
#     ("🔒", "Verifying package hashes", "bright_green"),
#     ("📚", "Updating package database", "bright_blue"),
#     ("🚀", "Optimizing bytecode", "bright_magenta"),
#     ("✨", "Finalizing installation", "bright_green"),
# ]

# progress = Progress(
#     SpinnerColumn("dots"),
#     TextColumn("[bold blue]{task.description}"),
#     BarColumn(bar_width=40, complete_style="green"),
#     TaskProgressColumn(),
#     TimeElapsedColumn(),
# )

# task = progress.add_task("", total=100)

# with Live(
#     progress,
#     console=console,
#     refresh_per_second=60,
#     transient=True,
# ):

#     for icon, message, color in items:

#         progress.reset(task)
#         progress.update(task, description=message)

#         duration = random.uniform(0.3, 0.8)
#         start = time.perf_counter()

#         while True:

#             elapsed = time.perf_counter() - start

#             progress.update(
#                 task,
#                 completed=min(elapsed / duration * 100, 100),
#             )

#             if elapsed >= duration:
#                 break

#             time.sleep(0.01)

#         console.print(
#             f"[bold {color}]{icon}[/] "
#             f"[bold white]{message:<35}[/] "
#             f"[bold green]✓[/]"
#         )

# console.print()
# console.print("[bold bright_green]✔ Successfully installed 5 packages[/]")
# console.print("[dim]Completed in 8.24 seconds[/]")


# from rich.rule import Rule
# from rich.console import Console
# from rich.panel import Panel
# from pyfiglet import Figlet

# console = Console()
# logo = Figlet(font="slant").renderText("QLogicae Logis")

# console.print(f"[green]{logo}[/]")
# console.print(Rule("[bold cyan]QLogicae[/]"))
# console.print(
#     Panel.fit(
#         f"[bold cyan]{logo}[/]\n"
#         "[green]Python Developer Toolkit[/]",
#         border_style="cyan",
#     )
# )


#!/usr/bin/env python3


# from rich import box
# from rich.console import Console
# from rich.table import Table

# console = Console()


# def sample_rows(table: Table):
#     table.add_row("numpy", "2.3.1", "✓ Installed", "0.32 s")
#     table.add_row("pandas", "2.3.0", "✓ Installed", "0.47 s")
#     table.add_row("scipy", "1.16.0", "⚠ Warning", "1.21 s")
#     table.add_row("matplotlib", "3.10.3", "✗ Failed", "0.89 s")


# def demo_box_styles():
#     console.rule("[bold cyan]Box Styles")

#     styles = [
#         ("ASCII", box.ASCII),
#         ("ASCII2", box.ASCII2),
#         ("MINIMAL", box.MINIMAL),
#         ("SIMPLE", box.SIMPLE),
#         ("SIMPLE_HEAD", box.SIMPLE_HEAD),
#         ("SQUARE", box.SQUARE),
#         ("ROUNDED", box.ROUNDED),
#         ("HEAVY", box.HEAVY),
#         ("HEAVY_EDGE", box.HEAVY_EDGE),
#         ("HEAVY_HEAD", box.HEAVY_HEAD),
#         ("DOUBLE", box.DOUBLE),
#         ("DOUBLE_EDGE", box.DOUBLE_EDGE),
#         ("HORIZONTALS", box.HORIZONTALS),
#         ("MARKDOWN", box.MARKDOWN),
#     ]

#     for name, border in styles:
#         table = Table(
#             title=name,
#             box=border,
#             border_style="cyan",
#             title_style="bold magenta",
#         )

#         table.add_column("Package")
#         table.add_column("Version")
#         table.add_column("Status")

#         table.add_row("rich", "14.0", "Installed")
#         table.add_row("numpy", "2.3.1", "Pending")

#         console.print(table)


# def demo_row_styles():
#     console.rule("[bold cyan]Row Styles")

#     table = Table(
#         title="Alternating Row Colors",
#         box=box.ROUNDED,
#         row_styles=["", "dim"],
#     )

#     table.add_column("Package")
#     table.add_column("Language")

#     table.add_row("Rich", "Python")
#     table.add_row("Cargo", "Rust")
#     table.add_row("npm", "JavaScript")
#     table.add_row("NuGet", "C#")

#     console.print(table)


# def demo_colored_rows():
#     console.rule("[bold cyan]Colored Rows")

#     table = Table(box=box.ROUNDED)

#     table.add_column("Step")
#     table.add_column("Result")

#     table.add_row("Download", "Success", style="green")
#     table.add_row("Compile", "Warning", style="yellow")
#     table.add_row("Install", "Failed", style="red")
#     table.add_row("Cleanup", "Skipped", style="cyan")

#     console.print(table)


# def demo_alignment():
#     console.rule("[bold cyan]Column Alignment")

#     table = Table(box=box.ROUNDED)

#     table.add_column("Left", justify="left")
#     table.add_column("Center", justify="center")
#     table.add_column("Right", justify="right")

#     table.add_row("numpy", "2.3.1", "Installed")
#     table.add_row("pandas", "2.3.0", "Installed")

#     console.print(table)


# def demo_expand():
#     console.rule("[bold cyan]Expand to Terminal Width")

#     table = Table(
#         title="Expand=True",
#         expand=True,
#         box=box.ROUNDED,
#     )

#     table.add_column("Package", ratio=3)
#     table.add_column("Version", ratio=1)
#     table.add_column("Status", ratio=2)

#     sample_rows(table)

#     console.print(table)


# def demo_show_lines():
#     console.rule("[bold cyan]Show Lines")

#     table = Table(
#         title="show_lines=True",
#         show_lines=True,
#         box=box.ROUNDED,
#     )

#     table.add_column("Package")
#     table.add_column("Version")
#     table.add_column("Status")
#     table.add_column("Time")

#     sample_rows(table)

#     console.print(table)


# def demo_padding():
#     console.rule("[bold cyan]Custom Padding")

#     table = Table(
#         title="padding=(0,4)",
#         padding=(0, 4),
#         box=box.ROUNDED,
#     )

#     table.add_column("Package")
#     table.add_column("Version")
#     table.add_column("Status")
#     table.add_column("Time")

#     sample_rows(table)

#     console.print(table)


# def demo_leading():
#     console.rule("[bold cyan]Leading")

#     table = Table(
#         title="leading=1",
#         leading=1,
#         box=box.ROUNDED,
#     )

#     table.add_column("Package")
#     table.add_column("Version")
#     table.add_column("Status")
#     table.add_column("Time")

#     sample_rows(table)

#     console.print(table)


# def demo_footer():
#     console.rule("[bold cyan]Footer")

#     table = Table(
#         title="Column Footers",
#         box=box.ROUNDED,
#     )

#     table.add_column(
#         "Package",
#         footer="[bold]4 Packages[/]",
#     )

#     table.add_column(
#         "Time",
#         justify="right",
#         footer="[green]2.89 s[/]",
#     )

#     table.add_row("numpy", "0.32 s")
#     table.add_row("pandas", "0.47 s")
#     table.add_row("scipy", "1.21 s")
#     table.add_row("matplotlib", "0.89 s")

#     console.print(table)


# def demo_overflow():
#     console.rule("[bold cyan]Overflow")

#     table = Table(
#         title="Ellipsis Overflow",
#         box=box.ROUNDED,
#     )

#     table.add_column(
#         "Description",
#         overflow="ellipsis",
#         width=30,
#     )

#     table.add_row(
#         "This is a very long package description that should be truncated."
#     )

#     console.print(table)


# def demo_nowrap():
#     console.rule("[bold cyan]No Wrap")

#     table = Table(
#         box=box.ROUNDED,
#     )

#     table.add_column(
#         "Package",
#         no_wrap=True,
#     )

#     table.add_column("Description")

#     table.add_row(
#         "super-long-package-name-with-many-components",
#         "Normal wrapped description.",
#     )

#     console.print(table)


# def demo_gridless():
#     console.rule("[bold cyan]Gridless")

#     table = Table(
#         title="No Border",
#         box=None,
#     )

#     table.add_column("Package")
#     table.add_column("Version")
#     table.add_column("Status")

#     sample_rows(table)

#     console.print(table)


# def demo_dashboard():
#     console.rule("[bold cyan]Modern Dashboard Style")

#     table = Table(
#         title="[bold cyan]Package Installation[/]",
#         caption="Generated by Rich",
#         box=box.ROUNDED,
#         border_style="cyan",
#         header_style="bold white on blue",
#         title_style="bold cyan",
#         caption_style="dim",
#         row_styles=["", "grey15"],
#         expand=True,
#         highlight=True,
#     )

#     table.add_column("Package", style="cyan", ratio=3)
#     table.add_column("Version", justify="center", style="yellow")
#     table.add_column("Status", justify="center")
#     table.add_column("Elapsed", justify="right", style="magenta")

#     sample_rows(table)

#     console.print(table)


# def main():
#     console.print("\n[bold green]Rich Table Demonstrations[/]\n")

#     demo_box_styles()
#     demo_row_styles()
#     demo_colored_rows()
#     demo_alignment()
#     demo_expand()
#     demo_show_lines()
#     demo_padding()
#     demo_leading()
#     demo_footer()
#     demo_overflow()
#     demo_nowrap()
#     demo_gridless()
#     demo_dashboard()

#     console.rule("[bold green]End of Demonstration")


# if __name__ == "__main__":
#     main()


# import time

# from rich.console import Console
# from rich.live import Live
# from rich.spinner import SPINNERS, Spinner
# from rich.table import Table

# console = Console()


# def build_table() -> Table:
#     table = Table(title="Rich Spinner Showcase", expand=True)

#     table.add_column("Spinner", style="bold cyan", width=10)
#     table.add_column("Preview")

#     for name in sorted(SPINNERS):
#         table.add_row(
#             name,
#             Spinner(name, style="bold bright_green"),
#         )

#     return table


# with Live(
#     build_table(),
#     console=console,
#     refresh_per_second=30,
# ) as live:
#     while True:
#         live.update(build_table())
#         time.sleep(1 / 30)


# console = Console()

# items = [
#     ("Loading", "white"),
# ]

# progress = Progress(
#     SpinnerColumn("dots", style="bold bright_white"),
#     TextColumn("[white]{task.description}"),
#     BarColumn(bar_width=80, complete_style="white"),
#     TextColumn("[white]{task.percentage:>6.2f}%"),
#     TimeElapsedColumn(),
#     TimeRemainingColumn(),
# )

# task = progress.add_task("", total=100)

# with Live(
#     progress,
#     console=console,
#     refresh_per_second=60,
#     transient=True,
# ):
#     for message, color in items:
#         progress.reset(task)
#         progress.update(task, description=message)

#         duration = 10
#         start = time.perf_counter()

#         while True:
#             elapsed = time.perf_counter() - start

#             progress.update(
#                 task,
#                 completed=min(elapsed / duration * 100, 100),
#                 elapsed=f"{elapsed:.2f}s",
#             )

#             if elapsed >= duration:
#                 break

#             time.sleep(0.1)

#             console.print(
#                 f"[white]✓[/]"
#             )

# console.print("[dim]Completed in 8.24 seconds[/]")


# items = [
#     ("Loading | 1", "white"),
#     ("Loading | 2", "white"),
#     ("Loading | 3", "white"),
#     ("Loading | 4", "white"),
#     ("Loading | 5", "white"),
# ]
# console = Console()
# progress = Progress(
#     SpinnerColumn("dots", style="bold bright_white"),
#     TextColumn("[white]{task.description}"),
#     BarColumn(bar_width=80, complete_style="white"),
#     TextColumn("[white]{task.percentage:>6.2f}%"),
#     TimeElapsedColumn(),
# )
# task = progress.add_task("", total=100)
# with Live(
#     progress,
#     console=console,
#     refresh_per_second=60,
#     transient=True,
# ):
#     start = time.perf_counter()

#     for index, (message, color) in enumerate(items):
#         progress.update(task, description=message)

#         progress.update(
#             task,
#             completed=min(index / len(items) * 100, 100),
#             elapsed=f"{(time.perf_counter() - start):.2f}s",
#         )
#         time.sleep(0.5)
#         progress.update(
#             task,
#             completed=min(index / len(items) * 100, 100),
#             elapsed=f"{(time.perf_counter() - start):.2f}s",
#         )
#         time.sleep(0.5)
#         progress.update(
#             task,
#             completed=min(index / len(items) * 100, 100),
#             elapsed=f"{(time.perf_counter() - start):.2f}s",
#         )
#         time.sleep(0.5)

#         console.print(
#             f"[white]✓[/]"
#         )

# console.print("[dim]Completed in 8.24 seconds[/]")
