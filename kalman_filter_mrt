import numpy as np

class KalmanFilter:
    def __init__(self, initial_state_mean, initial_state_covariance, transition_matrix, observation_matrix, observation_covariance, process_covariance):
        self.state_mean = initial_state_mean
        self.state_covariance = initial_state_covariance
        self.transition_matrix = transition_matrix
        self.observation_matrix = observation_matrix
        self.observation_covariance = observation_covariance
        self.process_covariance = process_covariance

    def predict(self):
        self.state_mean = np.dot(self.transition_matrix, self.state_mean)
        self.state_covariance = np.dot(np.dot(self.transition_matrix, self.state_covariance), self.transition_matrix.T) + self.process_covariance

    def update(self, observation):
        innovation = observation - np.dot(self.observation_matrix, self.state_mean)
        innovation_covariance = np.dot(np.dot(self.observation_matrix, self.state_covariance), self.observation_matrix.T) + self.observation_covariance
        kalman_gain = np.dot(np.dot(self.state_covariance, self.observation_matrix.T), np.linalg.inv(innovation_covariance))
        self.state_mean = self.state_mean + np.dot(kalman_gain, innovation)
        self.state_covariance = self.state_covariance - np.dot(np.dot(kalman_gain, self.observation_matrix), self.state_covariance)

def main():
    # DATA1 adlı veri dosyasından verileri oku
    with open("DATA1.txt", "r") as file:
        data = []
        for line in file:
            parts = line.split(":")
            acceleration_data = float(parts[1].split(",")[-1])  # Satırın sonundaki z değerini al
            data.append(acceleration_data)

    # Filtre parametrelerini tanımla
    initial_state_mean = np.array([data[0]])  # Başlangıç durumu
    initial_state_covariance = np.array([[1]])  # Başlangıç durumu kovaryansı
    transition_matrix = np.array([[1]])  # Durum geçiş matrisi
    observation_matrix = np.array([[1]])  # Gözlem matrisi
    observation_covariance = np.array([[1]])  # Gözlem kovaryansı
    process_covariance = np.array([[0.01]])  # Süreç kovaryansı

    # Kalman filtresini oluştur
    kf = KalmanFilter(initial_state_mean, initial_state_covariance, transition_matrix, observation_matrix, observation_covariance, process_covariance)

    # Veriler üzerinde filtreleme yap
    filtered_data = []
    for observation in data:
        kf.predict()
        kf.update(np.array([observation]))
        filtered_data.append(kf.state_mean[0])

    # Filtrelenmiş verileri yazdır
    for i, filtered_value in enumerate(filtered_data):
        print("Veri {}: {:.2f}".format(i+1, filtered_value))

if __name__ == "__main__":
    main()
