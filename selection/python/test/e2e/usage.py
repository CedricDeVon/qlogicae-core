import pkgutil

from qlogicae_cor import v1

for module in pkgutil.walk_packages(
    v1.__path__,
    prefix=v1.__name__ + ".",
):
    print(module.name)


