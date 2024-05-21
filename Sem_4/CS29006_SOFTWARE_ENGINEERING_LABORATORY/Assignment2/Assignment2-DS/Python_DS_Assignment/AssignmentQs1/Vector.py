class Vector:

    def __init__(self, *args):
        self._coords = []
        if isinstance(args[0], int):
            self._coords = [0] * args[0]
        else:
            try:
                for x in args[0]:
                    if not isinstance(x, int):
                        raise Exception("Iterable should contain only 'int'")
                    self._coords.append(x)
            except Exception as what:
                print(what)

    def __len__(self):
        return len(self._coords)

    def __getitem__(self, j):  # indexing from 1
        return self._coords[j - 1]

    def __setitem__(self, j, val):  # indexing from 1
        self._coords[j - 1] = val

    def __add__(self, other):
        try:
            if len(self) == len(other):
                return Vector([x + y for (x, y) in zip(self._coords, other._coords)])
            else:
                raise Exception("Length error.")
        except Exception as what:
            print(what)

    def __eq__(self, other):
        return self._coords == other._coords

    def __ne__(self, other):
        return not self == other

    def __str__(self):
        if not len(self):
            return "<>"
        vec = f"<{self._coords[0]}"
        for coord in self._coords[1:]:
            vec = vec + f", {coord}"
        vec = vec + ">"
        return vec

    def __sub__(self, other):
        return self + (-other)

    def __neg__(self):
        return Vector([-x for x in self._coords])

    def __rmul__(self, value):
        return self * value

    def __mul__(self, other):
        try:
            if isinstance(other, int):
                return Vector([other * x for x in self._coords])
            elif isinstance(other, Vector):
                if len(self) == len(other):
                    return sum([u * v for (u, v) in zip(self._coords, other._coords)])
                else:
                    raise Exception("Length error.")
            else:
                raise Exception(f"Cannot multiply objects of type {type(self).__name__} and {type(other).__name__}")
        except Exception as what:
            print(what)


def main():
    v1 = Vector(5)  # construction from integer
    v2 = Vector(7)  # construction from integers
    v3 = Vector([1, 2, 3, 4, 5])  # construction from iterable
    v4 = Vector((x % 2 + 1 for x in range(5)))  # construction from iterable
    temp_dict = {'a': 1, 'b': 2, 'c': 3, 'd': 4, 'e': 5}
    v5 = Vector(temp_dict.values())  # construction from iterable

    print(f"v1 = {v1}")
    print(f"v2 = {v2}")
    print(f"v3 = {v3}")
    print(f"v4 = {v4}")
    print(f"v5 = {v5}")
    print()
    print(f"Length of v2 = {len(v2)}")
    print(f"Length of v5 = {len(v5)}")
    print()
    print(f"v4[4] = {v4[4]}")
    print("Setting v2[5] to 9")
    v2[5] = 9
    print(f"v2 = {v2}")
    print()
    print(f"v1 == v2 -> {v1==v2}")
    print(f"v3 == v5 -> {v3 == v5}")
    print(f"v3 != v4 -> {v3 != v4}")
    print(f"v3 != v5 -> {v3 != v5}")
    print()
    print(f"v4 + v3 = {v4 + v3}")
    print(f"v4 - v3 = {v4 - v3}")
    print(f"-v4 = {-v4}")
    print()
    print(f"v3 * 3 = {v3 * 3}")
    print(f"3 * v3 = {3 * v3}")
    print(f"v3 * v4 = {v3 * v4}")


if __name__ == '__main__':
    main()
