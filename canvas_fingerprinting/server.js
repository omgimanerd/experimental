/**
 * @fileoverview Canvas fingerprinting server
 * @author alvin@omgimanerd.tech (Alvin Lin)
 */

const PORT = 5000

const express = require('express')
const path = require('path')
const socket = require('socket.io')

const app = express()

app.get('/', (request, response) => {
  response.sendFile(path.join(__dirname, 'index.html'))
})

app.use(express.static('client'))

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`)
})
