package io.github.omgimanerd.merrychristmas.ui;

import android.text.Editable;
import android.view.View;

/**
 * Created by omgimanerd on 12/23/14.
 */
public class Message {

  private String outputText;
  private String correctInputText;
  private String hint;
  private boolean hideInputText;
  private String buttonText;

  public Message(String outputText_, String correctInputText_, String hint_,
                 boolean hideInputText_, String buttonText_) {
    outputText = outputText_;
    correctInputText = correctInputText_;
    hint = hint_;
    hideInputText = hideInputText_;
    buttonText = buttonText_;
  }

  public String getOutputText() {
    return outputText;
  }

  public String getCorrectInputText() {
    return correctInputText;
  }

  public String getHint() {
    return hint;
  }

  public boolean hideInputText() {
    return hideInputText;
  }

  public String getButtonText() {
    return buttonText;
  }
}
