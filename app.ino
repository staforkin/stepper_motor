const int pinStep = 3; //
const int pinDir = 4;
const int pinMs1 = 5;
const int pinMs2 = 2;
const int pinMs3 = 6;

//MS1 MS2 MS3 Resolution
//0   0   0   Full step
//1   0   0   Half step
//0   1   0   Quarter step
//1   1   0   Eighth step
//1   1   1   Sixteenth step

const int8_t speeds[5][3] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 1, 1}};
int currentSpeedIndex = 4;

//временная задержка между шагами мотора в мс
const int move_delay = 3;

//шагов на полный оборот в full step режиме
const int steps_rotate_360 = 200;

#include "GyverButton.h"
#define BTN_PIN 7
GButton button(BTN_PIN);

int8_t direction = 0;
boolean ONflag = true;
//a4988
/*Функция, в которой происходит инициализация всех переменных программы*/
void setup()
{
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
  pinMode(pinMs1, OUTPUT);
  pinMode(pinMs2, OUTPUT);
  pinMode(pinMs3, OUTPUT);
  digitalWrite(pinStep, HIGH);
  digitalWrite(pinDir, direction);
  digitalWrite(pinMs1, HIGH);
  digitalWrite(pinMs2, HIGH);
  digitalWrite(pinMs3, HIGH);

  Serial.begin(115200);
  Serial.println();
}

/*Функция-цикл в которой задаётся поведение программы*/
void loop()
{
  mainTick();
  buttonTick();
}

void mainTick()
{
  if (ONflag)
  {
    digitalWrite(pinStep, HIGH);
    delay(move_delay);
    digitalWrite(pinStep, LOW);
    delay(move_delay);
  }
}

void buttonTick()
{
  button.tick();
  if (button.isSingle())
  {
    Serial.println("single click");
    //change speed
    increaseSpeed();
    ONflag = true;
  }
  if (ONflag && button.isDouble())
  {
    direction ^= 1; //change direction
    digitalWrite(pinDir, direction);
    Serial.println("double click");
  }
  if (ONflag && button.isTriple())
  {
    Serial.println("triple click");
  }
  if (ONflag && button.isHolded())
  {
    ONflag = !ONflag;
  }
}

void increaseSpeed()
{
  if (currentSpeedIndex == 0)
  {
    currentSpeedIndex = 4;
  }
  else
  {
    currentSpeedIndex--;
  }
  digitalWrite(pinMs1, speeds[currentSpeedIndex][0]);
  digitalWrite(pinMs2, speeds[currentSpeedIndex][1]);
  digitalWrite(pinMs3, speeds[currentSpeedIndex][2]);
}