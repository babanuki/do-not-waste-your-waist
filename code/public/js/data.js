var express = require('express')
var app = express()
fs = require('fs');
moment=require('moment');
mysql = require('mysql');
require('moment-timezone');
moment.tz.setDefault("Asia/Seoul");

var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'dudwo135',
    database: 'hurryup'
})

connection.connect();


