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




# from pathlib import Path

# import os
# import psutil
# import pyperf


# DATA = b"x" * (1024 * 1024)  # 1 MB


# def write_file():
#     path = Path("benchmark.bin")

#     with path.open("wb") as file:
#         file.write(DATA)

#     path.unlink()




# def benchmark():
#     runner = pyperf.Runner()

#     runner.bench_func(
#         "Write 1 MB",
#         write_file,
#     )


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

import random


def bubble_sort(values: list[int]) -> list[int]:
    values = values.copy()

    n = len(values)

    for i in range(n):
        for j in range(n - i - 1):
            if values[j] > values[j + 1]:
                values[j], values[j + 1] = (
                    values[j + 1],
                    values[j],
                )

    return values


def main():
    data = [
        random.randint(0, 100000)
        for _ in range(50000)
    ]

    bubble_sort(data)


if __name__ == "__main__":
    main()