import paho.mqtt.client as mqtt

broker_address = '127.0.0.1'
broker_port = 1883
topic = 'my/topic'

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker")

    client.subscribe(topic)

def on_message(client, userdata, msg):
    print(f"Received:{msg.payload.decode()}")

client = mqtt.Client()

client.on_connect = on_connect
client.on_message = on_message

client.connect(broker_address, broker_port)
client.loop_forever()
