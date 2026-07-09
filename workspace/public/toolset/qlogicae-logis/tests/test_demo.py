# from pathlib import Path

# DATA = b"x" * (1024 * 1024)  # 1 MB


# def write_file(path: Path, data: bytes) -> int:
#     with path.open("wb") as file:
#         return file.write(data)

# def test_write_file(benchmark, tmp_path):
#     path = tmp_path / "benchmark.bin"

#     bytes_written = benchmark(
#         write_file,
#         path,
#         DATA,
#     )

#     assert bytes_written == len(DATA)


# import pyperf

# def benchmark_write_file():
#     path = Path("benchmark.bin")

#     try:
#         write_file(path, DATA)
#     finally:
#         path.unlink(missing_ok=True)


# if __name__ == "__main__":
#     runner = pyperf.Runner()

#     runner.bench_func(
#         "write_file (1 MB)",
#         benchmark_write_file,
#     )
