from library import (
    log_manager,
    file_log_manager,
    value_cache_manager,
)
from library.target_cache_value import TargetCacheValue


class WorkspaceLogManager:
    def setup(self) -> bool:
        value_cache_manager.singleton.set_one_value(
            ["workspace/private/temporary/log/all.log-full-path"],
            f"{
                value_cache_manager.singleton.get_one_value(
                    ['current-root-full-path'],
                    output_type=TargetCacheValue.DEFINED,
                )
            }/workspace/private/temporary/log/all.log"
        )
        
        file_log_manager.singleton.add_file_output(
            value_cache_manager.singleton.get_one_value(
                ["workspace/private/temporary/log/all.log-full-path"],
                output_type=TargetCacheValue.DEFINED,
            )
        )

        return True

    def shutdown(self) -> bool:
        log_manager.singleton.shutdown()

        return True


singleton = WorkspaceLogManager()
