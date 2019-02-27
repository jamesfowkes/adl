import clang.cindex

def flatten(l):

    flat = []
    for el in l:
        if type(el) is list:
            flat.extend(el)
        else:
            flat.append(el)
    return flat

def sort_by_line_number(refs):
    by_line_number = {}
    for r in refs:
        by_line_number.setdefault(r.location.line, []).append(r)

    return by_line_number

class ParsedFile:

    def __init__(self, filepath):
        self.index = clang.cindex.Index.create()
        self.tu = self.index.parse(str(filepath))

    def _find_nodes_recurse(self, node, filter_func=None):
        if filter_func is None:
            filter_func = lambda n: True

        if filter_func(node):
            return node

        return flatten([self._find_nodes_recurse(c, filter_func) for c in node.get_children()])

    def find_varrefs(self, varname):
        def filter_function(node):
            return node.kind.is_reference() and node.displayname == varname

        return self._find_nodes_recurse(self.tu.cursor, filter_function)


    def find_typerefs(self, typename, varname=None):

        def filter_function(node):
            if varname is not None:
                return node.kind.is_reference() and node.get_definition().spelling == typename
            else:
                return node.kind.is_reference() and node.get_definition().spelling == typename and node.displayname.startswith(varname)

        return self._find_nodes_recurse(self.tu.cursor, filter_function)

