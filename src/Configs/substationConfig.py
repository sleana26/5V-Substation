import time

import gpiod

def setPins():
    #transformer temperature monitor
    transformerMonitor = 24

    #Gate monitor
    gateMonitor = 15

    chip = gpiod.Chip('/dev/gpiochip0')

    #Lines settings direction configurations
    outputLine = gpiod.LineSettings(direction = gpiod.line.Direction.OUTPUT, output_value=gpiod.line.Value.INACTIVE)
    inputLine = gpiod.LineSettings(direction = gpiod.line.Direction.INPUT, output_value=gpiod.line.Value.ACTIVE)

    #Lines settings value configurations
    active = gpiod.line.Value.ACTIVE
    inactive = gpiod.line.Value.INACTIVE

    chip.request_lines(
        config = 
            {transformerMonitor:inputLine, gateMonitor:inputLine
        }
            ,
        consumer = '5VSubstation',
        output_values = 
            { transformerMonitor:active, gateMonitor:active
        }
    )
    return


#close pins, might pass in the chip and then release?
def releaseLines():
