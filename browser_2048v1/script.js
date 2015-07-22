var board = new Object();
board.board = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];
board.domBoard = document.getElementById('board');
board.output = function () {
  var  replace = "<table id='game-table'>";
  for (var x = 0; x < 4; x++) {
    replace = replace.concat("<tr>");
    for (var y = 0; y < 4; y++) {
      replace = replace.concat("<td>");
      if (this.board[x][y] != 0) {
        replace = replace.concat(this.board[x][y].toString());
      }
      replace = replace.concat("</td>");
    }
    replace = replace.concat("</tr>");
  }
  replace = replace.concat("</table>");
  document.getElementById('board').innerHTML = replace;
}
board.isNotEmpty = function () {
  for (var x = 0; x < 4; x++) {
    for (var y = 0; y < 4; y++) {
      if (this.board[x][y] == 0) {
        return true;
      }
    }
  }
  return false;
}
board.generate = function () {
  var x = Math.floor(Math.random() * 100) % 4;
  var y = Math.floor(Math.random() * 100) % 4;
  while (this.board[x][y] != 0 && this.isNotEmpty()) {
    x = Math.floor(Math.random() * 100) % 4;
    y = Math.floor(Math.random() * 100) % 4;
  }
  if (this.isNotEmpty()) {
    if (Math.floor(Math.random() * 10) < 3) {
      this.board[x][y] = 4;
    } else {
      this.board[x][y] = 2;
    }
  }
}
board.clearBoard = function () {
  this.board = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];
  this.generate();
  this.output();
}
board.left = function () {
  for (var x = 0; x < 4; x++) {
    var skip = -1;
    for (var y = 1; y < 4; y++) {
      if (y <= skip) {
        if (y == skip) {
          skip = -1;
        }
        continue;
      }
      var i = 1;
      while (y - i > -1 && this.board[x][y] != 0) {
        if (this.board[x][y - i] != 0 && this.board[x][y - i] != this.board[x][y]) {
          break;
        }
        if (this.board[x][y - i] == this.board[x][y]) {
          skip = y + 1;
          this.board[x][y - i] *= 2;
          this.board[x][y] = 0;
        }
        i++;
      }
    }
  }
  for (var x = 0; x < 4; x++) {
    for (var y = 1; y < 4; y++) {
      var i = 1;
      while (y - i > -1) {
        if (this.board[x][y - i] == 0) {
          this.board[x][y - i] = this.board[x][y - i + 1];
          this.board[x][y - i + 1] = 0;
        } else {
          break;
        }
        i++;
      }
    }
  }
  this.generate();
  this.output();
}
board.right = function () {
  for (var x = 0; x < 4; x++) {
    var skip = 4;
    for (var y = 2; y > -1; y--) {
      if (y >= skip) {
        if (y == skip) {
          skip = 4;
        }
        continue;
      }
      var i = 1;
      while (y + i < 4 && this.board[x][y] != 0) {
        if (this.board[x][y + i] != 0 && this.board[x][y + i] != this.board[x][y]) {
          break;
        }
        if (this.board[x][y + i] == this.board[x][y]) {
          skip = y - 1;
          this.board[x][y + i] *= 2;
          this.board[x][y] = 0;
        }
        i++;
      }
    }
  }
  for (var x = 0; x < 4; x++) {
    for (var y = 2; y > -1; y--) {
      var i = 1;
      while (y + i < 4) {
        if (this.board[x][y + i] == 0) {
          this.board[x][y + i] = this.board[x][y + i - 1];
          this.board[x][y + i - 1] = 0;
        } else {
          break;
        }
        i++;
      }
    }
  }
  this.generate();
  this.output();
}
board.up = function () {
  for (var y = 0; y < 4; y++) {
    var skip = -1;
    for (var x = 1; x < 4; x++) {
      if (x <= skip) {
        if (x == skip) {
          skip = -1;
        }
        continue;
      }
      var i = 1;
      while (x - i > -1 && this.board[x][y] != 0) {
        if (this.board[x - i][y] != 0 && this.board[x - i][y] != this.board[x][y]) {
          break;
        }
        if (this.board[x - i][y] == this.board[x][y]) {
          skip = x + 1;
          this.board[x - i][y] *= 2;
          this.board[x][y] = 0;
        }
        i++;
      }
    }
  }
  for (var y = 0; y < 4; y++) {
    for (var x = 1; x < 4; x++) {
      var i = 1;
      while (x - i > -1) {
        if (this.board[x - i][y] == 0) {
          this.board[x - i][y] = this.board[x - i + 1][y];
          this.board[x - i + 1][y] = 0;
        } else {
          break;
        }
        i++;
      }
    }
  }
  this.generate();
  this.output();
}
board.down = function () {
  for (var y = 0; y < 4; y++) {
    var skip = 4;
    for (var x = 2; x > -1; x--) {
      if (x >= skip) {
        if (x == skip) {
          skip = 4;
        }
        continue;
      }
      var i = 1;
      while (x + i < 4 && this.board[x][y] != 0) {
        if (this.board[x + i][y] != 0 && this.board[x + i][y] != this.board[x][y]) {
          break;
        }
        if (this.board[x + i][y] == this.board[x][y]) {
          skip = x - 1;
          this.board[x + i][y] *= 2;
          this.board[x][y] = 0;
        }
        i++;
      }
    }
  }
  for (var y = 0; y < 4; y++) {
    for (var x = 2; x > -1; x--) {
      var i = 1;
      while (x + i < 4) {
        if (this.board[x + i][y] == 0) {
          this.board[x + i][y] = this.board[x + i - 1][y];
          this.board[x + i - 1][y] = 0;
        } else {
          break;
        }
        i++;
      }
    }
  }
  this.generate();
  this.output();
}

document.onkeydown = checkKey;
function checkKey(e) {
    e = e || window.event;
  if (e.keyCode == '37') {
    board.left();
  }
    else if (e.keyCode == '38') {
        board.up();
    }
  else if (e.keyCode == '39') {
    board.right();
  }
    else if (e.keyCode == '40') {
        board.down();
    }
}