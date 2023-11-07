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
        # Fetch data from Sensors table
        cursor.execute('SELECT * FROM Sensors')
        sensors_data = cursor.fetchall()
        print(type(sensors_data))
        print(sensors_data)

        # Fetch data from SensorData table
        cursor.execute('SELECT * FROM SensorData')
        sensor_data_data = cursor.fetchall()
        print(sensor_data_data)

        # Fetch data from SensorStatus table
        cursor.execute('SELECT * FROM SensorStatus')
        sensor_status_data = cursor.fetchall()
        print(sensor_status_data)

        # Close the cursor and connection
        #cursor.close()
        #connection.close()

        return render_template('index.html', sensors=sensors_data, sensor_data=sensor_data_data, sensor_status=sensor_status_data)

if __name__ == '__main__':
    app.run(debug=True)

