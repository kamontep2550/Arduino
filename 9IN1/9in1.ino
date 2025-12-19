#include <DHT.h> 
#define DHTPIN 4   
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

#define ledR 12
#define ledB 13

#define SW1 2
#define SW2 3 

#define LDRPin A1
#define potpin A0
#define LM35Pin A2

void setup() {
    Serial.begin(9600);
    dht.begin();

    pinMode(ledB, OUTPUT);
    pinMode(ledR, OUTPUT);

    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
}

void loop() { 
    int timeValue = 1000;

    LEDBLYNK(timeValue);    //Work 1
    SW();                   //Work 2
    DHT5();                 //Work 3
    pot();                  //Work 4
    ldr();                  //work 5
    lm();                   //work 6

    delay(1000);
} 

void LEDBLYNK(int t) { 
    digitalWrite(ledR, HIGH);
    digitalWrite(ledB, HIGH);
    delay(t); 
    digitalWrite(ledR, LOW);
    digitalWrite(ledB, LOW);
    delay(t);
}

void SW() { 
    int b1 = digitalRead(SW1);
    int b2 = digitalRead(SW2);

    if (b1 == 0) {
        digitalWrite(ledR, HIGH);
        digitalWrite(ledB, LOW);
    } 
    else if (b2 == 0) { 
        digitalWrite(ledR, LOW);
        digitalWrite(ledB, HIGH);
    }
    else {
        digitalWrite(ledR, LOW);
        digitalWrite(ledB, LOW);
    }
}

void DHT5() { 
    float h = dht.readHumidity(); 
    float c = dht.readTemperature();

    if (isnan(h) || isnan(c)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Hum: ");  
    Serial.print(h);  
    Serial.print(" % , Temp: ");  
    Serial.print(c);  
    Serial.println(" C"); // อยู่ในบรรทัดเดียว และจบด้วย println
}

void pot() { 
    int adcValue = analogRead(potpin);
    float vdcValue = (adcValue * (5.0 / 1023.0)); 

    Serial.print("ABCpot: ");  
    Serial.print(adcValue);  
    Serial.print(" , vdcpot: ");  
    Serial.println(vdcValue);  // อยู่บรรทัดเดียว
}

void ldr() { 
    int LDRadcValue = analogRead(LDRPin);
    float vdcValue = (LDRadcValue * (5.0 / 1023.0)); 

    Serial.print("LDR ADC: ");  
    Serial.print(LDRadcValue);  
    Serial.print(" , VDCLDR: ");  
    Serial.println(vdcValue);  // อยู่บรรทัดเดียว
} 

void lm() { 
    int adcTempC = analogRead(LM35Pin);
    float TempC = (adcTempC * (5.0 / 1023.0)); 

    Serial.print("LMA35 ADC: ");  
    Serial.print(adcTempC); 
    Serial.print(" , LMA35 TempC: ");  
    Serial.println(TempC); // อยู่บรรทัดเดียว
}
