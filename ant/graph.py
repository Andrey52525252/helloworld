import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Настройка стиля и шрифтов
plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['font.family'] = 'DejaVu Sans'

# Чтение данных из первого CSV-файла
data_01 = pd.read_csv('data_03_hook.txt', sep='\s+', header=None)
data_01.columns = ['voltage1']

# Чтение данных из второго CSV-файла
data_02 = pd.read_csv('data_13_hook.txt', sep='\s+', header=None)
data_02.columns = ['voltage2']

CONSTANT_ADD = data_01['voltage1'].max() - data_02['voltage2'].max()

CYCLIC_SHIFT = 0

# Прибавление константы ко всем значениям



# Преобразуем в numpy array для удобства сдвига
voltage_values = data_02['voltage2'].values
length = min(data_01['voltage1'].count(), data_02['voltage2'].count())
min = 1000000000
min_shift = 0
shifted_voltage = voltage_values
for i in range(0, length, 1):
    # Выполняем циклический сдвиг
    shifted_voltage = np.roll(voltage_values, i)
    local_min = 0.0
    for j in range (0, length, 3):
        local_min += (data_01['voltage1'][j] - shifted_voltage[j])*(data_01['voltage1'][j] - shifted_voltage[j])
    print(f"проверили сдвиг на {i}, local_min = {local_min}")
    if (local_min < min):
        min = local_min
        min_shift = i
        print('Обновили min до ', min)
    local_min = 0

print('Закончили с поиском минимума')
shifted_voltage = np.roll(voltage_values, min_shift)
data_02['voltage2'] = shifted_voltage
print(f"Выполнен циклический сдвиг на {min_shift} точек")

if CONSTANT_ADD != 0:
    data_02['voltage2'] = data_02['voltage2'] + CONSTANT_ADD
    print(f"Прибавлена константа {CONSTANT_ADD} ко всем значениям data_02")



# Диагностика
print("Форма данных data_01:", data_01.shape)
print("Форма данных data_02:", data_02.shape)
print("Первые 5 строк data_01:")
print(data_01.head())
print("Первые 5 строк data_02:")
print(data_02.head())

# Создание графика
plt.figure(figsize=(10, 6))

# Создаем ось X для обоих наборов данных
x_values_01 = range(len(data_01))
x_values_02 = range(len(data_02))

# Построение линейного графика для первого файла
plt.plot(x_values_01, data_01['voltage1'], color='blue', alpha=0.8, linewidth=1, label='Data 01')

# Построение линейного графика для второго файла другим цветом
plt.plot(x_values_02, data_02['voltage2'], color='red', alpha=0.8, linewidth=1, label='Data 02')

# Настройка осей и заголовка
plt.xlabel('time, ns', fontsize=12)
plt.ylabel('voltage, V', fontsize=12)
plt.title('Амплитуда волны от времени', fontsize=14)

# Добавление легенды
plt.legend()

# Добавление сетки
plt.grid(True, linestyle='--', alpha=0.7)

# Автоматическая настройка layout
plt.tight_layout()

# Сохранение графика
plt.savefig("C:\\Users\\admin\\projects\\helloworld\\ant\\images\\data_hook_3.png")

# Показать график
plt.show()