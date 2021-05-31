#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AxisJoystick.h>

#include <LcdMenu.h>

#define LCD_ROWS 2
#define LCD_COLS 16

#define SW_PIN 3
#define VRX_PIN A0
#define VRY_PIN A1

Joystick* joystick;

extern MenuItem mainMenu[];

MenuItem mainMenu[] = {ItemHeader(),
                       MenuItem("Start service"),
                       MenuItem("Connect to WiFi"),
                       MenuItem("Settings"),
                       MenuItem("Blink SOS"),
                       ItemFooter()};

LcdMenu menu(LCD_ROWS, LCD_COLS);

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

void setup() { 
    menu.setupLcdWithMenu(0x27, mainMenu); 
    joystick = new AxisJoystick(SW_PIN, VRX_PIN, VRY_PIN);
}

void loop() {
    /**
     * IMPORTANT: You must call this function for the notification to take time
     * into account
     */
    menu.updateTimer();

    // Listen to key
//    char key = keypad.getKey();
//    if (key == NO_KEY) return;

//    switch (key) {
//        case 'A':
//            menu.up();
//            break;
//        case 'B':
//            menu.down();
//            break;
//        case 'C':
//            menu.enter();
            break;
        case 'D':
            menu.back();
            break;
        case '#':
            // When the # key is pressed, the message displays for two seconds
            showNotification();
            break;
        default:
            break;
    }
}

void showNotification() { menu.displayNotification("Success", 2000); }