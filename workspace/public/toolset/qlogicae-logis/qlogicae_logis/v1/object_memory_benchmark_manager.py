from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.object_memory_benchmark_manager_configurations import (
    ObjectMemoryBenchmarkManagerConfigurations,
)


class ObjectMemoryBenchmarkManager(
    AbstractManager[ObjectMemoryBenchmarkManagerConfigurations]
):
    def __init__(self) -> None:
        super().__init__(ObjectMemoryBenchmarkManagerConfigurations())


singleton = ObjectMemoryBenchmarkManager()
