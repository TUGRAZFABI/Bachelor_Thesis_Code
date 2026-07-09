import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

file_path = r'C:\Users\39320\Desktop\bachelor_thesis\Bachelor_Thesis_Code\Implementation\Data\output.txt'

# MODIFIED: Use read_csv and specify the comma delimiter to unpack columns
# names=['X', 'Y'] assigns clean column names automatically
df = pd.read_csv(file_path, nrows= 10000000, header=None, sep=',', names=['X', 'Y'])

print("First few rows of extracted coordinates:")
print(df.head())

# --- 2D VISUAL FINGERPRINT PLOT ---
plt.figure(figsize=(10, 8))

# Plot X vs Y as a scatter plot to construct the visual cluster maps
plt.scatter(df['X'], df['Y'], c=df.index, cmap='viridis', s=15, alpha=0.7)

# Add a colorbar tracking the passage of time/samples
cbar = plt.colorbar()
cbar.set_label('Time / Sample Index (Window Progress)', fontsize=12)

plt.xlabel('Principal Component 1 (X Axis)', fontsize=12)
plt.ylabel('Principal Component 2 (Y Axis)', fontsize=12)
plt.title('Streaming PCA Visual Fingerprint Spatial Mapping', fontsize=14, fontweight='bold')
plt.grid(True, linestyle='--', alpha=0.5)

# Save the fingerprint layout graph
plt.savefig("visual_fingerprint_2D.png", dpi=150, bbox_inches='tight')
plt.show()