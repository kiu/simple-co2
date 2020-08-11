// https://github.com/kiu/simple-co2/

#include <MD_Parola.h> //v3.0.1
#include <MD_MAX72xx.h> //v3.0.2

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 7

#define DEBUG 1
#define MEASURE_INTERVAL_SECONDS 20

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

byte tx_cmd_read[9] =             { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };
byte tx_cmd_zero_calibration[9] = { 0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78 };
byte rx_buf[8] = {};

uint8_t ticks = 0;
char text[5];

void tick() {
  ticks++;

  if (ticks > MEASURE_INTERVAL_SECONDS) {
    ticks = 0;
    Serial.write(tx_cmd_read, 9);
    Serial.flush();
  }
}

ISR(TIMER1_COMPA_vect) {
  tick();
}

void setupTimer1() { // https://www.arduinoslovakia.eu/application/timer-calculator
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR1A = 15624;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}



void readout() {
  if (Serial.available() == 0) {
    return;
  }

  for (uint8_t i = 0; i <= 7; i++) {
    rx_buf[i] = 0;
  }

  while (Serial.available() > 0 && Serial.read() != 0xFF) {
  }

  Serial.readBytes(rx_buf, 8);

  if (DEBUG) {
    Serial.print("\nRX: ");
    for (uint8_t i = 0; i <= 7; i++) {
      Serial.print(rx_buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  if (rx_buf[0] != 0x86) {
    return;
  }

  uint8_t checksum = 0xFF - (rx_buf[0] + rx_buf[1] + rx_buf[2] + rx_buf[3] + rx_buf[4] + rx_buf[5] + rx_buf[6]) + 1;
  int16_t co2 = ((int16_t)rx_buf[1] * 0x00FF) + rx_buf[2];

  if (DEBUG) {
    Serial.print("Checksum: ");
    Serial.print(checksum, HEX);
    Serial.print(" vs ");
    Serial.println(rx_buf[7], HEX);
    Serial.print("CO2 value: ");
    Serial.println(co2);
  }

  if (rx_buf[7] != checksum) {
    co2 = 0;
  }

  sprintf(text, "%d", co2);
  P.displayText(text, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
}

void setup(void) {
  P.begin();

  Serial.begin(9600);
  Serial.setTimeout(1000);

  setupTimer1();

  P.displayText("CO2 ppm by kiu", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (ticks < 11) {
    P.displayAnimate();
  }
  P.displayText("?", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);

  // Serial.write(tx_cmd_zero_calibration, 9);
  // Serial.flush();

  ticks = 0xFE;
}

void loop(void) {
  P.displayAnimate();
  readout();
}
