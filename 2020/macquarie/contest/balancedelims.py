import sys

def balanceDelims(s):
    m = {')':'(', ']':'[', '}':'{'}
    st = []
    for c in s.rstrip():
        if c in m:
            if st:
                p = st.pop()
                if m[c] == p:
                    continue
            return False
        else:
            st.append(c)
    return (not bool(st))

def main():
    line = sys.stdin.readline()
    print(balanceDelims(line))

if __name__ == '__main__':
    main()
