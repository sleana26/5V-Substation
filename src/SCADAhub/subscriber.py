import paho.mqtt.client as mqtt
import time
import datetime
import sqlite3
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from config import Config

config = Config()

##sends message to technician to inspect reason for high temp or humidity levels
def email_technician(config, subject, body):
    #compose email
    message = MIMEMultipart()
    message['From'] = config.SCADA_email
    message['To'] = config.technician_email
    message['Subject'] = subject

    message.attach(MIMEText(body, 'plain'))

    try:
        ##connect to gmail SMTP
        server = smtplib.SMTP(config.smtp_server, 587)
        
        ##probably delete this and put login at program start
        ##enable TLS
        server.starttls()
        server.login(config.SCADA_email, config.SCADA_password)

        server.sendmail(config.SCADA_email, config.technician_email, message.as_string())
        print('Notification sent')

    except Exception as e:
        print(f"Error sending email: {e}")

    finally: server.quit()

## handle environment notifications and print data with time stamp
def manage_data(temp, humidity):
    timestamp = datetime.datetime.now()
    data = [timestamp, temp, humidity]
    ##print data
    print("Time: " + timestamp + "| Temp: " + temp + "| Humidity: " + humidity)
    if temp > 30:
        print("Temp high, sending message to technician")
        ##call technician_SMS function
        email_technician(config, "High Temp", "Network closet temperature high")
    # if humidity > 60:
    #     print("Humidity high, sending message to technician")
    #     ##call technician_SMS function
    #     email_technician(config, "High Humidity", "Network closet humidity high")
    ##store data in SQLite
    cur.executemany("INSERT INTO 5VSubstation VALUES(?, ?, ?)", data)
    con.commit()

##defines on_message response. We want to take in the data as an int, check which value it is, temp or humidity, set a value for
def on_message(client, userdata, message):
    data = int(message.payload.decode("utf-8"))
    if message.topic == 'temp':
        temp = data
        if humidity != None:
            ##both values aquired, manage data together
            manage_data(temp, humidity)
            ##set values to zero after handling data
            temp = None
            humiidity = None
    if message.topic == 'humidity':
        humidity = data
        if temp != None:
            ##both values aquired, manage data together
            manage_data(temp, humidity)
            ##set values to zero after handling data
            temp = None
            humiidity = None

##connect to SQLite
con = sqlite3.connect("tempHumidity.db")
cur = con.cursor()
cur.execute("CREATE TABLE 5VSubstation(Time, Transformer Temp, Voltage (C1))")

##testing table creation
result = cur.execute("SELECT name FROM sqlite_master")
result.fetchone()

##buffer values enable the ability to add data to database at same timestamp
temp = None
humidity = None

##connect client to broker and subscribe to temp/humidity data
##change this to use websockets
broker = "localhost"
client = mqtt.Client("EnvMonitor")
client.username_pw_set(config.mosquitto_username, config.mosquitto_password)

client.connect(broker)
client.loop_start()
client.subscribe("home/temp")
client.subscribe("home/humidity")
client.on_message = on_message

##handle data for 30 seconds
time.sleep(30)
client.loop_end()