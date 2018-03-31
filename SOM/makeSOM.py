import numpy as np

x = int(raw_input())
y = int(raw_input())

print x
print y 
mat = np.random.choice((x*y),(x,y),False)
# print mat

mat=np.sort(np.sort(mat),axis=0)
# print mat
for x in mat.ravel():
    print x

key = int(raw_input())

print key