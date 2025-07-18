from dotenv import load_dotenv
import os

class Config:
    def __init__(self):
        load_dotenv()
        self.SCADA_email = os.getenv('SCADA_EMAIL')
        self.SCADA_password = os.getenv('SCADA_PASSWORD')
        self.technician_email = os.getenv('TECH_EMAIL')
        self.mosquitto_username = os.getenv('MOSQUITTO_USERNAME')
        self.mosquitto_password = os.getenv('MOSQUITTO_PASSWORD')
        self.broker_address = os.getenv('BROKER_ADDRESS')
        self.smtp_server = os.getenv('SMTP_SERVER')

