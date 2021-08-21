import sys

def fib(l, d):
    if l > 1:
        if l in d:
            return d[l]
        r = fib(l - 1, d) + fib(l - 2, d)
        d[l] = r
        return r
    return l

def main():
    d = {}
    line = sys.stdin.readline()
    while line:
        print(fib(int(line), d))
        line = sys.stdin.readline()

if __name__ == '__main__':
    main()
