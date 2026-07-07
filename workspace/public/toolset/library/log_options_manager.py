import logging

from library.log_options import LogOptions


class LogOptionsManager:
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
