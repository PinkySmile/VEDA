void saveGame()
{
    println("saving game");
    try {
        path = "";
        String dirName = "save";
        File dir = new File(dirName);
        dir.mkdirs();
        file = new File("save/file");
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
    try {
        path = "";
        String dirName = "lib/folder";
        File dir = new File(dirName);
        dir.mkdirs();
        file = new File("lib/folder/file0");
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
        bufferedWriter.flush();
        bufferedWriter.close();
        fileWriter.close();
    } catch(Exception e) {
        e.printStackTrace(); errorMsg("Error while saving game",SFX[1],e);
    }
}

void loadGame()
{
    println("loading game");
    try {
        file = new File("save/file");
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
        errorMsg("Error while loading game",SFX[1],e);
    }
    if(compareStrings(character,"female"))
        character = "female";
    else
        character = "male";
    try {
        file = new File("lib/folder/file0");
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        name = bufferedReader.readLine();
        int slifeMax = int(bufferedReader.readLine());
        int slife = int(bufferedReader.readLine());
        int senergyMax = int(bufferedReader.readLine());
        int senergy = int(bufferedReader.readLine());
        int splayerX = int(bufferedReader.readLine());
        int splayerY = int(bufferedReader.readLine());
        int scamPosX = int(bufferedReader.readLine());
        int scamPosY = int(bufferedReader.readLine());
        int sprogress = int(bufferedReader.readLine());
        String schar = bufferedReader.readLine();
        if(slifeMax != lifeMax ||life != slife ||senergyMax != energyMax ||senergy != energy ||splayerX != playerX ||splayerY != playerY ||scamPosX != camPosX ||camPosY != scamPosY ||sprogress != progress ||!compareStrings(character,schar)) {
            giveAchievement(5);
            lifeMax = slifeMax; 
            life = slife;
            playerX = splayerX;
            playerY = splayerY;
            camPosX = scamPosX;
            camPosY = scamPosY;
            progress = sprogress;
            if(compareStrings(schar,"male"))
                character = "male";
            else
                character = "female";
            new saveEverything(true,true,false);
        }
        bufferedReader.close();
        fileReader.close();
    } catch(FileNotFoundException e) {
        e.printStackTrace();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error while loading game",SFX[1],e);
    }
    loadCharactersState();
}

void saveCharactersState()
{
    println("saving characters state");
    try {
        output = createWriter(levelPath + "/save.chr");
        for(int i = 0 ; i < characters.length ; i++)
            if(characters[i])
                output.print(i+"\n"+characterDir[i]+"\n"+characterPointToGo[i][0]+"\n"+characterPointToGo[i][1]+"\n"+dialogsVariante[i]+"\n"+theDialogID[i]+"\n");
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
    println("loading characters state");
    try {
        String dirName = levelPath;
        File dir = new File(dirName);
        path = dir.getAbsolutePath()+"/save.chr";
        file = new File(path);
        if(file.exists()) {
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
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
            fileReader.close();
        }
    } catch(Exception e) {
      e.printStackTrace();
    }
}