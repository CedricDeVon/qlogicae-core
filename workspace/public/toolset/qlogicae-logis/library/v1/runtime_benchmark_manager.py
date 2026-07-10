from library.v1.abstract_manager import AbstractManager
from library.v1.runtime_benchmark_manager_configurations import (
    RuntimeBenchmarkManagerConfigurations,
)


class RuntimeBenchmarkManager(AbstractManager[RuntimeBenchmarkManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(RuntimeBenchmarkManagerConfigurations())


singleton = RuntimeBenchmarkManager()
