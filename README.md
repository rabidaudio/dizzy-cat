Downsampling audio:

- Crop section as small as possible
- Convert to mono
- Downsample to 8KHz
- Export as Raw (Headerless) unsigned 8-bit

    od -w1 -A n -v -t u1 cat1.wav > cat1.txt

    ls cat*.wav | while read line; do od -w1 -A n -v -t u1 "$line" | tr -d ' ' > "${line}.txt"; done

`eeprom_write` expects one serial line per byte like:

`[address (DEC)] [byte (DEC)]\n`

EEPROM has room for 256K, each meow seems to be about 40K

