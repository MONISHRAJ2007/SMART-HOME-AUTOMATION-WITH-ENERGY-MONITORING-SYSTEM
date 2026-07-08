#define BLYNK_TEMPLATE_ID "TMPL3AtNcv5OZ" 
#define BLYNK_TEMPLATE_NAME "MINI PROJECT 1" 
#define BLYNK_AUTH_TOKEN "WAjRIKWbbSD9jnYlv820gQECZNOHePys"  

#include <WiFi.h> 
#include <BlynkSimpleEsp32.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  
#include <ESP32Servo.h> // Added to support Servo on ESP32

// ------------------ WiFi Credentials ------------------ 
char ssid[] = "POCO M5"; 
char pass[] = "123456789";  

// ------------------ Relay Pins ------------------ 
#define RELAY_0W_BULB 14 
#define RELAY_MOTOR 12 
#define RELAY_INCADE 27 
#define RELAY_SOCKET 26 
#define RELAY_VACATION 18  

// ------------------ Sensor Pins ------------------ 
#define CURRENT_BULB 34 
#define CURRENT_MOTOR 35 
#define CURRENT_SOCKET 32 
#define VOLTAGE_PIN 33  

// ------------------ Manual Switch Pins ------------------ 
#define SWITCH_BULB 19 
#define SWITCH_MOTOR 15 
#define SWITCH_INCADE 5 
#define SWITCH_SOCKET 4  

// ------------------ Safety & Security Pins (Added) ---------
#define SERVO_PIN 13 
#define BUZZER_PIN 25 
#define FIRE_PIN 2 
#define GAS_PIN 23 // MQ sensor output 

// ------------------ Variables ------------------ 
bool vacationMode = false; 
int bulbState = 0, motorState = 0, incadeState = 0, socketState = 0;  
int lastFireState = -1; // Added to prevent Blynk flooding
int lastGasState = -1;  // Added to prevent Blynk flooding

// ------------------ Energy Tracking ------------------ 
float energyCostPerKWh = 6.5; 
float totalEnergyWh = 0; 
float totalEnergyKWh = 0; 
float estimatedBill = 0; 
unsigned long lastCalcTime = 0; 
unsigned long lastSendTime = 0; 
unsigned long lastSerialTime = 0;  

// ------------------ Objects Setup ------------------ 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
unsigned long lastLcdUpdate = 0; 
int lcdScreen = 0;  
Servo myServo; // Added Servo object

// ------------------ Manual Switch Last States ------------------ 
bool lastBulbSwitchState = HIGH; 
bool lastMotorSwitchState = HIGH; 
bool lastIncadeSwitchState = HIGH; 
bool lastSocketSwitchState = HIGH;  

// ------------------ Helper Functions ------------------ 
void setRelay(int pin, int state) {   
  digitalWrite(pin, state ? LOW : HIGH); // active LOW 
}  

float readCurrent(int pin) {   
  const float sensitivity = 0.100; // 100 mV/A for ACS712 20A   
  const int samples = 10;   
  float sum = 0;   
  for (int i = 0; i < samples; i++) sum += analogRead(pin);   
  float raw = sum / samples;   
  float voltage = (raw / 4095.0) * 3.3;   
  float offset = 3.3 / 2.0;   
  float current = (voltage - offset) / sensitivity;   
  if (abs(current) < 0.05) current = 0; // noise filter   
  return abs(current); 
}  

float measureVrms(int pin, int samples, int delayMicrosVal) {   
  double sumSq = 0;   
  for (int i = 0; i < samples; i++) {     
    int raw = analogRead(pin);     
    float voltage = (raw / 4095.0) * 3.3;     
    float acVoltage = voltage - 1.65;     
    sumSq += acVoltage * acVoltage;     
    delayMicroseconds(delayMicrosVal);   
  }   
  float rms = sqrt(sumSq / samples);   
  float scaledVrms = rms * (230.0 / 0.5);    
  if (scaledVrms < 5) return 0.0;    
  return scaledVrms; 
}  

