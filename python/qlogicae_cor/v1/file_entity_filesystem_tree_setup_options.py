from dataclasses import dataclass

from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.text_encoding_manager import TextEncodingManager


@dataclass(frozen=True, slots=True)
class FileEntityFileSystemTreeSetupOptions:
    content: str = "data"
    name: str = "file"
    encoding: str = SingletonManager.get_singleton(
        TextEncodingManager,
    ).selected_encoding
    is_modifiable: bool = False
