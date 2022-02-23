def fibonacci_generator(n):
    prev = 1
    yield prev
    cur = 1
    yield cur

    for _ in range(n-2):
        temp = prev + cur
        prev = cur
        cur = temp
        yield cur

n = int(input("Count: "))
fib = fibonacci_generator(n)
for num in fib:
    print(num,end=", ")
print()
