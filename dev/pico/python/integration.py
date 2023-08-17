import numpy as np
def integral (start_time, end_time,deltat):
    #finding the number of rectangles
    n=(end_time-start_time)/deltat
    i=1
    #define a running total of rectangle areas
    totalArea = 0
    while(i < n):
       
        #calculate next height of rectangle
        t = start_time + i*deltat
        v = 6*t +5 #height of rectangle
        #calculate area of rectangle
        area = v * deltat

        #add that rectangle right to running total
        totalArea += area
        i+=1
        #return the total area -->estimation of distance traveled
    return totalArea
print(integral(0, 3 ,0.001))