var express = require("express");
var app = express();
var port = 3000;

app.use(express.static('../frontend'));

app.listen(port, () => {
  console.log("Server listening on port " + port);
});
