from datetime import date


class TimeManager:
    def generate_current_iso8601_date(self) -> str:
        return date.today().strftime("%Y-%m-%d")


singleton = TimeManager()
