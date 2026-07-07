from datetime import UTC

from library import (
    time_manager,
    macros_manager,
    timestamp_manager,
    value_cache_manager,
    time_zone_enum_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceValueCacheManager:
    def setup_pre_macros(self) -> bool:
        time_manager.singleton.current_time_zone = (
            time_zone_enum_manager.singleton.convert_from_string_to_timezone(
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "time",
                        "zone",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or UTC
            )
        )

        value_cache_manager.singleton.set_one_value(
            ["current-date"], time_manager.singleton.current_iso8601_date
        )

        value_cache_manager.singleton.set_one_value(
            ["current-year"], time_manager.singleton.current_year
        )

        return True

    def setup_post_macros(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["timestamp-execution-start"],
            timestamp_manager.singleton.current_standard_timestamp,
        )

        value_cache_manager.singleton.set_one_value(
            ["default-workspace-selections"],
            set(
                key
                for key, value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "selection",
                            "default",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                ).items()
            ),
        )

        value_cache_manager.singleton.set_one_value(
            ["project-workspace-selections"],
            set(
                key
                for key, value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "selection",
                            "project",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                ).items()
            ),
        )

        value_cache_manager.singleton.set_one_value(
            ["workspace-selections"],
            set(
                value_cache_manager.singleton.get_one_value(
                    ["default-workspace-selections"],
                    output_type=TargetCacheValue.ANY,
                )
                or {}
            )
            | set(
                value_cache_manager.singleton.get_one_value(
                    ["project-workspace-selections"],
                    output_type=TargetCacheValue.ANY,
                )
                or {}
            ),
        )

        value_cache_manager.singleton.set_one_value(
            ["clean-include-selections"],
            {
                value
                for value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "script",
                            "clean",
                            "include",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                )
            },
        )

        value_cache_manager.singleton.set_one_value(
            ["script-selections"],
            {
                key
                for key, value in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "script",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                ).items()
            },
        )

        value_cache_manager.singleton.set_one_value(
            ["clean-exclude-selections"],
            {
                macros_manager.singleton.parse_one(
                    item["name"],
                    (
                        value_cache_manager.singleton.get_one_value(
                            ["workspace-macros"],
                            output_type=TargetCacheValue.ANY,
                        )
                        or {}
                    ),
                )
                for item in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "script",
                            "clean",
                            "exclude",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or []
                )
            },
        )

        value_cache_manager.singleton.set_one_value(
            ["log-file-targets"],
            {
                macros_manager.singleton.parse_one(
                    item["name"],
                    (
                        value_cache_manager.singleton.get_one_value(
                            ["workspace-macros"],
                            output_type=TargetCacheValue.ANY,
                        )
                        or {}
                    ),
                )
                for item in (
                    value_cache_manager.singleton.get_one_value(
                        [
                            "workspace/public/configuration/workspace.yaml-raw",
                            "data",
                            "log",
                            "file",
                            "targets",
                        ],
                        output_type=TargetCacheValue.ANY,
                    )
                    or []
                )
            },
        )

        return True

    def shutdown(self) -> bool:
        return True


singleton = WorkspaceValueCacheManager()
