from __future__ import annotations

from copy import deepcopy
from typing import Any

from qlogicae_cor.v1.abstract_manager import (
    AbstractManager,
)
from qlogicae_cor.v1.object_merge_manager_configurations import (
    ObjectMergeManagerConfigurations,
)


class ObjectMergeManager(AbstractManager[ObjectMergeManagerConfigurations]):
    def __init__(self) -> None:
        super().__init__(ObjectMergeManagerConfigurations())

    def deep_merging(
        self,
        left: Any,
        right: Any,
    ) -> Any:
        if left is None:
            return deepcopy(right)

        if right is None:
            return deepcopy(left)

        if isinstance(left, dict) and isinstance(right, dict):
            result = deepcopy(left)

            for key, value in right.items():
                if key in result:
                    result[key] = self.deep_merging(
                        result[key],
                        value,
                    )
                else:
                    result[key] = deepcopy(value)

            return result

        if isinstance(left, list) and isinstance(right, list):
            return deepcopy(left) + deepcopy(right)

        return deepcopy(right)

    def deep_merge_fragments(
        self,
        left: Any,
        right: Any,
    ) -> Any:
        if left is None:
            return deepcopy(right)

        if right is None:
            return deepcopy(left)

        if isinstance(left, dict) and isinstance(right, dict):
            result = deepcopy(left)

            for key, value in right.items():
                if key in result:
                    result[key] = self.deep_merge_fragments(
                        result[key],
                        value,
                    )
                else:
                    result[key] = deepcopy(value)

            return result

        if isinstance(left, list) and isinstance(right, list):
            return deepcopy(right)

        return deepcopy(right)
