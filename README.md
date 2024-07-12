# ESPHOME-LED-Clock

Add Lidl AURIOL LED-Wand- und Tischuhr with an ESP, ESPHome to Home Assistant

Steps to add an ESP:
* Remove U1
* Connect GND and VCC with the ESP
* Connect the PIN 10 of U1 to PIN D1 of the ESP


IDs of the LEDs
```text
      _ 19 _ _ _ 18 _        _ 5 _ _ _ 4 _                          _ 55 _ _ _ 54 _        _ 49 _ _ _ 48 _
     |               |      |               |   _            _    |                |      |               |
    20              17      6               3  |1|          |60| 59               53     50              47
     |               |      |               |   -            -    |                |      |               |
     |               |      |               |          _          |                |      |               |
    21              16      7               2         |0|        58               52     51              46
     |               |      |               |          -          |                |      |               |
     |               |      |               |                     |                |      |               |
      - 22 - - - 23 -        - 8 - - - 9  -                       - 57 - - - 58 -         - 44 - - - 45 -
     |               |      |               |                     |                |      |               |
    24              15     13              10          _         33               37     38              43
     |               |      |               |         |31|        |                |      |               |
     |               |      |               |          -          |                |      |               |
    25              14     12              11                    32               36     39              42
     |               |      |               |   _                 |                |      |               |
     |               |      |               |  |30|               |                |      |               |
      - 26 - - - 27 -        - 28 - - - 29 -    -                  - 34 - - - 35 -        - 40 - - - 41 -
```
