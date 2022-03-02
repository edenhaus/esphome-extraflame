# Extraflame Address Translation

Below my analysis of my oven. As I cannot find any model number on it, a image of it can be found [here](images/board.jpeg).

All description beginning with `??`, means I'm not sure and it's only a fast assumption.

## RAM (0x00)

| **Address** | **Formula** | **Unit** | **Description**                           | **Ex. value (dec)** |
| ----------- | ----------- | -------- | ----------------------------------------- | ------------------- |
| 0x00        |             |          | ?? CPU Timer?                             | 40                  |
| 0x01        | x/2         | °C       | Ambient temperature                       | 40                  |
| 0x02        |             |          | ?? Abgastemperatur?                       | 110                 |
| 0x03        |             |          | ?? constant?                              | 156                 |
| 0x04        |             |          | ?? Random values between 0-40             | 0                   |
| 0x05        |             |          | ?? Random values 0,32,48                  | 0                   |
| 0x06        |             |          | ?? Random values 100-103                  | 100                 |
| 0x07        |             |          | ?? Random values 0-3                      | 3                   |
| 0x08        |             |          | ?? constant?                              | 129                 |
| 0x09        |             |          | ?? constant?                              | 0                   |
| 0x0A        |             |          | low value when running, off -> 255        | 14                  |
| 0x0B        |             |          | low value when running, off -> 255        | 25                  |
| 0x0C        |             |          |                                           | 160                 |
| 0x0D        |             |          | ?? constant?                              | 255                 |
| 0x0E        |             |          | ?? constant?                              | 0                   |
| 0x0F        |             |          | ?? constant?                              | 15                  |
| 0x10        |             |          | ?? similar to 0x29 but not always         | 15                  |
| 0x11        |             |          | ?? constant?                              | 17                  |
| 0x12        |             |          | ?? constant?                              | 1                   |
| 0x13        |             |          | Display Level                             | 4                   |
| 0x14        |             |          | Display 4. char (right)                   | 70                  |
| 0x15        |             |          | Display 3. char                           | 70                  |
| 0x16        |             |          | Display 2. char                           | 79                  |
| 0x17        |             |          | Display 1. char (left)                    | 68                  |
| 0x18        |             |          | ?? constant?                              | 0                   |
| 0x19        |             |          | ?? constant?                              | 26                  |
| 0x1A        |             |          |                                           | 0                   |
| 0x1B        |             |          | ?? constant?                              | 0                   |
| 0x1C        |             |          | ?? constant?                              | 0                   |
| 0x1D        |             |          |                                           | 86                  |
| 0x1E        |             |          |                                           | 0                   |
| 0x1F        |             |          |                                           | 124                 |
| 0x20        |             |          | ?? constant?                              | 7                   |
| 0x21        | x           |          | Status oven                               | 7                   |
| 0x22        |             |          | ?? constant?                              | 0                   |
| 0x23        |             |          | ?? constant?                              | 0                   |
| 0x24        |             |          | ?? constant?                              | 33                  |
| 0x25        |             |          | ?? constant?                              | 0                   |
| 0x26        |             |          | ?? constant?                              | 0                   |
| 0x27        |             |          | ?? constant?                              | 0                   |
| 0x28        |             |          |                                           | 8                   |
| 0x29        | (hex) x     | min      | Current minute in hex                     | 18                  |
| 0x2A        | (hex) x     | h        | Current hour in hex                       | 34                  |
| 0x2B        |             |          | Day of week                               | 7                   |
| 0x2C        |             |          | ?? constant?                              | 0                   |
| 0x2D        |             |          |                                           | 5                   |
| 0x2E        |             |          | ?? constant?                              | 0                   |
| 0x2F        |             |          |                                           | 10                  |
| 0x30        |             |          | ?? constant?                              | 30                  |
| 0x31        |             |          |                                           | 54                  |
| 0x32        | x           | min      | Time until next cleaning. See EEPROM 0x02 | 4                   |
| 0x33        |             |          | ?? similar to 0x02                        | 107                 |
| 0x34        |             |          |                                           | 167                 |
| 0x35        |             |          |                                           | 167                 |
| 0x36        |             |          | ?? constant?                              | 42                  |
| 0x37        | flag&level  |          | Copy of EEPROM 0x60                       | 204                 |
| 0x38        |             |          |                                           | 4                   |
| 0x39        |             |          | Copy of EEPROM 0x38?                      | 36                  |
| 0x3A        |             |          | Copy of EEPROM 0x39?                      | 132                 |
| 0x3B        |             |          | Copy of EEPROM 0x3A?                      | 20                  |
| 0x3C        |             |          | Copy of EEPROM 0x3C?                      | 10                  |
| 0x3D - 0x54 |             |          | Copy of EEPROM 0x04 - 0x1B                | ...                 |
| 0x55        |             |          | ?? constant?                              | 12                  |
| 0x56 - 0x69 |             |          | Copy of EEPROM 0x20 - 0x33                | ...                 |
| 0x6A        |             |          |                                           | 128                 |
| 0x6B        |             |          |                                           | 0                   |
| 0x6C        |             |          |                                           | 25                  |
| 0x6D        |             |          | ?? constant?                              | 0                   |
| 0x6E        |             |          | ?? constant?                              | 30                  |
| 0x6F        |             |          | ?? constant?                              | 0                   |
| 0x70        |             |          |                                           | 0                   |
| 0x71        |             |          |                                           | 11                  |
| 0x72        |             |          | ?? constant?                              | 1                   |
| 0x73        |             |          |                                           | 155                 |
| 0x74        |             |          | ?? constant?                              | 8                   |
| 0x75        |             |          | ?? constant?                              | 0                   |
| 0x76        |             |          | ?? constant?                              | 4                   |
| 0x77        |             |          | ?? constant?                              | 8                   |
| 0x78        |             |          |                                           | 0                   |
| 0x79        |             |          | ?? constant?                              | 39                  |
| 0x7A        |             |          | ?? constant?                              | 51                  |
| 0x7B        |             |          |                                           | 0                   |
| 0x7C        |             |          | ?? constant?                              | 0                   |
| 0x7D        |             |          | ?? constant?                              | 0                   |
| 0x7E        |             |          | ?? constant?                              | 0                   |
| 0x7F        |             |          | ?? constant?                              | 0                   |
| 0x80        |             |          | ?? constant?                              | 0                   |
| 0x81        |             |          | ?? constant?                              | 255                 |
| 0x82        |             |          | ?? constant?                              | 0                   |
| 0x83        |             |          | ?? constant?                              | 255                 |
| 0x84        |             |          | ?? constant?                              | 0                   |
| 0x85        |             |          | ?? constant?                              | 255                 |
| 0x86        |             |          | ?? constant?                              | 0                   |
| 0x87        |             |          | ?? constant?                              | 255                 |
| 0x88        |             |          | ?? constant?                              | 0                   |
| 0x89        |             |          | ?? constant?                              | 255                 |
| 0x8A        |             |          | ?? constant?                              | 0                   |
| 0x8B        |             |          | ?? constant?                              | 255                 |
| 0x8C        |             |          | ?? constant?                              | 0                   |
| 0x8D        |             |          | ?? constant?                              | 255                 |
| 0x8E        |             |          | ?? constant?                              | 0                   |
| 0x8F        |             |          | ?? constant?                              | 255                 |
| 0x90        |             |          | ?? constant?                              | 0                   |
| 0x91        |             |          | ?? constant?                              | 0                   |
| 0x92        |             |          | ?? constant?                              | 0                   |
| 0x93        |             |          | ?? constant?                              | 255                 |
| 0x94        |             |          | ?? constant?                              | 0                   |
| 0x95        |             |          | ?? constant?                              | 240                 |
| 0x96        |             |          | ?? constant?                              | 0                   |
| 0x97        |             |          | ?? constant?                              | 255                 |
| 0x98        |             |          | ?? constant?                              | 0                   |
| 0x99        |             |          | ?? constant?                              | 255                 |
| 0x9A        |             |          | ?? constant?                              | 0                   |
| 0x9B        |             |          | ?? constant?                              | 255                 |
| 0x9C        |             |          | ?? constant?                              | 0                   |
| 0x9D        |             |          | ?? constant?                              | 255                 |
| 0x9E        |             |          | ?? constant?                              | 253                 |
| 0x9F        |             |          | ?? constant?                              | 0                   |
| 0xA0        |             |          | ?? constant?                              | 0                   |
| 0xA1        |             |          | ?? constant?                              | 0                   |
| 0xA2        |             |          |                                           | 20                  |
| 0xA3        |             |          | ?? constant?                              | 255                 |
| 0xA4        |             |          | ?? constant?                              | 40                  |
| 0xA5        |             |          | ?? constant?                              | 55                  |
| 0xA6        |             |          |                                           | 168                 |
| 0xA7        |             |          | ?? constant?                              | 255                 |
| 0xA8        |             |          |                                           | 128                 |
| 0xA9        |             |          | ?? constant?                              | 126                 |
| 0xAA        |             |          | ?? constant?                              | 255                 |
| 0xAB        |             |          | ?? constant?                              | 255                 |
| 0xAC        |             |          | ?? constant?                              | 0                   |
| 0xAD        |             |          | ?? constant?                              | 0                   |
| 0xAE        |             |          | ?? constant?                              | 0                   |
| 0xAF        |             |          | ?? constant?                              | 0                   |
| 0xB0        |             |          |                                           | 3                   |
| 0xB1        |             |          |                                           | 0                   |
| 0xB2        |             |          | ?? constant?                              | 0                   |
| 0xB3        |             |          |                                           | 0                   |
| 0xB4        |             |          |                                           | 8                   |
| 0xB5        |             |          |                                           | 75                  |
| 0xB6        |             |          | ?? constant?                              | 0                   |
| 0xB7        |             |          | ?? constant?                              | 255                 |
| 0xB8        |             |          |                                           | 126                 |
| 0xB9        |             |          |                                           | 171                 |
| 0xBA        |             |          | ?? constant?                              | 0                   |
| 0xBB        |             |          | ?? constant?                              | 0                   |
| 0xBC        |             |          | ?? constant?                              | 0                   |
| 0xBD        |             |          | ?? constant?                              | 117                 |
| 0xBE        |             |          | ?? constant?                              | 0                   |
| 0xBF        |             |          | ?? constant?                              | 255                 |
| 0xC0        |             |          |                                           | 153                 |
| 0xC1        |             |          |                                           | 0                   |
| 0xC2        |             |          |                                           | 80                  |
| 0xC3        |             |          |                                           | 0                   |
| 0xC4        |             |          |                                           | 10                  |
| 0xC5        |             |          |                                           | 57                  |
| 0xC6        |             |          |                                           | 0                   |
| 0xC7        |             |          |                                           | 193                 |
| 0xC8        |             |          |                                           | 0                   |
| 0xC9        |             |          |                                           | 1                   |
| 0xCA        |             |          |                                           | 0                   |
| 0xCB        |             |          |                                           | 133                 |
| 0xCC        |             |          |                                           | 0                   |
| 0xCD        |             |          |                                           | 64                  |
| 0xCE        |             |          |                                           | 0                   |
| 0xCF        |             |          |                                           | 1                   |
| 0xD0        |             |          |                                           | 0                   |
| 0xD1        |             |          |                                           | 255                 |
| 0xD2        |             |          |                                           | 0                   |
| 0xD3        |             |          |                                           | 255                 |
| 0xD4        |             |          |                                           | 0                   |
| 0xD5        |             |          |                                           | 63                  |
| 0xD6        |             |          |                                           | 2                   |
| 0xD7        |             |          |                                           | 255                 |
| 0xD8        |             |          |                                           | 0                   |
| 0xD9        |             |          |                                           | 0                   |
| 0xDA        |             |          |                                           | 0                   |
| 0xDB        |             |          |                                           | 255                 |
| 0xDC        |             |          |                                           | 219                 |
| 0xDD        |             |          |                                           | 255                 |
| 0xDE        |             |          |                                           | 0                   |
| 0xDF        |             |          |                                           | 255                 |
| 0xE0        |             |          |                                           | 0                   |
| 0xE1        |             |          |                                           | 123                 |
| 0xE2        |             |          |                                           | 2                   |
| 0xE3        |             |          |                                           | 0                   |
| 0xE4        |             |          |                                           | 0                   |
| 0xE5        |             |          |                                           | 0                   |
| 0xE6        |             |          |                                           | 210                 |
| 0xE7        |             |          |                                           | 0                   |
| 0xE8        |             |          |                                           | 34                  |
| 0xE9        |             |          |                                           | 89                  |
| 0xEA        |             |          |                                           | 119                 |
| 0xEB        |             |          |                                           | 0                   |
| 0xEC        |             |          |                                           | 210                 |
| 0xED        |             |          |                                           | 0                   |
| 0xEE        |             |          |                                           | 144                 |
| 0xEF        |             |          |                                           | 209                 |
| 0xF0        |             |          |                                           | 107                 |
| 0xF1        |             |          |                                           | 0                   |
| 0xF2        |             |          |                                           | 242                 |
| 0xF3        |             |          |                                           | 89                  |
| 0xF4        |             |          |                                           | 0                   |
| 0xF5        |             |          |                                           | 0                   |
| 0xF6        |             |          |                                           | 63                  |
| 0xF7        |             |          |                                           | 24                  |
| 0xF8        |             |          |                                           | 255                 |
| 0xF9        |             |          |                                           | 5                   |
| 0xFA        |             |          |                                           | 250                 |
| 0xFB        |             |          |                                           | 255                 |
| 0xFC        |             |          |                                           | 76                  |
| 0xFD        |             |          |                                           | 109                 |
| 0xFE        |             |          |                                           | 254                 |
| 0xFF        |             |          |                                           | 1                   |

