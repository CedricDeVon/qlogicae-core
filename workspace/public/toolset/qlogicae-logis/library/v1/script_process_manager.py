import shlex
import subprocess

from library.v1 import text_encoding_manager
from library.v1.script_process import ScriptProcess


class ScriptProcessManager:
    def execute_command(
        self,
        command: str,
        script_process_type: ScriptProcess = ScriptProcess.SUBPROCESS,
    ) -> str:
        if not command:
            raise Exception("commands cannot be empty")

        match script_process_type:
            case ScriptProcess.SHELL:
                return subprocess.run(
                    command,
                    encoding=text_encoding_manager.singleton.encoding,
                    text=True,
                    shell=True,
                )

            case ScriptProcess.SUBPROCESS:
                return subprocess.run(
                    shlex.split(command),
                    encoding=text_encoding_manager.singleton.encoding,
                    text=True,
                )

            case _:
                return ""


singleton = ScriptProcessManager()
