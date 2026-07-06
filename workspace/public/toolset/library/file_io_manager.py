from library import text_manager


class FileIoManager:
    @property
    def file_encoding(self) -> str:
        return text_manager.singleton.encoding


singleton = FileIoManager()
