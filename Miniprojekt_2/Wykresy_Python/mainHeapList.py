import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000])

extract_max_time_heap = np.array([474, 518, 537, 567, 595, 627, 842, 973])
peek_time_heap = np.array([37, 42, 40, 40, 50, 71, 83, 111])
return_size_time_heap = np.array([44, 46, 41, 46, 47, 80, 94, 142])

extract_max_time_LinkedList = np.array([1467, 1495, 1455, 1640, 1630, 1712.5, 1975, 2150])
peek_time_LinkedList = np.array([505, 556, 496, 521, 540, 560, 620, 607])
return_size_time_LinkedList = np.array([503, 548, 549, 540, 536, 570, 590, 513])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, extract_max_time_heap, label='Extract Max Heap', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, extract_max_time_LinkedList, label='Extract Max LinkedList', marker='o', markersize=8, linewidth=1)

plt.plot(num_elements, peek_time_heap, label='Peek Heap', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, peek_time_LinkedList, label='Peek LinkedList', marker='o', markersize=8, linewidth=1)

plt.plot(num_elements, return_size_time_heap, label='Return Size Heap', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, return_size_time_LinkedList, label='Return Size LinkedList', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')

plt.title('Peek, ExtractMax and Return Size Operations: Linked List vs. Heap Performance Comparison.')
plt.legend(loc='upper left')
plt.grid(True)

plt.show()
