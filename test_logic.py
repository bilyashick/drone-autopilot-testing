# test_logic.py

import pytest
from flight_logic import get_safety_status, check_stability_status
from sensors import calculate_distance, map_to_percent
from constants import STAB_CENTER

# --- 1. ТЕСТУВАННЯ ЛОГІКИ УНИКНЕННЯ (AvoidanceLogic) ---

def test_distance_conversion():
    # емуляція значення тривалості ехо-сигналу
    assert calculate_distance(588) == 9

def test_critical_danger_zone():
    # Тест DANGER_DISTANCE_CM = 50
    assert get_safety_status(49) == "CRITICAL_DANGER"
    assert get_safety_status(1) == "CRITICAL_DANGER"

def test_caution_zone():
    # Тест CAUTION_DISTANCE_CM = 100
    assert get_safety_status(50) == "CAUTION"
    assert get_safety_status(99) == "CAUTION"

def test_safe_zone():
    assert get_safety_status(101) == "SAFE"

# --- 2. ТЕСТУВАННЯ ЛОГІКИ СТАБІЛІЗАЦІЇ (FlightControllerCore) ---

def test_stable_flight():
    # 512 - ідеальний центр
    assert check_stability_status(STAB_CENTER) == "STABLE"
    # 600 - у межах толерантності 100 (512 +/- 100)
    assert check_stability_status(600) == "STABLE"

def test_roll_error_high():
    # 650 - вище порогу 612
    assert check_stability_status(650) == "ROLL_ERROR" 

def test_roll_error_low():
    # 350 - нижче порогу 412
    assert check_stability_status(350) == "ROLL_ERROR"
