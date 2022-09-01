#ifndef __STEPPER_PULSE_GENERATOR_H__
#define __STEPPER_PULSE_GENERATOR_H__

#include <Arduino.h>
#include "pwm_lib.h"

namespace arduino_due
{

namespace stepper_pulse_generator
{

class PulseGeneratorInterface
{
public:
    PulseGeneratorInterface() {};
    ~PulseGeneratorInterface() {};

    virtual void setSpeed(int16_t speed_pps) = 0;
    virtual int16_t getSpeed() = 0;
};

template <arduino_due::pwm_lib::pwm_pin PIN>
class StepperPulseGenerator : public PulseGeneratorInterface
{
public:
    StepperPulseGenerator(int direction_pin, int enable_pin = -1);
    ~StepperPulseGenerator();

    virtual void setSpeed(int16_t speed_pps);
    virtual int16_t getSpeed();

private:
    int enable_pin_;
    int direction_pin_;
    arduino_due::pwm_lib::pwm<PIN> pwm_controller;

    bool is_pwm_started_;
    int16_t current_speed_pps;
};

template <arduino_due::pwm_lib::pwm_pin PIN>
StepperPulseGenerator<PIN>::StepperPulseGenerator(int direction_pin, int enable_pin)
: enable_pin_(enable_pin)
, direction_pin_(direction_pin)
, pwm_controller()
, is_pwm_started_(false)
{
    if (enable_pin_ != -1)
    {
        pinMode(enable_pin_, OUTPUT);
        digitalWrite(enable_pin_,HIGH);
    }

    pinMode(direction_pin_, OUTPUT);
    digitalWrite(direction_pin_,LOW);

    pwm_controller.stop();
}

template <arduino_due::pwm_lib::pwm_pin PIN>
StepperPulseGenerator<PIN>::~StepperPulseGenerator()
{
    if (enable_pin_ != -1)
    {
        digitalWrite(enable_pin_,LOW);
    }
    digitalWrite(direction_pin_,LOW);

    pwm_controller.stop();
}

template <arduino_due::pwm_lib::pwm_pin PIN>
void
StepperPulseGenerator<PIN>::setSpeed(int16_t speed_pps)
{
    current_speed_pps = speed_pps;

    digitalWrite(enable_pin_,HIGH);
    if (speed_pps == 0)
    {
        pwm_controller.stop();
        is_pwm_started_ = false;

        return;
    }
    else if (speed_pps > 0)
    {
        digitalWrite(direction_pin_, LOW);
    }
    else
    {
        digitalWrite(direction_pin_, HIGH);
    }
    uint32_t period = 100000000 / ((uint32_t) abs(speed_pps));
    if (is_pwm_started_)
    {
        pwm_controller.set_period_and_duty(period,(period>>1),false);
    }
    else
    {
        pwm_controller.start(period,(period>>1));
        is_pwm_started_ = true;
    }
}

template <arduino_due::pwm_lib::pwm_pin PIN>
int16_t
StepperPulseGenerator<PIN>::getSpeed()
{
    return current_speed_pps;
}

} /* namespace stepper_pulse_generator */

} /* namespace arduino_due */

#endif // __STEPPER_PULSE_GENERATOR_H__