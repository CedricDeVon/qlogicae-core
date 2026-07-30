from importlib.metadata import version

from qlogicae_cor.v1.cli_display_manager import CliDisplayManager
from qlogicae_cor.v1.singleton_manager import (
    SingletonManager,
)


def main() -> None:
    SingletonManager.get_singleton(
        CliDisplayManager,
    ).render_one_component(
        version("qlogicae-cor")
    )
