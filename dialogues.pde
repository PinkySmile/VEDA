void execDialogCommand(String command, int _temp)
{
    if(command.startsWith("battle")) {
        battleType = int(subString(command, 6,command.length()-1));
        if(battleType >= 0 && battleType <= 5)
            goInBattle = true;
    } else if(command.startsWith("kill")) {
        if(compareStrings(subString(command, 4,command.length()-1),"c"))
            dialogDeathBuffer = -1;
        else if(compareStrings(subString(command, 4,command.length()-1),"ca")) {
            playerX = 10100;
            playerY = 10100;
        } else
            dialogDeathBuffer = int(subString(command, 4,command.length()-1));
    } else if(command.startsWith("clear")) {
        stickDialog = true;
        dialogEnd = false;
    } else if(command.startsWith("setLife")) {
        int a = int(subString(command, 7, command.length()));
        if (a > life)
            takeDamages(int(life - a), 7);
        else
            takeDamages(int(life - a), 0);
    } else if(command.startsWith("cutscene")) {
        inCutscene = true;
        commandID = cutsceneStart[int(subString(command, 8,command.length()-1))];
        inDialog = false;
        dialogText = null;
        dialogEnd = false;
    } else if(command.startsWith("answer")) {
        int _temp_ = 7;
        int __temp = 6;
        int ___temp = 0;
        for(int i = 0 ; i < answers.length ; i++) {
            if(__temp < command.length() && command.charAt(__temp) == '\'') {
                __temp++;
                _temp_ = __temp;
                while(command.charAt(__temp) != '\'')
                    __temp++;
                answers[i] = subString(command,_temp_,__temp-1);
                __temp++;
            }
        }
        _temp++;
        while(_temp < dialogText.length()-1 && dialogText.charAt(_temp) == '(') {
            println("Found beginning of an answer at " + _temp);
            int temp__ = _temp+1;
            int temp = 0;
            _temp++;
            while(_temp < dialogText.length()-1 && dialogText.charAt(_temp) != ')')
                _temp++;
            _temp++;
            temp = _temp;
            println("Found end of the answer ID at " + _temp+" : " + subString(dialogText,temp__,temp-2));
            println("Shearching the end");
            while(_temp < dialogText.length()-1 && dialogText.charAt(_temp) != '(')
                _temp++;
            if(_temp < dialogText.length() - 1)
                ___temp = _temp - 1;
            else
                ___temp = _temp;
            println("Found end of an answer at " + _temp);
            println("Answer "+int(subString(dialogText,temp__,temp-2))+" has "+temp+" as beginning and " + (_temp-1)+" as ending --> "+subString(dialogText,temp,___temp));
            cases[int(subString(dialogText, temp__, temp - 2))][0] = temp;
            cases[int(subString(dialogText, temp__, temp - 2))][1] = ___temp;
            dialogEnd = false;
        }
    }
}

void showDialogBox()
{
    if (dialogText != null) {
        dialogPrinted = "";
        try {
            image(xywt, 0, height-100);
        }
        catch(Exception e) {
            e.printStackTrace();
        }
        if (dialogLetters < dialogText.length()-1 && !dialogEnd && !stickDialog && dialogLetters < theDialogEnd) {
            dialogLetters++;
            if(dialogText.charAt(dialogLetters) == '§') {
                //selectedAnswer = 0;
                //answers = new String[4];
                //cases = new int[4][2];
                int _temp = dialogLetters + 1;
                String command = "";
                while(dialogText.charAt(_temp) != '§') {
                    command = command + dialogText.charAt(_temp);
                    _temp++;
                }
                println("Found command "+command);
                dialogLetters--;
                dialogEnd = true;
                execDialogCommand(command, _temp);
            }
        } else if(!stickDialog)
            dialogEnd = true;
        dialogPrinted = subString(dialogText,dialogStart,dialogLetters);
        textSize(15);
        if (compareStrings(language, "yolo"))
            textSize(random(1, 50));
        fill(255);
        boolean activated = false;
        text(dialogPrinted, 10, height-90, width-20, 80);
        for(int i = 0 ; i < answers.length ; i++)
            if(answers[i] != null) {
                text(answers[i], 30+i*width/4, height-30, width/4, 80);
                activated = true;
            }
        if(activated) {
            noStroke();
            fill(255);
            triangle(10 + selectedAnswer * width / 4, height - 20, 10 + selectedAnswer * width / 4, height- 30, 20 + selectedAnswer * width / 4, height - 25);
        }
    }
}

void loadDialogs(String path)
{
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
            return;
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

void loadItemNames(String language)
{
    String[] file_content = loadStrings("data/languages/" + language + "/items.txt");
    
    if (file_content == null)
        file_content = loadStrings("data/languages/en/items.txt");
    for (int i = 0; file_content != null && i < file_content.length && i < allItems.length; i++)
        allItems[i].name = file_content[i];
}

void dialogBox(String dialogue)
{
    String name = null;
    PImage xywt = loadImage("misc/dialog_box.png");
  
    answers = new String[4];
    dialogLetters = 0;
    dialogStart = 0;
    try {
        image(xywt, 0,height-100);
    } catch(Exception e) {
        e.printStackTrace();
    }
    inDialog = true;
    println(fightingCharacter);
    if (fightingCharacter >= 0 && fightingCharacter < characterName.length)
        name = characterName[fightingCharacter];
    dialogText = name + " : " + dialogue;
    theDialogEnd = dialogText.length();
}