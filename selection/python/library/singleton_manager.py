from collections.abc import Callable
from typing import Any, TypeVar

from library.singleton_manager_configurations import (
    SingletonManagerConfigurations,
)

Type = TypeVar("Type")


class SingletonManager:
    configurations: SingletonManagerConfigurations = SingletonManagerConfigurations()

    _singletons: dict[
        Callable[[], Any],
        Any,
    ] = {}

    _singleton_arrays: dict[
        Callable[[], Any],
        list[Any],
    ] = {}

    def __init__(self) -> None:
        pass

    @classmethod
    def setup(
        self,
        new_configurations: SingletonManagerConfigurations,
    ) -> bool:
        try:
            if self.configurations.is_disabled_for_handling(
                new_configurations is None,
            ):
                return False

            self.configurations = new_configurations

            return True

        except Exception:
            return False

    @classmethod
    def reset(
        self,
    ) -> bool:
        try:
            if self.configurations.is_disabled_for_handling():
                return False

            self.configurations = SingletonManagerConfigurations()

            self._singletons.clear()
            self._singleton_arrays.clear()

            return True

        except Exception:
            return False

    @classmethod
    def get_singleton(
        self,
        constructor: Callable[[], Type],
    ) -> Type:
        try:
            instance = self._singletons.get(constructor)

            if instance is None:
                instance = constructor()
                self._singletons[constructor] = instance

            return instance

        except Exception as exception:
            raise RuntimeError(
                "error at 'qlogicae-cor' - something went wrong here"
            ) from exception

    @classmethod
    def get_singleton_from_pool(
        self,
        constructor: Callable[[], Type],
        instance_count: int,
        index: int,
    ) -> Type:
        try:
            if instance_count <= 0:
                raise ValueError("error at 'qlogicae-cor' - something went wrong here")

            instances = self._singleton_arrays.get(
                constructor,
            )

            if instances is None:
                instances = [constructor() for _ in range(instance_count)]

                self._singleton_arrays[constructor] = instances

            return instances[abs(index) % instance_count]

        except Exception as exception:
            raise RuntimeError(
                "error at 'qlogicae-cor' - something went wrong here"
            ) from exception
