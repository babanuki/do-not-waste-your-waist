var express = require('express')
var app = express()
var prompt=require('prompt');
var jsdom=require('jsdom');
var http=require('http');
var path=require('path');
var ejs=require('ejs');
fs = require('fs');
moment=require('moment');
mysql = require('mysql');
require('moment-timezone');
moment.tz.setDefault("Asia/Seoul");
const {JSDOM}=jsdom;

app.set("views", __dirname+"/views");
app.set("view engine", "ejs");
app.engine("html", ejs.renderFile);

app.use(express.static(__dirname+"/public"));

const mainPage=fs.readFileSync('./views/webpage.ejs', 'utf8');

var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'dudwo135',
    database: 'hurryup'
})

connection.connect();

app.get('/', function(req, res){
    connection.query("select * from degree where time>SUBDATE(NOW(), INTERVAL 1 minute)", function(err, rows, cols){
        var page=ejs.render(mainPage, {
            datx:rows
        });

	res.send(page);
    });

});

function getData(){
    connection.query("select * from degree where time>SUBDATE(NOW(), INTERVAL 1 months)", function(err, rows, cols){
        var page=ejs.render(mainPage, {
		datx:rows
	});
    });
}

setInterval(getData, 1000);

var server=app.listen(8082, function(){
	console.log("Web start");
});
