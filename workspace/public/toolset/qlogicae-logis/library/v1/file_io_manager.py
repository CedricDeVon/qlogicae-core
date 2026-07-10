from pathlib import Path
from typing import Any

from library.v1 import text_encoding_manager


class FileIoManager:
    @property
    def file_encoding(self) -> str:
        return text_encoding_manager.singleton.encoding

    def read_file(self, file: Any) -> str:
        return file.read() or {}

    def write_file(self, file: Any, data: Any) -> bool:
        Path(file).write_text(str(data), encoding=self.file_encoding)

        return True


singleton = FileIoManager()
