import time
from datetime import date, datetime, UTC


from library import time_manager
from library.time_unit import TimeUnit
from library.enum_conversion_output import EnumConversionOutput


class TimerManager:
    def __init__(self) -> None:
        self._start_timestamp = 0
        self._stop_timestamp = 0

    def start(self) -> bool:
        self._start_timestamp = time_manager.singleton.current_nanosecond

        return True

    def stop(self) -> bool:
        self._stop_timestamp = time_manager.singleton.current_nanosecond

        return True

    def clear(self) -> bool:
        self._start_timestamp = 0
        self._stop_timestamp = 0

        return True

    def reset(self) -> bool:
        self._start_timestamp = time_manager.singleton.current_nanosecond
        self._stop_timestamp = 0

        return True

    def calculate_elapsed(self, time_unit: TimeUnit = TimeUnit.SECOND) -> float:
        return self.convert_time_unit(
            time_manager.singleton.current_nanosecond - self._start_timestamp
        )

    def calculate_duration(self, time_unit: TimeUnit = TimeUnit.SECOND) -> float:
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
