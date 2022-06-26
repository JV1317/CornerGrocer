import re
import string
import collections

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def MultiplicationTable(number):
    for i in range(1, 11):
        print(number, "X", i, "=", number * i)

def DoubleValue(number):
    return number * 2


def ItemCounter():
    # Open file (safely) and use the collections module to store the values as a dictionary
    with open('CS210_Project_Three_Input_File.txt') as fIn:
        counts = collections.Counter(line.strip() for line in fIn)
    # For every key (item name), print the item and the amount sold
    for key in counts:
        print('%s %d' % (key, counts[key]))

def NumItemCounter(item):
    # Ignore case by capitalizing first letter regardless of entry
    item = item.capitalize()
    # Open file to read and use the built-in count function
    with open('CS210_Project_Three_Input_File.txt') as fIn:
        data = fIn.read()
        occurences = data.count(item)
        return occurences

def ItemWriter():
    # Open both the read and the write files
    with open('frequency.dat', "w") as fOut:    
        # Same code as in "ItemCounter" to store the values as a dictionary
        with open('CS210_Project_Three_Input_File.txt') as fIn:
            counts = collections.Counter(line.strip() for line in fIn)
        # Write the item and counts to the output file
        for key in counts:
            fOut.write('%s %d\n' % (key, counts[key]))
    # If the file was properly closed, tell the user
    if fOut.closed:
        print('Success')
