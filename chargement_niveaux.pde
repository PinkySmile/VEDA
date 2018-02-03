//*****************************************Chargement d'un niveau*********************************************
boolean loadLevel(String levelName, int floorNbr)
{
    String path = "";
    boolean temp = false;

    try{
        objects = new int[maxNbOfObjectsPerLevel];
        posObjectX = new int[maxNbOfObjectsPerLevel];
        posObjectY = new int[maxNbOfObjectsPerLevel];
        levelPath = "data/levels/" + levelName;
        path = levelPath + "/level/floor" + floorNbr + ".lvl";
        BufferedReader bufferedReader = createReader(path);
        String line;
        int a = 0;
        background = bufferedReader.readLine();
        blue_sky = loadImage(background);
        while((line = bufferedReader.readLine()) != null && !compareStrings(line, "{guards}") && !compareStrings(line, "")) {
            objects[a] = int(line);
            posObjectX[a] = int(bufferedReader.readLine());
            posObjectY[a] = int(bufferedReader.readLine());
            isGlitched[a] = (int(random(0, 2)) == 1);
            println("Created object " + a + " at pos "+ posObjectX[a] + ", " + posObjectY[a] + " with ID " + objects[a]);
            a++;
        }
        if(compareStrings(line,"{guards}") || compareStrings(line,"{cams}"))
            new Popup("This level has been created for QGel or with QGel. It might not work as expected.\nConsider loading this level using QGel","Warning !",JOptionPane.INFORMATION_MESSAGE,SFX[2]);
        nbOfObjects = a;
        bufferedReader.close();
        temp = true;
    } catch(FileNotFoundException e) {
        e.printStackTrace();
        errorMsg("The file "+'"'+Paths.get(path).toAbsolutePath()+'"'+" is missing.",SFX[2],e);
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error 19",SFX[2],e);
    }
    println(Paths.get(path).toAbsolutePath());
    characters = new boolean[maxNbOfCharacters];
    loadCharacters(levelPath);
    loadCharactersState();
    loadDialogs(levelPath + "/dialogs/" + language + ".txt");
    return temp;
}

