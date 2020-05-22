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
	obj.x_accel = req.query.xa;
	obj.y_accel = req.query.ya;
	obj.user_id = req.query.id;
	obj.x_delta = req.query.xd;
	obj.y_delta = req.query.yd;
	obj.x_deltaavg = req.query.xda;
	obj.y_deltaavg = req.query.yda;
	obj.sit_flag = req.query.sit;
	obj.time=""+moment().format('YYYY-MM-DD HH:mm:ss');

	connection.query("insert into degree set ?", obj, function(err, rows, cols) {
		if (err) throw err;

		res.send('Data Check');
		console.log(obj);
	});
});

http.createServer(app).listen(8083, function() {
	console.log('Server is Running...');
});
