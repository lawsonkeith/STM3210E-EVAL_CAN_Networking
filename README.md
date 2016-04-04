##Project to output CAN frames off a STM32F103. 
A debug port is added to USART 1 to debug the code, this transmits strings to a terminal at 19K2 baud.

Setup your CAN as follows using TI SN65HVD230 & STM32F103C8T6:

![](https://github.com/lawsonkeith/STM3210E-EVAL_CAN_Networking/raw/master/DSC_0383.JPG)

Canbus analyser setup (microchip)...

![](https://github.com/lawsonkeith/STM3210E-EVAL_CAN_Networking/raw/master/Can analyser.PNG)

Schematic for F103...

![](https://github.com/lawsonkeith/STM3210E-EVAL_CAN_Networking/raw/master/57.JPG)

Here I used a cheapo ebay CAN monitor:

STM3210E-EVAL_CAN_Networking/Can analyser.PNG

![](https://github.com/lawsonkeith/STM3210E-EVAL_CAN_Networking/raw/master/cheapo can wiring.PNG)

![](https://github.com/lawsonkeith/STM3210E-EVAL_CAN_Networking/raw/master/cheapo can.PNG)

###Wiring


Can analyser:

| CAN Tx | Analayzer |
| --- | --- |
|  Gnd | 6 Gnd |
|  Can H | 3 Can H |
| Can L | 2 Can L |


Can Transceiver:

| STM | Can Tx |
| ---  | --- |
| A11 | CRX |
| A12 | CTX |
| G   | GND |
| 3.3 | 3V3 |


3.3V TTL-> USB Converter (debug port)

| STM | TTL |
| --- | --- |
| G | Gnd |
| A9 | RXD |


STM32 to STLink

| STM | STLink |
| --- | --- |
| 3.3 | 3.3V |
| IO | SWDIO |
| CLK | SWCLK |
| GND | GND |

Boot  pins

| Boot0 | Boot1 |
| --- | --- |
| 0 | 0 |


###Mods
Generally:

* Cange build settings to your processor type STM32F103C8T6
* Change eval board to  USE_STM3210E_EVAL

Then check you're ont the right pins in platform_config.h. 
