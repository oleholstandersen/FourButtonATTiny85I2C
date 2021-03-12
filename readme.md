# FourButtonATTiny85I2C

A four button I2C device based in the ATMEL ATTiny85 chip

The state of the four buttons are returned to the master as a byte with the first four bits indicating the state of the four buttons.

Remark, that a high voltage programmer is needed to set the reset pin enable/disable fuse. If the reset pin is not disabled, the 4th button will not work.