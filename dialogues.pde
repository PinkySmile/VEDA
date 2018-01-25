void loadDialogs(String path) {
    int variation = 0;
    int caracter = 0;
    int dialog = 0;
    try{
        for(int i = 0 ; i < dialogs.length ; i++)
            for(int j = 0 ; j < dialogs[i].length ; j++)
                for(int k = 0 ; k < dialogs[i][j].length ; k++)
                    dialogs[i][j][k] = "";
        BufferedReader bufferedReader = createReader(path);
        if (bufferedReader == null)
            bufferedReader = createReader("data/dialogs_en");
        String line;
        while((line = bufferedReader.readLine()) != null) {
            if(line.charAt(0) == '{') {
                String a = "";
                for(int i = 1 ; i < line.length() -1 ; i++)
                    a = a + line.charAt(i);
                caracter = int(a);
                variation = 0;
            } else if(line.charAt(0) == '[') {
                String a = "";
                for(int i = 1 ; i < line.length() -1 ; i++)
                    a = a + line.charAt(i);
                dialog = int(a);
                variation = 0;
            } else if(line.charAt(0) == '"') {
                String a = "";
                for(int i = 1 ; i < line.length() -1 ; i++)
                    a = a + line.charAt(i);
                dialogs[caracter][dialog][variation] = a;
                variation++;
            }
        }
        bufferedReader.close();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error 18",SFX[1],e);
    }
}

void dialogBox(String dialogue) {
  answers = new String[4];
  PImage xywt = loadImage("misc/dialog_box.png");
  dialogLetters = 0;
  dialogStart = 0;
  try {
    image(xywt,0,height-100);
  } catch(Exception e) {
    e.printStackTrace();
  }
  inDialog = true;
  dialogText = dialogue;
  theDialogEnd = dialogText.length();
}