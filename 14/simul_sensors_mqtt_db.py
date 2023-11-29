import datetime
import random
import time
import paho.mqtt.client as mqtt
import pymysql

def on_message(client, userdata, message):
    try:
        global mmmmmhh
        payload = message.payload.decode()
        data = eval(payload)

        db_connection = pymysql.connect(host=db_host,user=db_user,password=db_password,database=db_name)
        cursor = db_connection.cursor()

        timestamp = datetime.datetime.strptime(data['time'], '%Y-%m-%d %H:%M:%S')
        sensor_id = data['sensor_id']
        reading = data['reading']
        temperature = data['temperature']
        humidity = data['humidity']
        illuminance = data['illuminance']

        query=f"INSERT INTO {table_name} (sensor_id, reading, timestamp, temperature, humidity, illuminance) VALUES (%s,%s,%s,%s,%s,%s)"
        cursor.execute(query,(sensor_id, reading, timestamp, temperature, humidity, illuminance))
        db_connection.commit()

        db_connection.close()
        print(f"Received and stored: Time:{timestamp}, SID:{sensor_id}, Reading:{reading}, Temp:{temperature}'C, Hum    i:{humidity}%, Illuminance: {illuminance} lux")
    except Exception as e:
        print(f"Error:{e}")

def simulate_and_send(client):
    while True:
        current_time = datetime.datetime.now()
        sensor_id = random.randint(1,3)
        reading = random.uniform(20,30)
        temperature = random.uniform(20,30)
        humidity = random.uniform(40,60)
        illuminance = random.uniform(500,1000)

        data = {'time': current_time.strftime('%Y-%m-%d %H:%M:%S'), 
                'sensor_id': sensor_id,
                'reading': reading,
                'temperature': temperature,
                'humidity': humidity,
                'illuminance': illuminance                                                                                              }
        client.publish(topic,str(data))

        print(f"Time:{current_time} - SID:{sensor_id}, Reading:{reading:.2f}, Temp:{temperature:.2f}'C, Humi:{humidity:.2f}%, Illuminanace:{illuminance:.2f} lux")
        time.sleep(1)

broker_address = 'broker.hivemq.com'
broker_port = 1883
topic = 'sensors'

db_host = 'localhost'
db_user = 'scott'
db_password = 'tiger'
db_name = 'mydb'
table_name = 'SensorData'

mqtt_client = mqtt.Client()
mqtt_client.connect(broker_address, broker_port)

mqtt_client.subscribe(topic)
mqtt_client.on_message = on_message
mqtt_client.loop_start()

simulate_and_send(mqtt_client)
