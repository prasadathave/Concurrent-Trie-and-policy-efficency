import matplotlib.pyplot as plt
import csv
import numpy as np
w =[]
x = []
y = []
z=[]


with open('rwlock.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    # print(plots)
    for row in plots:
        # print(row)
        if(row[0].strip()!="cache_size"):
            x.append(int(float(row[0])))
            y.append(int(float(row[1])))
            w.append(int(float(row[3])))
            z.append(int(float(row[2])))
# print(x)
# print(y)


plt.plot(np.array(x),np.array(y), label='time vs write intensive')
plt.plot(np.array(x),np.array(w), label='time vs read intensive')
plt.plot(np.array(x),np.array(z), label='time vs combination')
plt.xlabel('Number of threads')
plt.ylabel('time')
plt.title('Results for rw_lock')
plt.legend()
plt.show()