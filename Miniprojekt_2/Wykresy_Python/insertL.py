import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000])
insert_time_best_case = np.array([607, 747, 744, 774, 815, 868, 1316, 1800])
insert_time_worst_case = np.array([12294, 28108, 40249, 72890, 87624, 174060, 265350, 426946])
insert = np.array([10766, 27416, 33039, 35260, 61808, 119060, 123720, 200838])

# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, insert_time_best_case, label='Insert (Best Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, insert_time_worst_case, label='Insert (Worst Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, insert, label='Insert', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')

plt.title('Execution Time for Insert Operation in LinkedList (Best and Worst Case)')
plt.legend()
plt.grid(True)

plt.show()
