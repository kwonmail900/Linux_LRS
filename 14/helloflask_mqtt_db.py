from flask import Flask, render_template, json, request
import pymysql.cursors

app = Flask(__name__)

# Connect to the database
connection = pymysql.connect(host='localhost',
                             user='scott',
                             password='tiger',
                             database='mydb',
                             cursorclass=pymysql.cursors.DictCursor,
                             charset='utf8'
                             )

# Route for displaying the sensor data
@app.route('/')
def display_sensor_data():
    with connection.cursor() as cursor:

        # Fetch data from SensorData table
        cursor.execute('SELECT * FROM SensorData ORDER BY id DESC LIMIT 100')
        sensor_data_data = cursor.fetchall()
        print(sensor_data_data)

        return render_template('index_mqtt.html', sensor_data=sensor_data_data)

if __name__ == '__main__':
    app.run(debug=True)

