void saveSettings()
{
    String path = "";

    try{
        path = "text_files/setting.txt";
        file = new File(path);
        file.delete();
        FileWriter fileWriter = new FileWriter(file);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
        bufferedWriter.write(language);
        bufferedWriter.write('\n');
        bufferedWriter.write(SFXVolume + "");
        bufferedWriter.write('\n');
        bufferedWriter.write(musicVolume + "");
        bufferedWriter.write('\n');
        bufferedWriter.write(width + "");
        bufferedWriter.write('\n');
        bufferedWriter.write(height + "");
        bufferedWriter.write('\n');
        bufferedWriter.write(camScrollingDisabled + "");
        bufferedWriter.write('\n');
        for (int i = 0 ; i < keys.length ; i++) {
            bufferedWriter.write(keys[i] + "");
            bufferedWriter.write('\n');
        }
        bufferedWriter.flush();
        bufferedWriter.close();
    } catch(FileNotFoundException e) {
        e.printStackTrace();
        errorMsg(e+"\n\nCouldn't save your options.", SFX[2], e);
    } catch(IOException e) {
        e.printStackTrace();
        errorMsg(e+"\n\nCouldn't save your options.", SFX[2], e);
    }
}

//*****************************************Chargement des options**************************************************
void loadSettings()
{
    String path = "";

    try{
        path = "text_files/setting.txt";
        file = new File(path);
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;
        if((line = bufferedReader.readLine()) != null)
            language = line;
        if((line = bufferedReader.readLine()) != null)
            SFXVolume = int(line);
        if((line = bufferedReader.readLine()) != null)
            musicVolume = int(line);
        surface.setSize(int(bufferedReader.readLine()), int(bufferedReader.readLine()));
        camScrollingDisabled = compareStrings(bufferedReader.readLine(), "true");
        for (int i = 0 ; i < keys.length ; i++)
            keys[i] = int(bufferedReader.readLine());
        bufferedReader.close();
        fileReader.close();
        try {
            for (int i = 0 ; i < SFX.length ; i++)
                SFX[i].setGain(-50+50*SFXVolume/100);
        } catch(Exception e) {}
        try {
            for (int i = 0 ; i < Musics.length ; i++)
                Musics[i].setGain(-50 + 50 * musicVolume / 100 + baseGain[i]);
        } catch(Exception e) {}
        if(musicVolume == 0)
              musicDisabled = true;
    } catch(FileNotFoundException e) {
        saveSettings();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Unexpected error occured while loading settings", SFX[1], e);
    }
}

//******************************************Chargement des noms d'objets***************************************************
void loadItemsNames(String language)
{
    String path = "";

    try{
        path = "text_files/items_" + language + ".txt";
        file = new File(path);
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line = bufferedReader.readLine();
        for (int i = 0 ; line != null ; i++) {
            
        }
        bufferedReader.close();
        fileReader.close();
    } catch(FileNotFoundException e) {
        if(language == "en") {
            errorMsg("[ERROR]: Couldn't load items' names", SFX[1], e);
        } else
            loadItemsNames("en");
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Unexpected error occured while loading items names", SFX[1], e);
    }
}