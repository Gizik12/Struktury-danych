import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000, 1000000, 5000000, 10000000, 40000000])
insert_time_best_case = np.array([80, 77, 83, 81, 83, 111, 118, 150 ,160 ,210 , 220, 320])
insert_time_worst_case = np.array([642, 665, 719, 777, 828, 940, 982, 1188, 2010, 3100, 4205, 4865])
insert = np.array([72, 173, 136, 272, 291, 362, 511, 183, 795, 790, 785, 1990])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, insert_time_best_case, label='Insert (Best Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, insert_time_worst_case, label='Insert (Worst Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, insert, label='Insert', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')

plt.title('Execution Time for Insert Operation in Heap (Best and Worst Case)')
plt.legend()
plt.grid(True)

plt.show()
