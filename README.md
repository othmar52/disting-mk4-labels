# disting-mk4-labels
Arduino based eurorack module displaying text on OLED displays

## Parts
-  [Expert Sleepers - disting mk4 Eurorack module](https://www.expert-sleepers.co.uk/downloads/manuals/disting_user_manual_4.20.pdf)
-  [NodeMCU](https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png)
-  [3 x OLED Display 128 x 64](https://www.az-delivery.de/en/products/0-96zolldisplay)
-  [Rotary Encoder (Bourns Inc. PEC16-4015F-S0024)](https://www.digikey.at/product-detail/de/bourns-inc/PEC16-4015F-S0024/PEC16-4015F-S0024-ND/3780222)
-  2 x Resistor 10 K
-  2 x Resistor 220 Ohm

 
![Arduino for Expert Sleepers - disting mk4](media/disting-mk4-labels-arduino.jpg "Arduino for Expert Sleepers - disting mk4")  


## Schematics


```
             NodeMCU
      ┌──────────────────┐
      │◎ A0          D0 ◎│
      │◎ RSV         D1 ●│───> all 3 OLED SCL
      │◎ RSV         D2 ●│───> upper OLED SDA
      │◎ SD3         D3 ●│───> center OLED SDA
      │◎ SD2         D3 ●│───> lower OLED SDA
      │◎ SD1        3V3 ◎│
      │◎ CMD        GND ◎│
      │◎ SD0         D5 ●│───> RotaryEncoder OUTA ──> (see below)
      │◎ CLK         D6 ●│───> RotaryEncoder OUTB ──> (see below)
      │◎ GND         D7 ●│───> RotaryEncoder SW
      │◎ 3V3         D8 ◎│
      │◎ EN          RX ◎│
      │◎ RST         TX ●│───> Resistor 220 Ohm ──> Disting Midi Pin 3
      │◎ GND        GND ●│───> **COMMON GND**
  ┌───│● Vin        3V3 ●│───> **COMMON VCC**
  │   └──────────────────┘
  └──────────────────────────> to Eurorack power BUS 5V
   


**COMMON GND**
──> OLED upper GND
──> OLED center GND
──> OLED lower GND
──> RotaryEncoder GND (2x)
──> PowerBus GND


**COMMON VCC**
──> OLED upper VCC
──> OLED center VCC
──> OLED lower VCC
──> Resistor 220 Ohm ──> Disting Midi Pin 4
──> Resistor 10K  ──> RotaryEncoder OUTA
──> Resistor 10K  ──> RotaryEncoder OUTB



      OLED Screens

                      ┌────────────────┐
                      │ ╔═════════╗    │
                      │ ║  UPPER  ║    │
   to NodeMCU D2  <───│●║ SDA     ║    │
   to NodeMCU D1  <───│●║ SCL     ║    │
to **COMMON VCC** <───│●║ VCC     ║    │
to **COMMON GND** <───│●║ GND     ║    │
                      │ ║         ║    │
                      │ ╚═════════╝    │
                      └────────────────┘
                      ┌────────────────┐
                      │ ╔═════════╗    │
                      │ ║  CENTER ║    │
   to NodeMCU D3  <───│●║ SDA     ║    │
   to NodeMCU D1  <───│●║ SCL     ║    │
to **COMMON VCC** <───│●║ VCC     ║    │
to **COMMON GND** <───│●║ GND     ║    │
                      │ ║         ║    │
                      │ ╚═════════╝    │
                      └────────────────┘
                      ┌────────────────┐
                      │ ╔═════════╗    │
                      │ ║  LOWER  ║    │
   to NodeMCU D4  <───│●║ SDA     ║    │
   to NodeMCU D1  <───│●║ SCL     ║    │
to **COMMON VCC** <───│●║ VCC     ║    │
to **COMMON GND** <───│●║ GND     ║    │
                      │ ║         ║    │
                      │ ╚═════════╝    │
                      └────────────────┘
               


Encoder (Bourns Inc. PEC16-4015F-S0024)

                        ┌─────────────────────┐
                        │                GND ●│─────> to **COMMON GND**
                        │                     │
  to **COMMON GND** <───│● GND                │
                        │       ENCODER       │
                        │         TOP   OUTB ●│──●──> NodeMCU D6
                        │        VIEW         │  │
      to NodeMCU D7 <───│● SW                 │  └──> Resistor 10K ──> **COMMON VCC**
                        │                     │
                        │               OUTA ●│──●──> NodeMCU D5
                        └─────────────────────┘  │
                                                 └──> Resistor 10K ──> **COMMON VCC**

```

