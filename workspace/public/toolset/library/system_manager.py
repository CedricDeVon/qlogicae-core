import os
import shlex
import subprocess
from pathlib import Path
from collections.abc import Sequence

from library import text_manager
from library.script_command import ScriptCommand


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

    def execute_command(
        self,
        command: str,
        output_type: ScriptCommand = ScriptCommand.SUBPROCESS,
    ) -> bool:
        if not command:
            raise ValueError("command cannot be empty")

        match output_type:
            case ScriptCommand.SHELL:
                return subprocess.run(
                    command,
                    encoding=text_manager.singleton.encoding,
                    check=True,
                    text=True,
                    shell=True,
                    capture_output=True,
                )

            case ScriptCommand.SUBPROCESS:                
                return subprocess.run(
                    shlex.split(command),
                    encoding=text_manager.singleton.encoding,
                    check=True,
                    text=True,
                    capture_output=True,
                )

        return True


singleton = SystemManager()

