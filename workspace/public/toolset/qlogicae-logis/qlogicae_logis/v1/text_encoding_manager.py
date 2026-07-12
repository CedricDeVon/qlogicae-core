from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.text_encoding_manager_configurations import (
    TextEncodingManagerConfigurations,
)


class TextEncodingManager(AbstractManager[TextEncodingManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TextEncodingManagerConfigurations())

        self._encoding: str = "utf-8"

    @property
    def encoding(self) -> set[str]:
        return self._encoding


singleton = TextEncodingManager()
