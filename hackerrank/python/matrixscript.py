#!/bin/python3
import math
import os
import random
import re
import sys

first_multiple_input = input().rstrip().split()

n = int(first_multiple_input[0])

m = int(first_multiple_input[1])

matrix = []

for _ in range(n):
    matrix_item = input()
    matrix.append(matrix_item)

a = []
for j in range(0, m):
    for i in range(0, n):
        a.append(matrix[i][j])
s = "".join(a)
san = re.sub(r"([a-z,A-Z,0-9])[!,@,#,$,%,&, ]+([a-z,A-Z,0-9])", "\g<1> \g<2>", s).strip()
print(san)
