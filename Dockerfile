FROM python:3.11-slim

WORKDIR /app

# Встановлюємо залежності
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Копіюємо весь проєкт
COPY . .

# За замовчуванням при старті контейнера запускаємо тести
CMD ["pytest", "-v"]