//*****************************************Chargement d'un niveau via le chemin d'accès*********************************************
boolean loadLevelPath(String theLevelPath, int floorNbr)
{
    boolean temp = false;
    String path = "";

    if(compareStrings(theLevelPath, "debugLevel")) {
        temp = true;
        objects = new int[maxNbOfObjectsPerLevel];
        posObjectX = new int[maxNbOfObjectsPerLevel];
        posObjectY = new int[maxNbOfObjectsPerLevel];
        characters = new boolean[maxNbOfCharacters];
        int x = 1;
        int y = 1;
        for(int sdqfqsf = 0 ; sdqfqsf < textures.length-2 ; sdqfqsf++) {
            objects[sdqfqsf] = sdqfqsf;
            posObjectX[sdqfqsf] = x;
            posObjectY[sdqfqsf] = y;
            x += 2;
            if(x * 16-16 >= width) {
                y += 2;
                x = 1;
            }
        }
    } else if(compareStrings(theLevelPath, "debugLevelX")) {
        temp = true;
        objects = new int[maxNbOfObjectsPerLevel];
        posObjectX = new int[maxNbOfObjectsPerLevel];
        posObjectY = new int[maxNbOfObjectsPerLevel];
        characters = new boolean[maxNbOfCharacters];
        int x = 1;
        int y = 1;
        for(int sdqfqsf = 0 ; sdqfqsf < textures.length-2 ; sdqfqsf++) {
            objects[sdqfqsf] = sdqfqsf;
            posObjectX[sdqfqsf] = x;
            posObjectY[sdqfqsf] = y;
            y += 2;
            if(y * 16-16 >= height) {
                x += 2;
                y = 1;
            }
        }
    } else if(compareStrings(theLevelPath, "debugLevelCompact")) {
        temp = true;
        objects = new int[maxNbOfObjectsPerLevel];
        posObjectX = new int[maxNbOfObjectsPerLevel];
        posObjectY = new int[maxNbOfObjectsPerLevel];
        characters = new boolean[maxNbOfCharacters];
        int x = 1;
        int y = 1;
        for(int sdqfqsf = 0 ; sdqfqsf < textures.length-2 ; sdqfqsf++) {
            objects[sdqfqsf] = sdqfqsf;
            posObjectX[sdqfqsf] = x;
            posObjectY[sdqfqsf] = y;
            x++;
            if(x * 16 - 16 >= width) {
                y++;
                x = 1;
            }
        }
    } else {
        try{
            objects = new int[maxNbOfObjectsPerLevel];
            posObjectX = new int[maxNbOfObjectsPerLevel];
            posObjectY = new int[maxNbOfObjectsPerLevel];
            levelPath = theLevelPath;
            path = theLevelPath + "/level/floor" + floorNbr + ".lvl";
            file = new File(theLevelPath + "/level/floor" + floorNbr + ".lvl");
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String line;
            int a = 0;
            background = bufferedReader.readLine();
            blue_sky = loadImage(background);
            while((line = bufferedReader.readLine()) != null && !compareStrings(line,"{guards}") && !compareStrings(line,"")) {
                objects[a] = int(line);
                posObjectX[a] = int(bufferedReader.readLine());
                posObjectY[a] = int(bufferedReader.readLine());
                a++;
            }
            if(compareStrings(line,"{guards}") || compareStrings(line,"{cams}"))
                new Popup("This level has been created for QGel or with QGel. It might not work as expected.\nConsider loading this level using QGel","Warning !",JOptionPane.INFORMATION_MESSAGE,SFX[2]);
            nbOfObjects = a;
            bufferedReader.close();
            fileReader.close();
            temp = true;
        } catch(FileNotFoundException e) {
            e.printStackTrace();
            errorMsg("The file "+'"'+Paths.get(path).toAbsolutePath()+'"'+" is missing.",SFX[2],e);
        } catch(Exception e) {
            e.printStackTrace();
            errorMsg("Error 19 ",SFX[2],e);
        }
        characters = new boolean[maxNbOfCharacters];
        loadCharacters(theLevelPath);
        loadDialogs(theLevelPath + "/dialogs/" + language + ".txt");
        loadCharactersState();
    }
    return temp;
}

void loadItems()
{
    String path = "data/items.txt";

    for (int i = 0; i < allItems.length; i++) {
        allItems[i] = new Item();
        allItems[i].id = i;
    }
    try{
        BufferedReader bufferedReader = createReader(path);
        String line;
        int a = 0;
        while((line = bufferedReader.readLine()) != null && !compareStrings(line, "")) {
            allItems[a].name = line;
            allItems[a].type = bufferedReader.readLine();
            for (int i = 0; i < 6; i++)
                allItems[a].damages[i] = int(bufferedReader.readLine());
            for (int i = 0; i < 6; i++)
                allItems[a].resistances[i] = int(bufferedReader.readLine());
            allItems[a].durability = int(bufferedReader.readLine());
            allItems[a].ability = int(bufferedReader.readLine());
            a++;
        }
        bufferedReader.close();
    } catch(FileNotFoundException e) {
        e.printStackTrace();
        errorMsg("The file "+'"'+Paths.get(path).toAbsolutePath()+'"'+" is missing.",SFX[2],e);
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error 19",SFX[2],e);
    }
}

int getNbOfFiles(String path)
{
    int nbOfFiles = 0;
    String[] dirs = null;
    File file = new File(path);

    dirs = file.list();
    for(int i = 0 ; i < dirs.length ; i++) {
        println(path + "/" + dirs[i]);
        File files = new File(path + "/" + dirs[i]);
        if(files.isFile())
            nbOfFiles++;
        if(files.isDirectory())
            nbOfFiles += getNbOfFiles(new File(path +  "/" + dirs[i]).getAbsolutePath());
    }
    return nbOfFiles;
}