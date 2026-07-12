import shlex
import subprocess

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1 import text_encoding_manager
from qlogicae_logis.v1.script_process import ScriptProcess
from qlogicae_logis.v1.script_process_manager_configurations import (
    ScriptProcessManagerConfigurations,
)


class ScriptProcessManager(AbstractManager[ScriptProcessManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(ScriptProcessManagerConfigurations())

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
