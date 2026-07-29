import time
from datetime import date, datetime

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.time_manager_configurations import (
    TimeManagerConfigurations,
)
from qlogicae_cor.v1.time_unit import (
    TimeUnit,
)
from qlogicae_cor.v1.time_zone_manager import (
    TimeZoneManager,
)


class TimeManager(AbstractManager[TimeManagerConfigurations]):
    __slots__ = (
        "_TIME_UNIT_TO_NANOSECONDS",
    )

    def __init__(self) -> None:
        super().__init__(TimeManagerConfigurations())

        self._TIME_UNIT_TO_NANOSECONDS: dict[TimeUnit, float] = {
            TimeUnit.NANOSECOND: 1.0,
            TimeUnit.MICROSECOND: 1e3,
            TimeUnit.MILLISECOND: 1e6,
            TimeUnit.SECOND: 1e9,
            TimeUnit.MINUTE: 60e9,
            TimeUnit.HOUR: 3600e9,
            TimeUnit.DAY: 86400e9,
            TimeUnit.WEEK: 604800e9,
            TimeUnit.MONTH: 2629746e9,
            TimeUnit.YEAR: 31556952e9,
            TimeUnit.DECADE: 315569520e9,
            TimeUnit.CENTURY: 3155695200e9,
            TimeUnit.MILLENNIUM: 31556952000e9,
        }

    @property
    def current_iso8601_date(self) -> str:
        return date.today().strftime("%Y-%m-%d")

    @property
    def current_nanosecond(self) -> int:
        return time.time_ns()

    @property
    def current_microsecond(self) -> int:
        return self.current_nanosecond // 1_000

    @property
    def current_millisecond(self) -> int:
        return self.current_nanosecond // 1_000_000

    @property
    def current_second(self) -> int:
        return datetime.now(
            SingletonManager.get_singleton(
                TimeZoneManager
            ).selected_time_zone
        ).second

    @property
    def current_minute(self) -> int:
        return datetime.now(
            SingletonManager.get_singleton(
                TimeZoneManager
            ).selected_time_zone
        ).minute

    @property
    def current_hour(self) -> int:
        return datetime.now(
            SingletonManager.get_singleton(
                TimeZoneManager
            ).selected_time_zone
        ).hour

    @property
    def current_day(self) -> int:
        return datetime.now(
            SingletonManager.get_singleton(
                TimeZoneManager
            ).selected_time_zone
        ).day

    @property
    def current_week(self) -> int:
        return datetime.now().isocalendar().week

    @property
    def current_month(self) -> int:
        return datetime.now(
            SingletonManager.get_singleton(
                TimeZoneManager
            ).selected_time_zone
        ).month

    @property
    def current_year(self) -> int:
        return datetime.now(
            SingletonManager.get_singleton(
                TimeZoneManager
            ).selected_time_zone
        ).year

    @property
    def current_decade(self) -> int:
        return self.current_year // 10

    @property
    def current_century(self) -> int:
        return (self.current_year - 1) // 100 + 1

    @property
    def current_millenium(self) -> int:
        return (self.current_year - 1) // 1000 + 1

    def calculate_elapsed_time(
        self,
        start: float,
        time_unit: TimeUnit = TimeUnit.SECOND,
    ) -> float:
        return self.convert_time_unit(time.time_ns() - start, time_unit)

    def calculate_duration_time(
        self,
        start: float,
        end: float,
        time_unit: TimeUnit = TimeUnit.SECOND,
    ) -> float:
        return self.convert_time_unit(end - start, time_unit)

    def convert_time_unit(
        self,
        value: float,
        input_time_unit: TimeUnit = TimeUnit.SECOND,
        output_time_unit: TimeUnit = TimeUnit.SECOND,
    ) -> float:
        if input_time_unit is output_time_unit:
            return float(value)

        nanoseconds = (
            value
            * self._TIME_UNIT_TO_NANOSECONDS[input_time_unit]
        )

        return (
            nanoseconds
            / self._TIME_UNIT_TO_NANOSECONDS[output_time_unit]
        )
