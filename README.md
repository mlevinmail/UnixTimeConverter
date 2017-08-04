# UnixTimeConverter
Multi platform library that converts unix time to human readable date time and back. When I was looking on the internet I could not find a lightweight library that only have to methods:
    - Convert to unix time
    - Convert from unix time
    
Most libraries include tons of other functionality or tied to a certain platform. Therefore, it could be to "heavy" or simply impossible to run on microcontroller (AVR, ARM etc...)

The only requirement for the library is to be able to include stdint.h where uint8_t, uint16_t and uint32_t are defined.