// ------------------ Blynk Connection ------------------ 
BLYNK_CONNECTED() {   
  Blynk.syncVirtual(V0, V1, V2, V3, V5, V22); 
}  

// ------------------ Blynk Controls ------------------ 
BLYNK_WRITE(V0) { bulbState = param.asInt(); if (!vacationMode) setRelay(RELAY_0W_BULB, bulbState); } 
BLYNK_WRITE(V1) { motorState = param.asInt(); if (!vacationMode) setRelay(RELAY_MOTOR, motorState); } 
BLYNK_WRITE(V3) { incadeState = param.asInt(); if (!vacationMode) setRelay(RELAY_INCADE, incadeState); } 
BLYNK_WRITE(V5) { socketState = param.asInt(); if (!vacationMode) setRelay(RELAY_SOCKET, socketState); }  

BLYNK_WRITE(V2) {   
  vacationMode = param.asInt();   
  if (vacationMode) {     
    setRelay(RELAY_0W_BULB, 1);     
    setRelay(RELAY_MOTOR, 0);     
    setRelay(RELAY_INCADE, 0);     
    setRelay(RELAY_SOCKET, 0);     
    setRelay(RELAY_VACATION, 1);      
    Blynk.virtualWrite(V0, 1);     
    Blynk.virtualWrite(V1, 0);     
    Blynk.virtualWrite(V3, 0);     
    Blynk.virtualWrite(V5, 0);   
  } else {     
    setRelay(RELAY_VACATION, 0);     
    setRelay(RELAY_0W_BULB, bulbState);     
    setRelay(RELAY_MOTOR, motorState);     
    setRelay(RELAY_INCADE, incadeState);     
    setRelay(RELAY_SOCKET, socketState);   
  } 
}  

// Added Door/Servo Control
BLYNK_WRITE(V22) { 
  int value = param.asInt(); 
  if (value == 1) myServo.write(90); 
  else myServo.write(0); 
}

// ------------------ Setup ------------------ 
void setup() {   
  Serial.begin(115200);    
  
  pinMode(RELAY_0W_BULB, OUTPUT);   
  pinMode(RELAY_MOTOR, OUTPUT);   
  pinMode(RELAY_INCADE, OUTPUT);   
  pinMode(RELAY_SOCKET, OUTPUT);   
  pinMode(RELAY_VACATION, OUTPUT);    
  
  pinMode(SWITCH_BULB, INPUT_PULLUP);   
  pinMode(SWITCH_MOTOR, INPUT_PULLUP);   
  pinMode(SWITCH_INCADE, INPUT_PULLUP);   
  pinMode(SWITCH_SOCKET, INPUT_PULLUP);    

  // Security Pins Setup
  pinMode(BUZZER_PIN, OUTPUT); 
  pinMode(FIRE_PIN, INPUT_PULLUP); // more stable 
  pinMode(GAS_PIN, INPUT); 
  
  // Attach Servo
  myServo.attach(SERVO_PIN); 
  myServo.write(0); 

  digitalWrite(RELAY_0W_BULB, HIGH);   
  digitalWrite(RELAY_MOTOR, HIGH);   
  digitalWrite(RELAY_INCADE, HIGH);   
  digitalWrite(RELAY_SOCKET, HIGH);   
  digitalWrite(RELAY_VACATION, HIGH);    
  
  analogReadResolution(12);   
  analogSetAttenuation(ADC_11db);    
  
  lcd.init();   
  lcd.backlight();   
  lcd.clear();   
  lcd.setCursor(0, 0);   
  lcd.print("Smart Energy Sys");   
  lcd.setCursor(0, 1);   
  lcd.print("Initializing...");   
  delay(2000);    
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);   
  delay(200);    
  
  setRelay(RELAY_0W_BULB, 0);   
  setRelay(RELAY_MOTOR, 0);   
  setRelay(RELAY_INCADE, 0);   
  setRelay(RELAY_SOCKET, 0);   
  setRelay(RELAY_VACATION, 0); 
}  

