import logging

from library.v1 import log_options_manager
from library.v1.log_format import LogFormat
from library.v1.log_options import LogOptions


class ConsoleLogManager:
    def __init__(self) -> None:
        self.logger = logging.getLogger("console-logger")

        self.logger.setLevel(logging.DEBUG)

        self.logger.propagate = False

        self.logger.handlers.clear()

        handler = logging.StreamHandler()

        handler.setFormatter(LogFormat())

        self.logger.addHandler(handler)

        self._options = LogOptions()

    @property
    def options(self) -> LogOptions:
        return self._options

    @options.setter
    def options(self, value) -> bool:
        self._options = value

        return True

    def log(self, message: str, options: LogOptions = LogOptions()) -> str:
        if not options.is_enabled:
            return

        message = str(message).strip()

        if options.is_verbose_enabled:
            self.logger.log(
                options.log_level,
                message,
                stacklevel=options.stack_level,
            )
        else:
            print(message)

        return message

    def log_debug(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                self._options,
                log_level=logging.DEBUG,
            ),
        )

    def log_info(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                self._options,
                log_level=logging.INFO,
            ),
        )

    def log_warning(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                self._options,
                log_level=logging.WARNING,
            ),
        )

    def log_error(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                self._options,
                log_level=logging.ERROR,
            ),
        )

    def log_critical(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                self._options,
                log_level=logging.CRITICAL,
            ),
        )


singleton = ConsoleLogManager()
