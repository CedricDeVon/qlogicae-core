class TextEncodingManager:
    def __init__(self) -> None:
        self._encoding: str = "utf-8"

    @property
    def encoding(self) -> set[str]:
        return self._encoding


singleton = TextEncodingManager()
