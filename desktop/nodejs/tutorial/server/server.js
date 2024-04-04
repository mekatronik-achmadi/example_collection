let http = require('http')
let fs = require('fs')

let port = 8080

export function runserver() {
    fs.readFile('./server/index.html', (error,html) => {
        if(error) throw error;

        http.createServer((_,res) => {
            res.writeHead(200, {"Content-Type":"text/html"});
            res.write(html);
            res.end();
        }).listen(port);
    });
}

