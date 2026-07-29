from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.enum_conversion_value import (
    EnumConversionValue,
)
from qlogicae_cor.v1.enum_conversion_value_enum_manager_configurations import (
    EnumConversionValueEnumManagerConfigurations,
)


class EnumConversionValueEnumManager(
    AbstractManager[EnumConversionValueEnumManagerConfigurations]
):
    def __init__(self) -> None:
        super().__init__(EnumConversionValueEnumManagerConfigurations())

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
                    case EnumConversionValue.STRING:
                        return "string"

                    case EnumConversionValue.ENUM:
                        return "enum"

                    case EnumConversionValue.CUSTOM:
                        return "custom"

                    case _:
                        return "none"

            case EnumConversionValue.ENUM:
                match input_type.lower():
                    case "string":
                        return EnumConversionValue.STRING

                    case "none":
                        return EnumConversionValue.ENUM

                    case "custom":
                        return EnumConversionValue.CUSTOM

                    case _:
                        return EnumConversionValue.NONE

            case _:
                return EnumConversionValue.NONE

