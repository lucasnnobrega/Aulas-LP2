var http = require('http')
var path = require('path')
var express = require('express')


var app = express() 

app.get('/', function (req,res) {
	res.sendFile(path.join(__dirname + '/index.html'))
});

app.get('/sketch.js', function (req,res) {
	res.sendFile(path.join(__dirname + '/sketch.js'))
});

app.get('/log.txt', function(req,res) {
	res.sendFile(path.join(__dirname + '/log.txt'))
})

app.get('/addons/p5.dom.js', function(req, res){
	res.sendFile(path.join(__dirname + '/addons/p5.dom.js'))
})

app.get('/p5.min.js', function(req, res){
	res.sendFile(path.join(__dirname + '/p5.min.js'))
})

app.get('/addons/p5.dom.min.js', function(req, res){
	res.sendFile(path.join(__dirname + '/addons/p5.dom.min.js'))
})

app.get('/addons/p5.sound.min.js', function(req, res){
	res.sendFile(path.join(__dirname + '/addons/p5.sound.min.js'))
})

app.listen(8080, ()=>{
	console.log('Started listening')	
})
