from typing import Any

from library.enum_conversion_output import EnumConversionOutput


class EnumConversionOutputEnumManager:
    def convert_value(
        self, value, conversion_output_type=EnumConversionOutput.STRING
    ) -> Any:
        match conversion_output_type:
            case EnumConversionOutput.STRING:
                match value:
                    case EnumConversionOutput.STRING:
                        return "string"

                    case EnumConversionOutput.ENUM:
                        return "enum"

                    case EnumConversionOutput.CUSTOM:
                        return "custom"

                    case _:
                        return "none"

            case EnumConversionOutput.ENUM:
                match value.lower():
                    case "string":
                        return EnumConversionOutput.STRING

                    case "none":
                        return EnumConversionOutput.ENUM

                    case "custom":
                        return EnumConversionOutput.CUSTOM

                    case _:
                        return EnumConversionOutput.NONE

            case _:
                return EnumConversionOutput.NONE


singleton = EnumConversionOutputEnumManager()
