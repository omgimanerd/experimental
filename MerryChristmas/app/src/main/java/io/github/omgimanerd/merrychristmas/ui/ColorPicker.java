package io.github.omgimanerd.merrychristmas.ui;

import android.graphics.Color;

import java.util.Random;

/**
 * Created by omgimanerd on 11/28/14.
 */
public class ColorPicker {

  private Random randomGenerator = new Random();
  private String colors[] = {
      "#39add1", // light blue
      "#3079ab", // dark blue
      "#c25975", // mauve
      "#e15258", // red
      "#f9845b", // orange
      "#838cc7", // lavender
      "#7d669e", // purple
      "#53bbb4", // aqua
      "#51b46d", // green
      "#e0ab18", // mustard
      "#637a91", // dark gray
      "#f092b0", // pink
      "#b7c0c7"  // light gray
  };
  private String lastSetColor_;

  public int getColor() {
    String newColor = colors[randomGenerator.nextInt(colors.length)];
    while (newColor.equals(lastSetColor_)) {
      newColor = colors[randomGenerator.nextInt(colors.length)];
    }
    lastSetColor_ = newColor;
    return Color.parseColor(newColor);
  }
}
