# sensors.py

from constants import ADC_MAX

def calculate_distance(raw_duration_us: int) -> int:
    """Обчислює відстань у см на основі тривалості ехо-сигналу."""
    
    if raw_duration_us <= 0:
        # Імітація тайм-ауту або помилки датчика
        return 999  

    # Формула: duration * 0.034 / 2
    distance_cm = (raw_duration_us * 0.034) // 2
    
    if distance_cm > 400:
        return 400 # Обмеження максимального діапазону
    
    return distance_cm

def map_to_percent(value: int) -> int:
    """Перетворює значення ADC (0-1023) на відсотки (0-100)."""
    # map(value, 0, 1023, 0, 100)
    return (value * 100) // ADC_MAX