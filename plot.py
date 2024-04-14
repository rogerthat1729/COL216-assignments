import matplotlib.pyplot as plt

# Data
y_values = [50776344, 42992398, 10415208, 5989172, 5394892]
config = ["red", "red", "red", "red", "red"]
# colors = ['red', 're', 'green', 'black', 'orange']
x_values = [2, 5, 8, 11, 14]

color_map = { 'red': 'no-write-allocate, write-back'}

# Create a figure and an axes.
fig, ax = plt.subplots()

# Plotting data
plt.plot(x_values, y_values, marker='', linestyle = '-')  # 'o' adds circle markers

for x, y, color in zip(x_values, y_values, config):
    if color_map[color] in ax.get_legend_handles_labels()[1]:
        plt.plot(x, y, marker='o', linestyle='', color=color, markersize=10)
    else:
        plt.plot(x, y, marker='o', linestyle='', color=color, markersize=10, label = color_map[color])

# Setting the labels and title
ax.set_xlabel('Total Cache Size (in log(number of bytes))')
ax.set_ylabel('Minimum Clock Cycles Possible')
ax.set_title('Clock Cycles vs Cache Size')

# Adding grid
plt.grid(True)

plt.legend(title = 'Configurations')

# Show the plot
plt.show()
