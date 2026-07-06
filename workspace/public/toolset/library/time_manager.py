from datetime import date, datetime, UTC


class TimeManager:
    def __init__(self) -> None:
        self._current_time_zone = UTC

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
        return self.nanosecond // 1_000

    @property
    def current_millisecond(self) -> int:
        return self.nanosecond // 1_000_000

    @property
    def current_second(self) -> int:
        return self.nanosecond // 1_000_000_000

    @property
    def current_minute(self) -> int:
        return self.second // 60

    @property
    def current_hour(self) -> int:
        return self.minute // 60

    @property
    def current_day(self) -> int:
        return self.hour // 24

    @property
    def current_week(self) -> int:
        return self.day // 7

    @property
    def current_month(self) -> int:
        return datetime.now(UTC).month

    @property
    def current_year(self) -> int:
        return datetime.now(UTC).year

    @property
    def current_decade(self) -> int:
        return self.year // 10

    @property
    def current_century(self) -> int:
        return (self.year - 1) // 100 + 1

    @property
    def current_millenium(self) -> int:
        return (self.year - 1) // 1000 + 1


singleton = TimeManager()
