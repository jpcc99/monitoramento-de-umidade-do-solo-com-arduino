#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

const int ANALOG_PIN_SENSOR = A0;
const int LED = 2;
const int MIN_MOISTURE = 0;
const int MAX_MOISTURE = 539;
const int DRY_SOIL_LIMIT = 30;
const int MOIST_SOIL_LIMIT = 60;

LiquidCrystal_I2C lcd(32, 16, 2);

void setup()
{
    Serial.begin(9600);
    pinMode(LED, OUTPUT);

    // setup lcd
    lcd.init();
    lcd.backlight();
    lcd.leftToRight();

    // show starting msg on lcd
    lcd.setCursor(3, 0);
    lcd.print("Monitoring");
    lcd.setCursor(0, 1);
    lcd.print("Soil Moisture");
    delay(4000); // seconds
}

void loop()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture Level:");

    int soilMoisture = analogRead(ANALOG_PIN_SENSOR);
    // Change the reading from 0 to 539 to percentage
    soilMoisture = map(soilMoisture, MIN_MOISTURE, MAX_MOISTURE, 0, 100);

    // Show the moisture percentage on Serial Monitor
    Serial.print(soilMoisture);
    Serial.println("%");

    updateLedAndDisplayBasedOnMoistureState(soilMoisture);
    delay(2000);
}

void updateLedAndDisplayBasedOnMoistureState(int soilMosture)
{
    lcd.setCursor(6, 1);

    if (soilMosture <= DRY_SOIL_LIMIT)
    {
        digitalWrite(LED, HIGH);
        lcd.print("DRY");
    }
    else if (soilMosture > DRY_SOIL_LIMIT && soilMosture <= MOIST_SOIL_LIMIT)
    {
        digitalWrite(LED, LOW);
        lcd.print("MOIST");
    }
    else
    {
        digitalWrite(LED, LOW);
        lcd.setCursor(2, 1);
        lcd.print("WET");
    }
}
