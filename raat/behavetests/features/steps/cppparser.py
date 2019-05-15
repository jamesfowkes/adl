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

def node_string(node):
    try:
        spelling = node.get_definition().spelling
    except:
        spelling = "-"

    try:
        typename = "Type: " + node.type.spelling
    except:
        typename = None

    return "@{:d}: {:s} ({:s}), {:s}, {:s}, {:s}, {:d} children".format(
        node.location.line,
        node.displayname, spelling,
        "def" if node.is_definition() else "not def",
        "decl" if node.kind.is_declaration() else "not decl",
        typename if typename is not None else "no type",
        len(list(node.get_children()))
    )

def print_node(node):
    print(node_string(node))

def get_children(node):
    return list(node.get_children())

def get_child(node, n):
    children = []
    try:
        children = list(node.get_children())
        return children[n]
    except:
        print("Expected node {} to have child {})".format(node_string(node), n))
        raise

def print_tu(tu):

    print ("  \t" * print_tu.tabs, end='')
    print_node(tu)

    try:
        print_tu.tabs = print_tu.tabs + 1
        for c in tu.get_children():
            print_tu(c)
        print_tu.tabs = print_tu.tabs - 1
    except:
        pass

class ParsedFile:

    def __init__(self, filepath, include_paths=[]):
        arguments = ['-x', 'c++', '-std=c++14', "-D", "BEHAVETESTS"]

        for include_path in include_paths:
            arguments.append("-I")
            arguments.append(include_path)

        self.index = clang.cindex.Index.create()
        self.tu = self.index.parse(str(filepath), args=arguments)

        #for d in self.tu.diagnostics:
        #    print(d)
        #print_tu.tabs = 0
        #print_tu(self.tu.cursor)

    def _find_nodes_recurse(self, node, filter_func=None):
        if filter_func is None:
            filter_func = lambda n: True

        if filter_func(node):
            return node

        return flatten([self._find_nodes_recurse(c, filter_func) for c in node.get_children()])

    def find_vardefs(self, varname, typename=None, custom_filter_func=None):

        def filter_function(node):
            match = node.is_definition() and node.get_definition().spelling == varname and node.kind.is_declaration()

            if match and typename is not None:
                match = (node.type.spelling == typename)

            if match and custom_filter_func is not None:
                match = custom_filter_func(node)

            return match

        return self._find_nodes_recurse(self.tu.cursor, filter_function)

    def find_struct_decl(self, typename):

        def filter_function(node):
            match = (node.type.spelling == typename) and (node.is_definition())
            match = match and (node.kind.is_declaration())
            match = match and (node.get_definition().spelling == typename)
            match = match and (node.displayname == typename)
            return match

        return self._find_nodes_recurse(self.tu.cursor, filter_function)

    def find_typedefs(self, typename, custom_filter_func=None):

        def filter_function(node):
            match = node.type.spelling == typename and node.is_definition() and node.kind.is_declaration()
            return match

        return self._find_nodes_recurse(self.tu.cursor, filter_function)

    def find_typerefs(self, typename, varname=None):

        def filter_function(node):
            match = node.kind.is_reference() and node.get_definition().spelling == typename
            if varname is not None:
                match = match and (node.displayname == varname)
            return match

        return self._find_nodes_recurse(self.tu.cursor, filter_function)
