// Include the AccelStepper library:
#include <Arduino.h>
#include <ArxContainer.h>
#include <pwm_lib.h>
#include <stepper_pulse_generator.h>

using namespace arduino_due::pwm_lib;
using namespace arduino_due::stepper_pulse_generator;

std::vector<PulseGeneratorInterface*> steppers;
StepperPulseGenerator<pwm_pin::PWMH0_PC3 /*pin35*/> stepper0(33, 31);
StepperPulseGenerator<pwm_pin::PWML1_PC4 /*pin36*/> stepper1(34, 32);
StepperPulseGenerator<pwm_pin::PWML2_PC6 /*pin38*/> stepper2(40, 42);
StepperPulseGenerator<pwm_pin::PWMH3_PC9 /*pin41*/> stepper3(39, 37);
StepperPulseGenerator<pwm_pin::PWMH5_PC19/*pin44*/> stepper4(46, 48);
StepperPulseGenerator<pwm_pin::PWMH6_PC18/*pin45*/> stepper5(47, 49);

int speed_pps = 1000;

void setup() 
{
  steppers.push_back(&stepper0);
  steppers.push_back(&stepper1);
  steppers.push_back(&stepper2);
  steppers.push_back(&stepper3);
  steppers.push_back(&stepper4);
  steppers.push_back(&stepper5);

  Serial.begin(9600);
}

void loop() {
  speed_pps = -speed_pps;
  for(size_t motor_num = 0; motor_num < steppers.size(); motor_num++)
  {
    steppers[motor_num]->setSpeed(speed_pps);
  }

  for (int count = 0; count < 10; count++)
  {
    Serial.print("Steppers are spinning at ");
    Serial.print(steppers[0]->getSpeed());
    Serial.println("[pps].");
    delay(100);
  }
}
