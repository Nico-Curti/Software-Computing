#!/usr/bin/env node

// get/post requests
import express from 'express'
// necessary for request body parsing
import bodyParser from 'body-parser'
// import query functions
import {
  checkAccount
} from './database.js'

// declare the application
const app = express();
// set the parser for the body post request
app.use(bodyParser.json());

// initial page => https://localhost:8080
app.get('/', async (req, res) => {
  res.status(200).send('Test server is running');
});

// info and port setting
app.listen(8080, () => {
  console.log('Server is running on PORT 8080');
})

// check authentication
app.post('/auth', async (req, res) => {
  // extract the user, pwd from the post request
  const { email, password } = req.body;
  // query the db in the user table
  let account = await checkAccount(email, password);
  // if it is valid
  if (account) {
    res.status(200).send('Login Success\n');
  } else {
    res.status(201).send('Login Failed\n');
  }
});
