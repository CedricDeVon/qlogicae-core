import logging

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.log_options import LogOptions
from qlogicae_logis.v1.log_options_manager_configurations import (
    LogOptionsManagerConfigurations,
)


class LogOptionsManager(AbstractManager[LogOptionsManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(LogOptionsManagerConfigurations())

    def generate_modified_defaults(
        self, default_log_options, log_level=logging.DEBUG
    ) -> LogOptions:
        return LogOptions(
            is_enabled=default_log_options.is_enabled,
            is_verbose_enabled=default_log_options.is_verbose_enabled,
            log_level=log_level,
            stack_level=default_log_options.stack_level,
        )


singleton = LogOptionsManager()
