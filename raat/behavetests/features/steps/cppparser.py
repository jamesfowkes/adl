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

    def find_vardefs(self, varname, typename=None):
            
        def filter_function(node):
            match = node.is_definition() and node.get_definition().spelling == varname and node.kind.is_declaration()
            if typename is not None:
                match = match and (node.type.spelling == typename)
            return match

        return self._find_nodes_recurse(self.tu.cursor, filter_function)

    def find_typerefs(self, typename, varname=None):

        def filter_function(node):
            match = node.kind.is_reference() and node.get_definition().spelling == typename
            if varname is not None:
                match = match and (node.displayname == varname)
            return match

        return self._find_nodes_recurse(self.tu.cursor, filter_function)
