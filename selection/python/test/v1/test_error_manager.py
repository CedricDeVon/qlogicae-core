import pytest

from library.v1.error_manager import (
    ErrorManager,
)
from library.v1.error_manager_configurations import (
    ErrorManagerConfigurations,
)


class DisabledConfigurations(
    ErrorManagerConfigurations,
):
    def is_disabled_for_handling(
        self,
        *_,
        **__,
    ) -> bool:
        return True


class ExceptionConfigurations(
    ErrorManagerConfigurations,
):
    def is_disabled_for_handling(
        self,
        *_,
        **__,
    ) -> bool:
        raise RuntimeError(
            "failure",
        )


@pytest.fixture
def manager():
    return ErrorManager()


def test_constructor():
    manager = ErrorManager()

    assert manager is not None
    assert isinstance(
        manager._configurations,
        ErrorManagerConfigurations,
    )


def test_setup_success(
    manager: ErrorManager,
):
    configuration = ErrorManagerConfigurations()

    assert (
        manager.setup(
            configuration,
        )
        is True
    )

    assert manager._configurations is configuration


def test_setup_none_returns_false(
    manager: ErrorManager,
):
    assert (
        manager.setup(
            None,
        )
        is False
    )


def test_setup_configuration_disabled(
    manager: ErrorManager,
):
    manager._configurations = DisabledConfigurations()

    configuration = ErrorManagerConfigurations()

    assert (
        manager.setup(
            configuration,
        )
        is False
    )


def test_setup_configuration_exception(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
):
    manager._configurations = ExceptionConfigurations()

    called = False

    def handle(
        exception: Exception,
    ):
        nonlocal called

        called = True

        assert isinstance(
            exception,
            RuntimeError,
        )

    monkeypatch.setattr(
        manager,
        "handle_error_outputs",
        handle,
    )

    assert (
        manager.setup(
            ErrorManagerConfigurations(),
        )
        is False
    )

    assert called


def test_reset_success(
    manager: ErrorManager,
):
    assert manager.reset() is True

    assert isinstance(
        manager._configurations,
        ErrorManagerConfigurations,
    )


def test_reset_disabled(
    manager: ErrorManager,
):
    manager._configurations = DisabledConfigurations()

    assert manager.reset() is False


def test_reset_exception(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
):
    manager._configurations = ExceptionConfigurations()

    called = False

    def handle(
        exception: Exception,
    ):
        nonlocal called

        called = True

        assert isinstance(
            exception,
            RuntimeError,
        )

    monkeypatch.setattr(
        manager,
        "handle_error_outputs",
        handle,
    )

    assert manager.reset() is False

    assert called


def test_transform_error_log_from_exception(
    manager: ErrorManager,
):
    result = manager.transform_to_error_log(
        ValueError(
            "abc",
        ),
    )

    assert "ValueError" in result

    assert "abc" in result


def test_transform_error_log_from_title_and_message(
    manager: ErrorManager,
):
    result = manager.transform_to_error_log(
        "Title",
        "Message",
    )

    assert result == "Title - Message"


def test_transform_error_log_from_message(
    manager: ErrorManager,
):
    result = manager.transform_to_error_log(
        "Message",
    )

    assert result == ("error at 'qlogicae-cor1' - Message")


def test_transform_error_log_custom_separator(
    manager: ErrorManager,
):
    manager._configurations.title = "Title"

    manager._configurations.title_message_separator = "::"

    result = manager.transform_to_error_log(
        "Message",
    )

    assert result == "Title::Message"


def test_handle_error_outputs_exception(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
):
    value = None

    def handle(
        error_log: str,
    ):
        nonlocal value

        value = error_log

        return True

    monkeypatch.setattr(
        manager,
        "handle_error_output_conditions",
        handle,
    )

    assert (
        manager.handle_error_outputs(
            RuntimeError(
                "failure",
            ),
        )
        is True
    )

    assert "RuntimeError" in value


def test_handle_error_outputs_title_message(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
):
    value = None

    def handle(
        error_log: str,
    ):
        nonlocal value

        value = error_log

        return True

    monkeypatch.setattr(
        manager,
        "handle_error_output_conditions",
        handle,
    )

    assert (
        manager.handle_error_outputs(
            "Title",
            "Message",
        )
        is True
    )

    assert value == "Title - Message"


