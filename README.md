Downsampling audio:

- Crop section as small as possible
- Convert to mono
- Downsample to 8KHz
- Export as Raw (Headerless) unsigned 8-bit

    od -w1 -A n -v -t u1 cat1.wav > cat1.txt

    ls cat*.wav | while read line; do od -w1 -A n -v -t u1 "$line" | tr -d ' ' > "${line}.txt"; done

`eeprom_write` expects one serial line per byte like:

`[address (DEC)] [byte (DEC)]\n`

EEPROM has room for 32K, each meow seems to be about 8K



Notes

http://forum.arduino.cc/index.php?topic=72092.0
https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM
http://playground.arduino.cc/Main/TimerPWMCheatsheet
http://apcmag.com/arduino-project-5-digital-audio-player.htm/
https://github.com/robstave/ArduinoComponentSketches/wiki/ATTINY85-Timers
http://www.instructables.com/id/Arduino-Timer-Interrupts/?ALLSTEPS
http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html
http://ww1.microchip.com/downloads/en/DeviceDoc/20001203U.pdf
https://embeddedthoughts.com/2016/06/06/attiny85-introduction-to-pin-change-and-timer-interrupts/
