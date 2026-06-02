import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

file_path = r'C:\Users\39320\Desktop\bachelor_thesis\Bachelor_Thesis_Code\Implementation\Data\02 - m1_load_0.5Nm_half_speed.csv'

df = pd.read_csv(file_path)
vibration_data = df['Combined Vectors']

plt.figure(figsize=(12, 6))
plt.plot(vibration_data[:10000])
plt.xlabel('Time-step')
plt.ylabel('Vector magnitude')
plt.grid(True, alpha=0.3)
plt.savefig("vibration_data.png")
plt.show()