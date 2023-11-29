from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import pymysql
import pandas as pd

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from pandas import DataFrame
from random import randrange
from sqlalchemy import create_engine

app=Flask(__name__)
socketio=SocketIO(app,cors_allowed_origins="*")

def get_sensor_data():
    # conn = pymysql.connect(host='localhost',user='scott',password='tiger',database='mydb')
    engine = create_engine('mysql+pymysql://scott:tiger@localhost/mydb')
    query="SELECT timestamp, temperature, humidity, illuminance FROM (SELECT * FROM SensorData ORDER BY id DESC LIMIT 100)Var1 ORDER BY id ASC"
    df=pd.read_sql(query,con=engine)
    df=df.set_index('timestamp')
    # conn.close()
    engine.dispose()
    return df

def generate_plot(df):
    return df.plot(use_index=True,y=["temperature","humidity","illuminance"],
            kind="line",figsize=(10,5)).legend(loc='upper left')

@socketio.on('connect')
def handle_connect():
    print('Client connected')
    emit('update_plot','Connected')

@app.route('/')
def index():
    return render_template("index_plot.html")

@socketio.on('get_plot')
def handle_get_plot():
    sensor_data=get_sensor_data()
    plot=generate_plot(sensor_data)
    plt.savefig('static/plot.png')
    plt.close()
    emit('update_plot','plot.png')

if __name__ == '__main__':
    socketio.run(app,port=5001)
