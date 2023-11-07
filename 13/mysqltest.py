import pymysql.cursors

# Connect to the database
connection = pymysql.connect(host='localhost',
                             user='scott',
                             password='tiger',
                             database='mydb',
                             cursorclass=pymysql.cursors.DictCursor)

with connection:
    with connection.cursor() as cursor:
        # Create a new record
        sql = "INSERT INTO users (email, password) VALUES (%s, %s)"
        sql = "INSERT INTO SensorData (sensor_id, reading, timestamp) VALUES (%s, %s, CURRENT_TIMESTAMP)"
        cursor.execute(sql, (2, 30.5))

    # connection is not autocommit by default. So you must commit to save
    # your changes.
    connection.commit()

    with connection.cursor() as cursor:
        # Read a single record
        sql = "select b.id, a.name, b.sensor_id, b.reading, b.timestamp, c.status from Sensors as a, SensorData as b, SensorStatus as c WHERE a.id=b.sensor_id and a.id=c.sensor_id and a.name=%s"
        cursor.execute(sql, ('Sensor2',))
        result = cursor.fetchone()
        print(result)
