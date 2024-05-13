import random

flag = "fi3r_n4n0comb4ttant"

keys = []

"""
each key will be a quadruplet :
[flag letter, potential a*, potential +b, potential ^c]

then in each round I'll choose which combination of operations I want.
"""



for i in range(len(flag)):
    keys.append([flag[i], random.randint(1, 0xff), random.randint(0, 0xff), random.randint(0, 0xff)])

print(keys)


"""
Generated :

[['f', 247, 67, 4], ['i', 83, 98, 161], ['3', 25, 12, 199], ['r', 92, 236, 173], ['_', 242, 29, 197], ['n', 151, 35, 135], ['4', 39, 93, 131], ['n', 209, 191, 188], ['0', 37, 231, 11], ['c', 49, 10, 17], ['o', 30, 14, 41], ['m', 195, 195, 184], ['b', 108, 59, 52], ['4', 22, 57, 212], ['t', 173, 153, 234], ['t', 110, 67, 25], ['a', 104, 121, 187], ['n', 163, 255, 7], ['t', 208, 197, 51]]
"""
