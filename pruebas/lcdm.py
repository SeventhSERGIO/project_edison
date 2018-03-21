import mraa

lcd = mraa.I2c(0)
lcd.address(0x62)

# initialise device
lcd.writeReg(0, 0)
lcd.writeReg(1, 0)

lcd.writeReg(0x08, 255)
lcd.writeReg(0x04, 255)
lcd.writeReg(0x02, 255)