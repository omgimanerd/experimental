package io.github.omgimanerd.merrychristmas;

import android.graphics.Color;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import io.github.omgimanerd.merrychristmas.ui.ColorPicker;
import io.github.omgimanerd.merrychristmas.ui.Message;
import io.github.omgimanerd.merrychristmas.ui.Messages;


public class MainActivity extends ActionBarActivity {

  private Messages messages = new Messages();
  private ColorPicker colorPicker = new ColorPicker();
  private int messageNumber = 0;
  private RelativeLayout layout;
  private TextView outputText;
  private EditText inputText;
  private Button inputButton;

  private void loadNextMessage(int message) {
    final Message current = messages.getMessage(messageNumber);
    layout.setBackgroundColor(colorPicker.getColor());
    outputText.setText(current.getOutputText());
    inputText.setText("");
    if (current.hideInputText()) {
      inputText.setVisibility(View.GONE);
    } else {
      inputText.setVisibility(View.VISIBLE);
    }
    inputButton.setText(current.getButtonText());

    if (messageNumber == messages.getTotalMessages() - 1) {
      inputButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
          messageNumber = 0;
          finish();
        }
      });
    } else {
      inputButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
          String userInput = inputText.getText().toString();
          if (userInput.equalsIgnoreCase(current.getCorrectInputText())) {
            messageNumber++;
            loadNextMessage(messageNumber);
          } else {
            Toast.makeText(getBaseContext(), "Nope. " + current.getHint(),
                Toast.LENGTH_LONG).show();
          }
        }
      });
    }
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_first);

    layout = (RelativeLayout) findViewById(R.id.layout);
    outputText = (TextView) findViewById(R.id.outputText);
    inputText = (EditText) findViewById(R.id.inputText);
    inputButton = (Button) findViewById(R.id.inputButton);

    loadNextMessage(messageNumber);
  }
}
