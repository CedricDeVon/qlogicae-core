from library.v1.abstract_manager import AbstractManager
from library.v1.workspace_value_cache_manager_configurations import (
    WorkspaceValueCacheManagerConfigurations,
)


class WorkspaceValueCacheManager(
    AbstractManager[WorkspaceValueCacheManagerConfigurations]
):
    def __init__(self) -> None:
        super().__init__(WorkspaceValueCacheManagerConfigurations())


singleton = WorkspaceValueCacheManager()
