import shlex
import subprocess
from subprocess import CompletedProcess

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.script_process import (
    ScriptProcess,
)
from qlogicae_cor.v1.script_process_manager_configurations import (
    ScriptProcessManagerConfigurations,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.text_encoding_manager import (
    TextEncodingManager,
)


class ScriptProcessManager(AbstractManager[ScriptProcessManagerConfigurations]):
    __slots__ = (
        "_selected_script_process",
        "_valid_script_processes",
    )

    def __init__(self) -> None:
        super().__init__(ScriptProcessManagerConfigurations())

        self._selected_script_process: str = "shell"
        self._valid_script_processes: set[str] = { "shell", "subprocess" }

    @property
    def selected_script_process(self) -> str:
        return self._selected_script_process

    @selected_script_process.setter
    def selected_script_process(self, value: str) -> None:
        if value not in self._valid_script_processes:
            return

        self._selected_script_process = value

    @property
    def valid_script_processes(self) -> set[str]:
        return self._valid_script_processes


    def execute_command(
        self,
        command: str,
        script_process_type: ScriptProcess = ScriptProcess.SUBPROCESS,
    ) -> CompletedProcess[str]:
        if not command:
            raise ValueError("commands cannot be empty")

        match script_process_type:
            case ScriptProcess.SHELL:
                return subprocess.run(
                    command,
                    encoding=SingletonManager.get_singleton(
                        TextEncodingManager
                    ).selected_encoding,
                    text=True,
                    shell=True,
                )

            case ScriptProcess.SUBPROCESS:
                return subprocess.run(
                    shlex.split(command),
                    encoding=SingletonManager.get_singleton(
                        TextEncodingManager
                    ).selected_encoding,
                    text=True,
                )

            case _:
                raise ValueError("unsupported script process value")
