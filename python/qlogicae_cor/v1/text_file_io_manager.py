from pathlib import Path
from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.text_encoding_manager import (
    TextEncodingManager,
)
from qlogicae_cor.v1.text_file_io_manager_configurations import (
    TextFileIoManagerConfigurations,
)


class TextFileIoManager(AbstractManager[TextFileIoManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TextFileIoManagerConfigurations())

    def read_file(self, file_path: str) -> str:
        path = Path(file_path)
        output_data = ""
        with path.open(
            mode="r",
            encoding=SingletonManager.get_singleton(
                TextEncodingManager
            ).selected_encoding,
        ) as file:
            output_data = file.read() or ""

        return output_data

    def write_file(self, file_path: str, data: Any) -> bool:
        path = Path(file_path)
        path.parent.mkdir(
            parents=True,
            exist_ok=True,
        )
        with path.open(
            mode="w",
            encoding=SingletonManager.get_singleton(
                TextEncodingManager
            ).selected_encoding,
        ) as file:
            file.write(
                str(data)
            )

        return True
