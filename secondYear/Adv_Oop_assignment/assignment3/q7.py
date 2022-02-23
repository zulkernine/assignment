from os import walk,path
import os

def findfiles(dirpath):
    for root, dirname, filenames in walk(dirpath):
        for fname in filenames:
            print(path.join(root, fname))


if __name__ == '__main__':
    findfiles(os.getcwd())
