void saveSettings()
{
    String path = "";

    try{
        path = "save";
        file = new File(path);
        file.mkdirs();
        path += "/setting.txt";
        file = new File(path);
        file.delete();
        FileWriter fileWriter = new FileWriter(file);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
        bufferedWriter.write(compareStrings(language, "yolo") ? "en" : language);
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
        path = "save/setting.txt";
        file = new File(path);
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;
        if((line = bufferedReader.readLine()) != null)
            language = line;
        if((line = bufferedReader.readLine()) != null)
            SFXVolume = compareStrings(language, "yolo") ? 500 : int(line);
        if((line = bufferedReader.readLine()) != null)
            musicVolume = compareStrings(language, "yolo") ? 500 : int(line);
        surface.setSize(int(bufferedReader.readLine()), int(bufferedReader.readLine()));
        camScrollingDisabled = compareStrings(bufferedReader.readLine(), "true");
        for (int i = 0 ; i < keys.length ; i++)
            keys[i] = int(bufferedReader.readLine());
        bufferedReader.close();
        fileReader.close();
        for (int i = 0 ; i < SFX.length ; i++)
            if (SFX[i] != null)
                SFX[i].setGain(-50 + 50 * SFXVolume / 100);
        for (int i = 0 ; i < Musics.length ; i++)
            if (Musics[i] != null)
                Musics[i].setGain(-50 + 50 * musicVolume / 100 + baseGain[i]);
        if(musicVolume == 0)
              musicDisabled = true;
    } catch(FileNotFoundException e) {
        saveSettings();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Unexpected error occured while loading settings", SFX[1], e);
    }
}