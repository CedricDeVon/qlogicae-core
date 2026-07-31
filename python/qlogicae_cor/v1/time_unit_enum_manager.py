from __future__ import annotations

from typing import TYPE_CHECKING, Any

if TYPE_CHECKING:
    from qlogicae_cor.v1.enum_conversion_value import (
        EnumConversionValue,
    )

_enum_conversion_value: Any = None
_time_unit: Any = None


def _handle_dynamic_imports() -> None:
    global _handle_dynamic_imports
    global _enum_conversion_value
    global _time_unit

    import qlogicae_cor.v1.enum_conversion_value
    import qlogicae_cor.v1.time_unit

    _enum_conversion_value = (
        qlogicae_cor.v1.enum_conversion_value
    )
    _time_unit = (
        qlogicae_cor.v1.time_unit
    )

    _handle_dynamic_imports = lambda: None


class TimeUnitEnumManager:
    def __init__(self) -> None:
        _handle_dynamic_imports()

    def convert_value(
        self,
        input_type: object,
        output_type: EnumConversionValue | None = None,
    ) -> object:
        if output_type is None:
            output_type = _enum_conversion_value.STRING

        match output_type:
            case _enum_conversion_value.EnumConversionValue.STRING:
                match input_type:
                    case _time_unit.TimeUnit.NANOSECOND:
                        return "nanosecond"

                    case _time_unit.TimeUnit.MICROSECOND:
                        return "microsecond"

                    case _time_unit.TimeUnit.MILLISECOND:
                        return "millisecond"

                    case _time_unit.TimeUnit.SECOND:
                        return "second"

                    case _time_unit.TimeUnit.MINUTE:
                        return "minute"

                    case _time_unit.TimeUnit.HOUR:
                        return "hour"

                    case _time_unit.TimeUnit.DAY:
                        return "day"

                    case _time_unit.TimeUnit.WEEK:
                        return "week"

                    case _time_unit.TimeUnit.MONTH:
                        return "month"

                    case _time_unit.TimeUnit.YEAR:
                        return "year"

                    case _time_unit.TimeUnit.DECADE:
                        return "decade"

                    case _time_unit.TimeUnit.CENTURY:
                        return "century"

                    case _time_unit.TimeUnit.MILLENNIUM:
                        return "millennium"

                    case _:
                        return "none"

            case _enum_conversion_value.EnumConversionValue.ENUM:
                match str(input_type).lower():
                    case "nanosecond" | "ns":
                        return _time_unit.TimeUnit.NANOSECOND

                    case "microsecond" | "us":
                        return _time_unit.TimeUnit.MICROSECOND

                    case "millisecond" | "ms":
                        return _time_unit.TimeUnit.MILLISECOND

                    case "second" | "sec":
                        return _time_unit.TimeUnit.SECOND

                    case "minute" | "min":
                        return _time_unit.TimeUnit.MINUTE

                    case "hour" | "hr":
                        return _time_unit.TimeUnit.HOUR

                    case "day" | "d":
                        return _time_unit.TimeUnit.DAY

                    case "week" | "wk":
                        return _time_unit.TimeUnit.WEEK

                    case "month" | "mon":
                        return _time_unit.TimeUnit.MONTH

                    case "year" | "yr":
                        return _time_unit.TimeUnit.YEAR

                    case "decade" | "deca":
                        return _time_unit.TimeUnit.DECADE

                    case "century" | "cen":
                        return _time_unit.TimeUnit.CENTURY

                    case "millennium" | "mil":
                        return _time_unit.TimeUnit.MILLENNIUM

                    case _:
                        return _time_unit.TimeUnit.NONE

            case _:
                return _enum_conversion_value.EnumConversionValue.NONE
