from library.script_command import ScriptCommand


class ScriptCommandEnumManager:
    def convert_from_enum_to_string(self, value):
        match value:
            case ScriptCommand.SHELL:
                return "shell"

            case ScriptCommand.SUBPROCESS:
                return "subprocess"

            case _:
                return "none"

    def convert_from_string_to_enum(self, value):
        match value.lower():
            case "shell":
                return ScriptCommand.SHELL

            case "subprocess"
                return ScriptCommand.SUBPROCESS

            case _:
                return ScriptCommand.NONE
                
                
singleton = ScriptCommandEnumManager()
