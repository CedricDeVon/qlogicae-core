import logging

from qlogicae_logis.v1.console_log_manager import ConsoleLogManager
from qlogicae_logis.v1.file_log_manager import FileLogManager
from qlogicae_logis.v1.log_manager_configurations import (
    LogManagerConfigurations,
)
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


class LogManager(AbstractManager[LogManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(LogManagerConfigurations())

    def log(
        self,
        message: str,
        console_options: LogOptions,
        file_options: LogOptions,
    ) -> str:
        SingletonManager.get_singleton(
            ConsoleLogManager,
        ).log(
            message,
            console_options,
        )
        SingletonManager.get_singleton(
            FileLogManager,
                ).log(
            message,
            file_options,
        )

        return message

    def log_debug(self, message: str) -> str:
        return self.log(
            message,
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    ConsoleLogManager,
                ).options,
                log_level=logging.DEBUG,
            ),
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    FileLogManager,
                ).options,
                log_level=logging.DEBUG,
            ),
        )

    def log_info(self, message: str) -> str:
        return self.log(
            message,
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    ConsoleLogManager,
                ).options,
                log_level=logging.INFO,
            ),
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    FileLogManager,
                ).options,
                log_level=logging.INFO,
            ),
        )

    def log_warning(self, message: str) -> str:
        return self.log(
            message,
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    ConsoleLogManager,
                ).options,
                log_level=logging.WARNING,
            ),
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    FileLogManager,
                ).options,
                log_level=logging.WARNING,
            ),
        )

    def log_error(self, message: str) -> str:
        return self.log(
            message,
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    ConsoleLogManager,
                ).options,
                log_level=logging.ERROR,
            ),
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    FileLogManager,
                ).options,
                log_level=logging.ERROR,
            ),
        )

    def log_critical(self, message: str) -> str:
        return self.log(
            message,
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    ConsoleLogManager,
                ).options,
                log_level=logging.CRITICAL,
            ),
            SingletonManager.get_singleton(
                LogOptionsManager
            ).generate_modified_defaults(
                SingletonManager.get_singleton(
                    FileLogManager,
                ).options,
                log_level=logging.CRITICAL,
            ),
        )

    def shutdown(self) -> bool:
        SingletonManager.get_singleton(
                    FileLogManager,
                ).shutdown()

        return True
