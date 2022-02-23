isMultiple = lambda x : (x%5 == 0)

multipleOfFive = []

for n in range(0,51):
    if isMultiple(n):
        multipleOfFive.append(n)

print("Multiple of 5 : ",multipleOfFive)
