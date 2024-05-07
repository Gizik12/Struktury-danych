import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000, 1000000, 5000000, 10000000 , 40000000])
extract_max_time = np.array([474, 518, 537, 567, 595, 627, 842, 973,1490,2895,4480, 7565])
peek_time = np.array([37, 42, 40, 40, 50, 71, 83, 111, 355, 380, 425, 480])
return_size_time = np.array([44, 46, 41, 46, 47, 80, 94, 142, 150,185,165,175])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, extract_max_time, label='Extract Max', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, peek_time, label='Peek', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, return_size_time, label='Return Size', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')


plt.title('Peek, ReturnSize and ExtractMax Number of Elements for Heap Operations')
plt.legend()
plt.grid(True)

plt.show()
