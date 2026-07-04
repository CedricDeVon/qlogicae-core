from typing import Generic, TypeVar

from library.abstract_manager_configurations import (
    AbstractManagerConfigurations,
)
from library.error_manager import ErrorManager
from library.singleton_manager import SingletonManager


Configurations = TypeVar(
    "Configurations",
    bound=AbstractManagerConfigurations,
)

class AbstractManager(
    Generic[Configurations],
):
    def __init__(
        self,
        new_configurations: Configurations,
    ) -> None:
        self.configurations = new_configurations

    def setup(
        self,
        new_configurations: Configurations,
    ) -> bool:
        try:
            if self.configurations.is_disabled_for_handling(
                new_configurations is None,
            ):
                return False

            self.configurations = new_configurations

            return True

        except Exception as exception:
            self.handle_error_outputs(exception)

            return False

    def reset(
        self,
    ) -> bool:
        try:
            if self.configurations.is_disabled_for_handling():
                return False

            self.configurations = type(
                self.configurations,
            )()

            return True

        except Exception as exception:
            self.handle_error_outputs(exception)

            return False

    def handle_error_outputs(
        self,
        error: str | Exception,
        message: str | None = None,
    ) -> bool:
        error_manager = SingletonManager.get_singleton(
            ErrorManager,
        )

        if isinstance(error, Exception):
            return error_manager.handle_error_outputs(
                error,
            )

        if message is not None:
            return error_manager.handle_error_outputs(
                error,
                message,
            )

        return error_manager.handle_error_outputs(
            error,
        )
