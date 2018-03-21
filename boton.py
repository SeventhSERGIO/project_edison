#!/usr/bin/env python
from __future__ import print_function
import time
from upm import pyupm_grove as grove

def main():
    # Create the button object using GPIO pin 0
    button = grove.GroveButton(0)

    # Read the input and print, waiting one second between readings
    while 1:
        print(button.name(), ' value is ', button.value())
        time.sleep(1)

    # Delete the button object
    del button

if __name__ == '__main__':
    main()