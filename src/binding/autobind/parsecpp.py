from clang import cindex
from .compileflags import CompileFlagsFor
import os
import json
import sys

from .cppmodel.CxxNode import CxxNode
from .cppmodel.CxxFunction import CxxFunction
from .cppmodel.CxxInclude import CxxInclude


libclang_paths = [
    "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libclang.dylib",
    "/usr/local/lib/libclang.so",
    "/usr/lib/x86_64-linux-gnu/libclang-7.so"
]

EXPORT_ANNOTATION = "scriptexport"

class CppParser:

    def __init__(self, file, skipComments = False):
        self.file = file
        self.flags = CompileFlagsFor("../build", file)
        if skipComments is False:
            self.flags.append("-DSCRIPTBIND_RUN")
            self.flags.append("-fparse-all-comments")
        self.tree = {}
        self.model = None
        self.translation_unit = None

    def start(self, skipFunctionBodies = False):
        for cpath in libclang_paths:
            if os.path.exists(cpath):
                cindex.Config.set_library_file(cpath)
                break
        
        index = cindex.Index.create()
        if skipFunctionBodies is False:
            self.translation_unit = index.parse(self.file, self.flags)
        else:
            self.translation_unit = index.parse(self.file, self.flags, None, cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES | cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
        self.model = CxxNode(self.translation_unit.cursor)

    def cppmodel_generate(self):
        def node_factory(cursor, parent):
            if cursor.kind == cindex.CursorKind.FUNCTION_DECL:
                first_child = next(cursor.get_children(), None)
                if not first_child is None:
                    if first_child.kind == cindex.CursorKind.ANNOTATE_ATTR and first_child.spelling.startswith(EXPORT_ANNOTATION):
                        return CxxFunction(cursor, parent)

            return None

        def iterate(tree, node, file):
            for c in node.get_children():
                if c:
                    if c.location:
                        if c.location.file:
                            if c.location.file.name == file:
                                tree_node = node_factory(c, tree)
                                if tree_node is None:
                                    tree_node = tree
                                iterate(tree_node, c, file)

        iterate(self.model, self.translation_unit.cursor, self.file)

    def cppmodel_find_includes(self, commonRootDir):
        commonRoot = os.path.abspath(commonRootDir)

        def node_factory(cursor, parent, fromFile):
            fromDir = os.path.dirname(fromFile)
            if cursor.kind == cindex.CursorKind.INCLUSION_DIRECTIVE:
                include_file = os.path.abspath(os.path.join(fromDir, cursor.spelling))
                if os.path.exists(include_file) and include_file.startswith(commonRoot):
                    print(include_file)
                    return CxxInclude(cursor, include_file, parent)

            return None

        def iterate(tree, node, file):
            # nonlocal commonRoot
            filedir = os.path.dirname(os.path.abspath(file))
            for c in node.get_children():
                if c:
                    if c.location:
                        if c.location.file:
                            cursor_abs_path = os.path.abspath(os.path.join(filedir, c.location.file.name))
                            if cursor_abs_path.startswith(commonRoot):
                                tree_node = node_factory(c, tree, cursor_abs_path)
                                if tree_node is None:
                                    tree_node = tree
                                iterate(tree_node, c, file)

        iterate(self.model, self.translation_unit.cursor, self.file)

    def dump_cppmodel(self):
        print (self.model.dump())

    def cppmodel(self):
        return self.model

    def dump_code(self):
        template = """#include "shared/cube.h"
{}"""
        generated_funcs = []
        for node in self.model.forEachChild():
            if type(node) is CxxFunction:
                generated_funcs.append(node.generate())
        if len(generated_funcs) == 0:
            return ""
        return self.model
        template.format("\n".join(generated_funcs))

    def dump_includes(self):
        includes = set()
        for node in self.model.forEachChild():
            if type(node) is CxxInclude:
                includes.add(node.absoluteFile)
        return list(includes)

    def tree_generate(self):

        def append_tree(tree, node):
            if not "_children" in tree:
                tree["_children"] = []
            tree["_node"] = node

            return tree

        def iterate(tree, node, file):
            for c in node.get_children():
                if c:
                    if c.location:
                        if c.location.file:
                            if c.location.file.name == file:
                                tree_node = append_tree({}, c)
                                tree["_children"].append(tree_node)
                                iterate(tree_node, c, file)

        self.tree = append_tree(self.tree, self.translation_unit.cursor)
        iterate(self.tree, self.translation_unit.cursor, self.file)

    def dump_tree(self):
        def stringifier(obj):
            k = obj.kind.name
            s = obj.spelling
            d = obj.displayname
            c = obj.brief_comment

            return {"kind": k, "spelling": s, "displayname": d, "comment": c}

        print (json.dumps(self.tree, sort_keys=True, indent=4, default=stringifier))

        print ("---- DIAG ----", file=sys.stderr)
        for diag in self.translation_unit.diagnostics:
            print (diag, file=sys.stderr)


