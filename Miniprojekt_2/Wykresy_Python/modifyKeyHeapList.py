import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000])
insertHeap = np.array([11212, 17956, 22236, 35172, 43513, 86932, 131110, 216526])
insertList = np.array([32975, 36162.5, 54437.5, 69362.5, 91762.5, 295588, 374425,715500 ])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, insertList, label='ModifyKey LinkedList', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, insertHeap, label='Modifykey Heap', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')

plt.title('Modify Key Operations: Linked List vs. Heap Performance Comparison.')
plt.legend()
plt.grid(True)

plt.show()
