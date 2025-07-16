import paho.mqtt.client as mqtt
import time
import thermoHygrometer

##creates client to broker connection
mqttBroker = "10.0.2.15"
client = mqtt.Client("Environment")
client.connect(mqttBroker)

client.start_loop()
client.publish("home/temp", "temp", thermoHygrometer.getTemp())
client.publish("home/humidity", "humidity", thermoHygrometer.getHumidity())
print("Just published temp : " + thermoHygrometer.getTemp() + " and humidity: " + thermoHygrometer.getHumidity())

time.sleep(30)
client.finish_loop()