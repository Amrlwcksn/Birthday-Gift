#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 lcd(128, 32, &Wire, 4);
#define SCREEN_I2C_ADDR 0x3C // or 0x3C
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 32     // OLED display height, in pixels
#define OLED_RST_PIN -1
#define btnOk   4

boolean statusBtnOk   = false;
boolean statusAkhirBtnOk   = false;
boolean OK   = false;

int halaman  = 1;
int menuItem = 1;

#define FRAME_DELAY (42)
#define FRAME_WIDTH (32)
#define FRAME_HEIGHT (32)
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))
const byte PROGMEM frames[][128] = {
  {0,0,0,0,0,0,0,0,0,1,128,0,0,3,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,128,0,0,3,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,128,0,0,3,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,128,0,0,3,64,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,0,4,32,0,2,5,160,0,0,7,192,0,0,1,128,0,2,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,0,4,32,0,2,5,160,0,9,7,192,0,0,1,128,0,2,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,2,4,32,0,2,5,160,0,9,135,224,0,9,129,128,0,2,3,192,0,2,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,2,4,32,0,2,5,160,0,9,135,224,0,8,129,128,0,2,3,192,0,2,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,2,4,32,0,2,5,160,0,24,135,224,0,24,129,128,0,2,3,192,0,2,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,2,4,32,0,0,5,160,0,0,7,224,0,0,1,128,0,0,3,192,0,2,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,0,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,128,0,0,1,192,0,0,3,64,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,128,0,0,1,192,0,0,2,64,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,128,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,0,0,1,128,0,0,3,192,32,0,7,224,64,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,64,0,1,128,64,0,3,193,176,0,7,224,64,0,4,32,64,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,64,0,1,128,64,0,3,193,176,0,7,224,64,0,4,32,64,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,64,0,1,128,0,0,3,193,176,0,7,224,64,0,4,32,64,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,64,0,1,128,0,0,3,193,16,0,7,224,0,0,4,32,64,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,4,64,0,0,4,32,0,0,4,32,0,0,5,160,0,0,7,224,64,0,1,128,0,0,3,193,16,0,7,224,0,0,4,32,64,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,224,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,224,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,224,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,3,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,224,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,1,128,0,0,2,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,1,128,0,0,3,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,1,128,0,0,3,192,0,0,6,96,0,0,4,32,0,0,4,32,0,0,5,160,0,0,3,192,0,0,1,128,0,0,3,192,0,0,7,224,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,0,4,32,0,7,255,255,224,12,0,0,48,24,0,0,24,24,0,0,24,24,48,12,24,28,78,51,56,31,7,193,216,16,0,0,8,24,0,0,24,127,255,255,254,96,0,0,6,63,255,255,252,31,255,255,248,0,0,0,0}
};


void setup() {
  Serial.begin(115200);
  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  lcd.clearDisplay();

  pinMode(btnOk,   INPUT_PULLUP);
}
int frame = 0;
void loop() {
  tampil();

  statusBtnOk   = digitalRead(btnOk);

  saatOkDitekan();

  if (OK) {
OK = false;
    if (halaman == 1 && menuItem == 1) {
      halaman = 2;
    } else if (halaman == 2 && halaman == 2) {
      halaman = 3;
    } else if (halaman == 1 && menuItem == 3) {
      halaman = 4;
    } else if (halaman == 1 && menuItem == 4) {
      halaman = 5;
    }
  }

  Serial.println(menuItem);
  delay(100);

}

void saatOkDitekan() {
  if (statusBtnOk != statusAkhirBtnOk) {
    if (statusBtnOk == 0) {
      OK = true;
    }
    delay(50);
  }
  statusAkhirBtnOk = statusBtnOk;
}

//---------KLIK BUTTON--------
void tampil() {
  if (halaman == 1) {   
    lcd.clearDisplay();
    lcd.setTextSize(1);
    lcd.setTextColor(WHITE);
    lcd.setCursor(40, 5);
    lcd.print("Haii Fatma");

    if (menuItem == 1) {   //Jam
      lcd.setTextSize(1);
      lcd.setCursor(46, 20);
      lcd.setTextColor(WHITE);
      lcd.print("<(Buka)>");
    } 
//-----------yang akan tampil ketika di klik----------

  } else if (halaman == 2) {
    lcd.clearDisplay();
    lcd.drawBitmap(0, 0, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
    lcd.display();
    frame = (frame + 1) % FRAME_COUNT;
    delay(FRAME_DELAY);
  }
   else if (halaman == 3) {
    lcd.clearDisplay();
    lcd.setTextSize(1);
    lcd.setTextColor(WHITE);
    lcd.setCursor(1, 0);
    lcd.print("Hai");
    lcd.setTextSize(1);
    lcd.setCursor(20,10);
    lcd.print("esp32");
  }

  lcd.display();
}


