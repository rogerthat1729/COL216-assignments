import pandas as pd
import plotly.graph_objects as go
import matplotlib.pyplot as plt

df = pd.read_csv('output.csv')
df['Size']*=32

#plot this df using plt
# plt.figure(figsize=(10, 6))
# plt.plot(df['Size'], df['ijk'], marker='o', color='blue', label='ijk')
# plt.plot(df['Size'], df['ikj'], marker='o', color='green', label='ikj')
# plt.plot(df['Size'], df['jik'], marker='o', color='red', label='jik')
# plt.plot(df['Size'], df['jki'], marker='o', color='orange', label='jki')
# plt.plot(df['Size'], df['kij'], marker='o', color='magenta', label='kij')
# plt.plot(df['Size'], df['kji'], marker='o', color='yellow', label='kji')

# plt.xlabel('Size of Matrix')
# plt.ylabel('Time for Multiplication (microseconds)')
# plt.title('Execution Time for Matrix Multiplication vs. Matrix Size for Different Loop Orders')
# plt.legend()
# plt.grid(True, which="both", ls="--")
# plt.show()

plt.figure(figsize=(10, 6))
plt.plot(df['Size'], df['in_ij'], marker='o', color='blue', label='inPlace_ij')
plt.plot(df['Size'], df['in_ji'], marker='o', color='green', label='inPlace_ji')
plt.plot(df['Size'], df['out_ij'], marker='o', color='red', label='outPlace_ij')
plt.plot(df['Size'], df['out_ji'], marker='o', color='yellow', label='outPlace_ji')

plt.xlabel('Size of Matrix')
plt.ylabel('Time for Transpose (microseconds)')
plt.title('Execution Time for Matrix Transpose vs. Matrix Size')
plt.legend()
plt.grid(True, which="both", ls="--")
plt.show()
