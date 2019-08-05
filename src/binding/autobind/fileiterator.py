from pathlib import Path

def ForEachTranslationUnitInDirectory(path):
    pathObject = Path(path)
    for file in pathObject.iterdir():
        if file.is_file() and str(file).endswith(".cpp"):
            yield file
        if file.is_dir():
            yield from ForEachTranslationUnitInDirectory(str(file))