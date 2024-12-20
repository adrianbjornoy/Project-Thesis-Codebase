import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Serial port configuration
serial_port = 'COM5'
baud_rate = 9600

# Initialize serial connection
ser = serial.Serial(serial_port, baud_rate)

# Matrix dimensions
num_rows = 6
num_cols = 6

# Initialize the matrix globally
matrix = np.zeros((num_rows, num_cols))

def read_matrix():
    global matrix
    matrix_list = []
    while True:
        try:
            line = ser.readline().decode('utf-8').strip()
        except UnicodeDecodeError:
            # Handle decoding errors
            continue
        if not line:
            # Empty line indicates end of matrix
            if len(matrix_list) == num_rows:
                # Update the global matrix variable
                matrix = np.array(matrix_list, dtype=float)
                return
            else:
                matrix_list = []  # Reset if incomplete
        else:
            row_data = [float(value) for value in line.split(',')]
            if len(row_data) == num_cols:
                matrix_list.append(row_data)

def update(*args):
    global matrix
    read_matrix()  # This updates the global matrix variable
    mat.set_array(matrix.T)  # Transpose the matrix before displaying
    # Print the current matrix values
    print("Current Matrix Values:")
    print(matrix.T)  # Display the transposed matrix for reference
    return [mat]

# Set up the plot
fig, ax = plt.subplots()
mat = ax.imshow(matrix.T, cmap='viridis', vmin=300, vmax=1000)
fig.colorbar(mat)

# Remove axes for clarity
ax.axis('off')

# Start the animation
ani = animation.FuncAnimation(fig, update, interval=100, blit=True)
plt.show()


