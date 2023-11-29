from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

@app.route('/')
def index():
    return render_template('index_websocket.html')

@socketio.on('message')
def handle_message(message):
    print('Received message:', message)
    socketio.send('Server received: ' + message)

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)

