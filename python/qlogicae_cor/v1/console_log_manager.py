import logging

from qlogicae_logis.v1.console_log_manager_configurations import (
    ConsoleLogManagerConfigurations,
)
from qlogicae_logis.v1.log_format import LogFormat
from qlogicae_logis.v1.log_options import (
    LogOptions,
)
from qlogicae_logis.v1.log_options_manager import LogOptionsManager

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)


class ConsoleLogManager(AbstractManager[ConsoleLogManagerConfigurations]):
    __slots__ = ("_logger", "_options")

    def __init__(self) -> None:
        super().__init__(ConsoleLogManagerConfigurations())

        self._logger = logging.getLogger("console-logger")

        self._logger.setLevel(logging.DEBUG)

        self._logger.propagate = False

        self._logger.handlers.clear()

        handler = logging.StreamHandler()

        handler.setFormatter(LogFormat())

        self._logger.addHandler(handler)

        self._options: LogOptions = LogOptions()

    @property
    def options(self) -> LogOptions:
        return self._options

    @options.setter
    def options(self, value: LogOptions) -> None:
        self._options = value

    def log(self, message: str, options: LogOptions) -> str:
        if not options.is_enabled:
            return ""

        message = str(message).strip()

        if options.is_verbose_enabled:
            self._logger.log(
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
            SingletonManager.get_singleton(
                LogOptionsManager,
            ).generate_modified_defaults(
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
            SingletonManager.get_singleton(
                LogOptionsManager,
            ).generate_modified_defaults(
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
            SingletonManager.get_singleton(
                LogOptionsManager,
            ).generate_modified_defaults(
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
            SingletonManager.get_singleton(
                LogOptionsManager,
            ).generate_modified_defaults(
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
            SingletonManager.get_singleton(
                LogOptionsManager,
            ).generate_modified_defaults(
                self._options,
                log_level=logging.CRITICAL,
            ),
        )

