from flask import Flask, render_template, request

app = Flask(__name__)


esp_data = ""

@app.route('/')
def index():
    return render_template('index.html', data=esp_data)

@app.route('/receive_data', methods=['POST'])
def receive_data():
    global esp_data
    if request.method == 'POST':
        
        esp_data = request.form.get('data')
        print("Received data from ESP32: ", esp_data)
        return "Data received successfully!"

@app.route('/data')
def get_data():
    return esp_data  

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
