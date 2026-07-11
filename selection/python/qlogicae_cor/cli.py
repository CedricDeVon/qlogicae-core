from importlib.metadata import version


def main() -> int:
    print(version("qlogicae-cor"))

    return 0


# if __name__ == "__main__":
#     raise SystemExit(main())
