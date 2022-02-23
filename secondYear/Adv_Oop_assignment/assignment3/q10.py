squares = map(lambda x: x*x , range(20))

oddsquare = filter(lambda x: (x%2!=0), squares)

print("Odd square: ", list(oddsquare))
