/**
 * @fileoverview Canvas Fingerprinting Demo
 * @author alvin@omgimanerd.tech (Alvin Lin)
 */

const socket = io()

const TEXT = 'The quick brown fox jumped over the lazy dog'

const WIDTH = 600
const HEIGHT = 30

const elid = id => document.getElementById(id)
const el = name => document.createElement(name)

const getCanvasFingerprint = font => {
  const canvas = elid('canvas')
  canvas.width = WIDTH
  canvas.height = HEIGHT
  const context = canvas.getContext('2d')
  context.font = font
  context.textBaseline = 'top'
  context.fillText(TEXT, 0, 0)
  context.fillStyle = '#ABCDEF'
  context.fillText(TEXT, 60, 10)
  const data = context.getImageData(0, 0, WIDTH, HEIGHT).data
  return new Hashes.MD5().hex(String(data))
}

const renderTableDisplay = (selfFingerprint, fingerprints) => {
  const table = elid('display')
  while (table.firstChild) {
    table.removeChild(table.firstChild)
  }

  const addTableRow = (t1HTML, t2HTML, current) => {
    const trEl = el('tr')
    if (current) {
      trEl.className = 'current'
    }
    const t1El = el('td')
    t1El.innerHTML = t1HTML
    const t2El = el('td')
    t2El.innerHTML = t2HTML
    trEl.appendChild(t1El)
    trEl.appendChild(t2El)
    table.appendChild(trEl)
  }

  addTableRow('Fingerprint', 'Visits')
  for (const fingerprint in fingerprints) {
    addTableRow(fingerprint, fingerprints[fingerprint],
      selfFingerprint == fingerprint)
  }
}

window.addEventListener('load', () => {
  const hash = getCanvasFingerprint('12pt Arial')
  elid('fingerprint').innerHTML = `Canvas Fingerprint: ${hash}`
  socket.emit('fingerprint', hash)

  socket.on('render', fingerprints => {
    renderTableDisplay(hash, fingerprints)
  })
})
