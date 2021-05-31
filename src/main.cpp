#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AxisJoystick.h>
#include <AccelStepper.h>

#include <LcdMenu.h>

#define LCD_ROWS 2
#define LCD_COLS 16

#define SW_PIN 3
#define VRX_PIN A0
#define VRY_PIN A1

Joystick* joystick;

void startMixer();

extern MenuItem mainMenu[];
extern MenuItem mnuSettings[];


MenuItem mainMenu[] = {
    ItemHeader(),
    MenuItem("Keveres", startMixer, MENU_ITEM_COMMAND),
    MenuItem("Idozito"),
    ItemSubMenu("Beallitasok",mnuSettings),
    MenuItem("Reset"),
    ItemFooter()
};

MenuItem mnuSettings[] = {
    ItemHeader(mainMenu),
    MenuItem("Forgas irany"),
    MenuItem("Sebesseg"),
    MenuItem("Homerseklet"),
    MenuItem("Valtott irany"),
    ItemFooter()
};

LcdMenu menu(LCD_ROWS, LCD_COLS);


void setup() { 
    Serial.begin(9600);
    menu.setupLcdWithMenu(0x27, mainMenu); 
    joystick = new AxisJoystick(SW_PIN, VRX_PIN, VRY_PIN);
}

void loop() {
    /**
     * IMPORTANT: You must call this function for the notification to take time
     * into account
     */

    menu.updateTimer();
    Joystick::Move move = joystick->singleRead();

    switch(move) {
        case Joystick::Move::UP :
            menu.up();
            break;
        case Joystick::Move::DOWN:
            menu.down();
            break;
        case Joystick::Move::LEFT:
            menu.back();
            break;
        case Joystick::Move::RIGHT:
            menu.enter();
            break;
        case Joystick::Move::PRESS:
            menu.enter();
            break;    
        case Joystick::Move::NOT:
            break;
    }

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
//            break;
//        case 'D':
//            menu.back();
//            break;
//        case '#':
//            // When the # key is pressed, the message displays for two seconds
//            showNotification();
//            break;
//        default:
//            break;
//    }

}
void startMixer() {
    Serial.println("Keverés indul....");
}

void showNotification() { menu.displayNotification("Success", 2000); }