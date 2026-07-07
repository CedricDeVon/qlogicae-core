class WorkspaceMacrosManager:
    @property
    def current_root_full_path(self) -> str:
        return "${{ current-root-full-path }}"


singleton = WorkspaceMacrosManager()
