import re
import string
import os.path
from os import path


def NumberEachItem(): #number of for each item

    text = open("Groceries.txt", "r") #open Groceries text to read and work through information
    dictionary = dict()
    for line in text:
        line = line.strip()
        word = line.lower()
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
            dictionary[word] = 1

    for key in list(dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])
      
    text.close()

def NumberInstances(v): #number of for specific item

    v = v.lower()
    text = open("Groceries.txt", "r")
    wordCount = 0;
    for line in text:
        line = line.strip()
        word = line.lower()
        if word == term:
            wordCount += 1

    text.close()

def collectData(): #histogram function to be called in c++

    text = open("Groceries.txt", "r")
    frequency = open("Groceries", "r")
    dictionary = dict()
    for line in text:
        line = line.strip()
        word = line.lower()
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
            dictionary[word] = 1

    for key in list(dictionary.keys()):
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key] + "\n")


    text.close()
    frequency.close()
