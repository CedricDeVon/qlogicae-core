import time
from datetime import UTC, datetime

from library import time_manager
from library.time_zone import TimeZone


class TimestampManager:
    @property
    def current_standard_timestamp(self) -> str:
        timestamp_nanoseconds = time.time_ns()

        return f"{
            (
                f'{
                    datetime.fromtimestamp(
                        timestamp_nanoseconds / 1_000_000_000,
                        time_manager.singleton.current_time_zone,
                    ):%Y-%m-%dT%H:%M:%S}'
                f'.{timestamp_nanoseconds % 1_000_000_000:09d}'
                f'{"Z" if time_manager.singleton.current_time_zone is UTC else ""}'
            )
        }"

    def current_timestamp(self, time_unit: TimeUnit) -> str:
        timestamp_nanoseconds = time.time_ns()

        timestamp = datetime.fromtimestamp(
            timestamp_nanoseconds / 1_000_000_000,
            time_manager.singleton.current_time_zone,
        )

        suffix = "Z" if time_manager.singleton.current_time_zone is UTC else ""

        match time_unit:
            case TimeUnit.NONE:
                fraction = ""

            case TimeUnit.SECOND:
                fraction = ""

            case TimeUnit.MILLISECOND:
                fraction = f".{timestamp_nanoseconds // 1_000_000 % 1_000:03d}"

            case TimeUnit.MICROSECOND:
                fraction = f".{timestamp_nanoseconds // 1_000 % 1_000_000:06d}"

            case TimeUnit.NANOSECOND:
                fraction = f".{timestamp_nanoseconds % 1_000_000_000:09d}"

            case _:
                fraction = ""

        return f"{timestamp:%Y-%m-%dT%H:%M:%S}{fraction}{suffix}"


singleton = TimestampManager()
