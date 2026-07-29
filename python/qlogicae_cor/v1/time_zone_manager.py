from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.enum_conversion_value import (
    EnumConversionValue,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)
from qlogicae_cor.v1.time_zone_enum_manager import (
    TimeZoneEnumManager,
)
from qlogicae_cor.v1.time_zone_manager_configurations import (
    TimeZoneManagerConfigurations,
)


class TimeZoneManager(AbstractManager[TimeZoneManagerConfigurations]):
    __slots__ = (
        "_selected_time_zone_type",
        "_valid_time_zone_types"
    )

    def __init__(self) -> None:
        super().__init__(TimeZoneManagerConfigurations())

        self._selected_time_zone_type: str = "local"
        self._valid_time_zone_types: set[str] = {
            "local",
            "utc"
        }

    @property
    def selected_time_zone_type(self) -> str:
        return self._selected_time_zone_type

    @selected_time_zone_type.setter
    def selected_time_zone_type(self, value: str) -> None:
        if value not in self._valid_time_zone_types:
            raise ValueError(
                "time zones must include the followwing: "
                f"{self._valid_time_zone_types}"
            )

        self._selected_time_zone_type = value

    @property
    def selected_time_zone(self) -> Any:
        return SingletonManager.get_singleton(
                TimeZoneEnumManager
            ).convert_value(
                self._selected_time_zone_type,
                EnumConversionValue.CUSTOM,
            )
