from .CxxNode import CxxNode

class CxxClass(CxxNode):
    
    def __init__(self, sourceObject, parent = None):
        CxxNode.__init__(self, sourceObject, parent)

    def get_inheritance_hierarchy(self):
        pass
    # def function