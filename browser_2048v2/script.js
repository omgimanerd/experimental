var board = new Object();
board.board = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];
board.output = function () {
  var replace = "";
  for (var y = 0; y < 4; y++) {
    replace = replace.concat("<div class='row'>");
    for (var x = 0; x < 4; x++) {
      replace = replace.concat("<div class='cell'>");
      if (this.board[x][y] != 0) {
        if (this.board[x][y] >= 1024) {
          replace = replace.concat("<div class='tile4digit' id='"+x.toString()+y.toString()+"'>"+this.board[x][y].toString()+"</div>");
        }
        else {
          replace = replace.concat("<div class='tile' id='"+x.toString()+y.toString()+"'>"+this.board[x][y].toString()+"</div>");
        }
      }
      replace = replace.concat("</div>");
    }
    replace = replace.concat("</div>");
  }
  document.getElementById('grid').innerHTML = replace;
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
//Not implemented.
board.isClearLeft = function (x, y) {
  var i = x - 1;
  while (i > -1) {
    if (this.board[i][y] != 0) {
      window.alert(this.board[i][y].toString());
      break;
    }
    i--;
  }
}
//
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
board.clear = function () {
  this.board = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];
  this.generate();
  this.output();
}
board.up = function () {
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
      var translate = 110 * (i - 1);
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
board.down = function () {
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
board.left = function () {
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
board.right = function () {
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