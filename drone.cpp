#include <Wire.h> 
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const int trigPin = 8;        
const int echoPin = 9;        

const int DANGER_DISTANCE_CM = 50;
const int CAUTION_DISTANCE_CM = 100;

const int imuPin = A0;      
const int gpsPin = A1;      

long duration; 
long distanceCm; 


long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 10000); 
  
  if (duration > 0) {
    distanceCm = duration * 0.034 / 2;
    if (distanceCm > 400) distanceCm = 400; 
  } else {
    distanceCm = 999; 
  }
  return distanceCm;
}


void clearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }
  lcd.setCursor(0, line);
}


void setup() {
  Serial.begin(9600); 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Wire.begin();
  
  lcd.begin(16, 2); 
  lcd.setBacklight(1); 

  lcd.setCursor(0, 0);
  lcd.print("Drone System Ready");
  lcd.setCursor(0, 1);
  lcd.print("LCD Initialized!");

  Serial.println("System Initialized. Monitoring Status.");
  delay(1500);
}


void loop() {
  long currentDistance = measureDistance();

  int imuReading = analogRead(imuPin);
  int gpsReading = analogRead(gpsPin);
  
  clearLine(0);
  clearLine(1);
  
  if (currentDistance > 0 && currentDistance < DANGER_DISTANCE_CM) {
    
    lcd.setCursor(0, 0);
    lcd.print("STOP! Obstacle<50!");
    lcd.setCursor(0, 1);
    lcd.print("!!! DANGER ZONE");
    
    Serial.println("🔴 CRITICAL: EMERGENCY STOP.");
    
  } 
  else if (currentDistance >= DANGER_DISTANCE_CM && currentDistance < CAUTION_DISTANCE_CM) {
    
    lcd.setCursor(0, 0);
    lcd.print("D:");
    lcd.print(currentDistance);
    lcd.print("cm CAUTION");
    lcd.setCursor(0, 1);
    lcd.print("R.Speed: Monitor");
    
    Serial.println("🟡 CAUTION: REDUCING SPEED.");
  }
  else {
    
    int imuPercent = map(imuReading, 0, 1023, 0, 100);
    int gpsPercent = map(gpsReading, 0, 1023, 0, 100);
    
    if (abs(imuReading - 512) > 100) {
      lcd.setCursor(0, 0);
      lcd.print("WARNING: ROLL ERR");
      lcd.setCursor(0, 1);
      lcd.print("CORRECTION NEEDED");
      Serial.println("IMU Correction: Roll is off balance.");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Status: STABLE");
      lcd.setCursor(0, 1);
      lcd.print("IMU:");
      lcd.print(imuPercent);
      lcd.print("% G:");
      lcd.print(gpsPercent);
      
      Serial.println("🟢 SAFE: CONTINUE MISSION.");
    }
  }

  delay(200);
}