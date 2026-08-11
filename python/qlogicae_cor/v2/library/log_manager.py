from __future__ import annotations

__all__ = (
    "LogManager",
)

from typing import TYPE_CHECKING, Any

if TYPE_CHECKING:
    from .log_options import (
        LogOptions,
    )

_logging: Any = None
_ConsoleLogManager: Any = None
_FileLogManager: Any = None
_LogOptionsManager: Any = None
_SingletonManager: Any = None


def _handle_dynamic_imports() -> None:
    global _handle_dynamic_imports
    global _logging
    global _ConsoleLogManager
    global _FileLogManager
    global _LogOptionsManager
    global _SingletonManager

    import logging

    from .console_log_manager import (
        ConsoleLogManager,
    )
    from .file_log_manager import (
        FileLogManager,
    )
    from .log_options_manager import (
        LogOptionsManager,
    )
    from .singleton_manager import (
        SingletonManager,
    )

    _logging = logging
    _ConsoleLogManager = ConsoleLogManager
    _FileLogManager = FileLogManager
    _LogOptionsManager = LogOptionsManager
    _SingletonManager = SingletonManager

    _handle_dynamic_imports = lambda: None


class LogManager:
    def __init__(self) -> None:
        _handle_dynamic_imports()

    def log(
        self,
        message: str,
        console_options: LogOptions,
        file_options: LogOptions,
    ) -> str:
        _SingletonManager.get_singleton(
            _ConsoleLogManager,
        ).log(
            message,
            console_options,
        )

        _SingletonManager.get_singleton(
            _FileLogManager,
        ).log(
            message,
            file_options,
        )

        return message

    def log_debug(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _ConsoleLogManager,
                ).options,
                log_level=_logging.DEBUG,
            ),
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _FileLogManager,
                ).options,
                log_level=_logging.DEBUG,
            ),
        )

    def log_info(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _ConsoleLogManager,
                ).options,
                log_level=_logging.INFO,
            ),
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _FileLogManager,
                ).options,
                log_level=_logging.INFO,
            ),
        )

    def log_warning(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _ConsoleLogManager,
                ).options,
                log_level=_logging.WARNING,
            ),
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _FileLogManager,
                ).options,
                log_level=_logging.WARNING,
            ),
        )

    def log_error(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _ConsoleLogManager,
                ).options,
                log_level=_logging.ERROR,
            ),
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _FileLogManager,
                ).options,
                log_level=_logging.ERROR,
            ),
        )

    def log_critical(
        self,
        message: str,
    ) -> str:
        return self.log(
            message,
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _ConsoleLogManager,
                ).options,
                log_level=_logging.CRITICAL,
            ),
            _SingletonManager.get_singleton(
                _LogOptionsManager,
            ).generate_modified_defaults(
                _SingletonManager.get_singleton(
                    _FileLogManager,
                ).options,
                log_level=_logging.CRITICAL,
            ),
        )

    def shutdown(self) -> bool:
        _SingletonManager.get_singleton(
            _FileLogManager,
        ).shutdown()

        return True
