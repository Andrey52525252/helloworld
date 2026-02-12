import pandas as pd
import matplotlib.pyplot as plt

# Настройка стиля и шрифтов
plt.style.use('seaborn-v0_8-whitegrid')
plt.rcParams['font.family'] = 'DejaVu Sans'

# Чтение данных из CSV-файла с пробелом как разделителем
data = pd.read_csv('data.csv', delim_whitespace=True, header=None)

data.columns = ['steps', 'integral', 'answer']


# Диагностика
print("Форма данных:", data.shape)
print("Первые 5 строк:")
print(data.head())

# Создание графика
plt.figure(figsize=(10, 6))

# Построение точечных графиков разными цветами
plt.step(data['steps'], data['integral'], color='red', alpha=0.8, label='integral')
plt.plot(data['steps'], data['answer'], color='blue', alpha=0.8, label='answer')

#plt.plot(data['x'], data['s'], color='red', alpha=0.8, label='integral')

# Настройка осей и заголовка
plt.xlabel('number of steps', fontsize=12)
plt.ylabel('result of calculation', fontsize=12)
plt.title('accuracy from step number', fontsize=14)

# Добавление легенды
plt.legend()

# Добавление сетки
plt.grid(True, linestyle='--', alpha=0.7)

# Автоматическая настройка layout
plt.tight_layout()

# Сохранение графика
plt.savefig("C:\\Users\\admin\\projects\\helloworld\\accuracy_from_step_number.png")

# Показать график
plt.show()