from library import (
    time_manager,
    macros_manager,
    value_cache_manager,
    workspace_filesystem_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceValueCacheManager:
    @property
    def current_root_full_path(self) -> str:
        return value_cache_manager.singleton.get_one_value(
            ["current-root-full-path"],
            output_type=TargetCacheValue.FOLDER_PATH,
        )

    def setup_pre_macros(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["current-date"],
            time_manager.singleton.current_iso8601_date,
        )

        value_cache_manager.singleton.set_one_value(
            ["current-year"],
            time_manager.singleton.current_year,
        )

        value_cache_manager.singleton.set_one_value(
            ["default-workspace-selections"],
            set(
                key
                for key, value in (value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "selection",
                        "default",
                        "targets",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or {}).items()
            ),
        )

        value_cache_manager.singleton.set_one_value(
            ["project-workspace-selections"],
            set(
                key
                for key, value in (value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "selection",
                        "project",
                        "targets",
                    ],
                    output_type=TargetCacheValue.ANY,
                )
                or {}).items()
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
            ["default-workspace-selection"],
            value_cache_manager.singleton.get_one_value(
                [
                    "workspace/public/configuration/workspace.yaml-raw",
                    "data",
                    "selection",
                    "default",
                    "name",
                ],
                output_type=TargetCacheValue.ANY,
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

        return True

    def setup_post_macros(self) -> bool:
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
            ["log-targets"],
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
