void saveGame()
{
    String path = "";

    try {
        path = "";
        String dirName = "save";
        File dir = new File(dirName);
        dir.mkdirs();
        file = new File("save/file");
        println("saving game to " + file.getAbsolutePath());
        FileWriter fileWriter = new FileWriter(file);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
        bufferedWriter.write(name + "\n");
        bufferedWriter.write(lifeMax + "\n");
        bufferedWriter.write(life + "\n");
        bufferedWriter.write(energyMax + "\n");
        bufferedWriter.write(energy + "\n");
        bufferedWriter.write(playerX + "\n");
        bufferedWriter.write(playerY + "\n");
        bufferedWriter.write(camPosX + "\n");
        bufferedWriter.write(camPosY + "\n");
        bufferedWriter.write(progress + "\n");
        bufferedWriter.write(character + "\n");
        bufferedWriter.write(music + "\n");
        bufferedWriter.write(levelToLoad + "\n");
        bufferedWriter.write(items.length + "\n");
        for(int i = 0 ; i < items.length ; i++) {
            bufferedWriter.write((items[i] == null ? 0 : (items[i].id + 1)) + "\n");
            bufferedWriter.write((items[i] == null ? 0 : items[i].durability) + "\n");
            bufferedWriter.write(itemsQuantity[i] + "\n");
        }
        bufferedWriter.write(playTime+"\n");
        for (int i = 0; i < wornItems.length; i++) {
            bufferedWriter.write((wornItems[i] == null ? -1 : wornItems[i].id) + "\n");
            bufferedWriter.write((wornItems[i] == null ? -1 : wornItems[i].durability) + "\n");
        }
        bufferedWriter.flush();
        bufferedWriter.close();
        fileWriter.close();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error while saving game", SFX[1], e);
    }
}

void loadGame()
{
    try {
        file = new File("save/file");
        println("loading game from " + file.getAbsolutePath());
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        name = subString(bufferedReader.readLine(), 0, 12);
        lifeMax = int(bufferedReader.readLine());
        life = float(bufferedReader.readLine());
        energyMax = int(bufferedReader.readLine());
        energy = float(bufferedReader.readLine());
        playerX = float(bufferedReader.readLine());
        playerY = float(bufferedReader.readLine());
        camPosX = int(bufferedReader.readLine());
        camPosY = int(bufferedReader.readLine());
        progress = int(bufferedReader.readLine());
        character = bufferedReader.readLine();
        music = bufferedReader.readLine();
        levelToLoad = bufferedReader.readLine();
        items = new Item[int(bufferedReader.readLine())];
        itemsQuantity = new int[items.length];
        println("Inventory of size " + items.length);
        for(int i = 0 ; i < items.length ; i++) {
            int index = int(bufferedReader.readLine()) - 1;
            float durability = float(bufferedReader.readLine());
            if (index >= 0 && index < allItems.length) {
                items[i] = copyItemObject(allItems[index]);
                items[i].durability = durability;
            } else
                items[i] = null;
            itemsQuantity[i] = int(bufferedReader.readLine());
        }
        playTime = int(bufferedReader.readLine());
        for (int i = 0; i < wornItems.length; i++) {
            int index = int(bufferedReader.readLine());
            float durability = float(bufferedReader.readLine());
            if (index >= 0 && index < allItems.length) {
                wornItems[i] = copyItemObject(allItems[index]);
                wornItems[i].durability = (durability > allItems[wornItems[i].id].durability ? allItems[wornItems[i].id].durability : durability);
                for (int j = 0; j < wornItems[i].resistances.length; j++)
                    wornItems[i].resistances[j] *= durability/ allItems[wornItems[i].id].durability;
            } else
                wornItems[i] = null;
        }
        if((menu == 0 || menu == 1) && !musicDisabled) {
            if(compareStrings(music,"Mysterious") && !musicDisabled) {
                if (Music != null) {
                    Music.pause();
                    Music.rewind();
                }
                Music = Musics[2];
                if (Music != null)
                    Music.play();
            } else if(compareStrings(music,"Macabre") && !musicDisabled) {
                Music.pause();
                Music.rewind();
                Music = Musics[1];
                Music.play();
                if (Music != null) {
                    Music.pause();
                    Music.rewind();
                }
                Music = Musics[2];
                if (Music != null)
                    Music.play();
            } else if(compareStrings(music,"EpicBattle") && !musicDisabled) {
                if (Music != null) {
                    Music.pause();
                    Music.rewind();
                }
                Music = Musics[5];
                if (Music != null)
                    Music.play();
            } else if(compareStrings(music,"eugrt") && !musicDisabled) {
                if (Music != null) {
                    Music.pause();
                    Music.rewind();
                }
                Music = Musics[10];
                if (Music != null)
                    Music.play();
            } else if(!musicDisabled) {
                if (Music != null) {
                    Music.pause();
                    Music.rewind();
                }
                Music = (int(music) >= 0 && int(music) < Musics.length ? Musics[int(music)] : null);
                if (Music != null)
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
    if(compareStrings(character, "female"))
        character = "female";
    else
        character = "male";
    loadCharactersState();
}

void saveCharactersState()
{
    println("saving characters state to " + levelPath + "/save.chr");
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
    String path = "";

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