var index = 1;
var xlabel = "Run";

/*** Setting the Execution label ********/
$(document).ready(function(){
    $('#pandasExecution').click(function(){
        xlabel = 'Run'+index;
        index++;
        $('#codeExName').attr("placeholder", xlabel);
        
      }
        );
        
    });

/****** Chart for Stats *********/ 

    // var getData = $.get(/datag1);
    google.charts.load('current', { packages: ['corechart', 'bar']});
    google.charts.setOnLoadCallback(drawExecution);
    
    function drawExecution() {
            var data = new google.visualization.DataTable();
                data.addColumn('string', 'Run');
                data.addColumn('number', 'Grizly');
                data.addColumn({ type: 'string', role: 'annotation'});
                data.addColumn('number', 'Pandas');
                data.addColumn({type: 'string', role: 'annotation'});

                data.addRows([
                    ['Run1', 0.5, '0.5', .25, '.25'],
                    ['Run2', 0.25, '0.25', .15, '.15'],
                    ['Run3', 0.75, '0.75', .65, '.65'],   
                ]);

        var options = {
            title: 'Client RAM consumption',
            annotations: {
            alwaysOutside: true,
            textStyle: {
                fontSize: 14,
                color: '#000',
                auraColor: 'none'
            }
            },
            hAxis: {
            title: 'Executions',
            
            viewWindow: {
                min: [7, 30, 0],
                max: [17, 30, 0]
            }
            },
            vAxis: {
            title: 'Memory Consumption (GB)'
            }
        };

        var chart = new google.visualization.ColumnChart(document.getElementById('chart1_div'));
        var chart1 = new google.visualization.ColumnChart(document.getElementById('chart2_div'));
        chart.draw(data, options);
        chart1.draw(data, options);
        
        }

