import string
import random

sizes = [10, 100, 300, 500, 1000, 2000, 3000,
         4000, 5000, 6000, 7000, 8000, 9000, 10000]

for i in range(len(sizes)):
    name = "data/data_" + str(sizes[i]) + ".txt"
    f = open(name, "w")

    f.write(str(sizes[i]) + '\n')

    for j in range(sizes[i]):
        word_len = random.randint(1, 39)
        for k in range(word_len):
            f.write(str(random.choice(string.ascii_letters)))
        f.write("\n")

    f.close()
