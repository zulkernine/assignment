import re


class NotUniqueuserName(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return ("Error: "+self.value + " already exist!")

class InvalidAge(Exception):
    def __init__(self,value):
        self.value = value
    def __str__(self):
        if(self.value < 0):
            return ("Error: Age must be positive, provided: " + str(self.value))
        else:
            return ("Error: User must be minimum 16 years old. Current age: " + str(self.value))

class InvalidEmail(Exception):
    def __init__(self,value):
        self.value = value
    def __str__(self):
        return ("Error: Invalid email: " + self.value)



def check_mail(email):
    regex = '^(\w|\.|\_|\-)+[@](\w|\_|\-|\.)+[.]\w{2,3}$'
    if(re.search(regex, email)):
        pass
    else:
        raise InvalidEmail(email)

def check_username(usrname,passedList):
    if usrname in passedList:
        raise NotUniqueuserName(usrname)

def check_age(age):
    if age<16 :
        raise InvalidAge(age)

if __name__ == '__main__':
    userList = [
        ("abcd123","abcd123@domain.com",23),
        ("jkafsld34", "jdsl8934@domain.com", -1),
        ("kjlds3094","sjdk43domain.com",23),
        ("dfskjl09", "kjlgr9834@domain.com", 12),
        ("egkjlrw89", "gkj4893@domain.com", 23),
        ("ekjl34", "abcd123@domain.com", 23),
        ("abcd123", "abcd123@domain.com", 23),
    ]

    passedList = {}
    
    for user in userList:
        try:
            check_username(user[0],passedList)
            check_mail(user[1])
            check_age(user[2])
            passedList[user[0]] = user
        except Exception as e:
            print(e)
    
    print("\n\nPassed users:")
    print(" ,".join(passedList))
