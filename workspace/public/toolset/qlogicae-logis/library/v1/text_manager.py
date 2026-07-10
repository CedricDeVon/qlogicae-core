from typing import Any


class TextManager:
    def __init__(self) -> None:
        self._valid_file_extensions: set[str] = {".txt"}

    @property
    def valid_file_extensions(self, file: Any) -> bool:
        return self._valid_file_extensions

    def is_valid_file_extensions(self, file: Any) -> bool:
        return any(
            suffix in self._valid_file_extensions
            for suffix in self._valid_file_extensions
        )


singleton = TextManager()
