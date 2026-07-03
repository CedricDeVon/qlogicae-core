import json
from typing import Any


class TextFileIoManager:
    def is_valid(self, file: Any) -> bool:
        return any(
            suffix in {".txt"}
            for suffix in file.suffixes
        )

    def read(self, file: Any) -> int:
        return file.read() or {}


singleton = TextFileIoManager()
