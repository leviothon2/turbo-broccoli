#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>	
// Git Init 2023 hackathon entry by Lev Godar from the UK

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define LOOP_COUNT 5 // 5 times through is roughly one minute
int count = 0; // counter for the main loop

// 'hackathon logo' image via byte array, 64x64px
const unsigned char hackathon [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 
0x00, 0x00, 0x3f, 0xf8, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x01, 0xff, 0x00, 0x00, 
0x00, 0x03, 0xf8, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x07, 0xe0, 0x7f, 0xfe, 0x07, 0xe0, 0x00, 
0x00, 0x0f, 0x83, 0xff, 0xff, 0xc1, 0xf0, 0x00, 0x00, 0x1f, 0x0f, 0xff, 0xff, 0xf0, 0xf8, 0x00, 
0x00, 0x3c, 0x3f, 0xff, 0xff, 0xfc, 0x7c, 0x00, 0x00, 0x78, 0xff, 0xff, 0xff, 0xfe, 0x3e, 0x00, 
0x00, 0xf1, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x01, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x80, 
0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xe7, 0x80, 0x03, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xc0, 
0x07, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xc0, 0x0f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xe0, 
0x0e, 0x3f, 0xff, 0xdf, 0xfb, 0xff, 0xfc, 0xf0, 0x1e, 0x7f, 0xff, 0xdf, 0xfb, 0xff, 0xfc, 0x70, 
0x1c, 0x7f, 0xff, 0xdf, 0xfb, 0xff, 0xfe, 0x70, 0x1c, 0xff, 0xff, 0xdf, 0xfb, 0xff, 0xfe, 0x38, 
0x3c, 0xff, 0xff, 0x8f, 0xf9, 0xff, 0xff, 0x38, 0x39, 0xff, 0xff, 0x87, 0xf1, 0xff, 0xff, 0x3c, 
0x39, 0xff, 0xff, 0x03, 0xe0, 0xff, 0xff, 0x1c, 0x39, 0xff, 0xfe, 0x03, 0xc0, 0x7f, 0xff, 0x9c, 
0x71, 0xff, 0xfe, 0x03, 0xc0, 0x7f, 0xff, 0x9c, 0x73, 0xff, 0xfe, 0x01, 0xc0, 0x7f, 0xff, 0x9c, 
0x73, 0xff, 0xfe, 0x01, 0xc0, 0x3f, 0xff, 0x9e, 0x73, 0xfb, 0xfe, 0x01, 0x80, 0x3f, 0xff, 0x8e, 
0x73, 0xfb, 0xfc, 0x01, 0x80, 0x3f, 0xdf, 0xce, 0x73, 0xfb, 0xfc, 0x01, 0x80, 0x3f, 0x9f, 0xce, 
0x73, 0xfb, 0xfe, 0x01, 0x80, 0x3f, 0x9f, 0xce, 0x73, 0xf9, 0xfe, 0x01, 0x80, 0x3f, 0x9f, 0xce, 
0x73, 0xf8, 0x7e, 0x01, 0xc0, 0x7e, 0x1f, 0x8e, 0x73, 0xf8, 0x1e, 0x03, 0xc0, 0x78, 0x1f, 0x9e, 
0x73, 0xf8, 0x0f, 0x03, 0xc0, 0x70, 0x1f, 0x9c, 0x71, 0xf8, 0x0f, 0x07, 0xe0, 0xe0, 0x3f, 0x9c, 
0x79, 0xf8, 0x07, 0x8f, 0xe0, 0xe0, 0x3f, 0x9c, 0x39, 0xfc, 0x03, 0xff, 0xfb, 0xc0, 0x3f, 0x1c, 
0x39, 0xfc, 0x03, 0xff, 0xff, 0xc0, 0x3f, 0x3c, 0x3c, 0xfc, 0x03, 0xff, 0xff, 0xc0, 0x3f, 0x38, 
0x1c, 0xfc, 0x03, 0xff, 0xff, 0x80, 0x7e, 0x38, 0x1c, 0x7e, 0x01, 0xf8, 0x3f, 0x80, 0x7e, 0x78, 
0x1e, 0x7f, 0x01, 0xf0, 0x1f, 0x80, 0xfc, 0x70, 0x0e, 0x3f, 0x03, 0xe0, 0x0f, 0x80, 0xfc, 0xf0, 
0x0f, 0x3f, 0x83, 0xe0, 0x07, 0xc1, 0xf8, 0xe0, 0x07, 0x9f, 0xe7, 0xc0, 0x07, 0xc7, 0xf1, 0xe0, 
0x07, 0x8f, 0xff, 0xc0, 0x03, 0xff, 0xf3, 0xc0, 0x03, 0xc7, 0xff, 0x80, 0x03, 0xff, 0xe7, 0x80, 
0x01, 0xe3, 0xff, 0x80, 0x01, 0xff, 0xc7, 0x80, 0x00, 0xf1, 0xfe, 0x00, 0x00, 0xff, 0x8f, 0x00, 
0x00, 0xf8, 0xf8, 0x00, 0x00, 0x7e, 0x1e, 0x00, 0x00, 0x7c, 0x20, 0x00, 0x00, 0x0c, 0x7c, 0x00, 
0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x01, 0xf0, 0x00, 
0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x1f, 0xc0, 0x00, 
0x00, 0x01, 0xfe, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x0f, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
    Serial.begin(115200);
    // configure the screen, if the screen isn't working we'll know from the console logs. 
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for official Adafruit oled
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    delay(2000); // Give the display some time to get ready
    // Draw the logo for the hackathon and display it for 2 seconds
    display.clearDisplay();
    display.drawBitmap(32, 0, hackathon, 64, 64, WHITE);
    display.display();
    delay(2000);
    // Draw some text to kick off the app, this will show only once
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Time to Relax!");
    display.display(); 
    delay(1000);
}

void breathInAndOut(void) {
    // Instructions for the app on the screen, simply to breath
    display.clearDisplay();
    display.println("Breathe In and Out");
    display.display();
    delay(1000);
    display.clearDisplay();
    // Create a rectangle with curved edges
    display.fillRoundRect(SCREEN_WIDTH/4, 0, 30, SCREEN_HEIGHT, 2, WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1000);
    // Scroll that rectangle for 3.6 seconds to represent taking in a deep breath
    // Scroll is smooth and efficient, this is why I do it this way. I didn't want stuttery animations
    // to break the calming focus of this app.
    display.startscrollright(0x00, 0x0F);
    delay(3600);
    // Scroll that rectangle back but for 5 seconds for a slower breath out
    display.startscrollleft(0x00, 0x0F);
    delay(5000);
    display.stopscroll();
    delay(500);
}

void loop() {
    
    // Simple app loop that runs the breathInAndOut function until you power off the ESP32
    if(count < LOOP_COUNT) {
        breathInAndOut();
        count ++;
    } else {
        // Finished, congratulate the user
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        // Display static text
        display.println("Congratulations!");
        display.display(); 
        delay(10000);
    }
  
}
