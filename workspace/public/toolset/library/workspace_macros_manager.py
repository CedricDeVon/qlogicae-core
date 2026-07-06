from library import (
    macros_manager,
    value_cache_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceMacrosManager:
    def setup(self) -> bool:

        value_cache_manager.singleton.set_one_value(
            ["workspace-macros"],
            macros_manager.singleton.resolve_many(
                {
                    item["name"]: f"{value_cache_manager.singleton.get_one_value(
                        [
                            item["name"]
                        ],
                        output_type=TargetCacheValue.ANY,
                    )}"
                    for item in (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/private/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "value-cache",
                                "targets"
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    ) + (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/public/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "value-cache",
                                "targets"
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    )
                } |
                {
                    item["name"]: f"{item["value"]}"
                    for item in (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/private/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "file",
                                "targets"
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    ) + (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/public/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "file",
                                "targets"
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or []
                    )
                }
            )
            or {},
            output_type=TargetCacheValue.ANY,
        )

        return True

    def shutdown(self) -> bool:
        return True


singleton = WorkspaceMacrosManager()

