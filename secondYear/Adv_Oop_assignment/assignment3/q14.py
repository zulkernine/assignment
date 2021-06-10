class Palindrome() :
    def __init__(self,value) :
        self.__value = value
        self.__findPlindromes()
    
    def __findPlindromes(self):
        if not isinstance(self.__value,str):
            print("Passed value is not a string!")
            self.__pwords = []
            return

        words = self.__value.split(" ")
        pwords = []
        for word in words:
            if word == word[::-1] :
                pwords.append(word)
        self.__pwords = pwords
    
    def hasPalindromeWords(self):
        return len(self.__pwords)!=0

    def getPalindromeWords(self):
        l = []
        l.extend(self.__pwords)
        return l

def main():
    string = str(input("Text: "))
    pchecker = Palindrome(string)
    if pchecker.hasPalindromeWords() :
        print("Total number of words: ",len(pchecker.getPalindromeWords()))
        print("Palindrome words: ",pchecker.getPalindromeWords())
    else :
        print("Given text contains no palindrome words :(")
    return

    
if __name__ == '__main__':
    main()

# Example input text: asf anna fasjkld civic fajds kayak level jsafkl madam faskn rotor f aklf fjksal stats lksad klfa kljlfg jfaksddf tenet saldf
