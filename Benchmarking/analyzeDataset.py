#Implementation of the dataset reducing algo
#1.0 Add all vectors to 1 single vector. 
#2.0 Statictics about the delta-t 
import pandas as pd 
import numpy as np
import math
import os 
import matplotlib.pyplot as plt

files = "Benchmarking\Data"
resultsTime = []

for file in os.scandir(files):
    if file.is_file():
        with open(file.path, "r") as csvfile:
            previous = 0
            resultVectors= []
            counter = 0 
            for line in csvfile.readlines():
                if(counter > 0):    
                    array = line.split(',')
                    if(len(array) == 4):
                        vector = math.sqrt((float(array[1]) ** 2) + (float(array[2]) ** 2) + (float(array[3]) ** 2))
                        resultVectors.append(vector)
                        if(counter > 1 and float(array[0])  > float(previous)):
                            delta = float(array[0]) - float(previous)
                            resultsTime.append(delta)
                        previous = array[0]
                counter = counter + 1
print("Number intervals: ", len(resultsTime))
print("Mean delta-t: ",np.mean(resultsTime))
print("Standard deviation: ",np.std(resultsTime))
print("Median: " ,np.median(resultsTime))
print("Minimum: ",np.min(resultsTime))
print("Maximum: ", np.max(resultsTime))

deltaSeries = pd.Series(resultsTime)
deltaSeries.plot()
plt.show()
        
