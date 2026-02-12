import numpy as np
import matplotlib.pyplot as plt
import imageio.v2 as imageio
from cycler import cycler


def readIntensity(photoName, plotName, lamp, surface, 
                  x_min=0, x_max=100, x_step=10):
    """
    x_min, x_max - диапазон значений на оси X (по умолчанию 0-100)
    x_step - шаг меток на оси X (по умолчанию 10)
    """
    photo = imageio.imread(photoName)

    # Обрезка по новым координатам
    background_x_start = 969
    background_x_end = 1120
    background_y_start = 403
    background_y_end = 706

    cut_x_start = 980
    cut_x_end = 1110
    cut_y_start = 403
    cut_y_end = 706

    # Обрезка изображений
    background = photo[background_y_start:background_y_end,
                background_x_start:background_x_end, 0:3].swapaxes(0, 1)

    cut = photo[cut_y_start:cut_y_end,
          cut_x_start:cut_x_end, 0:3].swapaxes(0, 1)

    rgb = np.mean(cut, axis=(0))
    luma = 0.2989 * rgb[:, 0] + 0.5866 * rgb[:, 1] + 0.1144 * rgb[:, 2]

    # Создаем новый массив X-координат
    x_coords = np.linspace(x_min, x_max, len(luma))
    x_ticks = np.arange(x_min, x_max + x_step, x_step)
    
    plt.rc('axes', prop_cycle=(cycler('color', ['r', 'g', 'b'])))

    fig = plt.figure(figsize=(10, 5), dpi=200)

    plt.title('Интенсивность отражённого излучения\n' + '{} / {}'.format(lamp, surface))
    plt.xlabel('Относительный номер пикселя')
    plt.ylabel('Яркость')

    rgb = rgb / 2
    luma = luma / 2

    # Строим график с новыми X-координатами
    plt.plot(x_coords, rgb, label=['r', 'g', 'b'])
    plt.plot(x_coords, luma, 'w', label='I')
    
    plt.ylim(0, 150)
    plt.legend()
    
    # Устанавливаем метки на оси X
    plt.xticks(x_ticks)

    background = (background * 0.7).astype(np.uint8)

    # Растягиваем фон, чтобы он соответствовал новому диапазону X
    plt.imshow(background, origin='lower', 
               extent=[x_min, x_max, 0, background.shape[1]], 
               aspect='auto')

    plt.savefig(plotName)
    plt.close()

    # Возвращаем luma, rgb и x_coords для дальнейших вычислений
    return luma, rgb, x_coords


def calculate_albedo(color_data, reference_data):
    """
    Вычисляет альбедо как отношение цвета к эталонному белому
    """
    # Для безопасности: избегаем деления на ноль
    with np.errstate(divide='ignore', invalid='ignore'):
        albedo = color_data / reference_data
        albedo[~np.isfinite(albedo)] = 0
    
    return albedo


def plot_albedo(albedo_data, x_coords, colors, x_min=350, x_max=760, x_step=50):
    """
    Строит графики альбедо для всех цветов
    """
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6), dpi=200)
    
    # График 1: Альбедо по каналам RGB для каждого цвета
    ax1.set_title('Альбедо поверхностей (RGB каналы)')
    ax1.set_xlabel('Относительный номер пикселя')
    ax1.set_ylabel('Альбедо')
    ax1.grid(True, alpha=0.3)
    
    for color_name, albedo_rgb in albedo_data.items():
        for i, (channel, color) in enumerate(zip(['R', 'G', 'B'], ['r', 'g', 'b'])):
            ax1.plot(x_coords, albedo_rgb[:, i], 
                    color=color, 
                    alpha=0.7,
                    label=f'{color_name} {channel}',
                    linewidth=0.8)
    
    ax1.legend(fontsize=8, ncol=3)
    ax1.set_ylim(0, 1.5)
    ax1.set_xticks(np.arange(x_min, x_max + x_step, x_step))
    
    # График 2: Среднее альбедо для каждого цвета
    ax2.set_title('Среднее альбедо поверхностей')
    ax2.set_xlabel('Цвет поверхности')
    ax2.set_ylabel('Среднее альбедо')
    ax2.grid(True, alpha=0.3)
    
    color_names = list(albedo_data.keys())
    mean_albedos = []
    
    for color_name in color_names:
        albedo_rgb = albedo_data[color_name]
        # Среднее альбедо по всем каналам и точкам
        mean_albedo = np.mean(albedo_rgb)
        mean_albedos.append(mean_albedo)
    
    bars = ax2.bar(color_names, mean_albedos, 
                   color=['green', 'blue', 'red', 'goldenrod', 'gray'])
    
    # Добавляем значения на столбцы
    for bar, value in zip(bars, mean_albedos):
        ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height() + 0.02,
                f'{value:.3f}', ha='center', va='bottom', fontsize=9)
    
    ax2.set_ylim(0, max(mean_albedos) * 1.2)
    
    plt.tight_layout()
    plt.savefig("альбедо_графики.png")
    plt.close()
    
    print("Графики альбедо сохранены в 'альбедо_графики.png'")
    
    # Выводим средние значения альбедо
    print("\nСредние значения альбедо:")
    for color_name, mean_albedo in zip(color_names, mean_albedos):
        print(f"{color_name}: {mean_albedo:.3f}")


