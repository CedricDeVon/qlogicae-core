from pathlib import Path

from library.target_cache_value import TargetCacheValue
from library.execute_command_return import ExecuteCommandReturn
from library import (
    workspace_manager,
    value_cache_manager,
)


def handle_manager_callback():
    value_cache_manager.singleton.display_all_items()


workspace_manager.singleton.handle(handle_manager_callback)
