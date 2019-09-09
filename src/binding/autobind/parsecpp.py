from clang import cindex
from .compileflags import CompileFlagsFor
import asciitree
import os
import json
import sys

from .cppmodel.CxxNode import CxxNode
from .cppmodel.CxxFunction import CxxFunction


libclang_paths = [
    "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libclang.dylib",
    "/usr/local/lib/libclang.so"
]

EXPORT_ANNOTATION = "scriptexport"

class CppParser:

    def __init__(self, file):
        self.file = file
        self.flags = CompileFlagsFor("../build", file)
        self.flags.append("-fparse-all-comments")
        self.tree = {}
        self.model = None
        self.translation_unit = None

    def start(self):
        for cpath in libclang_paths:
            if os.path.exists(cpath):
                cindex.Config.set_library_file(cpath)
                break
        
        index = cindex.Index.create()
        self.translation_unit = index.parse(self.file, self.flags)
        self.model = CxxNode(self.translation_unit.cursor)

    def cppmodel_generate(self):
        def node_factory(cursor, parent):
            if cursor.kind.name == "FUNCTION_DECL":
                first_child = next(cursor.get_children(), None)
                if not first_child is None:
                    if first_child.kind.name == "ANNOTATE_ATTR" and first_child.spelling == EXPORT_ANNOTATION:
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

    def dump_cppmodel(self):
        print (self.model.dump())

    def dump_code(self):
        for node in self.model.forEachChild():
            if type(node) is CxxFunction:
                try:
                    print (node.generate())
                except(Exception):
                    pass

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


