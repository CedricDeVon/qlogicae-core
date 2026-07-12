from pathlib import Path
from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import text_encoding_manager
from qlogicae_logis.v1.text_file_io_manager_configurations import (
    TextFileIoManagerConfigurations,
)


class TextFileIoManager(AbstractManager[TextFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TextFileIoManagerConfigurations())

    def read_file(self, file: Any) -> str:
        return file.read() or {}

    def write_file(self, file: Any, data: Any) -> bool:
        Path(file).write_text(
            str(data), encoding=text_encoding_manager.singleton.file_encoding
        )

        return True


singleton = TextFileIoManager()
