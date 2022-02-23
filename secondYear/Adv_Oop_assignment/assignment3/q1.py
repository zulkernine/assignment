import math

n = int(input("Range: "))
# n=11
numbers = {i: True for i in range(2, n+1)}

for i in range(2,math.ceil(math.sqrt(n))):
    if(numbers[i]):
        j =  i*i
        while j <= n :
            numbers[j] = False
            j += i
print("Prime numbers upto {n} are :".format(n=n))
for (k,v) in numbers.items() :
    if(v):
        print(k ,end=", ")
print()
