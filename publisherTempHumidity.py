import paho.mqtt.client as mqtt
import time
import thermoHygrometer
from config import Config

config = Config()

##creates client to broker connection
mqttBroker = "10.0.2.15"
client = mqtt.Client("EnvSensor")
client.username_pw_set(config.mosquitto_username, config.mosquitto_password)

client.connect(mqttBroker)
client.loop_start()
client.publish("home/temp", "temp", thermoHygrometer.getTemp())
client.publish("home/humidity", "humidity", thermoHygrometer.getHumidity())
print("Just published temp : " + thermoHygrometer.getTemp() + " and humidity: " + thermoHygrometer.getHumidity())

time.sleep(30)
client.loop_end()