#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AxisJoystick.h>
#include <A4988.h>

#include <LcdMenu.h>

#define MOTOR_STEPS 200
#define RPM 120

#define DIR 8
#define STEP 9
#define SLEEP 13 // optional (just delete SLEEP from everywhere if not used)

#define LCD_ROWS 2
#define LCD_COLS 16

#define SW_PIN 4
#define VRX_PIN A0
#define VRY_PIN A1
#define ARDUINO_ADC_MIN 0
#define ARDUINO_ADC_MAX 1023
#define AXES_DEVIATION 100

#define MS1 10
#define MS2 11
#define MS3 12
A4988 stRotator(MOTOR_STEPS, DIR, STEP, SLEEP, MS1, MS2, MS3);

const int stepsPerRevolution = 600;

Joystick* joystick;

void startMixer();

extern MenuItem mainMenu[];
extern MenuItem mnuSettings[];
extern void tglIrany();
extern void tglBackLight();
extern void inpTimer();


MenuItem mainMenu[] = {
    ItemHeader(),
    MenuItem("Keveres", startMixer, MENU_ITEM_COMMAND),
    ItemInput("Idozito","300",inpTimer),
    ItemSubMenu("Beallitasok",mnuSettings),
    ItemToggle("LCD feny","BE","KI",tglBackLight),
    MenuItem("Reset"),
    ItemFooter()
};

MenuItem mnuSettings[] = {
    ItemHeader(mainMenu),
    ItemToggle("Forgas ","Bal","Jobb",tglIrany),
    MenuItem("Sebesseg"),
    MenuItem("Homerseklet"),
    MenuItem("Valtott irany"),
    ItemFooter()
};

LcdMenu menu(LCD_ROWS, LCD_COLS);


void setup() { 
    Serial.begin(9600);
    stRotator.begin(RPM);
    stRotator.enable();
    menu.setupLcdWithMenu(0x27, mainMenu); 
    joystick = new AxisJoystick(SW_PIN, VRX_PIN, VRY_PIN);
    //joystick->calibrate(0,100);
    //joystick->calibrate(ARDUINO_ADC_MIN, ARDUINO_ADC_MAX, AXES_DEVIATION);

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



}
void startMixer() {
    Serial.println("Keverés indul....");
    menu.displayNotification("Keveres...",3000);
    stRotator.startMove(200);
}

void tglIrany() {
    Serial.println("Irány változás...");
}

void showNotification() { menu.displayNotification("Success", 2000); }

void tglBackLight() {
    menu.lcd->setBacklight(menu.getItemAt(menu.getCursorPosition())->isOn);
}

void inpTimer() {
  MenuItem* inp =  menu.getItemAt(menu.getCursorPosition());
  Joystick::Move mv = joystick->singleRead();
  int val = inp->value.toInt();
  int old = val;
  while (mv != Joystick::Move::PRESS) {
      switch(mv) {
          case Joystick::Move::UP:
          val += 10;
          break;
          case Joystick::Move::DOWN:
          val -= 10;
          break;
          case Joystick::Move::RIGHT:
          val += 1;
          break;
          case Joystick::Move::LEFT:
          val -= 1;
          break;
      };
      if ( val < 0 ) val = 0;
      if ( val > 10000 ) val = 10000;
      inp->value = String(val);
      mv = joystick->singleRead();
      if (old != val)
      {
          menu.repaint();
          old = val;
      }
  };
}
