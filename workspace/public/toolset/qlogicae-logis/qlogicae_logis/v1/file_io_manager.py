from pathlib import Path
from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import text_encoding_manager
from qlogicae_logis.v1.file_io_manager_configurations import FileIoManagerConfigurations


class FileIoManager(AbstractManager[FileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(FileIoManagerConfigurations())

    @property
    def file_encoding(self) -> str:
        return text_encoding_manager.singleton.encoding

    def read_file(self, file: Any) -> str:
        return file.read() or {}

    def write_file(self, file: Any, data: Any) -> bool:
        Path(file).write_text(str(data), encoding=self.file_encoding)

        return True


singleton = FileIoManager()
