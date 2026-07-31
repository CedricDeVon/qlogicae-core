from __future__ import annotations

from typing import TYPE_CHECKING, Any

if TYPE_CHECKING:
    from qlogicae_cor.v1.enum_conversion_value import EnumConversionValue

_datetime: Any = None
_UTC: Any = None
_enum_conversion_value: Any = None
_time_zone: Any = None


def _handle_dynamic_imports() -> None:
    global _handle_dynamic_imports
    global _datetime
    global _UTC
    global _enum_conversion_value
    global _time_zone

    from datetime import UTC, datetime

    import qlogicae_cor.v1.enum_conversion_value
    import qlogicae_cor.v1.time_zone

    _datetime = datetime
    _UTC = UTC
    _enum_conversion_value = (
        qlogicae_cor.v1.enum_conversion_value
    )
    _time_zone = (
        qlogicae_cor.v1.time_zone
    )

    _handle_dynamic_imports = lambda: None


class TimeZoneEnumManager:
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
                    case _time_zone.TimeZone.LOCAL:
                        return "local"

                    case _time_zone.TimeZone.UTC:
                        return "utc"

                    case _time_zone.TimeZone.CUSTOM:
                        return "custom"

                    case _:
                        return "local"

            case _enum_conversion_value.EnumConversionValue.ENUM:
                match str(input_type).lower():
                    case "local":
                        return _time_zone.TimeZone.LOCAL

                    case "utc":
                        return _time_zone.TimeZone.UTC

                    case "custom":
                        return _time_zone.TimeZone.CUSTOM

                    case _:
                        return _time_zone.TimeZone.LOCAL

            case _enum_conversion_value.EnumConversionValue.CUSTOM:
                match str(input_type).lower():
                    case "local":
                        return _datetime.now().astimezone().tzinfo

                    case "utc":
                        return _UTC

                    case "custom":
                        return _datetime.now().astimezone().tzinfo

                    case _:
                        return _datetime.now().astimezone().tzinfo

            case _:
                return _enum_conversion_value.EnumConversionValue.NONE
