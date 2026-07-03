import yaml
from typing import Any


class YamlFileIoManager:
    def is_valid(self, file: Any) -> bool:
        return any(
            suffix in {".yaml", ".yml"}
            for suffix in file.suffixes
        )

    def read(self, file: Any) -> int:
        return yaml.safe_load(current_file) or {}


singleton = YamlFileIoManager()
