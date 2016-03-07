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
  var unlistinterval = parseInt(Math.random() * 3 + 1);
  var listinterval = parseInt(Math.random() * 3 + 1);
  for (var lineindex = 0; lineindex < lines.length;){
    while (lineindex + unlistinterval > lines.length){ unlistinterval--; }
    for (var i = 0; i < unlistinterval; i++){
      body.appendParagraph(lines[lineindex + i].trim() + '. ');
    }
    lineindex += unlistinterval;
    while(lineindex + listinterval > lines.length) {listinterval--; }
    for (var i = 0; i < listinterval; i++){
      var piece = lines[lineindex + i].trim();
      if (piece.length != 0){
        body.appendListItem(piece + '. ').setGlyphType(DocumentApp.GlyphType.BULLET);
      }
    }
    
    lineindex += listinterval;
    unlistinterval = parseInt(Math.random() * 3 + 1);
    listinterval = parseInt(Math.random() * 3 + 1);
  }
//  DocumentApp.getUi().alert(lines);
}
