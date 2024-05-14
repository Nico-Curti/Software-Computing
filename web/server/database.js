#!/usr/bin/env node

// connection with db
import mysql from 'mysql2'
// usage of env variables
import dotenv from 'dotenv'

// load the env variables from .env file
dotenv.config();

// connect to the MYSQL db with a pool of
// async connections
const db = mysql.createPool({
  host        : process.env.MYSQL_HOST,
  user        : process.env.MYSQL_USER,
  password    : process.env.MYSQL_PWD,
  port        : process.env.MYSQL_PORT,
  database    : process.env.MYSQL_DATABASE,
  dateStrings : 'date',
}).promise();

// check the correctness of the pair info
// provided in input
export async function checkAccount (email, pwd) {
  const [rows] = await db.query(`
    SELECT *
    FROM accounts
    WHERE
      email = ?
    AND
      password = ?
  `, [email, pwd]);
  return rows.length > 0 ? true : false;
}

if (false) {
  const results = await db.query(`
      SELECT *
      FROM accounts
    `);
  console.log(results);
  console.log(results[0]);

  const [value, table_info] = await db.query(`
      SELECT *
      FROM accounts
    `);
  console.log(value);

  console.log(value[0].email, value[0].password);

  const valid = await checkAccount('test@test.com', 'test')
  console.log(valid);

  const invalid = await checkAccount('test@test.com', 'hello')
  console.log(invalid);
}
