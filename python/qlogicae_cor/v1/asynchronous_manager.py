from __future__ import annotations

import asyncio
import threading
from collections.abc import Callable, Coroutine, Iterable
from concurrent.futures import (
    ProcessPoolExecutor,
    ThreadPoolExecutor,
)
from functools import partial
from typing import Any, ParamSpec, TypeVar

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.asynchronous_manager_configurations import (
    AsynchronousManagerConfigurations,
)

P = ParamSpec("P")
T = TypeVar("T")


class AsynchronousManager(AbstractManager[AsynchronousManagerConfigurations]):
    __slots__ = (
        "_thread_executor",
        "_process_executor",
    )

    def __init__(self) -> None:
        self._thread_executor: ThreadPoolExecutor | None = None
        self._process_executor: ProcessPoolExecutor | None = None

    @property
    def thread_executor(
        self,
    ) -> ThreadPoolExecutor:
        if self._thread_executor is None:
            self._thread_executor = ThreadPoolExecutor()

        return self._thread_executor

    @property
    def process_executor(
        self,
    ) -> ProcessPoolExecutor:
        if self._process_executor is None:
            self._process_executor = ProcessPoolExecutor()

        return self._process_executor

    async def run_thread(
        self,
        function: Callable[P, T],
        /,
        *args: P.args,
        **kwargs: P.kwargs,
    ) -> T:
        return await asyncio.to_thread(
            function,
            *args,
            **kwargs,
        )

    async def run_thread_pool(
        self,
        function: Callable[P, T],
        /,
        *args: P.args,
        **kwargs: P.kwargs,
    ) -> T:
        loop = asyncio.get_running_loop()

        return await loop.run_in_executor(
            self.thread_executor,
            partial(
                function,
                *args,
                **kwargs,
            ),
        )

    async def run_process_pool(
        self,
        function: Callable[P, T],
        /,
        *args: P.args,
        **kwargs: P.kwargs,
    ) -> T:
        loop = asyncio.get_running_loop()

        return await loop.run_in_executor(
            self.process_executor,
            partial(
                function,
                *args,
                **kwargs,
            ),
        )

    async def gather(
        self,
        *coroutines: Coroutine[Any, Any, Any],
        return_exceptions: bool = False,
    ) -> list[Any]:
        return await asyncio.gather(
            *coroutines,
            return_exceptions=return_exceptions,
        )

    async def wait(
        self,
        *coroutines: Coroutine[Any, Any, Any],
        timeout: float | None = None,
    ) -> tuple[
        set[asyncio.Task[Any]],
        set[asyncio.Task[Any]],
    ]:
        tasks: set[asyncio.Task[Any]] = {
            asyncio.create_task(coroutine)
            for coroutine in coroutines
        }

        return await asyncio.wait(
            tasks,
            timeout=timeout,
        )

    def create_task(
        self,
        coroutine: Coroutine[Any, Any, T],
        name: str | None = None,
    ) -> asyncio.Task[T]:
        return asyncio.create_task(
            coroutine,
            name=name,
        )

    async def timeout(
        self,
        coroutine: Coroutine[Any, Any, T],
        seconds: float,
    ) -> T:
        return await asyncio.wait_for(
            coroutine,
            timeout=seconds,
        )

    async def map_thread(
        self,
        function: Callable[..., T],
        *iterables: Iterable[Any],
    ) -> list[T]:
        return await asyncio.gather(
            *(
                self.run_thread(
                    function,
                    *values,
                )
                for values in zip(
                    *iterables,
                    strict=True,
                )
            )
        )

    async def map_thread_pool(
        self,
        function: Callable[..., T],
        *iterables: Iterable[Any],
    ) -> list[T]:
        return await asyncio.gather(
            *(
                self.run_thread_pool(
                    function,
                    *values,
                )
                for values in zip(
                    *iterables,
                    strict=True,
                )
            )
        )

    async def map_process_pool(
        self,
        function: Callable[..., T],
        *iterables: Iterable[Any],
    ) -> list[T]:
        return await asyncio.gather(
            *(
                self.run_process_pool(
                    function,
                    *values,
                )
                for values in zip(
                    *iterables,
                    strict=True,
                )
            )
        )

    def create_thread(
        self,
        function: Callable[..., Any],
        /,
        *args: Any,
        daemon: bool = False,
        start: bool = True,
        **kwargs: Any,
    ) -> threading.Thread:
        thread = threading.Thread(
            target=function,
            args=args,
            kwargs=kwargs,
            daemon=daemon,
        )

        if start:
            thread.start()

        return thread

    def shutdown(
        self,
        *,
        wait: bool = True,
    ) -> None:
        if self._thread_executor is not None:
            self._thread_executor.shutdown(
                wait=wait,
            )
            self._thread_executor = None

        if self._process_executor is not None:
            self._process_executor.shutdown(
                wait=wait,
            )
            self._process_executor = None

    def __enter__(
        self,
    ) -> AsynchronousManager:
        return self

    def __exit__(
        self,
        exc_type: type[BaseException] | None,
        exc: BaseException | None,
        traceback: Any,
    ) -> None:
        self.shutdown()
