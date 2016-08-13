package io.github.omgimanerd.merrychristmas.ui;

import android.view.View;

/**
 * Created by omgimanerd on 12/23/14.
 */
public class Messages {

  private Message[] messages;

  public Messages() {
    messages = new Message[10];

    messages[0] = new Message("Merry Christmas, James. I think this is " +
        "something that's most representative of my abilities, " +
        "and I know you like having stuff that people make. So here you go.",
        "", "", true, "Continue");

    messages[1] = new Message("You're not getting a present that easily, " +
        "James. This one is supposed to be special, I think. There are a few " +
        "Easter eggs hidden in this phone. Find them all. Now let's get down " +
        "to business. Easy questions first. What is my favorite color?",
        "orange", "Hint: It's not blue", false, "Submit");

    messages[2] = new Message("Good, you either knew that or guessed it. " +
        "Either way works. Now who is my favorite Roman goddess?", "Juno",
        "Hint: It's not Diana", false, "Submit");

    messages[3] = new Message("Okay, that was an easy one. This one " +
        "should be more of a cockblock. What is my locker number?",
        "4-217", "It's on the fourth floor", false, "Submit");

    messages[4] = new Message("Nice job, this is when it gets hard. That's " +
        "what she said. What do we like to give each other?", "Hugs",
        "Hint: No, it's not blowjobs.", false, "Submit");

    messages[5] = new Message("Merry Christmas and Happy Birthday to come. " +
        "Since I'm getting sentimental anyways, I " +
        "really appreciate your friendship. You're one of the very few people" +
        " that I talk to and bother to acknowledge... Wait a minute... You " +
        "exist? What's my astrological sign?", "Gemini",
        "Hint: What month is my birthday?", false, "Submit");

    messages[6] = new Message("I like how philanthropic you are. I still " +
        "think you're a better person that I and worth much more than I am. " +
        "With that in mind, what is the name of the greatest programming " +
        "achievement I have made?", "Tap", "Hint: No hints here :)", false,
        "Submit");

    messages[7] = new Message("Nice, well now you know pretty much the sum of" +
        " myself. You're a great engineer and you'll be very successful in " +
        "life. Go start your own company. On that note, " +
        "who is the CEO of SchoolYourself, Inc?", "Zach Wissner-Gross",
        "Hint: Who works with John?", false, "Submit");

    messages[8] = new Message("I suck at this. This ended up being cheesy as " +
        "fuck, so decrypt 'uibol zpv' for me.", "thank you",
        "Hint: What cipher could this be?", false, "Submit");

    messages[9] = new Message("Oh well, thanks for being a friend. " +
        "You're an awesome person, James. There's " +
        "more where this came from. Keep the phone and get a SIM card for it " +
        "so you don't have to use your damn brick.", "", "", true,
        "Receive virtual hug.");
  }

  public Message getMessage(int index) {
    return messages[index];
  }

  public int getTotalMessages() {
    return messages.length;
  }
}
