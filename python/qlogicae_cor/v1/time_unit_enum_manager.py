from __future__ import annotations

from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.enum_conversion_value import (
    EnumConversionValue,
)
from qlogicae_cor.v1.time_unit import (
    TimeUnit,
)
from qlogicae_cor.v1.time_unit_enum_manager_configurations import (
    TimeUnitEnumManagerConfigurations,
)


class TimeUnitEnumManager(AbstractManager[TimeUnitEnumManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(TimeUnitEnumManagerConfigurations())

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

                    case TimeUnit.MILLENNIUM:
                        return "millennium"

                    case _:
                        return "none"

            case EnumConversionValue.ENUM:
                match input_type.lower():
                    case "nanosecond":
                        return TimeUnit.NANOSECOND

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

                    case "millennium":
                        return TimeUnit.MILLENNIUM

                    case "ns":
                        return TimeUnit.NANOSECOND

                    case "us":
                        return TimeUnit.MICROSECOND

                    case "ms":
                        return TimeUnit.MILLISECOND

                    case "sec":
                        return TimeUnit.SECOND

                    case "min":
                        return TimeUnit.MINUTE

                    case "hr":
                        return TimeUnit.HOUR

                    case "d":
                        return TimeUnit.DAY

                    case "wk":
                        return TimeUnit.WEEK

                    case "mon":
                        return TimeUnit.MONTH

                    case "yr":
                        return TimeUnit.YEAR

                    case "deca":
                        return TimeUnit.DECADE

                    case "cen":
                        return TimeUnit.CENTURY

                    case "mil":
                        return TimeUnit.MILLENNIUM

                    case _:
                        return TimeUnit.NONE

            case _:
                return EnumConversionValue.NONE

