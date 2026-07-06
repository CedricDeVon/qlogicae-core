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
                        time_manager.singleton.current_time_zone
                    ):%Y-%m-%dT%H:%M:%S}'
                f'.{timestamp_nanoseconds % 1_000_000_000:09d}'
                f'{"Z" if time_manager.singleton.current_time_zone is UTC else ""}'
            )
        }"


singleton = TimestampManager()
