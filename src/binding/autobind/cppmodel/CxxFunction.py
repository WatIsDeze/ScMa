from .CxxNode import CxxNode

class CxxFunction(CxxNode):
    def __init__(self, sourceObject, parent = None):
        CxxNode.__init__(self, sourceObject, parent)
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
        return self.sourceObject.spelling + "(" + (", ".join(args)) + ")"

    def generate(self):
        template = 'COMMAND({functioname}, "{proto}", "{doc}")'

        # {'i', "int"},
        # {'b', "bool"},
        # {'f', "float"},
        # {'F', "Float"}, //?
        # {'t', "tea?"}, //??
        # {'T', "Tea?"}, //??
        # {'E', "Exp?"}, //??
        # {'N', "Number?"}, //??
        # {'D', "Double?"}, //??
        # {'S', "String?"},
        # {'s', "string"},
        # {'e', "e?"},
        # {'r', "r?"},
        # {'$', "$?"},
        # {'1', "1?"},
        # {'2', "2?"},
        # {'3', "3?"},
        # {'4', "4?"},
        # {'C', "C?"},
        # {'V', "V?"}

        spelling2proto  = {
            "int": "i",
            "float": "f",
            "bool": "b",
            "const char *": "s",
            "char *": "s",
        }

        proto = ""
        for arg in self.forEachArgument():
            if (arg.spelling in spelling2proto):
                proto = proto + spelling2proto[arg.spelling]
            else:
                raise ValueError("Function argument type not implemented", arg.spelling, self.sourceObject.spelling)
            # for typedef in arg.get_children():
            #     if typedef.kind.name == "TYPE_REF":
            #         if (typedef.spelling in spelling2proto):
            #             proto = proto + spelling2proto[typedef.spelling]
            #         else:
            #             raise ValueError("Function argument type not implemented", typedef.spelling, self.sourceObject.spelling)

        return template.format(
            functioname = self.sourceObject.spelling,
            proto = proto,
            doc = self.comment()
        )