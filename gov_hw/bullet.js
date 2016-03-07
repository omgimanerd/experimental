function onOpen() {
  var ui = DocumentApp.getUi();
  // Or DocumentApp or FormApp.
  ui.createMenu('Kek')
      .addItem('Bulletme', 'addBullets')
      .addToUi();
}

function addBullets() {
  var body = DocumentApp.getActiveDocument().getBody();
  var lines = body.getText().split('.');
  body.clear();
  Logger.log(lines);
  var interval = parseInt(Math.random() * 3 + 1);
  for (var lineindex = 0; lineindex < lines.length;){
    var line = "";
    Logger.log(lines.length);
    while(lineindex + interval > lines.length) {interval--};
    for (var i = 0; i < interval; i++){
      var piece = lines[lineindex + i].trim();
      if (piece.length != 0){
        line += piece + '. ';
      }
    }
    Logger.log(interval + ' ' +  line);
    body.appendListItem(line).setGlyphType(DocumentApp.GlyphType.BULLET);
    lineindex += interval;
    interval = parseInt(Math.random() * 3 + 1);
  }
//  DocumentApp.getUi().alert(lines);
}
