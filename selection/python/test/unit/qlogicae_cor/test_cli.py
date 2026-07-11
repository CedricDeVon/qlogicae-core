import pytest

from library.qlogicae_cor.cli import main


def test_main_should_print_version_and_return_zero(
    capsys: pytest.CaptureFixture[str],
) -> None:
    result = main()

    captured = capsys.readouterr()

    assert result == 0
    assert captured.err == ""
