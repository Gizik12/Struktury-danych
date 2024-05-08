import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000])
insertHeap = np.array([72, 173, 136, 272, 291, 362, 511, 183])
insertList = np.array([10766, 27416, 33039, 35260, 61808, 119060, 123720, 200838])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, insertList, label='Insert LinkedList', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, insertHeap, label='Insert Heap', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')

plt.title('Insert Operations: Linked List vs. Heap Performance Comparison.')
plt.legend()
plt.grid(True)

plt.show()
