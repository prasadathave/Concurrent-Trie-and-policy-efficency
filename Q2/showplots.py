import os
import multiprocessing
import matplotlib.pyplot as plt
import csv


def runcommand(str1):
    os.system(str1)


p1 = multiprocessing.Process(target=runcommand,args=['python3 loops1.py'])

p2 = multiprocessing.Process(target=runcommand,args=['python3 local1.py'])

p3 = multiprocessing.Process(target=runcommand,args=['python3 random1.py'])

p1.start()
p2.start()
p3.start()