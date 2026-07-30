import time
from typing import Any

from rich.live import Live

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.cli_component_manager import (
    CliComponentManager,
)
from qlogicae_cor.v1.cli_display_manager_configurations import (
    CliDisplayManagerConfigurations,
)
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)


class CliDisplayManager(AbstractManager[CliDisplayManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(CliDisplayManagerConfigurations())

    def render_directly(
        self,
        data: dict[str, Any] | None = None
    ) -> bool:
        if not data:
            return False

        progress_items = (data["items"] if "items" in data else []) or []

        for task in progress_items:
            task_callback = (
                task["callback"] if task and "callback" in task else None
            )
            task_arguments = (
                task["arguments"] if task and "arguments" in task else {}
            )
            task_delay = (task["delay"] if task and "delay" in task else {}) or {}
            task_delay_in_seconds = (
                task_delay["value"] if task_delay and "value" in task_delay else 0
            ) or 0

            if task_delay_in_seconds:
                time.sleep(task_delay_in_seconds)

            if task_callback:
                task_callback(**task_arguments)

        return True

    def render_progress_bar(
        self,
        data: dict[str, Any] | None = None
    ) -> bool:
        if not data:
            return False

        progress_bar = SingletonManager.get_singleton(
            CliComponentManager
        ).progress_bar
        progress_bar_task = progress_bar.add_task("", total=100)

        progress_items = (data["items"] if "items" in data else []) or []
        progress_refresh = (data["refresh"] if "refresh" in data else {}) or {}
        progress_refresh_value = (
            progress_refresh["value"] if "value" in progress_refresh else 60
        )
        progress_transient = (data["transient"] if "transient" in data else {}) or {}
        progress_transient_value = (
            progress_transient["value"] if "value" in progress_transient else True
        )
        with Live(
            progress_bar,
            console=SingletonManager.get_singleton(
                CliComponentManager
            ).console,
            refresh_per_second=progress_refresh_value,
            transient=progress_transient_value,
        ):
            time_start = time.perf_counter()
            for index, task in enumerate(progress_items):
                task_message = (
                    task["message"] if task and "message" in task else "Loading"
                ) or "Loading"
                task_callback = (
                    task["callback"] if task and "callback" in task else None
                )
                task_arguments = (
                    task["arguments"] if task and "arguments" in task else {}
                ) or {}
                task_delay = (task["delay"] if task and "delay" in task else {}) or {}
                task_delay_in_seconds = (
                    task_delay["value"] if task_delay and "value" in task_delay else 0
                ) or 0

                progress_bar.update(
                    progress_bar_task,
                    description=task_message,
                )

                if task_delay_in_seconds:
                    time.sleep(task_delay_in_seconds)

                if task_callback:
                    task_callback(**task_arguments)

                progress_bar.update(
                    progress_bar_task,
                    completed=min(
                        index / len(progress_items) * 100,
                        100,
                    ),
                    elapsed=f"{(time.perf_counter() - time_start):.2f}s",
                )

        return True

    def render_one_component(
        self,
        text: str = ""
    ) -> bool:
        SingletonManager.get_singleton(
            CliComponentManager
        ).console.print(text)

        return True

    def render_many_components(
        self,
        items: list[Any] | None = None
    ) -> bool:
        if not items:
            return False

        for item in items:
            if not item:
                return False

            self.render_one_component(item)

        return True
