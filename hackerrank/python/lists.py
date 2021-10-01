if __name__ == '__main__':
    N = int(input())
    l = []
    for i in range(0, N):
        c = input().split()
        if len(c) > 1:
            args = tuple(int(i) for i in c[1:])
            getattr(l, c[0])(*args)
        elif c[0] == "print":
            print(l)
        else:
            getattr(l, c[0])()



