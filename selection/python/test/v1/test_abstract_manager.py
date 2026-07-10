import pytest

from library.v1.abstract_manager import (
    AbstractManager,
)
from library.v1.abstract_manager_configurations import (
    AbstractManagerConfigurations,
)
from library.v1.error_manager import (
    ErrorManager,
)
from library.v1.singleton_manager import (
    SingletonManager,
)


class DummyConfigurations(
    AbstractManagerConfigurations,
):
    pass


class DisabledConfigurations(
    DummyConfigurations,
):
    def is_disabled_for_handling(
        self,
        conditions: bool = False,
    ) -> bool:
        return True


class ExceptionConfigurations(
    DummyConfigurations,
):
    def is_disabled_for_handling(
        self,
        conditions: bool = False,
    ) -> bool:
        raise RuntimeError(
            "failure",
        )


class DummyManager(
    AbstractManager[DummyConfigurations],
):
    pass


@pytest.fixture(autouse=True)
def reset_singleton():
    SingletonManager.reset()
    yield
    SingletonManager.reset()


@pytest.fixture
def manager():
    return DummyManager(
        DummyConfigurations(),
    )


def test_constructor():
    manager = DummyManager(
        DummyConfigurations(),
    )

    assert isinstance(
        manager.configurations,
        DummyConfigurations,
    )


def test_setup_success(
    manager: DummyManager,
):
    configuration = DummyConfigurations()

    assert (
        manager.setup(
            configuration,
        )
        is True
    )

    assert manager.configurations is configuration


def test_setup_none_returns_false(
    manager: DummyManager,
):
    assert (
        manager.setup(
            None,
        )
        is False
    )


def test_setup_disabled(
    manager: DummyManager,
):
    manager.configurations = DisabledConfigurations()

    configuration = DummyConfigurations()

    assert (
        manager.setup(
            configuration,
        )
        is False
    )


