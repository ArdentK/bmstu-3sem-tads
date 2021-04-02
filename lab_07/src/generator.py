import random

num_points = [10, 20, 50]
num_arc = [20, 50, 80]

for i in range(len(num_points)):
    name = "data/data_" + str(num_points[i]) + ".txt"
    f = open(name, "w")

    f.write(str(num_points[i]) + "\n")

    for j in range(num_arc[i]):
        n1 = random.randint(1, num_points[i])
        n2 = random.randint(1, num_points[i])
        while (n1 == n2):
            n2 = random.randint(1, num_points[i])
        f.write(str(n1) + "->" + str(n2) + '\n')

    f.close()
