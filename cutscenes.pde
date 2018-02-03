void loadCutscenes(String path)
{
    try {
        file = new File(sketchPath(path));
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;
        int temp = 0;
        cutsceneStart[temp] = 0;
        for (int ID = 0 ; (line = bufferedReader.readLine()) != null ; ID++) {
            cutscenesCommands[ID] = line;
            if (compareStrings(line, "end")) {
                temp++;
                println("Cutscene "+ (temp - 1) + " ends at pos "+ID);
                cutsceneStart[temp] = ID + 1;
            }
        }
        bufferedReader.close();
        fileReader.close();
    } 
    catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error 18", SFX[1], e);
    }
}

boolean doCommand(String commandLine)
{
    boolean flag = false;
    try {
        if (waitingTime <= 0) {
            flag = true;
            String command = "";
            String args[] = new String[10];
            //commandLine = "test mdr lol \"n o\" test \"test\" \"fr tr\"";
            boolean quote = false;
            int argNumber = -1;
            int temp = 0;
            int posInString = 0;
            while (posInString < commandLine.length()) {
                if (commandLine.charAt(posInString) == '"' && posInString < commandLine.length()-1 && commandLine.charAt(posInString+1) == ' ')
                    quote = false;
                if (commandLine.charAt(posInString) == ' ' && !quote) {
                    if (argNumber == -1)
                        command = subString(commandLine, temp, posInString-1);
                    else {
                        args[argNumber] = subString(commandLine, temp, posInString-1);
                        if (args[argNumber].charAt(args[argNumber].length()-1) == '"')
                            args[argNumber] = subString(args[argNumber], 0, args[argNumber].length()-2);
                    }
                    temp = posInString+1;
                    if (commandLine.charAt(temp) == '"') {
                        quote = true;
                        temp++;
                    }
                    argNumber++;
                }
                posInString++;
            }
            if (quote && argNumber != -1)
                args[argNumber] = subString(commandLine, temp, posInString-2);
            else if (argNumber != -1)
                args[argNumber] = subString(commandLine, temp, posInString-1);
            else
                command = commandLine;
            print("Found command \""+command+"\" with args : ");
            for (int i = 0; i < args.length; i++) {
                print(args[i] + "");
                if (i != args.length - 1)
                    print(",");
                else
                    print("\n");
            }
            if (compareStrings(command, "save")) {
                saveGame();
                saveCharactersState();
            } else if (compareStrings(command, "setPlayerLife"))
                life = int(args[0]);
            else if (compareStrings(command, "setCharactersLife"))
                for (int argPos = 0; argPos*2 < args.length; argPos++)
                    characterLife[int(args[argPos])] = int(args[argPos+1]);
            else if (compareStrings(command, "healPlayer"))
                life += int(args[0]);
            else if (compareStrings(command, "healCharacters"))
                for (int argPos = 0; argPos*2 < args.length; argPos++)
                    characterLife[int(args[argPos])] = int(args[argPos+1]);
            else if (compareStrings(command, "deleteBlock")) {
                for (int argPos = 0; argPos*2 < args.length; argPos++)
                    for (int i = 0; i < nbOfObjects; i++)
                        if (posObjectX[i] == int(args[argPos]) && posObjectY[i] == int(args[argPos+1]))
                            objects[i] = 0;
                saveCommand(commandLine);
            } else if (compareStrings(command, "setBlock")) {
                for (int argPos = 0; argPos*3 < args.length; argPos += 3) {
                    if (detectVoid() == -15) {
                        slot = nbOfObjects;
                        nbOfObjects++;
                    } else
                        slot = detectVoid();
                    println(slot+":"+args[argPos + 2] + ":"+args[argPos] + ":"+args[argPos+1]);
                    objects[slot] = int(args[argPos + 2]);
                    posObjectX[slot] = int(args[argPos]);
                    posObjectY[slot] = int(args[argPos+1]);
                }
                saveCommand(commandLine);
            } else if (compareStrings(command, "timeOut"))
                waitingTime = int(args[0]);
            else if (compareStrings(command, "killPlayer"))
                life = 0;
            else if (compareStrings(command, "kill"))
                for (int argPos = 0; argPos < args.length; argPos++)
                    characterLife[argPos] = 0;
            else if (compareStrings(command, "changeCamPos")) {
                camPosX = int(args[0]);
                camPosY = int(args[1]);
            } else if (compareStrings(command, "teleportPlayer")) {
                playerX = int(args[0]);
                playerY = int(args[1]);
            } else if (compareStrings(command, "teleportCharacter")) {
                for (int argPos = 0; argPos*3 < args.length; argPos+= 3) {
                    characterX[int(args[argPos])] = int(args[argPos+1]);
                    characterY[int(args[argPos])] = int(args[argPos + 2]);
                }
            } else if (compareStrings(command, "movePlayer")) {
                playerX += int(args[0]);
                playerY += int(args[1]);
            } else if (compareStrings(command, "moveCharacter")) {
                for (int argPos = 0; argPos*3 < args.length; argPos+= 3) {
                    characterPointToGo[int(args[argPos])][0] = int(args[argPos+1]);
                    characterPointToGo[int(args[argPos])][1] = int(args[argPos + 2]);
                }
            } else if (compareStrings(command, "changePlayerSprite")) {
                character = args[0];
                status = args[1];
                direction = args[2];
                animation = int(args[3]);
            } else if (compareStrings(command, "changeCharacterSprite")) {
                for (int argPos = 0; argPos*4 < args.length; argPos+= 4) {
                    int newDir = 0;
                    int newStatus = 0;
                    int newAnim = 0;
                    if (args[argPos+1] == "moving")
                        newStatus = 1;
                    if (args[argPos + 2] == "down")
                        newDir = 2;
                    else if (args[argPos + 2] == "left")
                        newDir = 3;
                    else if (args[argPos + 2] == "right")
                        newDir = 4;
                    newAnim = int(argPos+3);
                    characterDir[int(args[argPos])] = newDir;
                    characterStatus[int(args[argPos])] = newStatus;
                    characterAnim[int(args[argPos])] = newAnim;
                }
            } else if (compareStrings(command, "playSound")) {
                if (compareStrings(args[0], "SFX")) {
                    SFX[int(args[1])].play();
                    SFX[int(args[1])].setGain(-50+50*SFXVolume/100);
                } else if (compareStrings(args[0], "Music")) {
                    Musics[int(args[1])].play();
                    Musics[int(args[1])].setGain(-50+50*SFXVolume/100);
                }
            } else if (compareStrings(command, "loopSound")) {
                if (compareStrings(args[0], "SFX")) {
                    SFX[int(args[1])].loop();
                    SFX[int(args[1])].setGain(-50+50*SFXVolume/100);
                } else if (compareStrings(args[0], "Music")) {
                    Music.pause();
                    Music = Musics[int(args[1])];
                    Music.loop();
                    music = args[1];
                }
            } else if (compareStrings(command, "stopSound")) {
                if (compareStrings(args[0], "SFX")) {
                    SFX[int(args[1])].pause();
                    SFX[int(args[1])].rewind();
                } else if (compareStrings(args[0], "Music")) {
                    Musics[int(args[1])].pause();
                    Musics[int(args[1])].rewind();
                } else if (compareStrings(args[0], "All")) {
                    for (int i = 0; i < Musics.length; i++) {
                        try {
                            Musics[i].pause();
                            Musics[i].rewind();
                        } 
                        catch(Exception e) {}
                    }
                    for (int i = 0; i < SFX.length; i++) {
                        try {
                            SFX[i].pause();
                            SFX[i].rewind();
                        } 
                        catch(Exception e) {}
                    }
                }
            } else if (compareStrings(command, "changeMenu"))
              menu = int(args[0]);
            else if (compareStrings(command, "showDialog"))
                dialogBox(dialogs[int(args[0])][int(args[1])][int(args[2])]);
            else if (compareStrings(command, "forceDialogID"))
                for (int argPos = 0; argPos*2 < args.length; argPos+= 2)
                    theDialogID[int(args[argPos])] = int(argPos+1);
            else if (compareStrings(command, "forceVariant"))
                for (int argPos = 0; argPos*2 < args.length; argPos+= 2)
                    dialogsVariante[int(args[argPos])] = int(argPos+1);
            else if (compareStrings(command, "showCutscene"))
                commandID = cutsceneStart[int(args[0])];
            else if (compareStrings(command, "loadImage")) {
                for (int argPos = 0; argPos*2 < args.length; argPos+= 2)
                    textures[int(args[argPos+1])] = loadImage(args[argPos]);
                saveCommand(commandLine);
            } else if (compareStrings(command, "loadSound")) {
                for (int argPos = 0; argPos*3 < args.length; argPos+= 3)
                    if (compareStrings(args[argPos], "SFX"))
                        SFX[int(args[argPos + 2])] = minim.loadFile(args[argPos]);
                    else if (compareStrings(args[argPos], "Music"))
                        Musics[int(args[argPos + 2])] = minim.loadFile(args[argPos]);
                saveCommand(commandLine);
            } else if (compareStrings(command, "end"))
                inCutscene = false;
        } else {
            waitingTime--;
        }
    } 
    catch(Exception e) {
      error("[FATAL]:Error while executing command \""+commandLine+"\" with ID "+commandID, e);
      e.printStackTrace();
      inCutscene = false;
    }
    return flag;
}

void saveCommand(String commandline) {
    String[] commandAlreadyWritten = new String[200];

    try {
        file = new File("save/file");
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        int i = 0;
        String line = bufferedReader.readLine();
        while (line != null) {
            commandAlreadyWritten[i] = line;
            line = bufferedReader.readLine();
            i++;
        }
        bufferedReader.close();
        fileReader.close();
    } 
    catch(FileNotFoundException e) {
        e.printStackTrace();
    } 
    catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error while loading game", SFX[1], e);
    }

    try {
        String dirName = "save";
        File dir = new File(dirName);
        dir.mkdirs();
        file = new File("save/file");
        FileWriter fileWriter = new FileWriter(file);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
        bufferedWriter.write(name+"\n");
        bufferedWriter.flush();
        bufferedWriter.close();
        fileWriter.close();
    } 
    catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error while saving game", SFX[1], e);
    }
}