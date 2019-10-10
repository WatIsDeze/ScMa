import json
# from ..cppmodel.CxxNode import CxxNode
# from ..cppmodel.CxxInclude import CxxInclude

def Generate(cxxRootNode):
    from ..cppmodel.CxxFunction import CxxFunction
    
    template = """#include "shared/cube.h"
{}"""
    generated_funcs = []
    for node in cxxRootNode.forEachChild():
        if type(node) is CxxFunction:
            generated_funcs.append(GenerateFunction(node))
    if len(generated_funcs) == 0:
        return ""
    return template.format("\n".join(generated_funcs))

def GenerateFunction(cxxFunc):
#         template = """COMMAND({functionname}, "{proto}", {doc});
# """
#         template_custom = """ICOMMAND({functionname}, "{proto}", ({argdecl}), {realfunctionname}({arguse}), {doc});
# """

    template = """{returnt} {functionname}({argdecl});
COMMAND({functionname}, "{proto}", {doc});
"""
    template_custom = """namespace {namespace}{{ {returnt} {functionnamebound}({argdecl}); }}
ICOMMAND({functionname}, "{proto}", ({argdecl}), {realfunctionname}({arguse}), {doc});
"""
    template_custom_nns = """{returnt} {realfunctionname}({argdecl});
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
        "ident *": "r",
        "CommandTypes::ArgLen": "N",
        "CommandTypes::Expression": "e",
        "CommandTypes::OptionalFloat": "F",
        "tagval *": "t",
    }

    proto = ""
    cppargs = []
    argname = []
    argnameitr = 0
    for arg in cxxFunc.forEachArgument():
        if (arg.spelling in spelling2proto):
            proto = proto + spelling2proto[arg.spelling]
            cppargs.append(arg.spelling)
            argname.append(chr(97 + argnameitr))
            argnameitr = argnameitr + 1
        else:
            raise ValueError("Function argument type not implemented", arg.spelling, cxxFunc.sourceObject.spelling)
        # for typedef in arg.get_children():
        #     if typedef.kind.name == "TYPE_REF":
        #         if (typedef.spelling in spelling2proto):
        #             proto = proto + spelling2proto[typedef.spelling]
        #         else:
        #             raise ValueError("Function argument type not implemented", typedef.spelling, cxxFunc.sourceObject.spelling)

    arguselst = []
    for [a, b] in zip(cppargs, argname):
        arguselst.append(a + " " + b)

    argdecl = ", ".join(cppargs)
    argusedecl = ", ".join(arguselst)
    arguse = ", ".join(argname)
    functionName = cxxFunc.sourceObject.spelling
    returntype = cxxFunc.sourceObject.result_type.spelling
    namespace = "::".join(cxxFunc.getContainingNamespaces(cxxFunc.sourceObject, []))
    realFunctionName = ""
    if namespace:
        realFunctionName = namespace + "::"

    realFunctionName = realFunctionName + functionName
    functionNameBound = functionName

    if cxxFunc.customFuctionName or namespace:
        if cxxFunc.customFuctionName:
            functionName = cxxFunc.customFuctionName
        
        if namespace:
            return template_custom.format(
                argdecl = argusedecl,
                arguse = arguse,
                realfunctionname = realFunctionName,
                functionname = functionName,
                functionnamebound = functionNameBound,
                namespace = namespace,
                proto = proto,
                returnt = returntype,
                doc = json.dumps(str(cxxFunc.comment()))
            )
        else:
            return template_custom_nns.format(
                argdecl = argusedecl,
                arguse = arguse,
                realfunctionname = realFunctionName,
                functionname = functionName,
                namespace = namespace,
                proto = proto,
                returnt = returntype,
                doc = json.dumps(str(cxxFunc.comment()))
            )
    else:
        return template.format(
            argdecl = argdecl,
            functionname = functionName,
            realfunctionname = realFunctionName,
            namespace = namespace,
            proto = proto,
            returnt = returntype,
            doc = json.dumps(str(cxxFunc.comment()))
        )