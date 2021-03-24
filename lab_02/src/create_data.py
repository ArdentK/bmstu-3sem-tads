import random as r

for i in range(3, 21, 1):
    name = 'data/data_' + str(i * 500) + '.txt'
    f = open(name, 'w')
    f_copy = open('data/data_02.txt', 'r')
    data = f_copy.read()
    for j in range(i):
        f.write(data + '\n')
    f_copy.close()
    f.close()
