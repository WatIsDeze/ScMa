from .CxxNode import CxxNode

class CxxInclude(CxxNode):
    def __init__(self, sourceObject, absoluteFile, parent = None):
        CxxNode.__init__(self, sourceObject, parent)
        self.absoluteFile = absoluteFile
        pass
