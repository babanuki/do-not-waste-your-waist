var http = require('http');
var url = require("url");
var express = require("express");
var tz = require("moment-timezone");
var qs = require("querystring");
var mysql = require("mysql");

var app = express();

var connection = mysql.createConnection({
	host:"localhost",
	user:"root",
	password:"dudwo135",
	database:"hurryup"
});

connection.connect();

app.get('/degree', function(req, res) {
	var obj = req.query;

	connection.query("insert into degree (x_angle, y_angle) values (" + obj.x + ", " + obj.y + ")", function(err, rows, cols) {
		if (err) throw err;

		res.send('Data Check');
		console.log(obj);
	});
});

http.createServer(app).listen(8083, function() {
	console.log('Server is Running...');
});