def test_setup_exception(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    manager.configurations = ExceptionConfigurations()

    called = False

    def handle(
        error,
        message=None,
    ):
        nonlocal called

        called = True

        return True

    monkeypatch.setattr(
        manager,
        "handle_error_outputs",
        handle,
    )

    assert (
        manager.setup(
            DummyConfigurations(),
        )
        is False
    )

    assert called


def test_reset_success(
    manager: DummyManager,
):
    original = manager.configurations

    assert manager.reset() is True

    assert manager.configurations is not original

    assert isinstance(
        manager.configurations,
        DummyConfigurations,
    )


def test_reset_disabled(
    manager: DummyManager,
):
    manager.configurations = DisabledConfigurations()

    assert manager.reset() is False


def test_reset_exception(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    manager.configurations = ExceptionConfigurations()

    called = False

    def handle(
        error,
        message=None,
    ):
        nonlocal called

        called = True

        return True

    monkeypatch.setattr(
        manager,
        "handle_error_outputs",
        handle,
    )

    assert manager.reset() is False

    assert called


def test_handle_error_outputs_exception():
    manager = DummyManager(
        DummyConfigurations(),
    )

    error_manager = SingletonManager.get_singleton(
        ErrorManager,
    )

    assert manager.handle_error_outputs(
        RuntimeError(
            "failure",
        ),
    ) == error_manager.handle_error_outputs(
        RuntimeError(
            "failure",
        ),
    )


def test_handle_error_outputs_message():
    manager = DummyManager(
        DummyConfigurations(),
    )

    assert (
        manager.handle_error_outputs(
            "failure",
        )
        is True
    )


def test_handle_error_outputs_title_message():
    manager = DummyManager(
        DummyConfigurations(),
    )

    assert (
        manager.handle_error_outputs(
            "Title",
            "Message",
        )
        is True
    )


def test_multiple_setups(
    manager: DummyManager,
):
    configuration1 = DummyConfigurations()

    configuration2 = DummyConfigurations()

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

    assert manager.configurations is configuration2


def test_multiple_resets(
    manager: DummyManager,
):
    assert manager.reset() is True

    assert manager.reset() is True


def test_setup_after_reset(
    manager: DummyManager,
):
    manager.reset()

    configuration = DummyConfigurations()

    assert (
        manager.setup(
            configuration,
        )
        is True
    )

    assert manager.configurations is configuration


def test_setup_preserves_configuration_on_failure(
    manager: DummyManager,
):
    configuration = manager.configurations

    assert (
        manager.setup(
            None,
        )
        is False
    )

    assert manager.configurations is configuration


def test_configuration_defaults():
    configuration = DummyConfigurations()

    assert configuration.is_override_enabled is False

    assert configuration.is_enabled is True

    assert configuration.is_runtime_execution_handling_enabled is True

    assert configuration.is_edge_case_handling_enabled is True

    assert configuration.is_error_handling_enabled is True


def test_is_override_enabled_property():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = True

    assert configuration.is_override_enabled is True


def test_is_enabled_property():
    configuration = DummyConfigurations()

    configuration.is_enabled = False

    assert configuration.is_enabled is False


def test_runtime_execution_property():
    configuration = DummyConfigurations()

    configuration.is_runtime_execution_handling_enabled = False

    assert configuration.is_runtime_execution_handling_enabled is False


def test_edge_case_property():
    configuration = DummyConfigurations()

    configuration.is_edge_case_handling_enabled = False

    assert configuration.is_edge_case_handling_enabled is False


def test_error_handling_property():
    configuration = DummyConfigurations()

    configuration.is_error_handling_enabled = False

    assert configuration.is_error_handling_enabled is False


def test_disabled_for_handling_runtime_disabled():
    configuration = DummyConfigurations()

    configuration.is_runtime_execution_handling_enabled = False

    assert configuration.is_disabled_for_handling() is True


def test_disabled_for_handling_edge_case():
    configuration = DummyConfigurations()

    assert (
        configuration.is_disabled_for_handling(
            True,
        )
        is True
    )


def test_disabled_for_handling_false():
    configuration = DummyConfigurations()

    assert (
        configuration.is_disabled_for_handling(
            False,
        )
        is False
    )


def test_runtime_execution_override_enabled():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = True
    configuration.is_enabled = False
    configuration.is_runtime_execution_handling_enabled = True

    assert configuration.is_enabled_for_runtime_execution_handling() is False


def test_edge_case_override_enabled():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = True
    configuration.is_enabled = False
    configuration.is_edge_case_handling_enabled = True

    assert configuration.is_enabled_for_edge_case_handling() is False


def test_error_handling_override_enabled():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = True
    configuration.is_enabled = False
    configuration.is_error_handling_enabled = True

    assert configuration.is_enabled_for_error_handling() is False


def test_runtime_execution_without_override():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = False
    configuration.is_runtime_execution_handling_enabled = False

    assert configuration.is_enabled_for_runtime_execution_handling() is False


def test_edge_case_without_override():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = False
    configuration.is_edge_case_handling_enabled = False

    assert configuration.is_enabled_for_edge_case_handling() is False


def test_error_handling_without_override():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = False
    configuration.is_error_handling_enabled = False

    assert configuration.is_enabled_for_error_handling() is False


def test_setup_exception_preserves_configuration(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    original = DummyConfigurations()

    manager.configurations = original

    def raise_exception(
        *_,
        **__,
    ):
        raise RuntimeError()

    monkeypatch.setattr(
        original,
        "is_disabled_for_handling",
        raise_exception,
    )

    monkeypatch.setattr(
        manager,
        "handle_error_outputs",
        lambda *args, **kwargs: True,
    )

    assert (
        manager.setup(
            DummyConfigurations(),
        )
        is False
    )

    assert manager.configurations is original


def test_reset_exception_preserves_configuration(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    original = DummyConfigurations()

    manager.configurations = original

    def raise_exception(
        *_,
        **__,
    ):
        raise RuntimeError()

    monkeypatch.setattr(
        original,
        "is_disabled_for_handling",
        raise_exception,
    )

    monkeypatch.setattr(
        manager,
        "handle_error_outputs",
        lambda *args, **kwargs: True,
    )

    assert manager.reset() is False

    assert manager.configurations is original


def test_disabled_for_handling_edge_case_disabled():
    configuration = DummyConfigurations()

    configuration.is_edge_case_handling_enabled = False

    assert (
        configuration.is_disabled_for_handling(
            True,
        )
        is False
    )


def test_runtime_execution_override_enabled_true():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = True
    configuration.is_enabled = True
    configuration.is_runtime_execution_handling_enabled = False

    assert configuration.is_enabled_for_runtime_execution_handling() is True


def test_edge_case_override_enabled_true():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = True
    configuration.is_enabled = True
    configuration.is_edge_case_handling_enabled = False

    assert configuration.is_enabled_for_edge_case_handling() is True


def test_error_handling_override_enabled_true():
    configuration = DummyConfigurations()

    configuration.is_override_enabled = True
    configuration.is_enabled = True
    configuration.is_error_handling_enabled = False

    assert configuration.is_enabled_for_error_handling() is True


def test_handle_error_outputs_delegates_exception(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    received = None

    def handle(
        error,
        message=None,
    ):
        nonlocal received

        received = (
            error,
            message,
        )

        return True

    error_manager = SingletonManager.get_singleton(
        ErrorManager,
    )

    monkeypatch.setattr(
        error_manager,
        "handle_error_outputs",
        handle,
    )

    exception = RuntimeError(
        "failure",
    )

    assert (
        manager.handle_error_outputs(
            exception,
        )
        is True
    )

    assert received[0] is exception

    assert received[1] is None


def test_handle_error_outputs_delegates_message(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    received = None

    def handle(
        error,
        message=None,
    ):
        nonlocal received

        received = (
            error,
            message,
        )

        return True

    error_manager = SingletonManager.get_singleton(
        ErrorManager,
    )

    monkeypatch.setattr(
        error_manager,
        "handle_error_outputs",
        handle,
    )

    assert (
        manager.handle_error_outputs(
            "failure",
        )
        is True
    )

    assert received == (
        "failure",
        None,
    )


def test_handle_error_outputs_delegates_title_message(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    received = None

    def handle(
        error,
        message=None,
    ):
        nonlocal received

        received = (
            error,
            message,
        )

        return True

    error_manager = SingletonManager.get_singleton(
        ErrorManager,
    )

    monkeypatch.setattr(
        error_manager,
        "handle_error_outputs",
        handle,
    )

    assert (
        manager.handle_error_outputs(
            "Title",
            "Message",
        )
        is True
    )

    assert received == (
        "Title",
        "Message",
    )


def test_handle_error_outputs_requests_singleton(
    manager: DummyManager,
    monkeypatch: pytest.MonkeyPatch,
):
    called = False

    class FakeErrorManager:
        def handle_error_outputs(
            self,
            error,
            message=None,
        ):
            return True

    def get_singleton(
        constructor,
    ):
        nonlocal called

        called = True

        assert constructor is ErrorManager

        return FakeErrorManager()

    monkeypatch.setattr(
        SingletonManager,
        "get_singleton",
        get_singleton,
    )

    assert (
        manager.handle_error_outputs(
            "failure",
        )
        is True
    )

    assert called
