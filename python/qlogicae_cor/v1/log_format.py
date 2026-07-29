import logging

from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.timestamp_manager import TimestampManager


class LogFormat(logging.Formatter):
    def format(self, record: logging.LogRecord) -> str:
        timestamp = SingletonManager.get_singleton(
            TimestampManager,
        ).generate_current_timestamp()

        return (
            f"[ {timestamp} ] "
            f"[ {record.levelname} ] "
            f"{record.getMessage()}"
        )
