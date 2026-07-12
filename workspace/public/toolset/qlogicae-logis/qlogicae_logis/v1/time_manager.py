import time
from datetime import date, datetime

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import time_zone_enum_manager
from qlogicae_logis.v1.enum_conversion_output import EnumConversionOutput
from qlogicae_logis.v1.time_manager_configurations import TimeManagerConfigurations


class TimeManager(AbstractManager[TimeManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TimeManagerConfigurations())

        self._current_time_zone = time_zone_enum_manager.singleton.convert_value(
            "local", EnumConversionOutput.CUSTOM
        )

    @property
    def current_time_zone(self):
        return self._current_time_zone

    @current_time_zone.setter
    def current_time_zone(self, value) -> bool:
        self._current_time_zone = value

        return True

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
        return datetime.now(self._current_time_zone).second

    @property
    def current_minute(self) -> int:
        return datetime.now(self._current_time_zone).minute

    @property
    def current_hour(self) -> int:
        return datetime.now(self._current_time_zone).hour

    @property
    def current_day(self) -> int:
        return datetime.now(self._current_time_zone).day

    @property
    def current_week(self) -> int:
        return datetime.now().isocalendar().week

    @property
    def current_month(self) -> int:
        return datetime.now(self._current_time_zone).month

    @property
    def current_year(self) -> int:
        return datetime.now(self._current_time_zone).year

    @property
    def current_decade(self) -> int:
        return self.current_year // 10

    @property
    def current_century(self) -> int:
        return (self.current_year - 1) // 100 + 1

    @property
    def current_millenium(self) -> int:
        return (self.current_year - 1) // 1000 + 1


singleton = TimeManager()
