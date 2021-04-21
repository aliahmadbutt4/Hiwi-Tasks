from flask import Flask, render_template, request, redirect, jsonify
from random import sample
from datetime import datetime
from resource import *

app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])
def index():
    return render_template('index.html')

# Data for the Graph
@app.route('/datag1')
def executionTime():
    return jsonify([{'grizlyExec': sample(range(1, 10),4 )}, {'pandaExec': sample(range(1,10),4 )} ])




# ShowSQL button 
@app.route('/showSQL', methods=['POST','GET'])
def sqlcode():
    if request.method == 'POST':
        obj = compile(request.form['gcode'], 'testString', 'exec')
        exec(obj)
        return render_template('index.html')
    else:
        return render_template('index.html')

# RUN button
@app.route('/codeExecution', methods=['POST','GET'])
def pandasCode():
    if request.method == 'POST':
        obj = compile(request.form['pcode'], 'testString', 'exec')
        exec(obj)
        #print(getrusage(RUSAGE_SELF))
        #return render_template('index.html')
        return jsonify(getrusage(RUSAGE_SELF).ru_maxrss, getrusage(RUSAGE_SELF).ru_utime)
    else:
        #return render_template('index.html')
        return "There is something wrong!!!"
if __name__ == "__main__":
    app.run(debug=True)