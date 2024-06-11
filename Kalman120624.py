import numpy as np

# Read acceleration data from text file
acceleration_data = []
with open('LASTDATA.txt', 'r') as file:
    for line in file:
        try:
            # Try to convert the line to a float
            acceleration_value = float(line.strip())
            acceleration_data.append(acceleration_value)
        except ValueError:
            # Skip lines that cannot be converted to float
            continue

acceleration_data = np.array(acceleration_data)

# Define time step
dt = 0.1

# Initialize the filter with an initial estimate of the state and the associated uncertainty (covariance)
x_estimated = np.array([[0], [0]])  # [position, velocity]
P_estimated = np.eye(2)

# Define the state transition matrix
A = np.array([[1, dt], 
              [0, 1]])

# Define the control input matrix
B = np.array([[0.5 * dt**2], 
              [dt]])

# Define the measurement matrix (assuming we can measure acceleration directly)
H = np.array([[0, 1]])

# Define the measurement noise covariance
R = np.array([[0.01]])  # Reduced measurement noise covariance

# Define the process noise covariance
Q = np.array([[0.1, 0.1], 
              [0.1, 0.2]])  # Increased process noise covariance

# Placeholder for filtered acceleration data
filtered_acceleration_data = []

# Open a file to write the output
with open('output.txt', 'w') as output_file:
    for i in range(len(acceleration_data)):
        # Prediction step
        u = np.array([[acceleration_data[i]]])  # Control input is the acceleration data
        x_predicted = np.dot(A, x_estimated) + np.dot(B, u)
        P_predicted = np.dot(A, np.dot(P_estimated, A.T)) + Q

        # Correction step
        z = np.array([[acceleration_data[i]]])  # Measurement
        K = np.dot(P_predicted, np.dot(H.T, np.linalg.inv(np.dot(H, np.dot(P_predicted, H.T)) + R)))
        x_estimated = x_predicted + np.dot(K, (z - np.dot(H, x_predicted)))
        P_estimated = np.dot((np.eye(2) - np.dot(K, H)), P_predicted)

        # Save the estimated acceleration
        filtered_acceleration_data.append(x_estimated[1, 0])

        # Print the estimated position, velocity, and acceleration
        output_file.write(f"Step {i+1}\n")
        output_file.write(f"Estimated position: {x_estimated[0][0]}\n")
        output_file.write(f"Estimated velocity: {x_estimated[1][0]}\n")
        output_file.write(f"Measured acceleration: {acceleration_data[i]}\n")
        output_file.write(f"Filtered acceleration: {x_estimated[1][0]}\n")
        output_file.write("\n")

# Convert filtered acceleration data to a numpy array
filtered_acceleration_data = np.array(filtered_acceleration_data)

# Save filtered acceleration data to a text file
np.savetxt('filtered_acceleration_data.txt', filtered_acceleration_data, fmt='%.6f')

# Calculate the difference between original and filtered acceleration data
differences = acceleration_data - filtered_acceleration_data

# Save the differences to a text file
np.savetxt('differences.txt', differences, fmt='%.6f')

# Print the differences
with open('output.txt', 'a') as output_file:
    for i, difference in enumerate(differences):
        output_file.write(f"Step {i+1} Difference: {difference}\n")

    # Calculate and print the total difference
    total_difference = np.sum(np.abs(differences))
    output_file.write(f"Total Difference: {total_difference}\n")

