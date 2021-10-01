def merge_the_tools(string, k):
    sl = len(string)
    u = set()
    for i, c in enumerate(string):
        if i > 0 and i % k == 0:
            u = set()
            print("")
        if c not in u:
            print(c, end="")
            u.add(c)
    print("")

if __name__ == '__main__':
    string, k = input(), int(input())
    merge_the_tools(string, k)
