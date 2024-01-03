#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables
int playerY = 47;
int jumpCount = 50;
bool jump = false;

int chance;

int cactusX = 128;

int points = 0;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.invertDisplay(false);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(points);
  display.display();
  Serial.begin(9600);

  display.
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char key = Serial.read();
    if (key == 'w') {
      jump = true;
    }
  }
  // display.clearDisplay();
  player();
  spawnCactus();
  // cactusX--;
  display.display();
  // delay(10);
}
void player() {
  display.fillRoundRect(20, playerY, 10, 16, 5, BLACK);
  if (jumpCount < 1) {
    jump = false;
  }
  if (jump && jumpCount > 0) {
    jumpCount -= 2;
    playerY -= 2;
  } else if (playerY < 47) {
    playerY += 2;
  } else {
    jumpCount = 50;
  }
  display.fillRoundRect(20, playerY, 10, 16, 5, WHITE);
}

void spawnCactus() {
  if (cactusX < -10) {
    cactusX = random(128, 200);
    printPoints();
  }
  display.fillRect(cactusX, 47, 10, 16, BLACK);
  cactusX--;
  display.fillRect(cactusX, 47, 10, 16, WHITE);
  for (int x = cactusX; x < cactusX + 10; x++) {
    if (display.getPixel(x, 46)) {
      display.setCursor(20, 30);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("You got ");
      display.print(points);
      display.print(" points!");
      display.display();
      display.invertDisplay(true);
      delay(5000);
      display.invertDisplay(false);
      display.clearDisplay();
      points = -1;
      cactusX = 130;
      printPoints();
    }
  }
  for (int y = 47; y < 64; y++) {
    if (display.getPixel(cactusX - 1, y)) {
      display.setCursor(20, 30);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print("You got ");
      display.print(points);
      display.print(" points!");
      display.display();
      display.invertDisplay(true);
      delay(5000);
      display.invertDisplay(false);
      display.clearDisplay();
      points = -1;
      cactusX = 130;
      printPoints();
    }
  }
}

void printPoints() {
  display.fillRect(0, 0, 16, 16, BLACK);
  points++;
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(points);
  display.display();
}
