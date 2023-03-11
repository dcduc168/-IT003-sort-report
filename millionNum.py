import random

n=1000000
arrays = [round(random.uniform(1, 1000000), 2) for i in range(n)]

arrays.sort(reverse=True)

# Write the arrays to a file
with open("data_2.txt", "w") as f:

    for array in arrays:
        f.write(str(array) + " ")
