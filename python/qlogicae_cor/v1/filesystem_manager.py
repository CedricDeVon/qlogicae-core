import shutil
from pathlib import Path

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.file_entity_filesystem_tree_setup_options import (
    FileEntityFileSystemTreeSetupOptions,
)
from qlogicae_cor.v1.filesystem_manager_configurations import (
    FilesystemManagerConfigurations,
)
from qlogicae_cor.v1.folder_entity_filesystem_tree_setup_options import (
    FolderEntityFileSystemTreeSetupOptions,
)


class FilesystemManager(AbstractManager[FilesystemManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(FilesystemManagerConfigurations())

    def throw_if_filesystem_path_invalid(self,
        value: str,
    ) -> None | bool:
        path = Path(value)

        if not path.exists():
            raise ValueError(f"filesystem path '{path}' is invalid")

        return False

    def throw_if_file_path_invalid(self,
        value: str,
    ) -> None | bool:
        path = Path(value)

        if not path.is_file():
            raise ValueError(f"file path '{path}' is invalid")

        return False

    def throw_if_folder_path_invalid(self,
        value: str,
    ) -> None | bool:
        path = Path(value)

        if not path.is_dir():
            raise ValueError(f"folder path '{path}' is invalid")

        return False

    def is_filesystem_path_valid(self,
        value: str,
    ) -> None | bool:
        path = Path(value)

        return path.exists()

    def is_file_path_valid(self,
        value: str,
    ) -> None | bool:
        path = Path(value)

        return path.is_file()

    def is_folder_path_valid(self,
        value: str,
    ) -> None | bool:
        path = Path(value)

        return path.is_dir()

    def clean_filesystem_path(self, path: str) -> bool:
        directory = Path(path).resolve()

        protected_paths = {
            Path("/"),
            Path.home(),
        }

        if directory in protected_paths:
            raise ValueError(f"folder path '{path}' is protected")

        if not directory.exists():
            return True

        if not directory.is_dir():
            raise ValueError(f"file path '{path}' is not a folder")

        for item in directory.iterdir():
            if item.is_file() or item.is_symlink():
                item.unlink()

            elif item.is_dir():
                shutil.rmtree(item)

        return True

    def copy_filesystem_path(self,
        first_path: str,
        second_path: str
    ) -> bool:
        fs_first_path = Path(first_path)
        fs_second_path = Path(second_path)

        if fs_first_path.is_dir():
            shutil.copytree(
                fs_first_path,
                fs_second_path,
                dirs_exist_ok=True,
            )

        elif fs_first_path.is_file():
            fs_second_path.parent.mkdir(
                parents=True,
                exist_ok=True,
            )

            shutil.copy2(
                fs_first_path,
                fs_second_path,
            )

        else:
            return False

        return True

    def move_filesystem_path(self,
        first_path: str,
        second_path: str
    ) -> bool:
        source = Path(first_path)
        destination = Path(second_path)

        destination.parent.mkdir(
            parents=True,
            exist_ok=True,
        )

        shutil.move(
            str(source),
            str(destination),
        )

        return True

    def setup_filesystem_tree(
        self,
        parent_path: Path,
        options: FolderEntityFileSystemTreeSetupOptions,
    ) -> None:
        if not parent_path.exists():
            raise ValueError(f"filesystem path '{parent_path}' is invalid")

        parent_path.mkdir(parents=True, exist_ok=True)
        for entity in options.entities or []:
            entity_path = parent_path / entity.name

            if isinstance(
                entity,
                FolderEntityFileSystemTreeSetupOptions,
            ):
                entity_path.mkdir(parents=True, exist_ok=True)
                self.setup_filesystem_tree(entity_path, entity)

            elif isinstance(
                entity,
                FileEntityFileSystemTreeSetupOptions,
            ):
                if not entity_path.exists():
                    entity_path.write_text(
                        entity.content,
                        encoding=entity.encoding,
                    )

    def rename_filesystem_entity(
        self,
        source: str,
        destination: str,
    ) -> bool:
        Path(source).rename(destination)

        return True

    def setup_filesystem_tree_path(
        self,
        directory: str,
    ) -> bool:
        Path(directory).mkdir(
            parents=True,
            exist_ok=True,
        )

        return True

