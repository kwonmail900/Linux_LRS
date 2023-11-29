import paho.mqtt.client as mqtt
import time

# MQTT Broker configuration
broker_address = '127.0.0.1'
broker_port = 1883
topic = 'my/topic'

client = mqtt.Client()
client.connect(broker_address, broker_port)

while True:
    message = f"Hello, MQTT! Time:{time.strftime('%H:%M:%S')}"
    client.publish(topic,message)
    print(f"Published:{message}")
    time.sleep(1)
