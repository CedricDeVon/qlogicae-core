import os
from pathlib import Path


class SystemManager:
    def change_cli_filesystem_path(
        self,
        value: str,
    ) -> bool:
        path = Path(value).expanduser().resolve()

        if not path.exists():
            raise Exception(
                f"directory '{path}' does not exist.",
            )

        if not path.is_dir():
            raise Exception(
                f"'{path}' is not a directory.",
            )

        os.chdir(path)

        return True


singleton = SystemManager()
