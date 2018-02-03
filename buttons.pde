void enableMenus(int start , int end)
{
    for(int i = start ; i <= end ; i++)
        menuDisabled[i] = false;
}

void disableMenus()
{
    for(int i = 0 ; i < menuDisabled.length ; i++)
        menuDisabled[i] = true;
}

//*****************************************Création de bouttons*********************************************
void newMenu(int x, int y, String text, int couleur, int tailleX, int tailleY, boolean isDisabled)
{
    try {
        numberOfMenu++;
        menuDisabled[numberOfMenu - 1] = isDisabled;
        menuPos[2 * numberOfMenu - 2] = (x > 0 ? (x < width ? x : width) : 0);
        menuPos[2 * numberOfMenu - 1] = (y > 0 ? (y < height ? y : height) : 0);
        menuContent[numberOfMenu - 1] = text;
        menuColor[numberOfMenu - 1] = couleur;
        if (tailleX == 0)
            if (10 + text.length() * 18 < width)
                menuSize[2 * numberOfMenu - 2] = 10 + text.length() * 18;
            else
                menuSize[2 * numberOfMenu - 2] = width;
        else
            menuSize[2 * numberOfMenu - 2] = tailleX;
        if (tailleY == 0)
            menuSize[2 * numberOfMenu - 1] = 40;
        else
            menuSize[2 * numberOfMenu - 1] = tailleY;
    } catch(ArrayIndexOutOfBoundsException e) {
        errorMsg("", SFX[1], e);
    } catch(Exception e) {
        errorMsg("", SFX[1], e);
    }
}

//*****************************************Suppression des bouttons de menu*********************************************
void delMenus()
{
    menuPos = new int[200];
    menuColor = new int[100];
    menuSize = new int[200];
    menuContent = new String[100];
    menuDisabled = new boolean[100];
    numberOfMenu = 0;
}

void drawMenus()
{
    if(nbOfAchievementsLoaded > 0)
        try {
            achievementButtonImage = trophys[floor(3 * nbOfAchievementsGot / nbOfAchievementsLoaded)];
        } catch(Exception e) {
            achievementButtonImage = redCross;
        }
    else
        achievementButtonImage = trophys[0];
    if(menu == -1) {
        menuPos[46] = width - 25;
        menuPos[47] = 100;
    } else if (menu == 2) {
        menuDisabled[23] = true;
    } else if (menu >= 0 && menu <= 6) {
        tint(255, 150);
        menuPos[46] = width - 25;
        menuPos[47] = 20;
    }
    for (int i = 0; i < numberOfMenu; i++) {
        if (!menuDisabled[i]) {
            noStroke();
            int current_color = 0;
            int alph = 255;
            if (mouseX <= menuPos[2 * i] + menuSize[2 * i] && mouseX >= menuPos[2 * i] && mouseY <= menuPos[2 * i + 1] + menuSize[2 * i + 1] && mouseY >= menuPos[2 * i + 1]) {
                current_color = menuColor[i] - 100;
                if (i == 1 && compareStrings(language, "yolo"))
                    bug = godEater;
                else if (i == 1)
                    bug = bugRed;
                if (menu == 7) {
                    current_color = color(menuColor[i]);
                    alph = 10;
                }
            } else {
                if (i == 1)
                    bug = bugImage;
                if (menu == 0) {
                    current_color = color(menuColor[i]);
                    alph = 10;
                } else
                    current_color = menuColor[i];
            }
            tint(255, 255, 255, alph + 20);
            fill(current_color - 150, alph);
            rect(menuPos[2 * i], menuPos[2 * i + 1], menuSize[2 * i], menuSize[2 * i + 1]);
            fill(current_color-125, alph);
            rect(menuPos[2 * i] + 1, menuPos[2 * i + 1] + 1, menuSize[2 * i] - 2, menuSize[2 * i + 1] - 2);
            fill(current_color-100, alph);
            rect(menuPos[2 * i] + 2, menuPos[2 * i + 1] + 2, menuSize[2 * i] - 4, menuSize[2 * i + 1] - 4);
            fill(current_color-80, alph);
            rect(menuPos[2 * i] + 3, menuPos[2 * i + 1] + 3, menuSize[2 * i] - 6, menuSize[2 * i + 1] - 6);
            fill(current_color-60, alph);
            rect(menuPos[2 * i] + 4, menuPos[2 * i + 1] + 4, menuSize[2 * i] - 8, menuSize[2 * i + 1] - 8);
            fill(current_color-40, alph);
            rect(menuPos[2 * i] + 5, menuPos[2 * i + 1] + 5, menuSize[2 * i] - 10, menuSize[2 * i + 1] - 10);
            fill(current_color-25, alph);
            rect(menuPos[2 * i] + 6, menuPos[2 * i + 1] + 6, menuSize[2 * i] - 12, menuSize[2 * i + 1] - 12);
            fill(current_color-10, alph);
            rect(menuPos[2 * i] + 7, menuPos[2 * i + 1] + 7, menuSize[2 * i] - 14, menuSize[2 * i + 1] - 14);
            fill(current_color, alph);
            rect(menuPos[2 * i] + 8, menuPos[2 * i + 1] + 8, menuSize[2 * i] - 16, menuSize[2 * i + 1] - 16);
            fill(0);
            if (mouseX <= menuPos[2 * i] + menuSize[2 * i] && mouseX >= menuPos[2 * i] && mouseY <= menuPos[2 * i + 1] + menuSize[2 * i + 1] && mouseY >= menuPos[2 * i + 1] && i == 16)
                fill(0, 150);
            if (i == 1)
                try {
                    image(bug, menuPos[2 * i], menuPos[2 * i + 1]);
                }
                catch(Exception e) {
                    e.printStackTrace();
                    error("Error 10", e);
                }
            else if (i == 4) {
                try {
                    image(youtube, menuPos[2 * i] + 1, menuPos[2 * i + 1] + 1);
                }
                catch(Exception e) {
                    e.printStackTrace();
                    error("Error 11", e);
                }
            } else if(i == 23) {
                try {
                    image(achievementButtonImage, menuPos[2 * i], menuPos[2 * i + 1]);
                }
                catch(Exception e) {
                    try {
                      image(glitched_texture, menuPos[2 * i], menuPos[2 * i + 1]);
                    }
                    catch(Exception f) {
                      e.printStackTrace();
                      f.printStackTrace();
                      errorMsg("Error 10 " + f + " --> " + e, SFX[1], e);
                    }
                }
            }
            textSize(30);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            text(menuContent[i], menuPos[2 * i] + 4, menuPos[2 * i + 1] + menuSize[2 * i + 1] - 12);
            tint(255);
        }
    }
}

