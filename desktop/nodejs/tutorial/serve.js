const http = require('http');
const fs = require('fs');
const port = 8080;

const server = http.createServer((req,res) => {
    if(req.url=='/'){
        res.writeHead(200,{'content-type':'text/html'});
        fs.createReadStream('./index.html').pipe(res);
    }
});

http.use

function runserver() {
    server.listen(port);
}

module.exports = {
    port,
    runserver,
}
