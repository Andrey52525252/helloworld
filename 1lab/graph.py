import pandas as pd
import matplotlib.pyplot as plt

# Настройка стиля и шрифтов
plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['font.family'] = 'DejaVu Sans'

# Чтение данных из CSV-файла с пробелом как разделителем
data = pd.read_csv('1.csv', delim_whitespace=True, header=None)
# Удаление строк, где любое значение превышает 20000000
# Удаление строк, где только time_1 > 20000000
# Даем столбцам понятные имена
data.columns = ['array_length', 'BestSituation', 'AverageSituation', 'WorstSituation']


data = data[data['BestSituation'] <= 6000000]
data = data[data['AverageSituation'] <= 6000000]
data = data[data['WorstSituation'] <= 6000000]

# Диагностика
print("Форма данных:", data.shape)
print("Первые 5 строк:")
print(data.head())

# Создание графика
plt.figure(figsize=(10, 6))

# Построение трех точечных графиков разными цветами
plt.scatter(data['array_length'], data['BestSituation'], s=6, color='blue', alpha=0.8, label='Sorted')
plt.scatter(data['array_length'], data['AverageSituation'], s=6, color='red', alpha=0.8, label='Random')
plt.scatter(data['array_length'], data['WorstSituation'], s=6, color='green', alpha=0.8, label='Sorted backward')

# Настройка осей и заголовка
plt.xlabel('Array length', fontsize=12)
plt.ylabel('Time, ns', fontsize=12)
plt.title('HeapSort в разных случаях', fontsize=14)

# Добавление легенды
plt.legend()

# Добавление сетки
plt.grid(True, linestyle='--', alpha=0.7)

# Автоматическая настройка layout
plt.tight_layout()

# Сохранение графика
plt.savefig("C:\\Users\\admin\\projects\\helloworld\\1lab\\images\\HeapSort.png")

# Показать график
plt.show()