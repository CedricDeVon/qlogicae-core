import shlex
import subprocess

from library import text_manager, script_proccess_enum_manager
from library.script_proccess import ScriptProcess


class ScriptProcessManager:
    def __init__(self):
        self._default_script_proccess: ScriptProcess = ScriptProcess.SUBPROCESS

    @property
    def script_proccess_string(self) -> str:
        return (
            script_proccess_enum_manager.singleton.convert_from_enum_to_string(
                self._default_script_proccess
            )
        )

    @property
    def script_proccess_enum(self) -> str:
        return (
            script_proccess_enum_manager.singleton.convert_from_string_to_enum(
                self.script_proccess_string
            )
        )

    def execute_command(
        self,
        command: str,
        script_proccess_type: ScriptProcess = ScriptProcess.SUBPROCESS,
    ) -> bool:
        if not command:
            raise ValueError("command cannot be empty")

        match script_proccess_type:
            case ScriptProcess.SHELL:
                return subprocess.run(
                    command,
                    encoding=text_manager.singleton.encoding,
                    check=True,
                    text=True,
                    shell=True,
                    capture_output=True,
                )

            case ScriptProcess.SUBPROCESS:
                return subprocess.run(
                    shlex.split(command),
                    encoding=text_manager.singleton.encoding,
                    check=True,
                    text=True,
                    capture_output=True,
                )

        return True


singleton = ScriptProcessManager()
