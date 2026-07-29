from datetime import UTC, datetime
from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.enum_conversion_value import (
    EnumConversionValue,
)
from qlogicae_cor.v1.time_zone import TimeZone
from qlogicae_cor.v1.time_zone_enum_manager_configurations import (
    TimeZoneEnumManagerConfigurations,
)


class TimeZoneEnumManager(AbstractManager[TimeZoneEnumManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TimeZoneEnumManagerConfigurations())

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
                    case TimeZone.LOCAL:
                        return "local"

                    case TimeZone.UTC:
                        return "utc"

                    case TimeZone.CUSTOM:
                        return "custom"

                    case _:
                        return "local"

            case EnumConversionValue.ENUM:
                match input_type.lower():
                    case "local":
                        return TimeZone.LOCAL

                    case "utc":
                        return TimeZone.UTC

                    case "custom":
                        return TimeZone.CUSTOM

                    case _:
                        return TimeZone.LOCAL

            case EnumConversionValue.CUSTOM:
                match input_type.lower():
                    case "local":
                        return datetime.now().astimezone().tzinfo

                    case "utc":
                        return UTC

                    case "custom":
                        return datetime.now().astimezone().tzinfo

                    case _:
                        return datetime.now().astimezone().tzinfo

            case _:
                return EnumConversionValue.NONE
