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

fib = fibonacci_generator(7)
for num in fib:
    print(num,end=", ")
print()
