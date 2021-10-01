if __name__ == '__main__':
    s = input()
    print(s.isalnum())
    print((s.isalpha() or s.isalnum()) and not s.isdigit())
    print(s.isdigit() or s.isalnum())
    print((s.isalpha() or s.isalnum()) and not s.isupper())
    print((s.isalpha() or s.isalnum()) and not s.islower())