def test_handle_error_outputs_message(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
):
    value = None

    def handle(
        error_log: str,
    ):
        nonlocal value

        value = error_log

        return True

    monkeypatch.setattr(
        manager,
        "handle_error_output_conditions",
        handle,
    )

    assert (
        manager.handle_error_outputs(
            "Message",
        )
        is True
    )

    assert value.endswith(
        "Message",
    )


def test_handle_error_output_conditions_runtime_disabled(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
):
    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_runtime_execution_handling",
        lambda: False,
    )

    assert (
        manager.handle_error_output_conditions(
            "error",
        )
        is False
    )


def test_handle_error_output_conditions_console_only(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
    capsys: pytest.CaptureFixture[str],
):
    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_runtime_execution_handling",
        lambda: True,
    )

    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_console_output",
        lambda: True,
    )

    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_runtime_throw_output",
        lambda: False,
    )

    assert (
        manager.handle_error_output_conditions(
            "hello",
        )
        is True
    )

    captured = capsys.readouterr()

    assert captured.out.strip() == "hello"


def test_handle_error_output_conditions_runtime_throw(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
):
    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_runtime_execution_handling",
        lambda: True,
    )

    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_console_output",
        lambda: False,
    )

    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_runtime_throw_output",
        lambda: True,
    )

    with pytest.raises(
        RuntimeError,
    ):
        manager.handle_error_output_conditions(
            "failure",
        )


def test_handle_error_output_conditions_console_and_throw(
    manager: ErrorManager,
    monkeypatch: pytest.MonkeyPatch,
    capsys: pytest.CaptureFixture[str],
):
    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_runtime_execution_handling",
        lambda: True,
    )

    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_console_output",
        lambda: True,
    )

    monkeypatch.setattr(
        manager._configurations,
        "is_enabled_for_runtime_throw_output",
        lambda: True,
    )

    with pytest.raises(
        RuntimeError,
    ):
        manager.handle_error_output_conditions(
            "failure",
        )

    captured = capsys.readouterr()

    assert captured.out.strip() == "failure"


def test_is_output_enabled_property():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_enabled = False

    assert configuration.is_output_enabled is False


def test_is_output_override_enabled_property():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_override_enabled = True

    assert configuration.is_output_override_enabled is True


def test_is_asynchronous_output_enabled_property():
    configuration = ErrorManagerConfigurations()

    configuration.is_asynchronous_output_enabled = False

    assert configuration.is_asynchronous_output_enabled is False


def test_is_asynchronous_output_override_enabled_property():
    configuration = ErrorManagerConfigurations()

    configuration.is_asynchronous_output_override_enabled = True

    assert configuration.is_asynchronous_output_override_enabled is True


def test_is_console_output_enabled_property():
    configuration = ErrorManagerConfigurations()

    configuration.is_console_output_enabled = False

    assert configuration.is_console_output_enabled is False


def test_is_runtime_throw_output_enabled_property():
    configuration = ErrorManagerConfigurations()

    configuration.is_runtime_throw_output_enabled = True

    assert configuration.is_runtime_throw_output_enabled is True


def test_title_property():
    configuration = ErrorManagerConfigurations()

    configuration.title = "Test"

    assert configuration.title == "Test"


def test_message_property():
    configuration = ErrorManagerConfigurations()

    configuration.message = "Failure"

    assert configuration.message == "Failure"


def test_title_message_separator_property():
    configuration = ErrorManagerConfigurations()

    configuration.title_message_separator = "::"

    assert configuration.title_message_separator == "::"


def test_console_output_without_override():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_enabled = False
    configuration.is_output_override_enabled = False
    configuration.is_console_output_enabled = True

    assert configuration.is_enabled_for_console_output() is True


def test_console_output_with_override_enabled():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_enabled = True
    configuration.is_output_override_enabled = True
    configuration.is_console_output_enabled = False

    assert configuration.is_enabled_for_console_output() is True


def test_console_output_with_override_disabled():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_enabled = False
    configuration.is_output_override_enabled = True
    configuration.is_console_output_enabled = True

    assert configuration.is_enabled_for_console_output() is False


def test_runtime_throw_without_override():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_enabled = False
    configuration.is_output_override_enabled = False
    configuration.is_runtime_throw_output_enabled = True

    assert configuration.is_enabled_for_runtime_throw_output() is True


def test_runtime_throw_with_override_enabled():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_enabled = True
    configuration.is_output_override_enabled = True
    configuration.is_runtime_throw_output_enabled = False

    assert configuration.is_enabled_for_runtime_throw_output() is True


