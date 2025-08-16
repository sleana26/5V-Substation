import time

import gpiod

#set pin configurations
#reclosers
recloser1 = 17
recloser2 = 27
recloser3 = 22
recloserNO = 23

#manualRecloserSwitches
switch1 = 25
switch2 = 16
switch3 = 26
switch4 = 14

#potentiometers
v0 = 2
v1 = 3

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

with chip.request_lines(
        config = 
            {recloser1:outputLine, recloser2:outputLine, recloser3:outputLine, recloserNO:outputLine,
             switch1:inputLine, switch2:inputLine, switch3:inputLine, switch4:inputLine, v0:inputLine,
             v1:inputLine, transformerMonitor:inputLine, gateMonitor:inputLine
        }
            ,
        consumer = 'circuitInfrastructure',
        output_values = 
            { recloser1:inactive, recloser2:inactive, recloser3:inactive, recloserNO:inactive,
             switch1:active, switch2:active, switch3:active, switch4:active, v0:active,
             v1:active, transformerMonitor:active, gateMonitor:active
        }
) as lines:
    while True:

        i
        lines.set_value(recloser1, gpiod.line.Value.ACTIVE)
        time.sleep(1)
        lines.set_value(circuit1, gpiod.line.Value.INACTIVE)
        time.sleep(1)
lines.release()
