# flight_logic.py

from constants import DANGER_DISTANCE_CM, CAUTION_DISTANCE_CM, STAB_CENTER, STAB_TOLERANCE

def get_safety_status(distance: int) -> str:
    """Визначає статус безпеки на основі відстані (AvoidanceLogic)."""
    
    if distance <= 0:
        return "ERROR"
        
    if distance < DANGER_DISTANCE_CM:
        return "CRITICAL_DANGER"  # < 50 cm
        
    if distance < CAUTION_DISTANCE_CM:
        return "CAUTION"          # 50 cm - 100 cm
        
    return "SAFE"

def check_stability_status(imu_reading: int) -> str:
    """Перевіряє, чи не перевищено допуск крену (FlightControllerCore)."""
    
    # Обчислюємо абсолютне відхилення від центру (512)
    deviation = abs(imu_reading - STAB_CENTER)
    
    if deviation > STAB_TOLERANCE:
        return "ROLL_ERROR"  # Помилка стабілізації
        
    return "STABLE"