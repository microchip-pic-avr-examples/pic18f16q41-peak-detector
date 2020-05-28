<!-- Please do not change this html logo with link -->
<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Windowed Peak Detector with the PIC18F16Q41
The operational amplifier (OPA) module, along with a comparator, a digital-to-analog converter (DAC), and the analog-to-digital converter with computation (ADCC) can be used to implement a windowed peak detector.

## Related Documentation

<a href="https://www.microchip.com/wwwproducts/en/PIC18F16Q41">PIC18F16Q41 Product Information</a><br>
TBxxxx, "Using Operational Amplifiers in PIC16 and PIC18"<br>
TBxxxx, "Optimizing Internal Operational Amplifiers for Analog Signal Conditioning"<br>
ANxxxx, "Analog Sensor Measurement and Acquisition"

## Software Used

* <a href="http://www.microchip.com/mplab/mplab-x-ide">MPLAB® IDE 5.40 or newer</a>
* <a href="https://www.microchip.com/mplab/compilers">Microchip XC8 Compiler 2.20 or newer</a>
* <a href="https://www.microchip.com/mplab/mplab-code-configurator">MPLAB® Code Configurator (MCC) 3.95.0 or newer</a>

## Hardware Used

* <a href="https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/DM164137"> Microchip Curiosity Development Board (DM164137) </a>
* *(Optional)* Signal Source

## Setup

<img src="images/diagram.png" alt="schematic" width="500px" /><br>

| Pin | Function
| --- | --------
| RC2 | OPA Module Output
| RC0 | Potentiometer Output on Curiosity
| RB7 | UART Output, 9600 BAUD
| RB5 | Signal Input (connect a signal or RC0 to this input)

#### Special Pins

| Pin | Function
| --- | --------
| TX  | Curiosity UART to USB Transmit

## Operation
The windowed peak detector is a state machine that detects signals that exceed a set level (via DAC2). When a signal is above the set level, the ADCC continuously samples the output of the OPA module, and interrupts if the measured signal subtracted from the last peak value is greater than the 0. In this case, the measured signal is stored in the setpoint register of the ADCC and begins a new conversion. When the signal falls below the threshold, the ADCC stops and the peak value recorded is printed from the setpoint register.


#### Acquisition State Machine
<img src="images/stateMachine.png" alt="state machine drawing" width="400px" /><br>


#### Flowchart
<img src="images/flowchart.png" alt="flowchart" width="500px" /><br>


#### Signal Inputs
In the default configuration, the OPA module is configured as a unity gain buffer, which has a gain of 1. To enable smaller input signals (such as those from sensors), the OPA module can be reconfigured in Microchip Code Configurator (MCC) to a higher gain using the internal resistor ladder.

## Summary

<!-- Summarize what the example has shown -->
