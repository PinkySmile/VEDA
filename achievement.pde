void loadAchievements()
{
    nbOfAchievementsLoaded = 0;
    try {
        String lines[] = loadStrings("data/languages/" + language + "/achievements.txt");
        if (lines == null)
            lines = loadStrings("data/languages/en/achievements.txt");
        if (lines == null) {
            errorMsg("Couldn't find achievements data", SFX[1], null);
            return;
        }
        nbOfAchievementsLoaded = lines.length / 3;
        for(int i = 0 ; i <= nbOfAchievementsLoaded ; i++) {
            try {
                achievements[i] = lines[3 * i];
                achievementsContent[i] = lines[3 * i + 1];
                achievementImage[i] = loadImage(lines[3 * i + 2]);
            } catch(Exception f) {}
        }
    } catch(Exception e) {
        e.printStackTrace();
    }
}

void giveAchievement(int ID)
{
    if(!achievementsGot[ID] || ID == 2 || ID == 5) {
        achiev = ID;
        achievementBuffer = 0;
    }
    if(!achievementsGot[ID])
        nbOfAchievementsGot++;
    achievementsGot[ID] = true;
    saveAchievementsGot();
}

void loadAchievementsGot()
{
    String path;

    path = "save/achievement.txt";
    nbOfAchievementsGot = 0;
    try {
        file = new File(path);
        FileReader fileReader = new FileReader(file);
        String line;
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        for(int i = 0 ; i < achievementsGot.length ; i++) {
            line = bufferedReader.readLine();
            if(compareStrings(line,"true")) {
                achievementsGot[i] = true;
                nbOfAchievementsGot++;
            }
            else
                achievementsGot[i] = false;
        }
        bufferedReader.close();
        fileReader.close();
    } catch(FileNotFoundException e) {
        e.printStackTrace();
    } catch(Exception e) {
        e.printStackTrace();
    }
}

void saveAchievementsGot()
{
    String path;
    String dirName = "save";

    path = "save/achievement.txt";
    try {
        File dir = new File(dirName);
        dir.mkdirs();
        file = new File(path);
        file.delete();
        FileWriter fileWriter = new FileWriter(file);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
        for(int i = 0 ; i < achievementsGot.length ; i++)
            bufferedWriter.write(achievementsGot[i] + "\n");
        bufferedWriter.close();
        fileWriter.close();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Error while saving achievements",SFX[1],e);
    }
}