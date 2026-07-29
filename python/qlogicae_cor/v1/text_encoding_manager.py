from qlogicae_logis.v1.text_encoding_manager_configurations import (
    TextEncodingManagerConfigurations,
)

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)


class TextEncodingManager(AbstractManager[TextEncodingManagerConfigurations]):
    __slots__ = (
        "_selected_encoding",
    )

    def __init__(self) -> None:
        super().__init__(TextEncodingManagerConfigurations())

        self._selected_encoding: str = "utf-8"

    @property
    def selected_encoding(self) -> str:
        return self._selected_encoding
