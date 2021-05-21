from itertools import compress
n = int(input("Range: "))
odd = compress(range(n),[i%2 for i in range(n)])
even = compress(range(n), [not i % 2 for i in range(n)])
print("Even numbers: ",list(even))
print("Odd numbers: ",list(odd))
