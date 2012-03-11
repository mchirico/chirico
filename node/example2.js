var libpath = require('path'),
    http = require("http"),
    fs = require('fs'),
    url = require("url");


var path = "./tmp";
var port = 8124;

http.createServer(function (request, response) {

    var uri = url.parse(request.url).pathname;
    var filename = libpath.join(path, uri);

    libpath.exists(filename, function (exists) {
        if (!exists) {
            response.writeHead(404, {
                "Content-Type": "text/plain"
            });
            response.write("404 Not Found\n");
            response.end();
            return;
        }

        if (fs.statSync(filename).isDirectory()) {
            filename += '/index.html';
        }

        fs.readFile(filename, "binary", function (err, file) {
            if (err) {
                response.writeHead(500, {
                    "Content-Type": "text/plain"
                });
                response.write(err + "\n");
                response.end();
                return;
            }


        });
    });
}).listen(port);

