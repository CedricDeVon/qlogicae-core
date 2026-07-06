from library.time_zone import TimeZone


class TimeZoneEnumManager:
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


singleton = TimeZoneEnumManager()