def test_runtime_throw_with_override_disabled():
    configuration = ErrorManagerConfigurations()

    configuration.is_output_enabled = False
    configuration.is_output_override_enabled = True
    configuration.is_runtime_throw_output_enabled = True

    assert configuration.is_enabled_for_runtime_throw_output() is False


class RaiseConsoleConfiguration(
    ErrorManagerConfigurations,
):
    def is_enabled_for_console_output(
        self,
    ) -> bool:
        raise RuntimeError(
            "console failure",
        )


class RaiseRuntimeConfiguration(
    ErrorManagerConfigurations,
):
    def is_enabled_for_runtime_execution_handling(
        self,
    ) -> bool:
        raise RuntimeError(
            "runtime failure",
        )


class RaiseThrowConfiguration(
    ErrorManagerConfigurations,
):
    def is_enabled_for_runtime_throw_output(
        self,
    ) -> bool:
        raise RuntimeError(
            "throw failure",
        )


def test_handle_error_outputs_returns_true_for_exception(
    manager: ErrorManager,
):
    assert (
        manager.handle_error_outputs(
            RuntimeError(
                "failure",
            ),
        )
        is True
    )


def test_handle_error_outputs_returns_true_for_message():
    manager = ErrorManager()

    assert (
        manager.handle_error_outputs(
            "failure",
        )
        is True
    )


def test_handle_error_outputs_returns_true_for_title_message():
    manager = ErrorManager()

    assert (
        manager.handle_error_outputs(
            "Title",
            "Message",
        )
        is True
    )


def test_transform_to_error_log_empty_message(
    manager: ErrorManager,
):
    value = manager.transform_to_error_log(
        "",
    )

    assert value.endswith(
        " - ",
    )


def test_transform_to_error_log_empty_title_and_message(
    manager: ErrorManager,
):
    value = manager.transform_to_error_log(
        "",
        "",
    )

    assert value == " - "


def test_transform_to_error_log_exception_without_message(
    manager: ErrorManager,
):
    value = manager.transform_to_error_log(
        RuntimeError(),
    )

    assert "RuntimeError" in value


def test_configuration_default_values():
    configuration = ErrorManagerConfigurations()

    assert configuration.is_output_enabled is True

    assert configuration.is_output_override_enabled is False

    assert configuration.is_asynchronous_output_enabled is True

    assert configuration.is_asynchronous_output_override_enabled is False

    assert configuration.is_console_output_enabled is True

    assert configuration.is_runtime_throw_output_enabled is False

    assert configuration.title == "error at 'qlogicae-cor1'"

    assert configuration.message == "something went wrong here"

    assert configuration.title_message_separator == " - "


def test_handle_error_output_conditions_runtime_configuration_exception():
    manager = ErrorManager()

    manager._configurations = RaiseRuntimeConfiguration()

    with pytest.raises(
        RuntimeError,
    ):
        manager.handle_error_output_conditions(
            "failure",
        )


def test_handle_error_output_conditions_console_configuration_exception():
    manager = ErrorManager()

    manager._configurations = RaiseConsoleConfiguration()

    with pytest.raises(
        RuntimeError,
    ):
        manager.handle_error_output_conditions(
            "failure",
        )


def test_handle_error_output_conditions_throw_configuration_exception():
    manager = ErrorManager()

    manager._configurations = RaiseThrowConfiguration()

    with pytest.raises(
        RuntimeError,
    ):
        manager.handle_error_output_conditions(
            "failure",
        )


def test_multiple_setups():
    manager = ErrorManager()

    configuration1 = ErrorManagerConfigurations()

    configuration2 = ErrorManagerConfigurations()

    assert (
        manager.setup(
            configuration1,
        )
        is True
    )

    assert (
        manager.setup(
            configuration2,
        )
        is True
    )

    assert manager._configurations is configuration2


def test_multiple_resets():
    manager = ErrorManager()

    assert manager.reset() is True

    assert manager.reset() is True

    assert isinstance(
        manager._configurations,
        ErrorManagerConfigurations,
    )


def test_setup_after_reset():
    manager = ErrorManager()

    manager.reset()

    configuration = ErrorManagerConfigurations()

    assert (
        manager.setup(
            configuration,
        )
        is True
    )

    assert manager._configurations is configuration


def test_transform_to_error_log_uses_custom_title():
    manager = ErrorManager()

    manager._configurations.title = "Custom"

    value = manager.transform_to_error_log(
        "failure",
    )

    assert value.startswith(
        "Custom",
    )


