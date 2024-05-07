import numpy as np
import matplotlib.pyplot as plt

# Dane
num_elements = np.array([5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000, 1000000, 5000000, 10000000, 40000000])
ModifyKey_time_best_case = np.array([48, 56, 51, 48, 60, 94, 114, 174, 435,445 ,485 ,570 ])
ModifyKey_time_worst_case = np.array([11212, 17956, 22236, 35172, 43513, 86932, 131110, 216526, 2291780, 15226200, 32758800, 157745000])
ModifyKey = np.array([10668, 16944, 21334, 34059, 42731, 85883, 129883, 214225, 2523020 , 11457800, 33657700, 169028000])


# Wykres
plt.figure(figsize=(10, 6))

plt.plot(num_elements, ModifyKey_time_best_case, label='ModifyKey (Best Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, ModifyKey_time_worst_case, label='ModifyKey (Worst Case)', marker='o', markersize=8, linewidth=1)
plt.plot(num_elements, ModifyKey, label='ModifyKey', marker='o', markersize=8, linewidth=1)

plt.xlabel('Number of Elements')
plt.ylabel('Time (nanoseconds)')

plt.title('Execution Time for ModifyKey Operation in Heap (Best and Worst Case)')
plt.legend()
plt.grid(True)

plt.show()