//Créations des bouttons
void classicButtons()
{
    delMenus();
    if(compareStrings(language,"yolo")) {
        color r = color(255, 0, 0);
        newMenu(10, 10,"What have yˆB„Àuô‰$µXûýÿ1Ûè²  £PA ü‰÷‰Ø¹   º   ó«‰T$‹µdxýÿ¹ou done !",r, 140, 40,true);
        newMenu(width-32,height-32,"ƒì…À„¾",r, 32, 32,true);
        newMenu(10, 60,"€>SàmŒJ¯—àôHò xÇÐû‡éÀu /H¸\\",r, 140, 40,true);
        newMenu(10, 110,"CÙiŒ©è¿—(EUå¥òÌPÄê€Ñ¼vƒu¬.™å'@àFÄ­˜?£. ®r!z+†ðœ    IEND®B`‚",r, 140, 40,true);
        newMenu(width-65,height-32,"",r, 33, 32,true);
        newMenu(160, 10,"",r, 140, 40,true);
        newMenu(160, 60,"",r, 140, 40,true);
        newMenu(160, 210,"",r, 140, 40,true);
        newMenu(160, 110,"",r, 140, 40,true);
        newMenu(width/2-70, 10,"",r, 140, 40,true);
        newMenu(width/2-70, 60,"",r, 140, 40,true);
        newMenu(width-150,height-50,"",r, 140, 40,true);
        newMenu(10,height-50,"",r, 100, 40,true);
        newMenu(160, 160,"",r, 140, 40,true);
        newMenu(100, 10,"", 255, 140, 40,true);
        newMenu(100, 60,"", 255, 140, 40,true);
        newMenu(width-180,height-40,"ˆB„Àuô‰$µXûýÿ1Ûè²  £PA ü‰÷‰Ø¹   º   ó«‰T$‹µdxýÿ¹", 255, 180, 40,true);
        newMenu(width/2-70, 110,"", 255, 140, 40,true);
        newMenu(width/2-100,height/2-40,"Yes", 255, 80, 80,true);
        newMenu(width/2 + 20,height/2-40,"No", 255, 80, 80,true);
        newMenu(0,height-40,"", 255, 80, 40,true);
        newMenu(0,height-80,"", 255, 80, 40,true);
        newMenu(width-150,height-50,"", 255, 140, 40,true);
        newMenu(width-24, 50,"", 255, 25, 25,true); //achievements
        newMenu(width-150,height-50,"", 255, 140, 40,true);
        newMenu(200, 10,"",color(25, 25, 255), 80, 40,true);                //25
        currentButton = 25;
        createLanguageButtons();
      
    } else {
        String[] buttonContent = loadStrings("data/languages/" + language + "/buttons.txt");
        String[] buttons = new String[50];
        
        currentButton = 0;
        if (buttonContent == null)
            buttonContent = loadStrings("data/languages/en/buttons.txt");
        if (buttonContent == null) {
            errorMsg("Error while loading language " + language, SFX[1], null);
            for (int i = 0; i < buttons.length; i++)
                buttons[i] = "Error while loading language " + language;
        } else {
            for (int i = 0; i < buttonContent.length; i++)
                buttons[i] = buttonContent[i];
            for (int i = buttonContent.length; i < buttons.length; i++)
                buttons[i] = "";
        }
        newMenu(10             , 10             , buttons[currentButton++], 255               , 0  , 0 , true);          //0          Play
        newMenu(width - 32     , height - 32    , buttons[currentButton++], 255               , 32 , 32, true);          //1          Bug report
        newMenu(10             , 60             , buttons[currentButton++], 255               , 0  , 0 , true);          //2          Settings
        newMenu(10             , 110            , buttons[currentButton++], 255               , 0  , 0 , true);          //3          Quit
        newMenu(width - 65     , height - 32    , buttons[currentButton++], 255               , 33 , 32, true);          //4          Youtube
        newMenu(250            , 10             , buttons[currentButton++], 255               , 0  , 0 , true);          //5          Options
        newMenu(250            , 60             , buttons[currentButton++], 255               , 0  , 0 , true);          //6          Audio
        newMenu(250            , 210            , buttons[currentButton++], 255               , 0  , 0 , true);          //7          Back (menu = -1)
        newMenu(250            , 110            , buttons[currentButton++], 255               , 0  , 0 , true);          //8          Language
        newMenu(-10            , -10            , buttons[currentButton++], 255               , -1 , -1, true);          //9          Unused
        newMenu(-10            , -10            , buttons[currentButton++], 255               , -1 , -1, true);          //10         Unused
        newMenu(width - 150    , height - 50    , buttons[currentButton++], 255               , 0  , 0 , true);          //11         Cancel
        newMenu(10             , height - 50    , buttons[currentButton++], 255               , 0  , 0 , true);          //12         Save
        newMenu(250            , 160            , buttons[currentButton++], 255               , 0  , 0 , true);          //13         Controls
        newMenu(100            , 10             , buttons[currentButton++], 255               , 40 , 40, true);          //14         Music ON/OFF
        newMenu(100            , 60             , buttons[currentButton++], 255               , 40 , 40, true);          //15         Unused
        newMenu(width - 180    , height - 40    , buttons[currentButton++], 255               , 0  , 0 , true);          //16         Save (in lvlCreator)
        newMenu(width / 2 - 70 , 100010         , buttons[currentButton++], 255               , 0  , 0 , true);          //17         Unused
        newMenu(width / 2 - 100, height / 2 - 40, buttons[currentButton++], 255               , 0  , 0 , true);          //18         Yes
        newMenu(width / 2 + 20 , height / 2 - 40, buttons[currentButton++], 255               , 0  , 0 , true);          //19         No
        newMenu(0              , height - 40    , buttons[currentButton++], 255               , 0  , 0 , true);          //20         Add character
        newMenu(0              , height - 80    , buttons[currentButton++], 255               , 0  , 0 , true);          //21         Objects menu
        newMenu(width - 150    , height - 50    , buttons[currentButton++], 255               , 0  , 0 , true);          //22         Back (in menu objects)
        newMenu(width - 24     , 50             , buttons[currentButton++], 255               , 25 , 25, true);          //23         Achievements
        newMenu(width - 150    , height - 50    , buttons[currentButton++], 255               , 0  , 0 , true);          //24         Back (menu = lastMenu)
        newMenu(180            , 10             , buttons[currentButton++], color(25, 25, 255), 100, 40, true);          //25         Disable cam scrolling
    }
}

String readFile(String path)
{
    String result = null;
    BufferedReader buffer = createReader(path);
    
    try {
        if (buffer == null)
            return (null);
        result = buffer.readLine();
        buffer.close();
        return (result);
    } catch (Exception e) {
        e.printStackTrace();
        return (null);
    }
}

void createLanguageButtons()
{
    String[] dirs = null;
    String name = "";
    File file = new File(sketchPath("data/languages"));

    languagesNb = 0;
    try {
        println("file", file);
        dirs = file.list();
        for (int i = 0 ; i < dirs.length ; i++) {
            println("Found " + dirs[i]);
            languagesNb++;
            languagesFound[i] = dirs[i];
            name = readFile(sketchPath("data/languages/" + dirs[i] + "/name.txt"));
            if (name == null)
                name = "Language \"" + dirs[i] + "\"";
            newMenu((width - (10 + name.length() * 18)) / 2, 10 + 50 * i, name, 255, 0, 0, true);
        }
    } catch (Exception e) {
        errorMsg("Couldn't fetch languages list ", SFX[1], e);
    }
}