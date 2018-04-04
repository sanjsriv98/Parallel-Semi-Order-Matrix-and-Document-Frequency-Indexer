import numpy as np
import sys

x = int(sys.argv[1])  # int(raw_input())
# x = x#int(sys.argv[2])  # int(raw_input())
# key = int(sys.argv[3])  # int(raw_input())

print x
print x
mat = np.random.choice((x*x), (x, x), False)
# print mat

mat = np.sort(np.sort(mat), axis=0)
# print mat
for x in mat.ravel():
    print x

# print key
