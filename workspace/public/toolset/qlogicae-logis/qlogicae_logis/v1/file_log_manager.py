import logging
import queue
from logging.handlers import QueueHandler, QueueListener
from pathlib import Path

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import file_io_manager, log_options_manager
from qlogicae_logis.v1.file_log_manager_configurations import FileLogManagerConfigurations
from qlogicae_logis.v1.log_format import LogFormat
from qlogicae_logis.v1.log_options import LogOptions


class FileLogManager(AbstractManager[FileLogManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(FileLogManagerConfigurations())

        self.logger = logging.getLogger("file-logger")

        self.logger.setLevel(logging.DEBUG)

        self.logger.propagate = False

        self.logger.handlers.clear()

        self.file_handlers = {}

        self.log_queue = queue.Queue()

        self.queue_handler = QueueHandler(self.log_queue)

        self.logger.addHandler(self.queue_handler)

        self.listener = QueueListener(self.log_queue)

        self.listener.start()

        self._options = LogOptions()

    @property
    def options(self) -> LogOptions:
        return self._options

    @options.setter
    def options(self, value) -> bool:
        self._options = value

        return True

    def log(self, message: str, options: LogOptions) -> str:
        if not options.is_enabled:
            return message

        if options.is_verbose_enabled:
            self.logger.log(
                options.log_level,
                str(message).strip(),
                stacklevel=options.stack_level,
            )

        else:
            for current_file_path in self.file_handlers:
                with Path.open(
                    current_file_path,
                    "a",
                    encoding=file_io_manager.singleton.file_encoding,
                ) as file:
                    file.write(f"{str(message).strip()}\n")

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

    def rebuild_listener(self) -> bool:
        self.listener.stop()

        self.listener = QueueListener(self.log_queue, *self.file_handlers.values())

        self.listener.start()

        return True

    def add_file_output(self, file_path: str) -> bool:
        path = Path(file_path).resolve()

        if path in self.file_handlers:
            return False

        path.parent.mkdir(parents=True, exist_ok=True)

        handler = logging.FileHandler(
            path, encoding=file_io_manager.singleton.file_encoding
        )

        handler.setFormatter(LogFormat())

        self.file_handlers[path] = handler

        self.rebuild_listener()

        return True

    def remove_file_output(self, file_path: str) -> bool:
        path = Path(file_path).resolve()

        handler = self.file_handlers.get(path)

        if handler is None:
            return False

        handler.close()

        del self.file_handlers[path]

        self.rebuild_listener()

        return True

    def clear_file_outputs(self) -> bool:
        for handler in self.file_handlers.values():
            handler.close()

        self.file_handlers.clear()

        self.rebuild_listener()

        return True

    def shutdown(self) -> bool:
        self.listener.stop()

        for handler in self.file_handlers.values():
            handler.close()

        self.file_handlers.clear()

        return True


singleton = FileLogManager()
