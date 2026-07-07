class WorkspaceScriptManager:
    def setup(self) -> bool:
        return True

    def shutdown(self) -> bool:
        return True


singleton = WorkspaceScriptManager()