# Основная часть кода
if __name__ == "__main__":
    # Сначала читаем эталонную белую поверхность
    print("Загрузка эталонной белой поверхности...")
    white_luma, white_rgb, x_coords = readIntensity(
        "WHITE_REFERENC.jpg", 
        "график_эталон.png", 
        "Лампа накаливания", 
        "Эталонная белая поверхность",
        x_min=0, x_max=100, x_step=10
    )
    
    # Словарь для хранения данных цветов
    color_data = {}
    
    # Список файлов и их меток
    color_files = [
        ("GREEN.jpg", "график_зелёный.png", "Ртутная лампа", "Зелёная поверхность"),
        ("BLUE.jpg", "график_синий.png", "Лампа накаливания", "Синяя поверхность"),
        ("RED.jpg", "график_красный.png", "Лампа накаливания", "Красная поверхность"),
        ("YELLOW.jpg", "график_желтый.png", "Лампа накаливания", "Жёлтая поверхность"),
        ("RTUT2.jpg", "график_ртуть2.png", "Ртутная лампа", "Ртутная эталонная поверхность")
    ]
    
    # Обрабатываем каждый цвет
    print("\nОбработка цветных поверхностей...")
    for file_name, plot_name, lamp, surface in color_files:
        print(f"  Обработка {surface}...")
        color_luma, color_rgb, _ = readIntensity(
            file_name, plot_name, lamp, surface,
            x_min=0, x_max=100, x_step=10
        )
        
        # Сохраняем данные цвета для расчета альбедо
        color_name = surface.split()[0].lower()  # "зелёная", "синяя" и т.д.
        color_data[color_name] = color_rgb
    
    # Вычисляем альбедо для каждого цвета
    print("\nВычисление альбедо...")
    albedo_data = {}
    
    for color_name, color_rgb in color_data.items():
        albedo_rgb = calculate_albedo(color_rgb, white_rgb)
        albedo_data[color_name] = albedo_rgb
    
    # Цвета для графиков
    colors = {
        'зелёная': 'green',
        'синяя': 'blue',
        'красная': 'red',
        'жёлтая': 'goldenrod',
        'ртутная': 'gray'
    }
    
    # Строим графики альбедо
    plot_albedo(albedo_data, x_coords, colors, x_min=0, x_max=100, x_step=10)
    
    # Дополнительно: строим сводный график альбедо по яркости
    fig = plt.figure(figsize=(12, 6), dpi=200)
    plt.title('Альбедо поверхностей (отношение к белому эталону)')
    plt.xlabel('Относительный номер пикселя')
    plt.ylabel('Альбедо')
    plt.grid(True, alpha=0.3)
    
    for color_name, albedo_rgb in albedo_data.items():
        # Усредняем по каналам RGB для получения альбедо по яркости
        albedo_luma = np.mean(albedo_rgb, axis=1)
        plt.plot(x_coords, albedo_luma, 
                color=colors[color_name],
                label=f'{color_name} поверхность',
                linewidth=2)
    
    plt.legend()
    plt.ylim(0, 1.5)
    plt.xticks(np.arange(0, 101, 10))
    plt.savefig("альбедо_яркость.png")
    plt.close()
    print("\nГрафик альбедо по яркости сохранен в 'альбедо_яркость.png'")
    
    print("\nОбработка завершена!")