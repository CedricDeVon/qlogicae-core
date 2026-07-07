from typing import Any
from datetime import datetime, UTC

from library.time_zone import TimeZone
from library.enum_conversion_output import EnumConversionOutput


class TimeZoneEnumManager:
    def convert_value(
        self, value, conversion_output_type=EnumConversionOutput.STRING
    ) -> Any:
        match conversion_output_type:
            case EnumConversionOutput.STRING:
                return self.convert_from_enum_to_string(value)

            case EnumConversionOutput.ENUM:
                return self.convert_from_string_to_enum(value)

            case EnumConversionOutput.CUSTOM:
                return self.convert_from_string_to_timezone(value)

            case _:
                return EnumConversionOutput.NONE

    def convert_from_enum_to_string(
        self,
        value: TimeZone,
    ) -> str:
        match value:
            case TimeZone.UTC:
                return "utc"

            case TimeZone.LOCAL:
                return "local"

            case _:
                return "none"

    def convert_from_string_to_enum(
        self,
        value: str,
    ) -> TimeZone:
        match value.lower():
            case "utc":
                return TimeZone.UTC

            case "local":
                return TimeZone.LOCAL

            case _:
                return TimeZone.NONE

    def convert_from_string_to_timezone(
        self,
        value: str,
    ) -> TimeZone:
        match value.lower():
            case "utc":
                return UTC

            case "local":
                return datetime.now().astimezone().tzinfo

            case _:
                return TimeZone.NONE


singleton = TimeZoneEnumManager()
