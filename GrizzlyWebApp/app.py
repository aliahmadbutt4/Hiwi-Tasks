from flask import Flask, render_template, request, redirect, jsonify
from random import sample
from datetime import datetime

app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])
def index():
    return render_template('index.html')

# Data for the Graph
@app.route('/datag1')
def executionTime():
    return jsonify([{'grizlyExec': sample(range(1, 10),4 )}, {'pandaExec': sample(range(1,10),4 )} ])




# ShowSQL button and Grizzly script
@app.route('/showSQL', methods=['POST','GET'])
def sqlcode():
    if request.method == 'POST':
        codeText = request.form['gcode']
        
        return 'This is the text from the grizzly text area: ' + codeText
    else:
        return render_template('index.html')

# RUN button and Pandas script
@app.route('/pandasCode', methods=['POST','GET'])
def pandasCode():
    if request.method == 'POST':
        codeText = request.form['pcode']

        return 'This is the text pasted in the text area: ' + codeText
    else:
        return render_template('index.html')
if __name__ == "__main__":
    app.run(debug=True)