from typing import Any

from library.script_process import ScriptProcess
from library.enum_conversion_output import EnumConversionOutput


class ScriptProcessEnumManager:
    def convert_value(
        self, value, conversion_output_type=EnumConversionOutput.STRING
    ) -> Any:
        match conversion_output_type:
            case EnumConversionOutput.STRING:
                return self.convert_from_enum_to_string(value)

            case EnumConversionOutput.ENUM:
                return self.convert_from_string_to_enum(value)

            case _:
                return EnumConversionOutput.NONE

    def convert_from_enum_to_string(self, value):
        match value:
            case ScriptProcess.SHELL:
                return "shell"

            case ScriptProcess.SUBPROCESS:
                return "subprocess"

            case _:
                return "none"

    def convert_from_string_to_enum(self, value):
        match value.lower():
            case "shell":
                return ScriptProcess.SHELL

            case "subprocess":
                return ScriptProcess.SUBPROCESS

            case _:
                return ScriptProcess.NONE


singleton = ScriptProcessEnumManager()
