from typing import Any

from library.v1 import text_encoding_manager


class TextFileIoManager:
    def read_file(self, file: Any) -> str:
        return file.read() or {}

    def write_file(self, file: Any, data: Any) -> bool:
        Path(file).write_text(str(data), encoding=text_encoding_manager.singleton.file_encoding)

        return True


singleton = TextFileIoManager()
