from dataclasses import dataclass

from qlogicae_logis.v1 import file_io_manager


@dataclass(frozen=True, slots=True)
class FileEntityFileSystemTreeSetupOptions:
    content: str = "data"
    name: str = "file"
    encoding: str = file_io_manager.singleton.file_encoding
    is_modifiable: bool = False
