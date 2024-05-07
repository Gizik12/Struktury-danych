import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000])
ModifyKey_time_best_case = np.array([553, 541, 564, 519, 548, 598, 601, 664])
ModifyKey = np.array([32975, 36162.5, 54437.5, 69362.5, 91762.5, 295588, 374425,715500 ])
ModifyKey_time_worst_case = np.array([41875, 70312.5, 86737.5, 159125, 230625, 446038, 820062, 1663720])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, ModifyKey_time_best_case, label='ModifyKey (Best Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, ModifyKey_time_worst_case, label='ModifyKey (Worst Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, ModifyKey, label='ModifyKey', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')

plt.title('Execution Time for ModifyKey Operation in LinkedList (Best and Worst Case)')
plt.legend()
plt.grid(True)

plt.show()
