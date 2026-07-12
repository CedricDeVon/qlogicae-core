from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.benchmark_manager_configurations import BenchmarkManagerConfigurations


class BenchmarkManager(AbstractManager[BenchmarkManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(BenchmarkManagerConfigurations())

    def measure_runtime(self):
        pass

    def measure_object_memory(self):
        pass

    def snapshot(self):
        pass


singleton = BenchmarkManager()
