var http = require('http');
var url = require("url");
var moment=require("moment");
var express = require("express");
var tz = require("moment-timezone");
var qs = require("querystring");
var mysql = require("mysql");

var app = express();

moment.tz.setDefault("Asia/Seoul");

var connection = mysql.createConnection({
	host:"localhost",
	user:"root",
	password:"dudwo135",
	database:"hurryup"
});

connection.connect();

app.get('/degree', function(req, res) {
	obj={};

	obj.x_angle = req.query.x;
	obj.y_angle = req.query.y;
	obj.time=moment().format('YYYY,MM,DD,hh,mm,ss');

	connection.query("insert into degree set ?", obj, function(err, rows, cols) {
		if (err) throw err;

		res.send('Data Check');
		console.log(obj);
	});
});

http.createServer(app).listen(8083, function() {
	console.log('Server is Running...');
});
