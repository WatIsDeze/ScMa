from .CxxNode import CxxNode
import json
from clang import cindex
from .. import parsecpp

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

    def comment(self):
        if self.sourceObject.brief_comment is None:
            return ""
        return self.sourceObject.brief_comment

    def __str__(self):
        args = []
        for arg in self.forEachArgument():
            args.append(arg.spelling)
        functionName = self.sourceObject.spelling
        if self.customFuctionName:
            functionName = self.customFuctionName
        returntype = self.sourceObject.result_type.spelling
        return returntype + " " + functionName + "(" + (", ".join(args)) + ")"

    def generate(self):
        template = """extern {returnt} {functionname}({argdecl});
COMMAND({functionname}, "{proto}", {doc});
"""
        template_custom = """extern {returnt} {realfunctionname}({argdecl});
ICOMMAND({functionname}, "{proto}", ({argdecl}), {realfunctionname}({arguse}), {doc});
"""

        spelling2proto  = {
            "int": "i",
            "int *": "i",
            "float": "f",
            "float *": "f",
            "bool": "b",
            "const char *": "s",
            "char *": "s",
            "CommandTypes::KeyPress": "D",
            "CommandTypes::Boolean": "b",
            "ident *": "$",
            "CommandTypes::ArgLen": "N",
            "CommandTypes::Expression": "e",
            "CommandTypes::OptionalFloat": "F",
            "tagval *": "t",
        }

        proto = ""
        cppargs = []
        argname = []
        argnameitr = 0
        for arg in self.forEachArgument():
            if (arg.spelling in spelling2proto):
                proto = proto + spelling2proto[arg.spelling]
                cppargs.append(arg.spelling)
                argname.append(chr(97 + argnameitr))
                argnameitr = argnameitr + 1
            else:
                raise ValueError("Function argument type not implemented", arg.spelling, self.sourceObject.spelling)
            # for typedef in arg.get_children():
            #     if typedef.kind.name == "TYPE_REF":
            #         if (typedef.spelling in spelling2proto):
            #             proto = proto + spelling2proto[typedef.spelling]
            #         else:
            #             raise ValueError("Function argument type not implemented", typedef.spelling, self.sourceObject.spelling)

        arguselst = []
        for [a, b] in zip(cppargs, argname):
            arguselst.append(a + " " + b)

        argdecl = ", ".join(cppargs)
        argusedecl = ", ".join(arguselst)
        arguse = ", ".join(argname)
        functionName = self.sourceObject.spelling
        returntype = self.sourceObject.result_type.spelling
        if self.customFuctionName:
            realFunctionName = functionName
            functionName = self.customFuctionName
            
            return template_custom.format(
                argdecl = argusedecl,
                arguse = arguse,
                realfunctionname = realFunctionName,
                functionname = functionName,
                proto = proto,
                returnt = returntype,
                doc = json.dumps(str(self.comment()))
            )            
        else:
            return template.format(
                argdecl = argdecl,
                functionname = functionName,
                proto = proto,
                returnt = returntype,
                doc = json.dumps(str(self.comment()))
            )