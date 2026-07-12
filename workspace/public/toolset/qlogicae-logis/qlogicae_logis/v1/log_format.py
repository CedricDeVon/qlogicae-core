import logging

from qlogicae_logis.v1 import timestamp_manager


class LogFormat(logging.Formatter):
    def format(self, record: logging.LogRecord) -> str:
        return (
            f"[ {timestamp_manager.singleton.current_standard_timestamp} ] "
            f"[ {record.levelname} ] "
            f"\n{record.getMessage()}"
        )
