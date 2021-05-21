def flatten_json(y):
    result = {}

    def flatten(x, name=''):
        if type(x) is dict:
            for a in x:
                flatten(x[a], name + a + "_")
        elif type(x) is list:
            i = 0
            for a in x:
                flatten(a, name + str(i) +"_")
                i += 1
        else:
            result[name[:-1]] = x

    flatten(y)
    return result

nested = {'fullname': 'Alessandra', 'age': 41, 'phone-numbers': ['+447421234567', '+447423456789'], 'residence': {
    'address': {'first-line': 'Alexandra Rd', 'second-line': '', }, 'zip': 'N8 0PP', 'city': 'London', 'country': 'UK', }, }

for k,v in flatten_json(nested).items():
    print(k," : ",v)
print(flatten_json(nested))