def test_transform_to_error_log_uses_custom_separator():
    manager = ErrorManager()

    manager._configurations.title = "Title"

    manager._configurations.title_message_separator = "::"

    value = manager.transform_to_error_log(
        RuntimeError(
            "failure",
        ),
    )

    assert "::" in value


def test_console_and_throw_disabled():
    manager = ErrorManager()

    manager._configurations.is_console_output_enabled = False

    manager._configurations.is_runtime_throw_output_enabled = False

    assert (
        manager.handle_error_output_conditions(
            "failure",
        )
        is True
    )


def test_setup_none_preserves_configuration(
    manager: ErrorManager,
):
    configuration = manager._configurations

    assert (
        manager.setup(
            None,
        )
        is False
    )

    assert manager._configurations is configuration


def test_reset_replaces_configuration_instance(
    manager: ErrorManager,
):
    configuration = manager._configurations

    assert manager.reset() is True

    assert manager._configurations is not configuration


def test_handle_error_outputs_console_integration(
    manager: ErrorManager,
    capsys: pytest.CaptureFixture[str],
):
    configuration = ErrorManagerConfigurations()

    configuration.is_console_output_enabled = True
    configuration.is_runtime_throw_output_enabled = False

    manager.setup(
        configuration,
    )

    assert (
        manager.handle_error_outputs(
            "failure",
        )
        is True
    )

    captured = capsys.readouterr()

    assert captured.out.strip() == "error at 'qlogicae-cor1' - failure"


def test_handle_error_outputs_console_integration_title_message(
    manager: ErrorManager,
    capsys: pytest.CaptureFixture[str],
):
    configuration = ErrorManagerConfigurations()

    configuration.is_console_output_enabled = True
    configuration.is_runtime_throw_output_enabled = False

    manager.setup(
        configuration,
    )

    assert (
        manager.handle_error_outputs(
            "Title",
            "Message",
        )
        is True
    )

    captured = capsys.readouterr()

    assert captured.out.strip() == "Title - Message"


def test_handle_error_outputs_runtime_throw_integration():
    manager = ErrorManager()

    configuration = ErrorManagerConfigurations()

    configuration.is_console_output_enabled = False
    configuration.is_runtime_throw_output_enabled = True

    manager.setup(
        configuration,
    )

    with pytest.raises(
        RuntimeError,
    ) as exception:
        manager.handle_error_outputs(
            "failure",
        )

    assert (
        str(
            exception.value,
        )
        == "error at 'qlogicae-cor1' - failure"
    )


def test_handle_error_outputs_runtime_throw_exception_integration():
    manager = ErrorManager()

    configuration = ErrorManagerConfigurations()

    configuration.is_console_output_enabled = False
    configuration.is_runtime_throw_output_enabled = True

    manager.setup(
        configuration,
    )

    with pytest.raises(
        RuntimeError,
    ) as exception:
        manager.handle_error_outputs(
            ValueError(
                "failure",
            ),
        )

    assert (
        str(
            exception.value,
        )
        == "ValueError - failure"
    )


def test_handle_error_outputs_custom_configuration(
    manager: ErrorManager,
    capsys: pytest.CaptureFixture[str],
):
    configuration = ErrorManagerConfigurations()

    configuration.title = "Custom"
    configuration.title_message_separator = "::"

    manager.setup(
        configuration,
    )

    assert (
        manager.handle_error_outputs(
            "failure",
        )
        is True
    )

    captured = capsys.readouterr()

    assert captured.out.strip() == "Custom::failure"


def test_configuration_mutation_after_setup(
    manager: ErrorManager,
):
    configuration = ErrorManagerConfigurations()

    manager.setup(
        configuration,
    )

    configuration.title = "Updated"

    assert (
        manager.transform_to_error_log(
            "failure",
        )
        == "Updated - failure"
    )


def test_handle_error_outputs_empty_separator(
    manager: ErrorManager,
    capsys: pytest.CaptureFixture[str],
):
    configuration = ErrorManagerConfigurations()

    configuration.title = "Title"
    configuration.title_message_separator = ""

    manager.setup(
        configuration,
    )

    manager.handle_error_outputs(
        "failure",
    )

    captured = capsys.readouterr()

    assert captured.out.strip() == "Titlefailure"


def test_transform_to_error_log_empty_title(
    manager: ErrorManager,
):
    manager._configurations.title = ""

    assert (
        manager.transform_to_error_log(
            "failure",
        )
        == " - failure"
    )
