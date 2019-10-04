from pathlib import Path
import os

def ForEachTranslationUnitInDirectory(path, ext = "cpp"):
    pathObject = Path(path)
    dirs = []
    output = []
    for file in pathObject.iterdir():
        if file.is_file() and str(file).endswith("." + ext):
            output.append(file)
        if file.is_dir() and str(file) != ".":
            dirs.append(file)
    for d in dirs:
        # d = os.path.join(path, d)
        output = output + ForEachTranslationUnitInDirectory(d, ext)
        
    return output