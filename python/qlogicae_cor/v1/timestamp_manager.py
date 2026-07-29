import time
from datetime import UTC, datetime

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.time_unit import TimeUnit
from qlogicae_cor.v1.time_zone_manager import (
    TimeZoneManager,
)
from qlogicae_cor.v1.timestamp import Timestamp
from qlogicae_cor.v1.timestamp_manager_configurations import (
    TimestampManagerConfigurations,
)


class TimestampManager(AbstractManager[TimestampManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TimestampManagerConfigurations())

    def generate_current_timestamp(
        self,
        timestamp: Timestamp = Timestamp.ISO_DATE_STRING,
        time_unit: TimeUnit = TimeUnit.NANOSECOND,
    ) -> str:
        timestamp_nanoseconds = time.time_ns()

        current = datetime.fromtimestamp(
            timestamp_nanoseconds / 1_000_000_000,
            SingletonManager.get_singleton(
                TimeZoneManager,
            ).selected_time_zone,
        )

        match time_unit:
            case TimeUnit.NONE | TimeUnit.SECOND:
                fraction = ""

            case TimeUnit.MILLISECOND:
                fraction = (
                    f".{timestamp_nanoseconds // 1_000_000 % 1_000:03d}"
                )

            case TimeUnit.MICROSECOND:
                fraction = (
                    f".{timestamp_nanoseconds // 1_000 % 1_000_000:06d}"
                )

            case TimeUnit.NANOSECOND:
                fraction = (
                    f".{timestamp_nanoseconds % 1_000_000_000:09d}"
                )

            case _:
                fraction = ""

        if current.tzinfo is UTC:
            suffix = "Z"
        else:
            suffix = current.strftime("%z")

            if suffix:
                suffix = (
                    f"{suffix[:-2]}:{suffix[-2:]}"
                )

        match timestamp:
            case Timestamp.ISO_DATE_STRING:
                prefix = current.strftime("%Y-%m-%dT%H:%M:%S")

            case Timestamp.ISO_FILESYSTEM_STRING:
                prefix = current.strftime("%Y-%m-%dT%H-%M-%S")
                suffix = suffix.replace(":", "-")

            case _:
                return ""

        return "".join(
            (
                prefix,
                fraction,
                suffix,
            )
        )

