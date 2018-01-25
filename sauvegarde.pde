void saveGame()
{
    try {
        path = "";
        String dirName = "save";
        File dir = new File(dirName);
        dir.mkdirs();
        file = new File("save/file");
        println("saving game to " + file.getAbsolutePath());
        FileWriter fileWriter = new FileWriter(file);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
        bufferedWriter.write(name+"\n");
        bufferedWriter.write(lifeMax+"\n");
        bufferedWriter.write(life+"\n");
        bufferedWriter.write(energyMax+"\n");
        bufferedWriter.write(energy+"\n");
        bufferedWriter.write(playerX+"\n");
        bufferedWriter.write(playerY+"\n");
        bufferedWriter.write(camPosX+"\n");
        bufferedWriter.write(camPosY+"\n");
        bufferedWriter.write(progress+"\n");
        bufferedWriter.write(character+"\n");
        bufferedWriter.write(music+"\n");
        bufferedWriter.write(levelToLoad+"\n");
        bufferedWriter.write(items.length+"\n");
        for(int i = 0 ; i < items.length ; i++) {
            bufferedWriter.write(items[i]+"\n");
            bufferedWriter.write(itemsQuantity[i]+"\n");
        }
        bufferedWriter.write(playTime+"\n");
        bufferedWriter.flush();
        bufferedWriter.close();
        fileWriter.close();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error while saving game",SFX[1],e);
    }
}

void loadGame()
{
    try {
        file = new File("save/file");
        println("loading game from " + file.getAbsolutePath());
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        name = bufferedReader.readLine();
        lifeMax = int(bufferedReader.readLine());
        life = int(bufferedReader.readLine());
        energyMax = int(bufferedReader.readLine());
        energy = int(bufferedReader.readLine());
        playerX = int(bufferedReader.readLine());
        playerY = int(bufferedReader.readLine());
        camPosX = int(bufferedReader.readLine());
        camPosY = int(bufferedReader.readLine());
        progress = int(bufferedReader.readLine());
        character = bufferedReader.readLine();
        music = bufferedReader.readLine();
        levelToLoad = bufferedReader.readLine();
        items = new int[int(bufferedReader.readLine())];
        for(int i = 0 ; i < items.length ; i++) {
            items[i] = int(bufferedReader.readLine());
            itemsQuantity[i] = int(bufferedReader.readLine());
        }
        playTime = int(bufferedReader.readLine());
        if((menu == 0 || menu == 1) && !musicDisabled) {
            if(compareStrings(music,"Mysterious") && !musicDisabled) {
                Music.pause();
                Music.rewind();
                Music = Musics[2];
                Music.play();
            } else if(compareStrings(music,"Macabre") && !musicDisabled) {
                Music.pause();
                Music.rewind();
                Music = Musics[1];
                Music.play();
            } else if(compareStrings(music,"EpicBattle") && !musicDisabled) {
                Music.pause();
                Music.rewind();
                Music = Musics[5];
                Music.play();
            } else if(compareStrings(music,"eugrt") && !musicDisabled) {
                Music.pause();
                Music.rewind();
                Music = Musics[10];
                Music.play();
            } else if(!musicDisabled) {
                Music.pause();
                Music.rewind();
                Music = Musics[int(music)];
                Music.play();
            }
        }
        bufferedReader.close();
        fileReader.close();
    } catch(FileNotFoundException e) {
        e.printStackTrace();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error while loading game", SFX[1], e);
    }
    if(compareStrings(character,"female"))
        character = "female";
    else
        character = "male";
    loadCharactersState();
}

void saveCharactersState()
{
    println("saving characters state at " + levelPath + "/save.chr");
    try {
        output = createWriter(levelPath + "/save.chr");
        for(int i = 0 ; i < characters.length ; i++)
            if(characters[i]) {
                output.println(i);
                output.println(characterX[i]);
                output.println(characterY[i]);
                output.println(characterDir[i]);
                output.println(characterPointToGo[i][0]);
                output.println(characterPointToGo[i][1]);
                output.println(dialogsVariante[i]);
                output.println(theDialogID[i]);
            }
        output.flush();
        output.close();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Unhandled exception occured while saving",SFX[1],e);
    } 
}


void loadCharacters(String theLevelPath)
{
    String file_stream = "";

    try {
        levelPath = theLevelPath;
        path = theLevelPath + "/characters.chr";
        println("Loading characters (" + theLevelPath + "/characters.chr)");
        BufferedReader bufferedReader = createReader(path);
        String line;
        while((line = bufferedReader.readLine()) != null)
            file_stream += line;
        bufferedReader.close();
        parseFile(file_stream);
    } catch(FileNotFoundException e) {
        e.printStackTrace();
        errorMsg("The file "+'"'+Paths.get(path).toAbsolutePath()+'"'+" is missing.",SFX[2],e);
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error 19 ",SFX[2],e);
    }
}

void loadCharactersState()
{
    println("loading characters state (" + levelPath + "/save.chr)");
    try {
        BufferedReader bufferedReader = createReader(levelPath + "/save.chr");
        String line;
        int a = 0;
        while((line = bufferedReader.readLine()) != null && !compareStrings(line,"")) {
            a = int(line);
            characterX[a] = int(bufferedReader.readLine());
            characterY[a] = int(bufferedReader.readLine());
            characterDir[a] = int(bufferedReader.readLine());
            characterPointToGo[a][0] = int(bufferedReader.readLine());
            characterPointToGo[a][1] = int(bufferedReader.readLine());
            dialogsVariante[a] = int(bufferedReader.readLine());
            theDialogID[a] = int(bufferedReader.readLine());
        }
        bufferedReader.close();
    } catch(Exception e) {
      e.printStackTrace();
    }
}