import matplotlib.pyplot as plt
import numpy as np

f = open("timeIS.txt","r")
g = open("timeQS.txt","r")
h = open("timeMS.txt","r")
j = open("timeSS.txt","r")
l = open("timeBS.txt","r")
m = open("timeShS.txt","r")
i=0
Is=np.zeros(shape=(2,10),dtype = float)
Ss=np.zeros(shape=(2,10),dtype = float)
Qs=np.zeros(shape=(2,10),dtype = float)
Ms=np.zeros(shape=(2,10),dtype = float)
Bs=np.zeros(shape=(2,10),dtype = float)
Shs=np.zeros(shape=(2,10),dtype = float)
for i in range(0,10):
    x=f.readline().replace('us\n','')
    y=g.readline().replace('us\n','') 
    z=h.readline().replace('us\n','') 
    w=j.readline().replace('us\n','') 
    v=l.readline().replace('us\n','') 
    q=m.readline().replace('us\n','') 
    
    #k=int(i/10000)
    Is[0][i]=x
    Is[1][i]=i
    Qs[0][i]=y
    Qs[1][i]=i
    Ms[0][i]=z
    Ms[1][i]=i
    Ss[0][i]=w
    Ss[1][i]=i
    Bs[0][i]=v
    Bs[1][i]=i
    Shs[0][i]=q
    Shs[1][i]=i

    
    print(i)
f.close()
g.close()
h.close()
j.close()
l.close()
m.close()

plt.plot(Is[1],Is[0],label="Insertion Sort")
plt.plot(Ss[1],Ss[0],label="Selection Sort")
plt.plot(Qs[1],Qs[0],label="Quick Sort")
plt.plot(Ms[1],Ms[0],label="Merge Sort")
plt.plot(Bs[1],Bs[0],label="Bubble Sort")
plt.plot(Shs[1],Shs[0],label="Shell Sort")
plt.legend()
plt.show()