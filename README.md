# stepper_pulse_generator_for_arduino_due

## About
With PWM units in Arduino Due (SAM3X8E), this library can generate pulses suitable for rotating the stepper at a desired speed. 

## Description
digitalWrite() is mainly used to control the stepper.
While this allows the user to freely change the waveform, it requires the arduino to concentrate on its processing. If a time-consuming process such as serial communication is added, the waveform will be distorted.

This library generates waveforms from the PWM units in the Arduino Due. This frees the arduino from the process of generating waveforms and allows it to do other work.

Although a library for generating waveforms originally existed, this library is specialized for steppers. It does not control even the number of pulses generated, so it can be used to operate a stepper at a desired speed.

## Requirement
This library dependent below libraries. They are putted into lib/ as submodule.

- antodom/pwm_lib 

  This is library to use PWM units.

- antodom/tc_lib

  This is needed to build pwm_lib.


## How to build example
You can build by VS Platform IO with Visual Studio Code.