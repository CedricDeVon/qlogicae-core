class WorkspaceLogManager:
    def __init__(self) -> None:
        self._log_targets = {"file", "console"}

    @property
    def log_targets(self):
        return self._log_targets


singleton = WorkspaceLogManager()
