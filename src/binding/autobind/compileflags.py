import json
import os

compile_commands_filename = "compile_commands.json"
compile_commands = {}

def InitializeCompileCommands(buildpath):
    if not buildpath in compile_commands or compile_commands[buildpath] is None:
        compile_commands_path = os.path.join(buildpath, compile_commands_filename)
        if os.path.exists(compile_commands_path):
            with open(compile_commands_path, "r") as read_file:
                compile_commands[buildpath] = json.load(read_file)
        else:
            raise Exception("Invalid buildpath: {} not found in: {}".format(compile_commands_filename, buildpath))

def CompileFlagsFor(buildpath, file):
    InitializeCompileCommands(buildpath)

    if not buildpath in compile_commands or compile_commands[buildpath] is None:
        raise Exception("Unknown error: {} not loaded from: {}".format(compile_commands_filename, buildpath))

    absfile = os.path.abspath(file)
    for entry in compile_commands[buildpath]:
        if entry["file"] == absfile:
            flags = entry["command"].split()
            return flags[1:-5]

    raise Exception("TranslationUnit {} not found in {}, {}".format(absfile, compile_commands_filename, buildpath))

def ForEachCompileFile(buildpath, rootpath):
    InitializeCompileCommands(buildpath)

    if not buildpath in compile_commands or compile_commands[buildpath] is None:
        raise Exception("Unknown error: {} not loaded from: {}".format(compile_commands_filename, buildpath))

    absrootstr = os.path.abspath(os.path.join(os.path.abspath(buildpath), "..")) + os.path.sep

    for entry in compile_commands[buildpath]:
        yield os.path.join(rootpath, entry["file"].replace(absrootstr, ""))