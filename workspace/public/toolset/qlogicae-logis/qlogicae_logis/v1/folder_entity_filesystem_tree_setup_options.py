from dataclasses import dataclass, field


@dataclass(frozen=True, slots=True)
class FolderEntityFileSystemTreeSetupOptions:
    name: str = "folder"
    entities: list = field(default_factory=list)
