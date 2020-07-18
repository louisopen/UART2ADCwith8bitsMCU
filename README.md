### UARTtoEEPROMwith8bitsMCU
* HT-IDE3000 V7.99  HT66F317/HT66F318 28ssop
* Useing HT66F318 UART access to GPIO, LED matrix, EEPROM, ADC, I2C...(Same RS-485 driver)
* 此專案利用PC軟件下達指令以存取MCU內部的EEPROM(64bytes), ADC(10bits), I2C(Hi resolution adc), SPI(OLED display) 透過UART 9600,N,8,1 協議比照RS-485通訊協議格式.

* HT-IDE3000 V7.99
![Image](HT-IDE3000_version.jpg)
* HOLTEK C Compiler V3/Assembly
![Image](ProjectCompiler.jpg)
* HT66F318 Config, used 8Mhz X'tal external, VDD/VDDA all 3.3V
![Image](ProjectOption1.jpg)
![Image](ProjectOption2.jpg)
![Image](ProjectOption3.jpg)
![Image](ProjectOption4.jpg)


#### How to test:
* PC通訊軟件做為主動工具, 協議(9600,n,8,1), 格式比照RS-485格式 (PC指令CRC用 A0 0A代替, MCU反饋的為CRC-16)
* For Example: 
* UART Formate(Get from MCU): 44 03 00 00 00 04 A0 0A   #讀取EEPROM位址0x0000,4組(共計8個bytes)
MCU return設計最大每次讀取四組(8byte) 所以反饋時: 44 03 08 00 01 02 03 04 05 06 07 CRC CRC

* UART Formate(Get from MCU): 44 03 01 00 00 01 A0 0A   #讀取ADC通道0,1組(共計2個bytes), 有8通道可以讀取(an0~an7)
MCU return adc value (an0~an7): 44 03 02 03 FF CRC CRC

* UART Formate(Write to MCU): 44 06 00 0A EE FF A0 0A   #寫入EEPROM位址0x000A,資料為0xEEFF
MCU return: 44 06 00 0A EE FF CRC CRC

#### Other applications:
* UART access to ADC converter(HY3118 24bit ADC) via I2C bus.
* UART access to OLED 16x2 display driver via SPI bus.

