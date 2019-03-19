/**
 * @fileoverview Canvas fingerprinting server
 * @author alvin@omgimanerd.tech (Alvin Lin)
 */

const PORT = 5000

const express = require('express')
const http = require('http')
const path = require('path')
const socket = require('socket.io')
const useragent = require('express-useragent')

const app = express()
const server = http.Server(app)
const io = socket(server)

app.use(express.static('client'))
app.use(express.static('node_modules'))
app.use(useragent.express());

app.get('/', (request, response) => {
  response.sendFile(path.join(__dirname, 'index.html'))
})

/* kv-pairs of hash to hits */
const uniqueUsers = {}

io.on('connection', socket => {
  socket.on('fingerprint', fingerprint => {
    uniqueUsers[fingerprint] = uniqueUsers[fingerprint] ?
      uniqueUsers[fingerprint] + 1 : 1

    io.sockets.emit('render', uniqueUsers)
  })
})

server.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`)
})
