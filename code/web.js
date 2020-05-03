var express = require('express')
var app = express()
fs = require('fs');
moment=require('moment');
mysql = require('mysql');

var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'dudwo135',
    database: 'hurryup'
})

connection.connect();

app.get('/', function (req, res) {
    console.log('got app.get(graph)');
    var html = fs.readFile('./graph.html', function (err, html) {
    html = ""+ html
    console.log('read file');

    var qstr = 'select * from degree ';
    connection.query(qstr, function(err, rows, cols) {
      if (err) throw err;

      var data = "";
      var comma = ""
      for (var i=0; i< rows.length; i++) {
         r = rows[i];
         data += comma + "[new Date("+r.time+"),"+r.x_angle+","+r.y_angle+"]";
         comma = ",";
      }

      var header ="data.addColumn('datetime', 'Date/Time');"
      header += "data.addColumn('number', 'X_ANGLE');"
      header += "data.addColumn('number', 'Y_ANGLE');"
            console.log(header);
            console.log(data);
      html = html.replace("<%HEADER%>", header);
      html = html.replace("<%DATA%>", data);

      res.writeHeader(200, {"Content-Type": "text/html"});
      res.write(html);
      res.end();
    });
  });
})

var server = app.listen(8082, function () {
  console.log('Web is Running...')
});
