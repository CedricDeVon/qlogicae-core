from library.time_unit import TimeUnit


class TimeUnitEnumManager:
    def convert_from_enum_to_string(
        self,
        value: TimeUnit,
    ) -> str:
        match value:
            case TimeUnit.NANOSECOND:
                return "nanosecond"
            
            case TimeUnit.MICROSECOND:
                return "microsecond"
            
            case TimeUnit.MILLISECOND:
                return "millisecond"
            
            case TimeUnit.SECOND:
                return "second"
            
            case TimeUnit.MINUTE:
                return "minute"
            
            case TimeUnit.HOUR:
                return "hour"
            
            case TimeUnit.DAY:
                return "day"
            
            case TimeUnit.WEEK:
                return "week"
            
            case TimeUnit.MONTH:
                return "month"
            
            case TimeUnit.YEAR:
                return "year"
            
            case TimeUnit.DECADE:
                return "decade"
            
            case TimeUnit.CENTURY:
                return "century"
            
            case TimeUnit.MILLENIUM:
                return "millenium"

            case _:
                return "none"

    def convert_from_string_to_enum(
        self,
        value: str,
    ) -> TimeUnit:
        match value.lower():
            case "nanosecond":
                return TimeUnit.NANOSECOND
            
            case "microsecond":
                return TimeUnit.MICROSECOND
            
            case "millisecond":
                return TimeUnit.MILLISECOND
            
            case "second":
                return TimeUnit.SECOND
            
            case "minute":
                return TimeUnit.MINUTE
            
            case "hour":
                return TimeUnit.HOUR
            
            case "day":
                return TimeUnit.DAY
            
            case "week":
                return TimeUnit.WEEK
            
            case "month":
                return TimeUnit.MONTH
            
            case "year":
                return TimeUnit.YEAR
            
            case "decade":
                return TimeUnit.DECADE
            
            case "century":
                return TimeUnit.CENTURY
            
            case "millenium":
                return TimeUnit.MILLENIUM
            
            case _:
                return TimeUnit.NONE


singleton = TimeUnitEnumManager()
