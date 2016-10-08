Downsampling audio:

- Crop section as small as possible
- Convert to mono
- Downsample to 8KHz
- Export as Raw (Headerless) unsigned 8-bit

    od -A n -v -t u1 cat1.wav > cat1.txt


`eeprom_write` expects one serial line per byte like:

`[address (DEC)] [byte (DEC)]\n`

EEPROM has room for 256K, each meow seems to be about 40K

