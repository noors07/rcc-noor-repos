import numpy as np 

def diff (tau, deltat):
    x1=3*(tau)**2 + 5*(tau+deltat) +7
    x2=3*(tau+deltat)**2+5*(tau+deltat) +7
    der=(x2 -x1)/deltat 
    return der

if __name__=="__main__":
    print(diff(0,0.01))
    