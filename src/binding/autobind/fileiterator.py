from pathlib import Path

def ForEachTranslationUnitInDirectory(path, ext = "cpp"):
    pathObject = Path(path)
    for file in pathObject.iterdir():
        if file.is_file() and str(file).endswith("." + ext):
            yield file
        if file.is_dir():
            yield from ForEachTranslationUnitInDirectory(str(file), ext)