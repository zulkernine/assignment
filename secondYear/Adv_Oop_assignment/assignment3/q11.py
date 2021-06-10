pyhtagorianTriplets = [(2*x+1, 2*(x**2)+2*x, 2*(x**2)+2*x+1) for x in range(1,10)]

filteredTriplets = list(filter(lambda x: x[0] < 10, pyhtagorianTriplets))

modifiedTriplets2 = map(lambda x: (
    x[0]*2, x[1]*2, x[2]*2), pyhtagorianTriplets)   #Multiply triplets by 2 to generate new triplets
modifiedTriplets3 = map(lambda x: (
    x[0]*3, x[1]*3, x[2]*3), pyhtagorianTriplets)   #Multiply triplets by 3 to generate new triplets

filteredTriplets.extend(list(filter(lambda x: x[0] < 10, modifiedTriplets2)))   #Filter triplets to get short side less than 10
filteredTriplets.extend(list(filter(lambda x: x[0] < 10, modifiedTriplets3)))

print(filteredTriplets)
