import datetime
import random
import time

while True:
    current_time = datetime.datetime.now()
    temperature = random.uniform(20,30)
    humidity = random.uniform(40,60)
    illuminance = random.uniform(500,1000)

    print(f"Time:{current_time} - Temperature:{temperature:.2f}'C, Humidity:{humidity:.2f}%, Illuminance:{illuminance:.2f}lux")

    time.sleep(1)
