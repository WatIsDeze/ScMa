from autobind.fileiterator import ForEachTranslationUnitInDirectory
from autobind.compileflags import CompileFlagsFor, ForEachCompileFile
from autobind.parsecpp import CppParser 
import sys

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

if __name__ == "__main__":
    # for file in ForEachTranslationUnitInDirectory("../game"):
    #     flags = CompileFlagsFor("../build", file)
    #     print ("{}\n\t{}".format(file, " ".join(flags)))

    args = sys.argv[1:]

    if len(args) == 2:
        if args[0] == "dump":
            debug_dump(args[1])
        if args[0] == "cppmodel":
            debug_cppmodel(args[1])
        if args[0] == "gen":
            generate_code(args[1])
    else:
        print("Usage: {} (dump|cppmodel|gen) <file>".format(sys.argv[0]), file=sys.stderr)
