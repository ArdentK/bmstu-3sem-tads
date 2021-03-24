import random
import math

f = open("txt/num.txt", "r")
n = [0]*88
m = [0]*88
w = [0]*88
for i in range(88):
    data = f.readline().split()
    n[i] = int(data[0])
    m[i] = float(data[1])
    w[i] = int(data[2])
f.close()

# n = int(input("Введите n: "))

# m = float(input("Введите процент разреженности в долях: "))

# w = int(input("0 - обычная матрица и вектор, 1 - разреженная: "))

for i in range(len(n)):
    # кол-во нулевых элементов
    k = math.ceil(n[i] * n[i] * m[i])

    if w[i] == 1:
        f = open("data/sparse/data_" + str(n[i]) + "x" + str(n[i]) + "_" +
                 str(int(100 - m[i] * 100)) + "%.txt", "w")
        a = [-1 for i in range(n[i] * n[i])]

        for j in range(k):
            pos = random.randint(0, n[i] * n[i] - 1)
            # print(n[i] * n[i] - 1, pos)
            while a[pos] == 0:
                pos = random.randint(0, n[i] * n[i] - 1)
            a[pos] = 0

        for j in range(n[i] * n[i]):
            if a[j] != 0:
                x = random.randint(-10, 10)
                while x == 0:
                    x = random.randint(-10, 10)
                a[j] = x

        v = [-1 for j in range(n[i])]

        k = math.ceil(n[i] * m[i])

        for j in range(k):
            pos = random.randint(0, n[i] - 1)
            while v[pos] == 0:
                pos = random.randint(0, n[i] - 1)
            v[pos] = 0

        for j in range(n[i]):
            if v[j] != 0:
                x = random.randint(-10, 10)
                while x == 0:
                    x = random.randint(-10, 10)
                v[j] = x
        # сгенерировала обычную матрицу, конвертирую в 3 объекта
        a_n = []
        a_j = []
        a_i = []
        v_a = []
        v_i = []
        for j in range(n[i]*n[i]):
            if (a[j] != 0):
                a_n.append(a[j])
                a_j.append(j % n[i] + 1)

        a_i = [0 for j in range(n[i])]
        a_i.append(len(a_n) + 1)
        step = 0
        for d in range(n[i]):
            j = 0
            while j < n[i] and a[j + d * n[i]] == 0:
                j += 1
            if j != n[i]:
                step += 1
                a_i[d] = step
            while j < n[i]:
                if a[j + d * n[i]] != 0:
                    step += 1
                j += 1

        for j in range(n[i]):
            if (v[j] != 0):
                v_a.append(v[j])
                v_i.append(len(v_a))

        d = 0
        while d <= n[i]:
            if a_i[d] != 0:
                j = d - 1
                while j >= 0 and a_i[j] == 0:
                    a_i[j] = a_i[d]
                    j -= 1
            d += 1

        last = len(a_n)
        for j in range(len(a_i)):
            if a_i[j] >= last:
                ind = j
                break

        for j in range(ind + 1, len(a_i)):
            a_i[j] = last + 1

        f.write(str(n[i]) + '\n')
        f.write(str(len(a_n)) + '\n')

        for d in range(len(a_n)):
            f.write(str(a_n[d]))
            if d != (len(a_n) - 1):
                f.write(" ")
        f.write("\n")

        for d in range(len(a_j)):
            f.write(str(a_j[d]))
            if d != (len(a_j) - 1):
                f.write(" ")
        f.write("\n")

        for d in range(len(a_i)):
            f.write(str(a_i[d]))
            if d != (len(a_i) - 1):
                f.write(" ")
        f.write("\n")

        f.write(str(n[i]) + '\n')
        f.write(str(len(v_a)) + '\n')

        for d in range(len(v_a)):
            f.write(str(v_a[d]))
            if d != (len(v_a) - 1):
                f.write(" ")
        f.write("\n")

        for d in range(len(v_i)):
            f.write(str(v_i[d]))
            if d != (len(v_i) - 1):
                f.write(" ")
        f.close()

    if w[i] == 0:
        f = open("data/std/data_" + str(n[i]) + "x" + str(n[i]) + "_" +
                 str(100 - int(m[i] * 100)) + "%.txt", "w")

        a = [-1 for i in range(n[i] * n[i])]
        # print(len(a), k)

        for j in range(k + 1):
            pos = random.randint(0, n[i] * n[i] - 1)
            # print(n[i]*n[i], pos)
            while a[pos] == 0:
                pos = random.randint(0, n[i] * n[i] - 1)
            a[pos] = 0

        for j in range(n[i] * n[i]):
            if a[j] != 0:
                x = random.randint(-10, 10)
                while x == 0:
                    x = random.randint(-10, 10)
                a[i] = x

        v = [-1 for i in range(n[i])]

        k = math.ceil(n[i] * m[i])

        for j in range(k):
            pos = random.randint(0, n[i] - 1)
            while v[pos] == 0:
                pos = random.randint(0, n[i] - 1)
            v[pos] = 0

        for j in range(n[i]):
            if v[j] != 0:
                x = random.randint(-10, 10)
                while x == 0:
                    x = random.randint(-10, 10)
                v[j] = x

        f.write(str(n[i]) + '\n')
        f.write(str(n[i]) + '\n')

        for j in range(n[i] * n[i]):
            f.write(str(a[j]))
            if j % n[i] != (n[i] - 1):
                f.write(" ")
            else:
                f.write("\n")

        f.write(str(len(v)) + '\n')

        for j in range(n[i]):
            f.write(str(v[j]))
            if i != (n[i] - 1):
                f.write(" ")

        f.close()
