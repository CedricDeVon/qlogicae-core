from pathlib import Path
from zipfile import (
    ZIP_BZIP2,
    ZIP_DEFLATED,
    ZIP_LZMA,
    ZIP_STORED,
    ZipFile,
)

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.filesystem_compression_manager_configurations import (
    FilesystemCompressionManagerConfigurations,
)


class FilesystemCompressionManager(
    AbstractManager[FilesystemCompressionManagerConfigurations]
):
    def __init__(self) -> None:
        super().__init__(FilesystemCompressionManagerConfigurations())

    def get_zip_format_compression(self, value: str) -> int:
        match value.lower():
            case "store" | "stored" | "none":
                return ZIP_STORED

            case "deflate" | "deflated":
                return ZIP_DEFLATED

            case "bz2" | "bzip2":
                return ZIP_BZIP2

            case "lzma" | "xz":
                return ZIP_LZMA

            case _:
                return ZIP_DEFLATED

        return True

    def zip_extract(
        self,
        archive_path: str,
        destination_path: str,
        overwrite: bool = False,
    ) -> bool:
        fs_archive_path = Path(archive_path)
        fs_destination_path = Path(destination_path).resolve()

        fs_destination_path.mkdir(
            parents=True,
            exist_ok=True,
        )

        with ZipFile(fs_archive_path, "r") as archive:
            for member in archive.infolist():
                target = (fs_destination_path / member.filename).resolve()

                if (
                    fs_destination_path not in target.parents
                    and target != fs_destination_path
                ):
                    raise ValueError(
                        f"unsafe archive filesystem path '{member.filename}'"
                    )

                if not overwrite and target.exists():
                    continue

                archive.extract(member, fs_destination_path)

        return True
