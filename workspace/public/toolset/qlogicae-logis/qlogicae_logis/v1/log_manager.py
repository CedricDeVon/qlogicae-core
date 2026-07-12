import logging

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import console_log_manager, file_log_manager, log_options_manager
from qlogicae_logis.v1.log_manager_configurations import LogManagerConfigurations
from qlogicae_logis.v1.log_options import LogOptions


class LogManager(AbstractManager[LogManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(LogManagerConfigurations())

    def log(
        self,
        message: str,
        console_options: LogOptions,
        file_options: LogOptions,
    ) -> str:
        console_log_manager.singleton.log(
            message,
            console_options,
        )
        file_log_manager.singleton.log(
            message,
            file_options,
        )

        return message

    def log_debug(self, message: str) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                console_log_manager.singleton.options,
                log_level=logging.DEBUG,
            ),
            log_options_manager.singleton.generate_modified_defaults(
                file_log_manager.singleton.options,
                log_level=logging.DEBUG,
            ),
        )

    def log_info(self, message: str) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                console_log_manager.singleton.options,
                log_level=logging.INFO,
            ),
            log_options_manager.singleton.generate_modified_defaults(
                file_log_manager.singleton.options,
                log_level=logging.INFO,
            ),
        )

    def log_warning(self, message: str) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                console_log_manager.singleton.options,
                log_level=logging.WARNING,
            ),
            log_options_manager.singleton.generate_modified_defaults(
                file_log_manager.singleton.options,
                log_level=logging.WARNING,
            ),
        )

    def log_error(self, message: str) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                console_log_manager.singleton.options,
                log_level=logging.ERROR,
            ),
            log_options_manager.singleton.generate_modified_defaults(
                file_log_manager.singleton.options,
                log_level=logging.ERROR,
            ),
        )

    def log_critical(self, message: str) -> str:
        return self.log(
            message,
            log_options_manager.singleton.generate_modified_defaults(
                console_log_manager.singleton.options,
                log_level=logging.CRITICAL,
            ),
            log_options_manager.singleton.generate_modified_defaults(
                file_log_manager.singleton.options,
                log_level=logging.CRITICAL,
            ),
        )

    def shutdown(self):
        file_log_manager.singleton.shutdown()

        return True


singleton = LogManager()
