from typing import Any

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.text_manager_configurations import TextManagerConfigurations


class TextManager(AbstractManager[TextManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TextManagerConfigurations())

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
