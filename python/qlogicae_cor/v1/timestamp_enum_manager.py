from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.enum_conversion_value import (
    EnumConversionValue,
)
from qlogicae_cor.v1.timestamp import Timestamp
from qlogicae_cor.v1.timestamp_enum_manager_configurations import (
    TimestampEnumManagerConfigurations,
)


class TimestampEnumManager(AbstractManager[TimestampEnumManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TimestampEnumManagerConfigurations())

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
                    case Timestamp.ISO_DATE_STRING:
                        return "iso_date_string"

                    case Timestamp.ISO_FILESYSTEM_STRING:
                        return "iso_filesystem_string"

                    case _:
                        return "iso_date_string"

            case EnumConversionValue.ENUM:
                match input_type.lower():
                    case "local":
                        return Timestamp.ISO_DATE_STRING

                    case "iso_filesystem_string":
                        return Timestamp.ISO_FILESYSTEM_STRING

                    case _:
                        return Timestamp.NONE

            case _:
                return EnumConversionValue.NONE
