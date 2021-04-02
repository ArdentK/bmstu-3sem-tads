import random as r

lens = [100, 500, 2000]

for i in range(len(lens)):
    name = "data/data_"+str(lens[i])+".txt"
    f = open(name, "w")
    a = set()
    for j in range(lens[i]):
        x = r.randint(1, 30000)
        while (x in a):
            x = r.randint(1, 30000)
        a.add(x)
        f.write(str(x) + "\n")
    f.close()
