from autobind.fileiterator import ForEachTranslationUnitInDirectory
from autobind.compileflags import CompileFlagsFor, ForEachCompileFile
from autobind.parsecpp import CppParser 
import sys
import os

def debug_dump(file):
    parser = CppParser(file)
    parser.start()
    parser.tree_generate()
    parser.dump_tree()

def debug_cppmodel(file):
    parser = CppParser(file)
    parser.start()
    parser.cppmodel_generate()
    parser.dump_cppmodel()

def generate_code(file):
    parser = CppParser(file)
    parser.start()
    parser.cppmodel_generate()
    parser.dump_code()

def find_deps(file, commonRoot):
    parser = CppParser(file, skipComments = True)
    parser.start(skipFunctionBodies = True)
    parser.cppmodel_find_includes(commonRoot)
    # parser.dump_code()

def binding_sources():
    filelist = []
    for file in ForEachTranslationUnitInDirectory(".", "py"):
        filelist.append(str(file))
    print(";".join(filelist))

def cppfilelist():
    filelist = []
    for file in ForEachTranslationUnitInDirectory("../engine", "cpp"):
        filelist.append(str(file))
    for file in ForEachTranslationUnitInDirectory("../game", "cpp"):
        filelist.append(str(file))
    for file in ForEachTranslationUnitInDirectory("../shared", "cpp"):
        filelist.append(str(file))
    return filelist

def input_sources():
    print(";".join(cppfilelist()))

def calculate_output(file):
    path, ext = os.path.splitext(str(file))
    outputname = (path + ".binding" + ext).replace(os.path.sep, "+")
    # print(outputname)
    return outputname

def output_sources():
    filelist = cppfilelist()
    bindfilelist = []
    for file in filelist:
        bindfilelist.append(calculate_output(file))
    print(";".join(bindfilelist))

def usage():
    print("Usage: {} (dump|cppmodel|gen) <file> | (binding|input|ouput)".format(sys.argv[0]), file=sys.stderr)

if __name__ == "__main__":
    # for file in ForEachTranslationUnitInDirectory("../game"):
    #     flags = CompileFlagsFor("../build", file)
    #     print ("{}\n\t{}".format(file, " ".join(flags)))

    args = sys.argv[1:]

    if len(args) == 2:
        if args[0] == "dump":
            debug_dump(args[1])
        elif args[0] == "cppmodel":
            debug_cppmodel(args[1])
        elif args[0] == "gen":
            generate_code(args[1])
        elif args[0] == "deps":
            find_deps(args[1], "..")
        elif args[0] == "genlist":
            print(args[1])
        elif args[0] == "cmake_output":
            print(calculate_output(args[1]))
        else:
            usage()
    elif len(args) == 1:
        if args[0] == "binding":
            binding_sources()
        elif args[0] == "input":
            input_sources()
        elif args[0] == "output":
            output_sources()
        else:
            usage()
    else:
        usage()
