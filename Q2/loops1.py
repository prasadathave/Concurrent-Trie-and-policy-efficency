import matplotlib.pyplot as plt
import csv
import numpy as np
x = []
y = []

with open('loop.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    # print(plots)
    for row in plots:
        # print(row)
        if(row[0].strip()!="cache_size"):
            x.append(int(float(row[0])))
            y.append(int(100*float(row[1])))
# print(x)
# print(y)


plt.plot(np.array(x[1:100]),np.array(y[1:100]), label='FIFO')
plt.plot(np.array(x[101:200]),np.array(y[101:200]), label='LRU Exact')

plt.plot(np.array(x[201:300]),np.array(y[201:300]), label='RANDOM')
plt.plot(np.array(x[301:400]),np.array(y[301:400]), label='LRUApprox')
plt.xlabel('cache_size')
plt.ylabel('hit_rate')
plt.title('Results for loop data')
plt.legend()
plt.show()