from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import pandas as pd
import matplotlib.pyplot as plt
import base64
import io
import pymysql

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

# Function to fetch data from the MariaDB database
def fetch_data():

    connection = pymysql.connect(
        host='localhost',
        user='scott',
        password='tiger',
        database='mydb',
        charset='utf8mb4',
        cursorclass=pymysql.cursors.DictCursor
    )

    query = " SELECT * FROM ( SELECT * FROM SensorData ORDER BY id DESC LIMIT 100)Var1 ORDER BY id ASC"
    with connection.cursor() as cursor:
        cursor.execute(query)
        data = cursor.fetchall()
    
    connection.close()
    return pd.DataFrame(data)

@app.route('/')
def index():
    return render_template('index_refresh2.html')

@app.route('/data')
def send_data():
    while True:
        data = fetch_data().to_dict(orient='records')
        socketio.emit('update_data', data)
        socketio.sleep(1)  # Update every 1 second

if __name__ == '__main__':
    socketio.run(app)
