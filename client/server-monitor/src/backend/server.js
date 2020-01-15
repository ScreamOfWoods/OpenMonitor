const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const events = require('./events');
const sqlite3 = require('sqlite3').verbose();

const port = process.env.PORT || 8080;
const path = require('path');
const dbPath = path.resolve(__dirname, '../../../../list_serversDB.db');

let db = new sqlite3.Database(dbPath, sqlite3.OPEN_READWRITE, (err) => {
    if(err) {
        return console.error(err.message);
    }
    console.log("Connected to Database!");
});

const app = express()
    .use(cors())
    .use(bodyParser.json())
    .use(events(db));

app.listen(port, () => {
    console.log(`Express server listening on port ${port}`);
});

