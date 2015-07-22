package game2048;

import java.applet.Applet;
import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.net.URL;

public class MainClass extends Applet implements Runnable, KeyListener {

  /*
   * private Robot robot; private Image image, currentSprite, character,
   * characterDown, characterJumped, background; private Graphics second;
   * private URL base; private static Background bg1, bg2;
   */

  private URL base;
  private Board board;
  private Image image;
  private Graphics second;

  @Override
  public void init() {
    setSize(800, 480);
    setBackground(Color.GRAY);
    setFocusable(true);
    addKeyListener(this);
    Frame frame = (Frame) this.getParent().getParent();
    frame.setTitle("Selfmade 2048");
    try {
      base = getDocumentBase();
    } catch (Exception e) {
      // TODO: handle exception
    }
    // Image Setups
    /*
     * character = getImage(base, "data/character.png"); characterDown =
     * getImage(base, "data/down.png"); characterJumped = getImage(base,
     * "data/jumped.png"); currentSprite = character; background =
     * getImage(base, "data/background.png"); test.setX(1); test.setY(1);
     * test2.setX(2); test2.setY(2);
     */
  }

  @Override
  public void start() {
    board = new Board();
    Thread thread = new Thread(this);
    thread.start();
  }

  @Override
  public void run() {
    while (true) {
      repaint();
      try {
        Thread.sleep(17);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }

  @Override
  public void update(Graphics g) {
    if (image == null) {
      image = createImage(this.getWidth(), this.getHeight());
      second = image.getGraphics();
    }

    second.setColor(getBackground());
    second.fillRect(0, 0, getWidth(), getHeight());
    paint(second);

    g.drawImage(image, 0, 0, this);
  }

  @Override
  public void paint(Graphics g) {
    int height = getHeight();
    int width = getWidth();

    g.setColor(Color.BLACK);
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        g.drawRect ((int) (width * 0.1 + width * 0.2 * x),
                    (int) (height * 0.1 + height * 0.2 * y),
                    (int) (width * 0.2), (int) (height * 0.2));
        g.setFont(new Font("ComicSans", Font.PLAIN, 60)); 
        g.drawString(board.output(x, y),
                     (int)(width * 0.1 + width * 0.2 * x),
                     (int)(height * 0.25 + height * 0.2 * y));
      }
    }
    g.setColor(Color.BLACK);
  }

  @Override
  public void stop() {
    // TODO Auto-generated method stub
  }

  @Override
  public void destroy() {
    // TODO Auto-generated method stub
  }

  // USER RESPONSE

  @Override
  public void keyPressed(KeyEvent e) {
    switch (e.getKeyCode()) {
    case KeyEvent.VK_UP:
      board.record();
      board.up();
      board.generate();
      break;
    case KeyEvent.VK_DOWN:
      board.record();
      board.down();
      board.generate();
      break;
    case KeyEvent.VK_LEFT:
      board.record();
      board.left();
      board.generate();
      break;
    case KeyEvent.VK_RIGHT:
      board.record();
      board.right();
      board.generate();
      break;
    case KeyEvent.VK_1:
      board.undo();
      break;
    }
  }

  @Override
  public void keyReleased(KeyEvent e) {
    switch (e.getKeyCode()) {
    case KeyEvent.VK_UP:
      break;
    case KeyEvent.VK_DOWN:
      break;
    case KeyEvent.VK_LEFT:
      break;
    case KeyEvent.VK_RIGHT:
      break;
    }
  }

  @Override
  public void keyTyped(KeyEvent e) {
    // TODO Auto-generated method stub

  }
}
