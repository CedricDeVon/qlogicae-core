import shutil
from pathlib import Path

from qlogicae_cor.v1.abstract_manager import AbstractManager

from qlogicae_logis.v1.file_entity_filesystem_tree_setup_options import (
    FileEntityFileSystemTreeSetupOptions,
)
from qlogicae_logis.v1.filesystem_manager_configurations import FileSystemManagerConfigurations
from qlogicae_logis.v1.folder_entity_filesystem_tree_setup_options import (
    FolderEntityFileSystemTreeSetupOptions,
)


class FileSystemManager(AbstractManager[FileSystemManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(FileSystemManagerConfigurations())

    def throw_if_filesystem_path_invalid(self, value):
        path = Path(value)

        if not path.exists():
            raise Exception(f"filesystem path '{path}' is invalid")

        return False

    def throw_if_file_path_invalid(self, value):
        path = Path(value)

        if not path.is_file():
            raise Exception(f"file path '{path}' is invalid")

        return False

    def throw_if_folder_path_invalid(self, value):
        path = Path(value)

        if not path.is_dir():
            raise Exception(f"folder path '{path}' is invalid")

        return False

    def is_filesystem_path_valid(self, value):
        path = Path(value)

        if not path.exists():
            return False

        return True

    def is_file_path_valid(self, value):
        path = Path(value)

        if not path.is_file():
            return False

        return True

    def is_folder_path_valid(self, value):
        path = Path(value)

        if not path.is_dir():
            return False

        return True

    def clean_filesystem_path(self, path):
        directory = Path(path).resolve()

        protected_paths = {
            Path("/"),
            Path.home(),
        }

        if directory in protected_paths:
            raise Exception(f"folder path '{path}' is protected")

        if not directory.exists():
            return True

        if not directory.is_dir():
            raise Exception(f"file path '{path}' is not a folder")

        for item in directory.iterdir():
            if item.is_file() or item.is_symlink():
                item.unlink()

            elif item.is_dir():
                shutil.rmtree(item)

        return True

    def copy_filesystem_path(self, first_path, second_path):
        shutil.copytree(first_path, second_path, dirs_exist_ok=True)

        return True

    def move_filesystem_path(self, first_path, second_path):
        source = Path(first_path)
        destination = Path(second_path)

        destination.mkdir(parents=True, exist_ok=True)

        for path in source.iterdir():
            shutil.move(path, destination / path.name)

        return True

    def setup_filesystem_tree(
        self,
        parent_path: Path,
        options: FolderEntityFileSystemTreeSetupOptions,
    ):
        if not parent_path.exists():
            raise Exception(f"filesystem path '{parent_path}' is invalid")

        parent_path.mkdir(parents=True, exist_ok=True)
        for entity in options.entities or []:
            entity_path = parent_path / entity.name

            if isinstance(entity, FolderEntityFileSystemTreeSetupOptions):
                entity_path.mkdir(parents=True, exist_ok=True)
                self.setup_filesystem_tree(entity_path, entity)

            elif isinstance(entity, FileEntityFileSystemTreeSetupOptions):
                if not entity_path.exists():
                    entity_path.write_text(entity.content, encoding=entity.encoding)


singleton = FileSystemManager()
