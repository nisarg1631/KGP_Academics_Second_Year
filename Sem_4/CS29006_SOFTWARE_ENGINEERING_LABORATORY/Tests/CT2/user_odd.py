from library_odd import Base


class Derived(Base):
    def bar(self):
        return self.foo()


if __name__ == '__main__':
    if hasattr(Base, 'foo'):
        pass
    else:
        print("\'foo\' not implemented in Base.")
        exit(1)
    d1 = Derived()
    d1.bar()
