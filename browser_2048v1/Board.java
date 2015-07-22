package game2048;


import java.util.Random;

public class Board {

  private int[][] board = new int[4][4];
  private int[][] undo = new int[4][4];
  private Random random = new Random();

  public Board () {
    clearBoard();
    this.board[Math.abs(random.nextInt() % 4)][Math.abs(random.nextInt() % 4)] = 2;
    this.board[0][0] = 2;
    this.board[1][0] = 2;
    this.board[2][0] = 4;
    this.board[3][0] = 8;
    this.board[0][1] = 8;
    this.board[1][1] = 4;
    this.board[2][1] = 2;
    this.board[3][1] = 2;
  }

  private void clearBoard () {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        this.board[i][j] = 0;
      }
    }
  }

  private boolean isNotEmpty () {
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (this.board[x][y] == 0) {
          return true;
        }
      }
    }
    return false;
  }

  public boolean lost () {
    return true;
  }
  
  public void generate () {
    int x = Math.abs(random.nextInt() % 4);
    int y = Math.abs(random.nextInt() % 4);
    while (this.board[x][y] != 0 && isNotEmpty()) {
      x = Math.abs(random.nextInt() % 4);
      y = Math.abs(random.nextInt() % 4);
    }
    if (isNotEmpty()) {
      if (Math.abs(random.nextInt() % 10) < 3) {
        this.board[x][y] = 4;
      } else {
        this.board[x][y] = 2;
      }
    }
  }
  
  public void record () {
    this.undo = this.board;
  }
  
  public void undo () {
    this.board[0][0] = 2;
    this.board[1][0] = 2;
    this.board[2][0] = 4;
    this.board[3][0] = 8;
    this.board[0][1] = 8;
    this.board[1][1] = 4;
    this.board[2][1] = 2;
    this.board[3][1] = 2;
  }
  
  public String output (int x, int y) {
    if (this.board[x][y] == 0) {
      return "";
    } else {
      return Integer.toString(this.board[x][y]);
    }
  }

  public void up () {
    for (int x = 0; x < 4; x++) {
      int skip = -1;
      for (int y = 1; y < 4; y++) {
        if (y <= skip) {
          if (y == skip) {
            skip = -1;
          }
          continue;
        }
        int i = 1;
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
    for (int x = 0; x < 4; x++) {
      for (int y = 1; y < 4; y++) {
        int i = 1;
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
  }

  public void down () {
    for (int x = 0; x < 4; x++) {
      int skip = 4;
      for (int y = 2; y > -1; y--) {
        if (y >= skip) {
          if (y == skip) {
            skip = 4;
          }
          continue;
        }
        int i = 1;
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
    for (int x = 0; x < 4; x++) {
      for (int y = 2; y > -1; y--) {
        int i = 1;
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
  }

  public void left () {
    for (int y = 0; y < 4; y++) {
      int skip = -1;
      for (int x = 1; x < 4; x++) {
        if (x <= skip) {
          if (x == skip) {
            skip = -1;
          }
          continue;
        }
        int i = 1;
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
    for (int y = 0; y < 4; y++) {
      for (int x = 1; x < 4; x++) {
        int i = 1;
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
  }

  public void right () {
    for (int y = 0; y < 4; y++) {
      int skip = 4;
      for (int x = 2; x > -1; x--) {
        if (x >= skip) {
          if (x == skip) {
            skip = 4;
          }
          continue;
        }
        int i = 1;
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
    for (int y = 0; y < 4; y++) {
      for (int x = 2; x > -1; x--) {
        int i = 1;
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
  }

  public int getBoard (int x, int y) {
    return this.board[x][y];
  }
}