## EEPROM (0x20)

| **Adress**  | **Formula** | **Unit** | **Description**                                           | **Ex. value (dec)** |
| ----------- | ----------- | -------- | --------------------------------------------------------- | ------------------- |
| 0x00        | x           | min      | max Time for ignition                                     | 7                   |
| 0x01        | x           | min      | Time to fire up                                           | 1                   |
| 0x02        | x           | min      | Minutes between two cleanings                             | 200                 |
| 0x03        | 2x          |          | Pellets push at start                                     | 55                  |
| 0x04        | x/10        | kg/h     | Pellets during ignition                                   | 6                   |
| 0x05        | x/10        | kg/h     | Pellets on level 1                                        | 6                   |
| 0x06        | x/10        | kg/h     | Pellets on level 2                                        | 8                   |
| 0x07        | x/10        | kg/h     | Pellets on level 3                                        | 10                  |
| 0x08        | x/10        | kg/h     | Pellets on level 4                                        | 13                  |
| 0x09        | x/10        | kg/h     | Pellets on level 5                                        | 16                  |
| 0x0A        | 30+x        | °C       | min temperature ignition/no ignition                      | 10                  |
| 0x0B        | 30+x        | °C       | ?? max temperature smoke                                  | 250                 |
| 0x0C        | x           | level    | level during cleaning                                     | 2                   |
| 0x0D        | x           | min      | time automatic cleaning                                   | 31                  |
| 0x0E        | 10(25+x)    | rpm      | speed of smoke fan during cleaning                        | 167                 |
| 0x0F        | 10(25+x)    | rpm      | speed of smoke fan during ignition                        | 143                 |
| 0x10        | 10(25+x)    | rpm      | speed of smoke fan during fire up                         | 161                 |
| 0x11        | 10(25+x)    | rpm      | speed of smoke fan on level 1                             | 113                 |
| 0x12        | 10(25+x)    | rpm      | speed of smoke fan on level 2                             | 131                 |
| 0x13        | 10(25+x)    | rpm      | speed of smoke fan on level 3                             | 149                 |
| 0x14        | 10(25+x)    | rpm      | speed of smoke fan on level 4                             | 161                 |
| 0x15        | 10(25+x)    | rpm      | speed of smoke fan on level 5                             | 167                 |
| 0x16        | x           |          | speed of air fan on level 1                               | 16                  |
| 0x17        | x           |          | speed of air fan on level 2                               | 17                  |
| 0x18        | x           |          | speed of air fan on level 3                               | 18                  |
| 0x19        | x           |          | speed of air fan on level 4                               | 19                  |
| 0x1A        | x           |          | speed of air fan on level 5                               | 20                  |
| 0x1B        | 30+x        | °C       | ??                                                        | 95                  |
| 0x1C        |             |          |                                                           | 7                   |
| 0x1D        |             |          |                                                           | 33                  |
| 0x1E        |             |          |                                                           | 88                  |
| 0x1F        |             |          |                                                           | 0                   |
| 0x20        | time        | hh:mm    | switch-on time of the 2nd period                          | 87                  |
| 0x21        | time        | hh:mm    | switch-off time of the 2nd period                         | 114                 |
| 0x22        | day binary  |          | activated days 2nd period                                 | 127                 |
| 0x23        | time        | hh:mm    | switch-on time of the 3rd period                          | 144                 |
| 0x24        | time        | hh:mm    | switch-on time of the 3rd period                          | 144                 |
| 0x25        | day binary  |          | activated days 3rd period                                 | 0                   |
| 0x26        | 5x-50       | %        | pellet feed adjustment (-50 - +50)                        | 11                  |
| 0x27        | 30+x        | °C       | Tangential fan intervention temperature, on/off threshold | 35                  |
| 0x28        | 30+x        | °C       | Temperature control 1                                     | 25                  |
| 0x29        | 30+x        | °C       | Temperature control 2                                     | 55                  |
| 0x2A        | x           | °C       | Delta "T" of air temperature for re-ignition              | 3                   |
| 0x2B        | x           | min?     | Delay on second threshold intervention                    | 30                  |
| 0x2C        | 10(25+x)    | rpm      | Smoke extraction fan speed in alarm                       | 167                 |
| 0x2D        | x           |          | Tangential fan speed in shutdown                          | 20                  |
| 0x2E        | x           |          | Distribution fan speed at level 1                         | 15                  |
| 0x2F        | x           |          | Distribution fan speed at level 2                         | 16                  |
| 0x30        | x           |          | Distribution fan speed at level 3                         | 17                  |
| 0x31        | x           |          | Distribution fan speed at level 4                         | 18                  |
| 0x32        | x           |          | Distribution fan speed at level 5                         | 19                  |
| 0x33        | x           |          | Distribution fan speed in shutdown                        | 19                  |
| 0x34        |             | %        | Percentage of smoke fan speed adjustment                  | 8                   |
| 0x35        | x           | min?     | Delay from second to first threshold                      | 30                  |
| 0x36        |             | %        | Percentage of tangential fan speed adjustment             | 8                   |
| 0x37        |             |          |                                                           | 0                   |
| 0x38        | time        | hh:mm    | Beginning day period                                      | 36                  |
| 0x39        | time        | hh:mm    | Beginning night period                                    | 132                 |
| 0x3A        | x           | °C       | Day temperature                                           | 20                  |
| 0x3B        | x           | °C       | Night temperature                                         | 12                  |
| 0x3C        |             |          |                                                           | 10                  |
| 0x3D        |             | 0 or 1   | Distribution motor start/stop                             | 0                   |
| 0x3E        | 5x-50       | %        | setting of distribution motor                             | 10                  |
| 0x3F        |             |          | ?? not used?                                              | 255                 |
| 0x40        |             |          |                                                           | 32                  |
| 0x41        |             |          |                                                           | 32                  |
| 0x42        |             |          |                                                           | 32                  |
| 0x43        |             |          |                                                           | 32                  |
| 0x44        |             |          |                                                           | 32                  |
| 0x45        |             |          |                                                           | 44                  |
| 0x46        |             |          |                                                           | 20                  |
| 0x47        |             |          |                                                           | 19                  |
| 0x48        |             |          |                                                           | 29                  |
| 0x49        |             |          |                                                           | 53                  |
| 0x4A        |             |          |                                                           | 85                  |
| 0x4B        |             |          |                                                           | 2                   |
| 0x4C        |             |          |                                                           | 0                   |
| 0x4D        |             |          |                                                           | 85                  |
| 0x4E        |             |          |                                                           | 9                   |
| 0x4F        |             |          |                                                           | 0                   |
| 0x50        |             |          |                                                           | 42                  |
| 0x51        |             |          |                                                           | 10                  |
| 0x52        |             |          |                                                           | 0                   |
| 0x53        |             |          |                                                           | 70                  |
| 0x54        |             |          |                                                           | 1                   |
| 0x55        |             |          |                                                           | 0                   |
| 0x56        |             |          |                                                           | 40                  |
| 0x57        |             |          |                                                           | 0                   |
| 0x58        |             |          |                                                           | 0                   |
| 0x59 - 0x5B |             |          | ?? not used?                                              | 255                 |
| 0x5C        |             |          |                                                           | 0                   |
| 0x5D        |             |          |                                                           | 0                   |
| 0x5E        |             |          |                                                           | 3                   |
| 0x5F        |             |          | ?? not used?                                              | 255                 |
| 0x60        | flag&level  |          | See below                                                 | 204                 |
| 0x61        | x/2         | °C       | set (target) temperature                                  | 42                  |
| 0x62        |             |          | ?? last status                                            | 4                   |
| 0x63        |             |          | ?? error code? 32->No Pell                                | 0                   |
| 0x64        |             |          |                                                           | 0                   |
| 0x65        |             |          | ?? copy of 1D?                                            | 33                  |
| 0x66        |             |          | ?? copy of 1E?                                            | 88                  |
| 0x67        |             |          |                                                           | 44                  |
| 0x68        |             |          |                                                           | 8                   |
| 0x69        | x           | 0 or 1   | activate the weekly programmer                            | 0                   |
| 0x6A        | time        | hh:mm    | switch-on time of the 1st period                          | 39                  |
| 0x6B        | time        | hh:mm    | switch-off time of the 1st period                         | 51                  |
| 0x6C        | day binary  |          | activated days 1st period                                 | 0                   |
| 0x6D - 0x6E |             |          | ?? not used?                                              | 255                 |
| 0x6F        |             |          |                                                           | 10                  |
| 0x70        |             |          |                                                           | 10                  |
| 0x71        |             |          |                                                           | 10                  |
| 0x72        |             |          |                                                           | 10                  |
| 0x73        |             |          |                                                           | 10                  |
| 0x74        |             |          |                                                           | 10                  |
| 0x75        |             |          |                                                           | 10                  |
| 0x76        |             |          |                                                           | 10                  |
| 0x77        |             |          |                                                           | 10                  |
| 0x78        |             |          |                                                           | 10                  |
| 0x79        |             |          |                                                           | 10                  |
| 0x7A        |             |          |                                                           | 10                  |
| 0x7B        |             |          |                                                           | 10                  |
| 0x7C        |             |          |                                                           | 10                  |
| 0x7D        |             |          |                                                           | 10                  |
| 0x7E        |             |          |                                                           | 10                  |
| 0x7F - 0xC8 |             |          | ?? not used?                                              | 255                 |
| 0xC9        |             |          |                                                           | 1                   |
| 0xCA        |             |          |                                                           | 57                  |
| 0xCB - 0xCE |             |          | ?? not used?                                              | 255                 |
| 0xCF        |             |          |                                                           | 1                   |
| 0xD0 - 0xFF |             |          | ?? not used?                                              | 255                 |

## Custom formats

### Time

`floor(x/6)`:`(x%6)*10`

Ex.:

- 0x25 (37) -> 06:10
- 0x84 (132) -> 22:00

### Day binary

Value must be interpreted as binary string. For each day a bit exist.
Least significant bit is monday and highest significant bit is sunday.

Ex.:

- 0x0 (0) -> 0000000 -> All days deactivated
- 0x7 (7) -> 0000111 -> Mo,Tue, Wed activated
- 0x40 (64) -> 1000000 -> Sunday activated
- 0x7F (127) -> 1111111 -> All days activated

### Flag&Level

Value is composed of by 5 binary encoded flags and the oven level.
The 5 high significant bits, specifies the following flags in order:
- unknown
- unknown
- unknown
- night/day temperature feature enabled
- unknown

The three least significant bits specified the level.
To get the night/day temperature flag to the following:

```c++
return x & 0x10;
```

To find out the current level use the following snippet:

```c++
return x & 0x07;
```

Ex.:

- `0xDD (221)` -> Night/Day disabled, Level 5
- `0xC9 (201)` -> Night/Day enabled, Level 1
