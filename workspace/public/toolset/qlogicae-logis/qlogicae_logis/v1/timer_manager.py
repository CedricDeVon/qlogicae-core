from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import time_manager
from qlogicae_logis.v1.time_unit import TimeUnit
from qlogicae_logis.v1.timer_manager_configurations import TimerManagerConfigurations


class TimerManager(AbstractManager[TimerManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TimerManagerConfigurations())

        self._start_timestamp = 0
        self._stop_timestamp = 0

    def start_time(self) -> bool:
        self._start_timestamp = time_manager.singleton.current_nanosecond

        return True

    def stop_time(self) -> bool:
        self._stop_timestamp = time_manager.singleton.current_nanosecond

        return True

    def clear_time(self) -> bool:
        self._start_timestamp = 0
        self._stop_timestamp = 0

        return True

    def reset_time(self) -> bool:
        self._start_timestamp = time_manager.singleton.current_nanosecond
        self._stop_timestamp = 0

        return True

    def calculate_elapsed_time(self, time_unit: TimeUnit = TimeUnit.SECOND) -> float:
        return self.convert_time_unit(
            time_manager.singleton.current_nanosecond - self._start_timestamp
        )

    def calculate_duration_time(self, time_unit: TimeUnit = TimeUnit.SECOND) -> float:
        return self.convert_time_unit(self._stop_timestamp - self._start_timestamp)

    def convert_time_unit(
        self, value: float, time_unit: TimeUnit = TimeUnit.SECOND
    ) -> float:
        if value < 0:
            raise ValueError("timer has not been stopped or timestamps are invalid.")

        match time_unit:
            case TimeUnit.NANOSECOND:
                return float(value)

            case TimeUnit.MICROSECOND:
                return value / 1e3

            case TimeUnit.MILLISECOND:
                return value / 1e6

            case TimeUnit.SECOND:
                return value / 1e9

            case TimeUnit.MINUTE:
                return value / 60e9

            case TimeUnit.HOUR:
                return value / 3600e9

            case TimeUnit.DAY:
                return value / 86400e9

            case TimeUnit.WEEK:
                return value / 604800e9

            case TimeUnit.MONTH:
                return value / 2629746e9

            case TimeUnit.YEAR:
                return value / 31556952e9

            case TimeUnit.DECADE:
                return value / 315569520e9

            case TimeUnit.CENTURY:
                return value / 3155695200e9

            case TimeUnit.MILLENIUM:
                return value / 31556952000e9

            case _:
                return value


singleton = TimerManager()
