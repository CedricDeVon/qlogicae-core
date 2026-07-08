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

import random

from pathlib import Path

import os
import psutil
import pyperf


def create_list_1():
    return [random.random() for _ in range(1_000_000)]


def create_dict_1():
    return {
        i: random.random()
        for i in range(1_000_000)
    }


def create_list_2():
    return [random.random() for _ in range(1_000)]


def create_dict_2():
    return {
        i: random.random()
        for i in range(1_000)
    }

def main():
    numbers1 = create_list_1()

    del numbers1
    
    numbers1 = create_list_1()
    numbers2 = create_list_1()

    del numbers1

    numbers2 = create_list_1()

    # runner = pyperf.Runner()
    # runner.bench_func(
    #     "Write 1 MB",
    #     create_list_1,
    # )
    

if __name__ == "__main__":
    main()

# rm memray.bin && memray run -o memray.bin demo.py && memray table memray.bin

# memray summary memray1.bin
# memray table memray1.bin
# memray stats memray1.bin