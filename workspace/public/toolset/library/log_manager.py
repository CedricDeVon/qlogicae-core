import logging

from library.log_options import LogOptions
from library import console_log_manager, file_log_manager


class LogManager:
    def __init__(self) -> None:
        self._console_options = LogOptions()
        self._file_options = LogOptions()        

    @property
    def console_options(self) -> LogOptions:
        return self._console_options

    @console_options.setter
    def console_options(self, value) -> bool:
        self._console_options = value

        return True

    @property
    def file_options(self) -> LogOptions:
        return self._file_options

    @file_options.setter
    def file_options(self, value) -> bool:
        self._file_options = value

        return True

    def log(
        self,
        message: str,
        console_options: LogOptions = console_options,
        file_options: LogOptions = file_options,
    ) -> str:
        console_log_manager.singleton.log(
            message,
            LogOptions(
                is_enabled=console_options.is_enabled,
                is_verbose_enabled=console_options.is_verbose_enabled,
                log_level=logging.DEBUG,
                stack_level=console_options.stack_level,
            ),
        )

        file_log_manager.singleton.log(
            message,
            LogOptions(
                is_enabled=file_options.is_enabled,
                is_verbose_enabled=file_options.is_verbose_enabled,
                log_level=file_options.log_level,
                stack_level=file_options.stack_level,
            ),
        )

        return message

    def log_debug(
        self,
        message: str,
        console_options: LogOptions = LogOptions(
            log_level=logging.DEBUG, is_verbose_enabled=False
        ),
        file_options: LogOptions = LogOptions(log_level=logging.DEBUG),
    ) -> str:
        return self.log(message, console_options, file_options)

    def log_info(
        self,
        message: str,
        console_options: LogOptions = LogOptions(
            log_level=logging.INFO, is_verbose_enabled=False
        ),
        file_options: LogOptions = LogOptions(log_level=logging.INFO),
    ) -> str:
        return self.log(message, console_options, file_options)

    def log_warning(
        self,
        message: str,
        console_options: LogOptions = LogOptions(
            log_level=logging.WARNING, is_verbose_enabled=False
        ),
        file_options: LogOptions = LogOptions(log_level=logging.WARNING),
    ) -> str:
        return self.log(message, console_options, file_options)

    def log_error(
        self,
        message: str,
        console_options: LogOptions = LogOptions(
            log_level=logging.ERROR, is_verbose_enabled=False
        ),
        file_options: LogOptions = LogOptions(log_level=logging.ERROR),
    ) -> str:
        return self.log(message, console_options, file_options)

    def log_critical(
        self,
        message: str,
        console_options: LogOptions = LogOptions(
            log_level=logging.CRITICAL, is_verbose_enabled=False
        ),
        file_options: LogOptions = LogOptions(log_level=logging.CRITICAL),
    ) -> str:
        return self.log(message, console_options, file_options)

    def shutdown(self):
        file_log_manager.singleton.shutdown()

        return True


singleton = LogManager()
