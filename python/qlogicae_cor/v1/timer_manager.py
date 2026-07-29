from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.time_manager import (
    TimeManager,
)
from qlogicae_cor.v1.time_unit import TimeUnit
from qlogicae_cor.v1.timer_manager_configurations import (
    TimerManagerConfigurations,
)


class TimerManager(AbstractManager[TimerManagerConfigurations]):
    __slots__ = (
        "_start_timestamp",
        "_stop_timestamp"
    )

    def __init__(self) -> None:
        super().__init__(TimerManagerConfigurations())

        self._start_timestamp: float = 0
        self._stop_timestamp: float = 0

    @property
    def start_timestamp(self) -> float:
        return self._start_timestamp

    @property
    def stop_timestamp(self) -> float:
        return self._stop_timestamp

    def start_time(self) -> bool:
        self._start_timestamp = SingletonManager.get_singleton(
                TimeManager,
            ).current_nanosecond

        return True

    def stop_time(self) -> bool:
        self._stop_timestamp = SingletonManager.get_singleton(
                TimeManager,
            ).current_nanosecond

        return True

    def clear_time(self) -> bool:
        self._start_timestamp = 0
        self._stop_timestamp = 0

        return True

    def reset_time(self) -> bool:
        self._start_timestamp = SingletonManager.get_singleton(
                TimeManager,
            ).current_nanosecond
        self._stop_timestamp = 0

        return True

    def calculate_elapsed_time(
        self,
        time_unit: TimeUnit = TimeUnit.SECOND,
    ) -> float:
        return SingletonManager.get_singleton(
                TimeManager,
            ).convert_time_unit(
            SingletonManager.get_singleton(
                TimeManager,
            ).current_nanosecond - self._start_timestamp
        )

    def calculate_duration_time(
        self,
        time_unit: TimeUnit = TimeUnit.SECOND,
    ) -> float:
        return SingletonManager.get_singleton(
                TimeManager,
            ).convert_time_unit(
            self._stop_timestamp - self._start_timestamp
        )
