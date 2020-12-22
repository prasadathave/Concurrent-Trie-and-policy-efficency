import matplotlib.pyplot as plt
import csv
import numpy as np
w =[]
x =[]
y =[]
z=[]


with open('rwlock.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    # print(plots)
    for row in plots:
        # print(row)
        if(row[0].strip()!="cache_size"):
            x.append(int(float(row[0])))
            y.append(int(float(row[2])))

with open('hohlock.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    # print(plots)
    for row in plots:
        # print(row)
        if(row[0].strip()!="cache_size"):
            z.append(int(float(row[2])))

with open('slock.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    # print(plots)
    for row in plots:
        # print(row)
        if(row[0].strip()!="cache_size"):
            w.append(int(float(row[2])))




plt.plot(np.array(x),np.array(y), label='threads vs mix workload time in rwlock')
plt.plot(np.array(x),np.array(w), label='threads vs mix workload time in slock')
plt.plot(np.array(x),np.array(z), label='threads vs mix workload time in hohlock')
plt.xlabel('Number of threads')
plt.ylabel('time')
plt.title('Results for mix workload')
plt.legend()
plt.show()