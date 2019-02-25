import clang.cindex

def flatten(l):

    flat = []
    for el in l:
        if type(el) is list:
            flat.extend(el)
        else:
            flat.append(el)
    return flat

class ParsedFile:

    def __init__(self, filepath):
        self.index = clang.cindex.Index.create()
        self.tu = self.index.parse(str(filepath))

    def _find_typerefs_recurse(self, node, typename):
        if node.kind.is_reference():
            ref_node = node.get_definition()
            if ref_node.spelling == typename:
                return (typename, node.location.line, node.location.column)

        return flatten([self._find_typerefs_recurse(c, typename) for c in node.get_children()])


    def find_typerefs(self, typename, varname=None):
        #typerefs = []
        return self._find_typerefs_recurse(self.tu.cursor, typename)
        #return typerefs