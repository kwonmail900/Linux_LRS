import datetime
import random
import matplotlib.pyplot as plt

start_date = datetime.datetime(2023,1,1,0,0,0)
end_date = datetime.datetime(2023,1,2,0,0,0)
time_delta = datetime.timedelta(minutes=10)
timestamps = [start_date + i*time_delta for i in range(int((end_date - start_date)/time_delta))]

temperature = [random.uniform(20,30) for _ in range(len(timestamps))]
humidity = [random.uniform(40,60) for _ in range(len(timestamps))]
illuminance = [random.uniform(500,1000) for _ in range(len(timestamps))]

plt.figure(figsize=(10,5))
plt.plot(timestamps, temperature, label='Temperature (\'C)')
plt.plot(timestamps, humidity, label='Humidity (%)')
plt.plot(timestamps, illuminance, label='Illuminanace (lux)')
plt.xlabel('Time')
plt.ylabel('Value')
plt.title('Temperature, Humidity, and Illuminance Simulation')
plt.legend()
plt.grid(True)
plt.show()
