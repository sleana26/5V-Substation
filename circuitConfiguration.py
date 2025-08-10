import time
import gpiod

#set pin configurations
recloserA0 = 17
recloserA1 = 27
recloserB0 = 22
recloserB1 = 23
recloserNO = 24

chip = gpiod.Chip('/dev/gpiochip0')

outputLine = gpiod.LineSettings(direction = gpiod.line.Direction.OUTPUT, output_value=gpiod.line.Value.INACTIVE)
inputLine = gpiod.LineSettings(direction = gpiod.line.Direction.INPUT, output_value=gpio.line.Value.ACTIVE)

active = output_value=gpiod.line.Value.ACTIVE
inactive = output_value=gpiod.line.Value.INACTIVE

with chip.request_lines(
        config = {
            (recloserA0:outputLine, recloserA1:outputLine, recloserB0:outputLine, recloserB1:outputLine, recloserNO:outputLine)
            },
        consumer = 'circuitInfrastructure'
) as lines:
    while True:
        lines.getValue(recloserA).set_value(circuit1, gpiod.line.Value.ACTIVE)
        time.sleep(1)
        lines.set_value(circuit1, gpiod.line.Value.INACTIVE)
        time.sleep(1)
lines.release()