// ------------------ Main Loop ------------------ 
void loop() {   
  unsigned long now = millis();    
  
  // Manual Switch Toggle Logic    
  // Bulb Switch   
  bool bulbSwitchState = digitalRead(SWITCH_BULB);   
  if (bulbSwitchState == LOW && lastBulbSwitchState == HIGH) {     
    bulbState = !bulbState;     
    setRelay(RELAY_0W_BULB, bulbState);     
    Blynk.virtualWrite(V0, bulbState);     
    delay(200);   
  }   
  lastBulbSwitchState = bulbSwitchState;    
  
  // Motor Switch   
  bool motorSwitchState = digitalRead(SWITCH_MOTOR);   
  if (motorSwitchState == LOW && lastMotorSwitchState == HIGH) {     
    motorState = !motorState;     
    setRelay(RELAY_MOTOR, motorState);     
    Blynk.virtualWrite(V1, motorState);     
    delay(200);   
  }   
  lastMotorSwitchState = motorSwitchState;    
  
  // Incandescent Switch   
  bool incadeSwitchState = digitalRead(SWITCH_INCADE);   
  if (incadeSwitchState == LOW && lastIncadeSwitchState == HIGH) {     
    incadeState = !incadeState;     
    setRelay(RELAY_INCADE, incadeState);     
    Blynk.virtualWrite(V3, incadeState);     
    delay(200);   
  }   
  lastIncadeSwitchState = incadeSwitchState;    
  
  // Socket Switch   
  bool socketSwitchState = digitalRead(SWITCH_SOCKET);   
  if (socketSwitchState == LOW && lastSocketSwitchState == HIGH) {     
    socketState = !socketState;     
    setRelay(RELAY_SOCKET, socketState);     
    Blynk.virtualWrite(V5, socketState);     
    delay(200);   
  }   
  lastSocketSwitchState = socketSwitchState;    
  
  Blynk.run();    

  // --- FIRE & GAS DETECTION LOGIC ---
  int fire = digitalRead(FIRE_PIN); 
  int gas = digitalRead(GAS_PIN); 

  // Send to Blynk ONLY when state changes to prevent Flooding/Disconnects
  if (fire != lastFireState) {
    if (fire == LOW) Blynk.virtualWrite(V21, 1); // LOW = fire detected 
    else Blynk.virtualWrite(V21, 0);
    lastFireState = fire;
  }

  if (gas != lastGasState) {
    if (gas == LOW) Blynk.virtualWrite(V25, 1); // depends on module
    else Blynk.virtualWrite(V25, 0);
    lastGasState = gas;
  }

  // --- BUZZER LOGIC --- 
  if (fire == LOW || gas == LOW) { 
    digitalWrite(BUZZER_PIN, HIGH); 
  } else { 
    digitalWrite(BUZZER_PIN, LOW); 
  } 

  // --- TIMED TASKS ---
  if (now - lastCalcTime >= 1000) {     
    lastCalcTime = now;     
    calculateEnergy(false);   
  }    
  
  if (now - lastSendTime >= 10000) {     
    lastSendTime = now;     
    calculateEnergy(true);   
  }    
  
  if (now - lastSerialTime >= 3000) {     
    lastSerialTime = now;     
    printReadingsToSerial(); 

    // Moved the debug print here so it doesn't flood the serial monitor
    Serial.print("Fire: "); Serial.print(fire); 
    Serial.print(" | Gas: "); Serial.println(gas);
  }    
  
  if (now - lastLcdUpdate >= 2000) {     
    lastLcdUpdate = now;     
    lcd.clear();      
    float voltageNow = measureVrms(VOLTAGE_PIN, 200, 20);     
    if (voltageNow == 0) {       
      lcd.setCursor(0, 0);       
      lcd.print("⚡ NO SUPPLY");       
      lcd.setCursor(0, 1);       
      lcd.print("DETECTED");     
    } else {       
      float motorPower = voltageNow * readCurrent(CURRENT_MOTOR);       
      float bulbPower = voltageNow * readCurrent(CURRENT_BULB);       
      float socketPower = voltageNow * readCurrent(CURRENT_SOCKET);        
      switch (lcdScreen) {         
        case 0:           
          lcd.setCursor(0, 0);           
          lcd.print("MOTOR POWER:");           
          lcd.setCursor(0, 1);           
          lcd.print(motorPower, 1);           
          lcd.print(" W");           
          break;          
        case 1:           
          lcd.setCursor(0, 0);           
          lcd.print("BULB POWER:");           
          lcd.setCursor(0, 1);           
          lcd.print(bulbPower, 1);           
          lcd.print(" W");           
          break;          
        case 2:           
          lcd.setCursor(0, 0);           
          lcd.print("SOCKET POWER:");           
          lcd.setCursor(0, 1);           
          lcd.print(socketPower, 1);           
          lcd.print(" W");           
          break;          
        case 3:           
          lcd.setCursor(0, 0);           
          lcd.print("TOTAL BILL:");           
          lcd.setCursor(0, 1);           
          lcd.print("Rs ");           
          lcd.print(estimatedBill, 2);           
          break;       
      }       
      lcdScreen = (lcdScreen + 1) % 4;     
    }   
  } 
}  

