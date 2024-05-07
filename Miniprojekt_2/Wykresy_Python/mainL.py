import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000])
extract_max_time = np.array([1467, 1495, 1455, 1640, 1630, 1712.5, 1975, 2150])
peek_time = np.array([505, 556, 496, 521, 540, 560, 620, 607])
return_size_time = np.array([503, 548, 549, 540, 536, 570, 590, 513])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, extract_max_time, label='Extract Max', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, peek_time, label='Peek', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, return_size_time, label='Return Size', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')


plt.title('Peek, ReturnSize and ExtractMax Number of Elements for LinkedList Operations')
plt.legend()
plt.grid(True)

plt.show()
