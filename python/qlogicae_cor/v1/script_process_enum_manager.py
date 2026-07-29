from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.enum_conversion_value import (
    EnumConversionValue,
)
from qlogicae_cor.v1.script_process import (
    ScriptProcess,
)
from qlogicae_cor.v1.script_process_enum_manager_configurations import (
    ScriptProcessEnumManagerConfigurations,
)


class ScriptProcessEnumManager(AbstractManager[ScriptProcessEnumManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(ScriptProcessEnumManagerConfigurations())

    def convert_value(
        self,
        input_type: Any,
        output_type: EnumConversionValue = (
            EnumConversionValue.STRING
        ),
    ) -> Any:
        match output_type:
            case EnumConversionValue.STRING:
                match input_type:
                    case ScriptProcess.SHELL:
                        return "shell"

                    case ScriptProcess.SUBPROCESS:
                        return "subprocess"

                    case _:
                        return "none"

            case EnumConversionValue.ENUM:
                match input_type.lower():
                    case "shell":
                        return ScriptProcess.SHELL

                    case "subprocess":
                        return ScriptProcess.SUBPROCESS

                    case _:
                        return ScriptProcess.SUBPROCESS

            case _:
                return EnumConversionValue.NONE
