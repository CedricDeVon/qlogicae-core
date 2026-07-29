from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.text_manager_configurations import (
    TextManagerConfigurations,
)


class TextManager(AbstractManager[TextManagerConfigurations]):
    __slots__ = (
        "_valid_file_extensions",
    )

    def __init__(self) -> None:
        super().__init__(TextManagerConfigurations())

        self._valid_file_extensions: set[str] = {".txt"}

    @property
    def valid_file_extensions(self) -> set[str]:
        return self._valid_file_extensions

    def is_valid(self, file_path: Any) -> bool:
        if file_path.suffix.lower() not in self.valid_file_extensions:
            return False

        return True

