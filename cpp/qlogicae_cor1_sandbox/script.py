import json

from loguru import logger


def add(a, b):
    logger.info(f"Adding {a} + {b}")

    return a + b


data = {"result": add(2, 3), "status": "ok"}

print(json.dumps(data))
