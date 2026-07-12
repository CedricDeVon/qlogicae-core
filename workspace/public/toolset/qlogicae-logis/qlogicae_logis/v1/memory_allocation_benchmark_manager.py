from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.memory_allocation_benchmark_manager_configurations import (
    MemoryAllocationBenchmarkManagerConfigurations,
)


class MemoryAllocationBenchmarkManager(
    AbstractManager[MemoryAllocationBenchmarkManagerConfigurations]
):
    def __init__(self) -> None:
        super().__init__(MemoryAllocationBenchmarkManagerConfigurations())


singleton = MemoryAllocationBenchmarkManager()
