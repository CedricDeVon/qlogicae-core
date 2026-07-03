from pathlib import Path
from collections.abc import Callable

from library import (
    file_log_manager,
    filesystem_manager,
    log_manager,
    macros_manager,
    system_manager,
    value_cache_manager,
    file_io_manager,
    yaml_file_io_manager,
    json_file_io_manager,
    text_file_io_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceManager:
    def __init__(self) -> None:
        self._scope_selections: set[str] = {"private", "public"}

    @property
    def scope_selections(self) -> set[str]:
        return self._scope_selections

    def handle_read_file(self, file: Any) -> Any:
        if yaml_file_io_manager.singleton.is_valid(file):
            return yaml_file_io_manager.singleton.read_file(file)

        elif json_file_io_manager.singleton.is_valid(file):
            return json_file_io_manager.singleton.read_file(file)

        else:
            return text_file_io_manager.singleton.read_file(file)

    def throw_if_required_files_not_found(self) -> bool:
        if not filesystem_manager.singleton.is_file_path_valid(
            "workspace/public/configuration/workspace.yaml"
        ):
            raise Exception(
                "workspace/public/configuration/workspace.yaml' must exist"
            )

        if not filesystem_manager.singleton.is_file_path_valid(
            "workspace/public/configuration/workspace.yaml"
        ):
            raise Exception(
                "workspace/public/configuration/workspace.yaml' must exist"
            )

        return False

    def handle(self, callback: Callable[[void], void]) -> bool:
        try:
            self.handle_setup()

            callback()

            self.handle_shutdown()

            return True

        except Exception:
            raise Exception("'handle()' failed. check your logs")

            return False

    def handle_setup(self) -> bool:
        try:
            self.handle_value_cache_essential_setup()
            self.handle_initial_filesystem_path_setup()
            self.handle_value_cache_configuration_setup()
            self.handle_value_cache_macros_setup()
            self.handle_logger_setup()

            return True

        except Exception:
            raise Exception("'handle_setup()' failed. check your logs")

            return False

    def handle_shutdown(self) -> bool:
        try:
            log_manager.singleton.shutdown()

            return True

        except Exception:
            raise Exception("'handle_shutdown()' failed. check your logs")

            return False

    def handle_value_cache_essential_setup(self) -> bool:
        try:
            value_cache_manager.singleton.set_one_value(
                ["current-root-full-path"],
                filesystem_manager.singleton.get_root_workspace_folder(),
                output_type=TargetCacheValue.FOLDER_PATH,
            )
            value_cache_manager.singleton.set_one_value(
                ["original-console-full-path"],
                filesystem_manager.singleton.get_cli_folder(),
                output_type=TargetCacheValue.FOLDER_PATH,
            )
            value_cache_manager.singleton.set_one_value(
                ["previous-console-full-path"],
                value_cache_manager.singleton.get_one_value(
                    ["original-console-full-path"],
                    output_type=TargetCacheValue.FOLDER_PATH,
                ),
                output_type=TargetCacheValue.FOLDER_PATH,
            )
            value_cache_manager.singleton.set_one_value(
                ["current-console-full-path"],
                value_cache_manager.singleton.get_one_value(
                    ["current-root-full-path"],
                    output_type=TargetCacheValue.FOLDER_PATH,
                ),
                output_type=TargetCacheValue.FOLDER_PATH,
            )

            return True

        except Exception:
            raise Exception(
                "'handle_value_cache_essential_setup()' failed. check your logs"
            )

            return False

    def handle_initial_filesystem_path_setup(self) -> bool:
        try:
            system_manager.singleton.change_cli_filesystem_path(
                value_cache_manager.singleton.get_one_value(
                    ["current-root-full-path"],
                    output_type=TargetCacheValue.FOLDER_PATH,
                )
            )

            return True

        except Exception:
            raise Exception(
                "'handle_initial_filesystem_path_setup()' failed. check your logs"
            )

            return False

    def handle_value_cache_configuration_setup(self) -> bool:
        try:
            for workspace_scope_name in self.scope_selections:
                for configuration_file in Path(
                    f"{
                        value_cache_manager.singleton.get_one_value(
                            ['current-root-full-path'],
                            output_type=TargetCacheValue.FOLDER_PATH,
                        )
                    }/workspace/{workspace_scope_name}/configuration"
                ).iterdir():
                    if not configuration_file.is_file():
                        continue

                    with open(
                        configuration_file.resolve(),
                        encoding=file_io_manager.singleton.file_encoding,
                    ) as current_file:
                        raw_data = self.handle_read_file(current_file)

                        value_cache_manager.singleton.set_one_value(
                            [
                                f"workspace/{workspace_scope_name}/configuration/{configuration_file.name}-raw"
                            ],
                            ({} if raw_data is None else raw_data) or {},
                            output_type=TargetCacheValue.DEFINED,
                        )
                        value_cache_manager.singleton.set_one_value(
                            [
                                f"workspace/{workspace_scope_name}/configuration/{configuration_file.name}-full-path"
                            ],
                            configuration_file.resolve(),
                            output_type=TargetCacheValue.FILE_PATH,
                        )

            return True

        except Exception:
            raise Exception(
                "'handle_value_cache_configuration_setup()' failed. check your logs"
            )

            return False

    def handle_value_cache_macros_setup(self) -> bool:
        try:
            value_cache_manager.singleton.set_one_value(
                ["default-workspace-selections"],
                set(
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
                    or []
                ),
            )

            value_cache_manager.singleton.set_one_value(
                ["project-workspace-selections"],
                set(
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
                    or []
                ),
            )

            value_cache_manager.singleton.set_one_value(
                ["workspace-selections"],
                set(
                    value_cache_manager.singleton.get_one_value(
                        ["default-workspace-selections"],
                        output_type=TargetCacheValue.ANY,
                    )
                    or []
                )
                | set(
                    value_cache_manager.singleton.get_one_value(
                        ["project-workspace-selections"],
                        output_type=TargetCacheValue.ANY,
                    )
                    or []
                ),
            )

            value_cache_manager.singleton.set_one_value(
                ["default-workspace-selection"],
                value_cache_manager.singleton.get_one_value(
                    [
                        "workspace/public/configuration/workspace.yaml-raw",
                        "data",
                        "selection",
                        "target",
                    ],
                    output_type=TargetCacheValue.ANY,
                ),
            )

            value_cache_manager.singleton.set_one_value(
                ["workspace-macros"],
                macros_manager.singleton.resolve_many(
                    {
                        key: f"{
                            value_cache_manager.singleton.get_one_value(
                                [key],
                                output_type=TargetCacheValue.DEFINED,
                            )
                        }"
                        for key in (
                            value_cache_manager.singleton.get_one_value(
                                [
                                    "workspace/private/configuration/workspace.yaml-raw",
                                    "data",
                                    "macros",
                                    "value-cache",
                                ],
                                output_type=TargetCacheValue.ANY,
                            )
                            or []
                        )
                        + (
                            value_cache_manager.singleton.get_one_value(
                                [
                                    "workspace/public/configuration/workspace.yaml-raw",
                                    "data",
                                    "macros",
                                    "value-cache",
                                ],
                                output_type=TargetCacheValue.ANY,
                            )
                            or []
                        )
                    }
                    | (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/private/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "file",
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or {}
                    )
                    | (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/public/configuration/workspace.yaml-raw",
                                "data",
                                "macros",
                                "file",
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or {}
                    )
                )
                or {},
                output_type=TargetCacheValue.ANY,
            )

            value_cache_manager.singleton.set_one_value(
                ["clean-exclude-selections"],
                {
                    self.handle_one_macros_string_parsing(value)
                    for value in (
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
                ["script-types"],
                {
                    key
                    for key in (
                        value_cache_manager.singleton.get_one_value(
                            [
                                "workspace/public/configuration/workspace.yaml-raw",
                                "data",
                                "script",
                                "types",
                            ],
                            output_type=TargetCacheValue.ANY,
                        )
                        or {}
                    )
                },
            )

            return True

        except Exception:
            raise Exception(
                "'handle_value_cache_macros_setup()' failed. check your logs"
            )

    def handle_logger_setup(self) -> bool:
        try:
            value_cache_manager.singleton.set_one_value(
                ["workspace/private/temporary/log/all.log-full-path"],
                f"{
                    value_cache_manager.singleton.get_one_value(
                        ['current-root-full-path'],
                        output_type=TargetCacheValue.DEFINED,
                    )
                }/workspace/private/temporary/log/all.log",
            )

            file_log_manager.singleton.add_file_output(
                value_cache_manager.singleton.get_one_value(
                    ["workspace/private/temporary/log/all.log-full-path"],
                    output_type=TargetCacheValue.DEFINED,
                )
            )

            return True

        except Exception:
            raise Exception("'handle_logger_setup()' failed. check your logs")

    def handle_one_macros_string_parsing(self, value: Any) -> Any:
        try:
            return macros_manager.singleton.parse_one(
                value,
                (
                    value_cache_manager.singleton.get_one_value(
                        ["workspace-macros"],
                        output_type=TargetCacheValue.ANY,
                    )
                    or {}
                ),
            )

        except Exception:
            raise Exception(
                "'handle_one_macros_string_parsing()' failed. check your logs"
            )

            return False

    def handle_cli_argument_set_invalid(self, cli_arguments: Any) -> bool:
        log_manager.singleton.log_info(
            f"'{cli_arguments}' is not an existing cli option set"
        )

        return True


singleton = WorkspaceManager()
