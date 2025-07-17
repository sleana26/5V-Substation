import paho.mqtt.client as mqtt
import time
import datetime
import sqlite3
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import os
from dotenv import load_dotenv

##sends message to technician to inspect reason for high temp or humidity levels
def email_technician(SCADA_email, SCADA_password, technician_email, subject, body):
    #compose email
    message = MIMEMultipart()
    message['From'] = SCADA_email
    message['To'] = technician_email
    message['Subject'] = subject

    message.attach(MIMEText(body, 'plain'))

    try:
        ##connect to gmail SMTP
        server = smtplib.SMTP('smtp.gmail.com', 587)
        ##enable TLS
        server.starttls()
        server.login(SCADA_email, SCADA_password)

        server.sendmail(SCADA_email, technician_email, message.as_string())
        print('Notification sent')

    except Exception as e:
        print(f"Error sending email: {e}")

    finally: server.quit()

##publishes a request for a cooling to turn on
def cooling_activation():
    pass

## print data with time stamp
def manage_data(temp, humidity):
    timestamp = datetime.datetime()
    data = [timestamp, temp, humidity]
    ##print data
    print("Time: " + timestamp + "| Temp: " + temp + "| Humidity: " + humidity)
    if temp > 30:
        print("Temp high, sending message to technician")
        ##call technician_SMS function
        send_technician_SMS()
    if humidity > 60:
        print("Humidity high, sending message to technician")
        ##call technician_SMS function
        send_technician_SMS()
    ##store data in SQLite
    cur.executemany("INSERT INTO NetworkClosetEnv VALUES(?, ?, ?)", data)
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

##load variables from .env
load_dotenv()

#access email variables
account_sid = os.environ.get('TWILIO_ACCOUNT_SID')
auth_token = os.environ.get('TWILIO_AUTH_TOKEN')
twilio_phone_num = os.environ.get('PHONE_NUM')

#access mosquitto username and password
mosquitto_username = os.environ.get('MOSQUITTO_USER_NAME')
mosquitto_password = os.environ.get('MOSQUITTO_PASSWORD')

##connect to technician SMS
client = Client()

##connect to SQLite
con = sqlite3.connect("tempHumidity.db")
cur = con.cursor()
cur.execute("CREATE TABLE NetworkClosetEnv(time, temp, humidity)")

##testing table creation
result = cur.execute("SELECT name FROM sqlite_master")
result.fetchone()

##buffer values enable the ability to add data to database at same timestamp
temp = None
humidity = None

##connect client to broker and subscribe to temp/humidity data
broker = "localhost"
port = "1883"
client = mqtt.Client("Subscriber")
client.username_pw_set(mosquitto_username, mosquitto_password)
client.connect(broker, port)
client.subscribe("home/temp")
client.subscribe("home/humidity")
client.on_message = on_message

##handle data for 30 seconds
client.loop_start()
time.sleep(30)
client.loop_end()