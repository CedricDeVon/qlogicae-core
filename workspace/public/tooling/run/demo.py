from pathlib import Path

from library.target_cache_value import TargetCacheValue
from library.execute_command_return import ExecuteCommandReturn
from library import (
    log_manager,
    system_manager,
    handler_manager,
    value_cache_manager,
    value_cache_storage_manager,
    macros_manager,
    filesystem_manager,
)


def handle_manager_callback():
    value_cache_manager.singleton.display_all_items()
    # print(f"Memory Usage: {value_cache_storage_manager.singleton.get_memory_usage()}")


handler_manager.singleton.handle(handle_manager_callback)
