# After taking the acceleration values with using the MPU6050 and SD Card, MPU6050 IMU sensor is used for acceleration data collection and two Arduino systems: Arduino Nano and Uno to process signals. By taking the noise covariance into account, 
# Kalman filter estimation performance was improved and acceleration estimation of a=0.675 m/s2 was obtained within a range of 0.675±0.002.

import numpy as np

# Read acceleration data from text file (assuming MPU6050 provides acceleration data directly)
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

# Define time step (dt) according to the system dynamics (assumed as 0.085)
dt = 0.085

# Initialize the filter with an initial estimate of the state and the associated uncertainty (covariance)
# Initial position and velocity based on the provided scenario
x_estimated = np.array([[0], [1.35]])  # [position, velocity], starting from position 0 and initial velocity 1.35 m/s
P_estimated = np.eye(2) * 0.01  # Initial covariance matrix with small values

# Define the state transition matrix
A = np.array([[1, dt],
              [0, 1]])

# Define the control input matrix (assuming control input is velocity in PMW value)
velocity_pmw = 1.3  # Assume velocity in PMW value is 1.3
B = np.array([[0], [velocity_pmw]])


# Define the measurement matrix (assuming we can directly measure acceleration)
H = np.array([[0, 1]])

# Define the measurement noise covariance (adjust based on sensor noise characteristics)
R = np.array([[0.001]])  # Reduced measurement noise covariance

# Define the process noise covariance (adjust based on expected system dynamics and sensor characteristics)
Q = np.array([[0.01, 0],
              [0, 0.01]])  # Increased process noise covariance

# Placeholder for filtered acceleration data
filtered_acceleration_data = []

# Open output file to write results
with open('output.txt', 'w') as output_file:
    for i in range(len(acceleration_data)):
        # Prediction step
        x_predicted = np.dot(A, x_estimated)
        P_predicted = np.dot(A, np.dot(P_estimated, A.T)) + Q

        # Correction step
        z = np.array([[acceleration_data[i]]])  # Measurement (acceleration from MPU6050)
        K = np.dot(P_predicted, np.dot(H.T, np.linalg.inv(np.dot(H, np.dot(P_predicted, H.T)) + R)))
        x_estimated = x_predicted + np.dot(K, (z - np.dot(H, x_predicted)))
        P_estimated = np.dot((np.eye(2) - np.dot(K, H)), P_predicted)

        # Save the estimated acceleration
        filtered_acceleration_data.append(x_estimated[1, 0])

        # Write the results to the output file
        output_file.write(f"Step {i+1}\n")
        output_file.write(f"Estimated position: {x_estimated[0][0]}\n")
        output_file.write(f"Estimated velocity: {x_estimated[1][0]}\n")
        output_file.write(f"Measured acceleration: {acceleration_data[i]}\n")
        output_file.write(f"Filtered acceleration: {x_estimated[1][0]}\n\n")

# Convert filtered acceleration data to a numpy array
filtered_acceleration_data = np.array(filtered_acceleration_data)

# Save filtered acceleration data to a text file
np.savetxt('filtered_acceleration_data.txt', filtered_acceleration_data, fmt='%.6f')

# Calculate the difference between original and filtered acceleration data
differences = acceleration_data - filtered_acceleration_data

# Save the differences to a text file
np.savetxt('acceleration_differences.txt', differences, fmt='%.6f')

# Append differences to the output file
with open('output2.txt', 'a') as output_file:
    output_file.write("Differences:\n")
    for i, difference in enumerate(differences):
        output_file.write(f"Step {i+1} Difference: {difference}\n")

    # Calculate and append the total difference to the output file
    total_difference = np.sum(np.abs(differences))
    output_file.write(f"Total Difference: {total_difference}\n")

