/*****  jQuery script for clearResults button  ******/

$(document).ready(function(){
  $("#clresults").click(function(){
    $("#gcode").text("Hello world!");
    
  });
 });

 
/***********  Loading the examples in both the text areas  *******/
    $(document).ready(function(){
   $("#example1").click(function(){
     $("#gcode").text("x = [1,2,3,4,5]\r\ny=[6,7,8,9,0]\r\nsum = x + y\r\nprint (sum)");
     $("#pcode").text("import pandas\r\nmydataset = {'cars': [\"BMW\", \"Volvo\", \"Ford\"],\
     'passings': [3, 7, 2] }\r\nmyvar = pandas.DataFrame(mydataset)\r\nprint(myvar)");

   });
 });


    $(document).ready(function(){
   $("#example2").click(function(){
    $("#gcode").text("Example2");
     $("#pcode").text("Example2");

   });
 });

 
    $(document).ready(function(){
   $("#example3").click(function(){
    $("#gcode").text("Example3");
     $("#pcode").text("Example3");

   });
 });
  
 
    $(document).ready(function(){
   $("#example4").click(function(){
    $("#gcode").text("Example4");
     $("#pcode").text("Example4");

   });
 });
  


