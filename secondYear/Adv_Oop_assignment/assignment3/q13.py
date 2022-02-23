def seq_generator(a,q):
    while a<100000 :
        a = a*q
        yield a
    return a


for element in seq_generator(11,31):
    print(element)
