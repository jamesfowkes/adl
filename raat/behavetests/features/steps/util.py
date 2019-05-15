from itertools import tee, zip_longest

def pairwise(iterable, overlap=True):
    # pairwise('ABCDEFG', True) --> (A,B), (B,C), (C,D)..."
    # pairwise('ABCDEFG', False) --> (A,B), (C,D), (E<F), (G, None)"

    if overlap:
        a, b = tee(iterable)
        next(b, None)
        return zip(a, b)
    else:
        args = [iter(iterable)] * 2
        return zip_longest(*args, fillvalue=None)