from .CxxNode import CxxNode
import json
from clang import cindex
from .. import parsecpp
from ..generator import CubeScriptBinding

class CxxFunction(CxxNode):
    def __init__(self, sourceObject, parent = None):
        CxxNode.__init__(self, sourceObject, parent)
        first_child = next(sourceObject.get_children(), None)
        if not first_child is None:
            if first_child.kind == cindex.CursorKind.ANNOTATE_ATTR and first_child.spelling.startswith(parsecpp.EXPORT_ANNOTATION):
                start = first_child.spelling.rindex(parsecpp.EXPORT_ANNOTATION)
                if start == 0:
                    self.customFuctionName = first_child.spelling[len(parsecpp.EXPORT_ANNOTATION):]

        pass

    def forEachArgument(self):
        def iterate(node):
            if node.type.kind.name == "FUNCTIONPROTO":
                for c in node.type.argument_types():
                    yield c
            # for c in node.get_children():
            #     yield from iterate(c)
        
        yield from iterate(self.sourceObject)

    def getContainingNamespaces(self, node, data):
        if node is None:
            data = self.getContainingNamespaces(self.sourceObject, data)
        else:
            if node:
                if (node.kind == cindex.CursorKind.NAMESPACE):
                    data.append(node.spelling)
                if node.semantic_parent and node.semantic_parent.kind != cindex.CursorKind.TRANSLATION_UNIT:
                    data = self.getContainingNamespaces(node.semantic_parent, data)
        return data

    def comment(self):
        if self.sourceObject.brief_comment is None:
            return ""
        return self.sourceObject.brief_comment

    def __str__(self):
        args = []
        for arg in self.forEachArgument():
            args.append(arg.spelling)
        functionName = self.sourceObject.spelling
        namespace = "::".join(self.getContainingNamespaces(self.sourceObject, [])) 
        if self.customFuctionName:
            functionName = self.customFuctionName
        if namespace:
            functionName = namespace + "::" +functionName
        returntype = self.sourceObject.result_type.spelling
        return returntype + " " + functionName + "(" + (", ".join(args)) + ")"