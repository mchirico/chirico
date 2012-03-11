var http = require("http"),
    sys = require("sys");
function getElevation(lat,lng, callback){
    var options = {
        host: 'maps.googleapis.com',
        port: 80,
        path: '/maps/api/elevation/json?locations='+lat+','+lng+'&sensor=true'
    };
    http.get(options, function(res) {
        data = "";
        res.on('data', function (chunk) {
                data += chunk;
            });
        res.on('end', function (chunk) {
                el_response = JSON.parse(data);
                callback(el_response.results[0].elevation);
            });
    });
}

var elevations= [];
function elevationResponse(elevation){
    elevations.push(elevation);
    if(elevations.length == 2){
        console.log("Elevations: "+elevations);
    }
}
getElevation(40.714728,-73.998672, elevationResponse);
getElevation(-40.714728, 73.998672, elevationResponse);
