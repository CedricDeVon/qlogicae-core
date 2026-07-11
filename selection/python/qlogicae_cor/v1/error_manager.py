from qlogicae_cor.v1.error_manager_configurations import (
    ErrorManagerConfigurations,
)


class ErrorManager:
    def __init__(self) -> None:
        self._configurations = ErrorManagerConfigurations()

    def setup(
        self,
        new_configurations: ErrorManagerConfigurations,
    ) -> bool:
        try:
            if self._configurations.is_disabled_for_handling(
                new_configurations is None,
            ):
                return False

            self._configurations = new_configurations

            return True

        except Exception as exception:
            self.handle_error_outputs(exception)

            return False

    def reset(
        self,
    ) -> bool:
        try:
            if self._configurations.is_disabled_for_handling():
                return False

            self._configurations = ErrorManagerConfigurations()

            return True

        except Exception as exception:
            self.handle_error_outputs(exception)

            return False

    def transform_to_error_log(
        self,
        value1: str | Exception,
        value2: str | None = None,
    ) -> str:
        if isinstance(value1, Exception):
            return (
                f"{type(value1).__name__}"
                f"{self._configurations.title_message_separator}"
                f"{value1}"
            )

        if value2 is not None:
            return f"{value1}{self._configurations.title_message_separator}{value2}"

        return (
            f"{self._configurations.title}"
            f"{self._configurations.title_message_separator}"
            f"{value1}"
        )

    def handle_error_outputs(
        self,
        error: str | Exception,
        message: str | None = None,
    ) -> bool:
        if isinstance(error, Exception):
            self.handle_error_output_conditions(
                self.transform_to_error_log(error),
            )

            return True

        if message is not None:
            self.handle_error_output_conditions(
                self.transform_to_error_log(
                    error,
                    message,
                ),
            )

            return True

        self.handle_error_output_conditions(
            self.transform_to_error_log(error),
        )

        return True

    def handle_error_output_conditions(
        self,
        error_log: str,
    ) -> bool:
        if not self._configurations.is_enabled_for_runtime_execution_handling():
            return False

        if self._configurations.is_enabled_for_console_output():
            print(error_log)

        if self._configurations.is_enabled_for_runtime_throw_output():
            raise RuntimeError(error_log)

        return True
