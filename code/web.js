var express = require('express')
var app = express()
var prompt=require('prompt');
var jsdom=require('jsdom');
fs = require('fs');
moment=require('moment');
mysql = require('mysql');
require('moment-timezone');
moment.tz.setDefault("Asia/Seoul");

app.use(express.static(__dirname));

var user_id=undefined;

var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'dudwo135',
    database: 'hurryup'
})

connection.connect();

app.get('/', function(req, res){
    var html=fs.readFile('./login.html', function(err, html){
	html=""+html;
	    res.writeHeader(200, {"Content-Type": "text/html"});
      res.write(html);
      res.end();
    });
});

app.get('/id', function (req, res) {
    if(req.query.id!=undefined)
    	user_id=req.query.id;
    console.log('got app.get(graph)');
    var html = fs.readFile('./graph.html', function (err, html) {
    html = ""+ html
    console.log('read file');
    
    var qstr = 'select * from degree where user_id='+user_id;
    connection.query(qstr, function(err, rows, cols) {
      if (err) throw err;
      var pointX;
      var pointY;
      var point=""
      var data = "";
      var comma = ""
      for (var i=rows.length-1; i>-1; i--) {
	 if(i==rows.length-3600)
	      break;

         r = rows[i];
         data += comma + "["+i+","+r.x_angle+","+r.y_angle+"]";
         comma = ",";

	 if(i==rows.length-1)
	      pointX=r.x_angle, pointY=r.y_angle;
      }
      point="X="+pointX+"       |       Y="+pointY;

      var header ="data.addColumn('number', 'Time');"
      header += "data.addColumn('number', 'X_ANGLE');"
      header += "data.addColumn('number', 'Y_ANGLE');"
            console.log(header);
            console.log(data);
      html = html.replace("<%HEADER%>", header);
      html = html.replace("<%DATA%>", data);
      html = html.replace('"%point%"', point);
      html = html.replace('"%pointX%"', pointX);
      html = html.replace('"%pointY%"', pointY);

      var color = "";
      var comment="";

      if(pointX>-15 && pointX<15 && pointY>-10 && pointY<10){
	    color+="#00CC00";
	    comment+="Ohhh, your waist is good enough!<br>Keep that LUL\n";
      }
      else if(pointX>-24 && pointX<24 && pointY>-20 && pointY<20){
	    color+="#CCCC00";
	    comment+="Nah, your waist may be in trouble...\n";
      }
      else{
	      color+="#CC0000";
	      comment+="BAD, PRETTY BAD!!<br>SAY SORRY TO YOUR WAIST\n";
      }

      html = html.replace('%color%', color);
      html = html.replace('%comment%', comment);
      res.writeHeader(200, {"Content-Type": "text/html"});
      res.write(html);
      res.end();
    });
  });
})

var server = app.listen(8081, function () {
  console.log('Web is Running...')
});
