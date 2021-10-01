#!/bin/python

[n, k] = map(int, input().split())
a = sorted(map(int, input().split()))
T = [[-1 for j in range(n)] for i in range(n)]
for i in range(n):
    if i == 0: 
        T[i][0] = 0
        T[i][1] = 0
    else:
        for j in range(max(0,k-(n-i-1)), k+1):
            if T[i-1][j] == -1:
                continue
            T[i][j] = T[i-1][j] + (a[i]-a[i-1])*j*(n-i-(k-j))
            T[i][j] += (a[i]-a[i-1]) * (i-j) * (k-j)

        for j in range(max(0,k-(n-i)), k):
            if T[i-1][j] != -1:
                if T[i][j+1] == -1:
                    T[i][j+1] = T[i-1][j] + (a[i]-a[i-1]) * (j*(n-i-(k-j))+(i-j)*(k-j))
                else:
                    T[i][j+1] = min(T[i][j+1], T[i-1][j] + (a[i]-a[i-1])*(j*(n-i-(k-j))+(i-j)*(k-j)))
print(T[n-1][k])
