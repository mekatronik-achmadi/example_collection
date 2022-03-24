// npm install express
// npm install body-parser

const express = require("express");
const bodyParser = require("body-parser");

const router = express.Router();
const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

router.get('/', (req, res) => {
    res.send('Hello World!');
    console.log('Hello World!');
});

router.post('/coba', (req,res) => {
    console.log(req.body);
    var usernm = req.body.usernm;
    var passwd = req.body.passwd;
    console.log("User name = " + usernm + ", password is " + passwd);
    res.send('JSON received!');
});

app.use('/',router);

app.listen(port, () => {
    console.log(`server listen at port ${port} at 192.168.50.244`);
});
