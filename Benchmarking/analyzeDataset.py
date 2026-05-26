#Implementation of the dataset reducing algo
#1.0 Add all vectors to 1 single vector. 
#2.0 Statictics about the delta-t 
import pandas as pd 
import numpy as np
import math
import os 
import matplotlib.pyplot as plt

files = "Benchmarking\Data"
filesToWrite = "..\Bachelor_Thesis_Code\Implementation\Data"
resultsTime = []

for file in os.scandir(files):
    output_path = os.path.join(filesToWrite, file.name)
    if file.is_file():
        with open(output_path , "w") as outputFile:
            outputFile.write("Combined Vectors\n")
            with open(file.path, "r") as csvfile:
                next(csvfile) #just skip header
                previous = 0
                resultVectors= []
                for line in csvfile.readlines():   
                    array = line.split(',')
                    if(len(array) == 4):
                        vector = math.sqrt((float(array[1]) ** 2) + (float(array[2]) ** 2) + (float(array[3]) ** 2))
                        outputFile.write(f"{vector}\n")
                        resultVectors.append(vector)
                        delta = float(array[0]) - float(previous)
                        resultsTime.append(delta)
                        previous = array[0]
print("Number intervals: ", len(resultsTime))
print("Mean delta-t: ",np.mean(resultsTime))
print("Standard deviation: ",np.std(resultsTime))
print("Median: " ,np.median(resultsTime))
print("Minimum: ",np.min(resultsTime))
print("Maximum: ", np.max(resultsTime))

deltaSeries = pd.Series(resultsTime)
deltaSeries.plot()
plt.show()
        
