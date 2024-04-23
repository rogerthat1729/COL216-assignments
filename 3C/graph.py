import matplotlib.pyplot as plt

sizes = [128, 256, 512, 1024, 2048, 4096]
times_type_1 = [2, 27, 268, 2324, 17569, 218853]
times_type_2 = [1, 14, 92, 586, 3546, 20053]
times_type_3 = [3, 52, 484, 2720, 35969, 383982]
times_type_4 = [1, 13, 93, 233, 3554, 33282]
times_type_5 = [3, 51, 512, 2103, 36041, 380330]
times_type_6 = [3, 28, 277, 1048, 14482, 210456]

sizes1 = [128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768]
in_transpose_1 = [4, 19, 89, 879, 5145, 23542, 115326, 527112, 3421055]
in_transpose_2 = [9, 19, 86, 603, 4832, 24729, 120970, 526570, 2398925]
out_transpose1 = [5, 25, 75, 579, 3599, 20808, 95559, 421712, 1956967]
out_transpose2 = [5, 12, 93, 1223, 4039, 22472, 110833, 495096, 2986876] 

# Plotting the filtered data with distinct colors
# plt.figure(figsize=(10, 6))
# plt.plot(sizes, times_type_1, marker='o', color='blue', label='Type 1')
# plt.plot(sizes, times_type_2, marker='o', color='green', label='Type 2')
# plt.plot(sizes, times_type_3, marker='o', color='red', label='Type 3')
# plt.plot(sizes, times_type_4, marker='o', color='cyan', label='Type 4')
# plt.plot(sizes, times_type_5, marker='o', color='magenta', label='Type 5')
# plt.plot(sizes, times_type_6, marker='o', color='yellow', label='Type 6')

plt.figure(figsize=(10, 6))
plt.plot(sizes1, in_transpose_1, marker='o', color='blue', label='In-place Transpose 1')
plt.plot(sizes1, in_transpose_2, marker='o', color='green', label='In-place Transpose 2')
plt.plot(sizes1, out_transpose1, marker='o', color='red', label='Out-of-place Transpose 1')
plt.plot(sizes1, out_transpose2, marker='o', color='cyan', label='Out-of-place Transpose 2')

# Adding labels, title, legend, and setting the log scale for better visibility
plt.xlabel('Size of Matrix')
plt.ylabel('Time (microseconds)')
plt.title('Execution Time for Matrix Transpose vs. Matrix Size for Different Types')
plt.legend()
plt.yscale('log')  # Logarithmic scale due to the wide range of values
plt.xscale('log')  # Logarithmic scale for sizes, as sizes are powers of two
plt.grid(True, which="both", ls="--")
plt.show()