// ------------------ Energy Calculation ------------------ 
void calculateEnergy(bool sendToBlynk) {   
  float voltage = measureVrms(VOLTAGE_PIN, 1600, 50);    
  if (voltage < 90 || voltage > 280) voltage = 0.0;    
  
  float motorCurrent = 0, incadeCurrent = 0, socketCurrent = 0;   
  if (!vacationMode) {     
    if (motorState) motorCurrent = readCurrent(CURRENT_MOTOR);     
    if (incadeState) incadeCurrent = readCurrent(CURRENT_BULB);     
    if (socketState) socketCurrent = readCurrent(CURRENT_SOCKET);   
  }    
  
  float motorPower = voltage * motorCurrent;   
  float incadePower = voltage * incadeCurrent;   
  float socketPower = voltage * socketCurrent;   
  float totalPower = motorPower + incadePower + socketPower;    
  
  totalEnergyWh += totalPower / 3600.0;   
  if (totalEnergyWh > 1e6) totalEnergyWh = 0;    
  
  totalEnergyKWh = totalEnergyWh / 1000.0;   
  estimatedBill = totalEnergyKWh * energyCostPerKWh;    
  
  if (sendToBlynk) {     
    Blynk.virtualWrite(V7, voltage);     
    Blynk.virtualWrite(V8, motorCurrent);     
    Blynk.virtualWrite(V9, incadeCurrent);     
    Blynk.virtualWrite(V10, socketCurrent);     
    Blynk.virtualWrite(V11, estimatedBill);     
    Blynk.virtualWrite(V12, totalEnergyKWh);   
  } 
}  

// ------------------ Serial Monitor Function ------------------ 
void printReadingsToSerial() {   
  float voltage = measureVrms(VOLTAGE_PIN, 1600, 50);   
  float motorCurrent = readCurrent(CURRENT_MOTOR);   
  float bulbCurrent = readCurrent(CURRENT_BULB);   
  float socketCurrent = readCurrent(CURRENT_SOCKET);    
  
  Serial.print("Voltage(Vrms): "); Serial.print(voltage, 2);   
  Serial.print(" | Motor(A): "); Serial.print(motorCurrent, 3);   
  Serial.print(" | Bulb(A): "); Serial.print(bulbCurrent, 3);   
  Serial.print(" | Socket(A): "); Serial.print(socketCurrent, 3);   
  Serial.print(" | Energy(kWh): "); Serial.print(totalEnergyKWh, 6);   
  Serial.print(" | Bill(Rs): "); Serial.println(estimatedBill, 3); 
}