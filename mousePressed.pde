void mousePressed()
{
    try {
        if (menu == 12) {
            int xPos = 0;
            int yPos = 0;
            for (int k = 0; k < keys.length; k++) {
                if (mouseX > 115 + xPos * 192 && mouseX < 186 + xPos * 192 && mouseY > yPos * 32 + 5 && mouseY < yPos * 32 + 25)
                    changingKey = k;
                if (yPos * 32 > height - 128) {
                    yPos = -1;
                    xPos++;
                }
                yPos++;
            }
        }
        //Affichage des erreurs
        if (mouseX >= errorPos && mouseY >= height - 85) {
            int t = 0;
            if (fatalError)
                t = JOptionPane.ERROR_MESSAGE;
            else
                t = 2;
            JOptionPane.showMessageDialog(null, theErrorMessage, "Error", t);
        }
        //Musique
        if (menu == 5 && mouseX >= 100 && mouseX <= 300 && mouseY >= 23 && mouseY <= 43) {
            musicVolume = round(mouseX-100)/2;
            if (musicVolume <= 0)
                Musics[4].pause();
            else if (musicVolume > 0 && musicDisabled)
                Musics[4].loop();
            musicDisabled = musicVolume <= 0;
            pressedMusicBar = true;
        }
        //SFX
        if (menu == 5 && mouseX >= 100 && mouseX <= 300 && mouseY >= 73 && mouseY <= 93) {
            SFXVolume = round(mouseX-100)/2;
            int r = int(8+random(0,4));
            try {
                for (int i = 0 ; i < SFX.length ; i++)
                    SFX[i].setGain(-50+50*SFXVolume/100);
            } catch(Exception e) {}
            SFX[r].rewind();
            SFX[r].play();
            SFXDisabled = SFXVolume <= 0;
            pressedSFXBar = true;
        }
        for (int i = 0; i <= numberOfMenu-1; i = i+1) {
            if (mouseX <= menuPos[2*i]+menuSize[2*i] && mouseX >= menuPos[2*i] && mouseY <= menuPos[2*i+1]+menuSize[2*i+1] && mouseY >= menuPos[2*i+1] && !menuDisabled[i] && mouseButton == LEFT) {
                if (i == 0) { //boutton "play"
                    try {
                        disableMenus();
                        direction = "up";
                        status = "static";
                        textTyped = "";
                        oldCommands = "";
                        cursor = "";
                        statusBuffer = 0;
                        animation = 1;
                        playerX = 1;
                        playerY = 1;
                        animationBuffer = 0;
                        volume = 70;
                        life = 10*lifeMax;
                        lifeBuffer = 0;
                        camPosX = 0;
                        camPosY = 0;
                        menu = 0;
                        deathBuffer = 0;
                        cursorBuffer = 0;
                        if (!musicDisabled) {
                            Music.rewind();
                            Musics[0].rewind();
                            Musics[3].pause();
                            Musics[3].rewind();
                        }
                        if (compareStrings(language, "yolo")) {
                            if(!loadLevel("What have you done !", floor));
                                loadLevel("test", floor);
                            dialogBox("What have you done !");
                            inDialog = false;
                        }
                        menu = 0;
                        loadGame();
                        println(life+":"+lifeMax+":"+camPosX+":"+camPosY+":"+playerX+":"+playerY);
                        if (life > lifeMax*10) {
                            println(life > lifeMax*10);
                            background(0);
                            Music.pause();
                            menu = -11;
                            giveAchievement(2);
                        }
                    }
                    catch(Exception e) {
                        e.printStackTrace();
                        error("Error 12",e);
                    }
                } else if (i == 1 && !menuDisabled[i]) {  //boutton rapport de bugs
                  if (!compareStrings(language, "yolo")) {
                      try {
                          if(compareStrings(language,"fr"))
                              Desktop.getDesktop().browse(new URI("https://docs.google.com/forms/d/e/1FAIpQLScqeicBp8jvdGLMGwQ3AUdgrWt5SEqL7Fk4J9F3Hgnki0RRpw/viewform"));
                          if(compareStrings(language,"en"))
                              Desktop.getDesktop().browse(new URI("https://docs.google.com/forms/d/e/1FAIpQLSfEbzP2szdv4YDmLEpDhQEn6zw5hpMcb9GyY_zB-IMuG0pHIg/viewform"));
                          if(compareStrings(language,"de"))
                              Desktop.getDesktop().browse(new URI("https://docs.google.com/forms/d/e/1FAIpQLScOnaX9TvfYRspAAL0yIFZJCqAOOzKWBCOwaWXHSI6AWbw7Og/viewform"));
                      } 
                      catch(IOException e) {
                          e.printStackTrace();
                          errorMsg("", SFX[2],e);
                      } 
                      catch(URISyntaxException e) {
                          e.printStackTrace();
                          errorMsg("", SFX[2],e);
                      }
                  } else {
                      String tyuio = "";
                      if (godEaterActive) {
                          if (compareStrings(godEaterMode, "car-antenne"))
                              tyuio = "GodEater activated. Checking for corrupted files. Current default mode : Put In Quarantine";
                          else if (compareStrings(godEaterMode, "nosinegue"))
                              tyuio = "WARNING GodEater DISACTIVATED !!! Current default mode : Do Nothing";
                          else if (compareStrings(godEaterMode, "deal-êtes"))
                              tyuio = "GodEater activated. Checking for corrupted files. Current default mode : Delete Files";
                          else
                              tyuio = "GodEater activated. Checking for corrupted files. Current default mode : [ERROR]:NullPointerException";
                          new popUp(tyuio,"GodEater",JOptionPane.INFORMATION_MESSAGE,SFX[2]);
                      } else
                          errorMsg("Error in main chunk : No such process \"godEater\". Try restarting it and try again.", SFX[2],null);
                  }
                } else if (i == 2) {   //boutton "Settings"
                    if (!compareStrings(language, "yolo")) {
                        disableMenus();
                        enableMenus(5, 8);
                        enableMenus(13, 13);
                        menu = 3;
                    } else
                        errorMsg("Error at line 3849 : NullPointerException", SFX[1],null);
                } else if (i == 3) {   //boutton "Quit"
                    if (!compareStrings(language, "yolo")) {
                        file = new File("text_files/left");
                        if (file.exists())
                            file.delete();
                        System.exit(0);
                    } else {
                        errorMsg("Error at line 3849 : NullPointerException", SFX[1],null);
                    }
                } else if (i == 4) {   //boutton youtube
                    
                } else if (i == 5) {   //boutton "Options"
                    lastMenu = -1;
                    menu = 4;
                } else if (i == 6) {   //boutton "Audio"
                    lang = language;
                    musicBuffer = musicDisabled;
                    menu = 5;
                } else if (i == 7) {   //boutton "Retour"
                    menu = -1;
                } else if (i == 8) {   //boutton "Langue"
                    menu = 6;
                    lang = language;
                    musicBuffer = musicDisabled;
                } else if (i == 9) {   //boutton "fr"
                    language = "fr";
                    delMenus();
                    classicButtons();
                } else if (i == 10) {   //boutton "en"
                    language = "en";
                    delMenus();
                    classicButtons();
                } else if (i == 11) {   //boutton "annuler"
                    loadSettings();
                    changingKey = -1;
                    menu = -1;
                    delMenus();
                    classicButtons();
                } else if (i == 12) {   //boutton "save"
                    saveSettings();
                    changingKey = -1;
                    loadDialogs(levelPath + "/dialogs/" + language + ".txt");
                    loadAchievements();
                    menu = -1;
                } else if (i == 13) {   //boutton "Controles"
                    menu = 12;
                } else if (i == 14) {   //boutton "Music On/Off"
                    musicDisabled = !musicDisabled;
                    if (musicDisabled) {
                        musicVolume = 0;
                        SFXVolume = 0;
                        try {
                            for (int j = 0 ; i < SFX.length ; j++)
                                SFX[j].setGain(-50+50*SFXVolume/100);
                        } catch(Exception e) {}
                        try {
                            for (int j = 0 ; j < SFX.length ; j++)
                                Musics[j].setGain(-50+50*musicVolume/100);
                        } catch(Exception e) {}
                        Musics[4].pause();
                    } else {
                        musicVolume = 100;
                        SFXVolume = 100;
                        try {
                            for (int j = 0 ; i < SFX.length ; j++)
                                SFX[j].setGain(-50+50*SFXVolume/100);
                        } catch(Exception e) {}
                        try {
                            for (int j = 0 ; j < SFX.length ; j++)
                                Musics[j].setGain(-50+50*musicVolume/100);
                        } catch(Exception e) {}
                        Musics[4].loop();
                    }
                } else if (i == 16) {
                    menu = -1;
                    disableMenus();
                    enableMenus(0, 2);
                    saveLevel();
                    new saveEverything(true,false,false);
                    Music.pause();
                } else if (i == 17) {   //boutton "de"
                    language = "de";
                    delMenus();
                    classicButtons();
                } else if (i == 18) {   //boutton "Yes"
                    
                } else if (i == 19) {   //boutton "No"
                    
                } else if (i == 20) {   //boutton "Ajout d'un perso"
                    addingChar = true;
                } else if (i == 21) {   //boutton "Menu des objets"
                    menu = 8;
                } else if (i == 22) {   //boutton "Retour" dans le menu des objets
                    menu = 1000000;
                    menuPosition = 0;
                } else if (i == 23) {   //achievements
                    lastMenu = menu;
                    menu = 10;
                    achievementMenuPos = 0;
                } else if (i == 24) {   //boutton "Retour"
                    disableMenus();
                    menu = lastMenu;
                } else if (i == 25) {   //boutton Scrolling de la cam
                    camScrollingDisabled = !camScrollingDisabled;
                }
            }
        }
        if (menu == 7 && mouseButton == RIGHT && !savedMessageShown) {
            for (int i = 0; i < nbOfObjects; i++) {
                float temp = zoomLevel;
                float _temp = (1+temp/20);
                float tempx1 = mouseX;
                float tempx2 = camPosX;
                float tempy1 = mouseY;
                float tempy2 = camPosY;
                float calc1 = (tempx1/_temp/16.0+0.5-tempx2/16.0);
                float calc2 = (tempy1/_temp/16.0+0.5-tempy2/16.0);
                if (posObjectX[i] == round(calc1) && posObjectY[i] == round(calc2)) {
                    objects[i] = 0;
                }
            }
        } else if (menu == 7 && !savedMessageShown) {
            if (detectVoid() == -15) {
                slot = nbOfObjects;
                nbOfObjects++;
            } else
                slot = detectVoid();
            objects[slot] = selectedObject;
            float temp = zoomLevel;
            float _temp = (1+temp/20);
            float tempx1 = mouseX;
            float tempx2 = camPosX;
            float tempy1 = mouseY;
            float tempy2 = camPosY;
            float calc1 = (tempx1/_temp/16.0+0.5-tempx2/16.0);
            float calc2 = (tempy1/_temp/16.0+0.5-tempy2/16.0);
            posObjectX[slot] = round(calc1);
            posObjectY[slot] = round(calc2);
        }
        if(menu == 8) {
            if(mouseY <= height - 74) {
                selectedObject = floor(mouseX / 24) + floor(mouseY / 24) * floor((width - 8) / 24) + floor((width - 8) / 24) * floor((height - 50) / 24) * menuPosition + 1;
                if(selectedObject == 8) {
                    Music.pause();
                    Music = Musics[2];
                    music = "Mysterious";
                    Music.rewind();
                    Music.loop();
                }
                if(selectedObject == 9) {
                  Music.pause();
                    Music = Musics[1];
                    music = "Macabre";
                    Music.rewind();
                    Music.loop();
                }
                if(selectedObject == 10) {
                    Music.pause();
                    Music = Musics[5];
                    music = "EpicBattle";
                    Music.rewind();
                    Music.play();
                }
                if(selectedObject == 12) {
                    Music.pause();
                    Music = Musics[10];
                    music = "eugrt";
                    Music.rewind();
                    Music.play();
                }
            }
        }
        if(menu == 9) {
        }
        if(menu == 1000000)
            menu = 7;
    } 
    catch(Exception e) {
      e.printStackTrace();
      error("Error 20",e);
    }
}

void mouseDragged()
{
    try {
        if (menu == 5 && mouseX >= 100 && mouseX <= 300 && mouseY >= 23 && mouseY <= 43) {
            musicVolume = round(mouseX-100)/2;
            if (musicVolume <= 0)
                Musics[4].pause();
            else if (musicVolume > 0 && musicDisabled)
                Musics[4].loop();
            musicDisabled = musicVolume <= 0;
        }
        if (menu == 5 && mouseX >= 100 && mouseX <= 300 && mouseY >= 73 && mouseY <= 93) {
            SFXVolume = round(mouseX-100)/2;
            int r = int(8+random(0,4));
            try {
                for (int i = 0 ; i < SFX.length ; i++)
                    SFX[i].setGain(-50+50*SFXVolume/100);
            } catch(Exception e) {}
            SFX[r].rewind();
            SFX[r].play();
            SFXDisabled = SFXVolume == 0;
        }
        if (menu == 5 && mouseX <= 45 && mouseX >= 40 && mouseY >= 130 && mouseY <= 150) {
            musicVolume = 0;
            if(musicVolume == 0 && !musicDisabled)
                Musics[4].pause();
            musicDisabled = true;
        }
        if (menu == 5 && mouseX <= 245 && mouseX >= 240 && mouseY >= 130 && mouseY <= 150) {
            musicVolume = 100;
            if(musicVolume > 0 && musicDisabled)
                Musics[4].loop();
            musicDisabled = false;
        }
        if (menu == 7 && mouseButton == RIGHT && !savedMessageShown) {
            boolean flag = true;
            int i = nbOfObjects;
            boolean deleted = false;
            while(flag && upperLayerShown) {
                float temp = zoomLevel;
                float _temp = (1+temp/20);
                float tempx1 = mouseX;
                float tempx2 = camPosX;
                float tempy1 = mouseY;
                float tempy2 = camPosY;
                float calc1 = (tempx1/_temp/16.0+0.5-tempx2/16.0);
                float calc2 = (tempy1/_temp/16.0+0.5-tempy2/16.0);
                if (posObjectX[i] == round(calc1) && posObjectY[i] == round(calc2) && isOnUpperLayer(i)) {
                    objects[i] = 0;
                    if(!replaceMode) {
                        deleted = true;
                        flag = false;
                        println("deleted object on upper layer"+i);
                    }
                }
                if(i == 0)
                    flag = false;
                i--;
            }
            flag = true;
            i = nbOfObjects;
            println(deleted);
            while(flag && !deleted) {
                float temp = zoomLevel;
                float _temp = (1+temp/20);
                float tempx1 = mouseX;
                float tempx2 = camPosX;
                float tempy1 = mouseY;
                float tempy2 = camPosY;
                float calc1 = (tempx1/_temp/16.0+0.5-tempx2/16.0);
                float calc2 = (tempy1/_temp/16.0+0.5-tempy2/16.0);
                if (posObjectX[i] == round(calc1) && posObjectY[i] == round(calc2) && !isOnUpperLayer(i) && objects[i] != 0) {
                    objects[i] = 0;
                    if(!replaceMode) {
                        deleted = true;
                        flag = false;
                        println("deleted object on lower layer"+i);
                    }
                }
                if(i == 0)
                    flag = false;
                i--;
            }
        } else if (menu == 7 && !savedMessageShown) {
            println(nbOfObjects);
            if (detectVoid() == -15) {
                slot = nbOfObjects;
                nbOfObjects++;
            } else
                slot = detectVoid();
            objects[slot] = selectedObject;
            float temp = zoomLevel;
            float _temp = (1+temp/20);
            float tempx1 = mouseX;
            float tempx2 = camPosX;
            float tempy1 = mouseY;
            float tempy2 = camPosY;
            float calc1 = (tempx1/_temp/16.0+0.5-tempx2/16.0);
            float calc2 = (tempy1/_temp/16.0+0.5-tempy2/16.0);
            posObjectX[slot] = round(calc1);
            posObjectY[slot] = round(calc2);
            for (int i = 0; i < nbOfObjects; i++) {
                if (posObjectX[slot] == posObjectX[i] && posObjectY[slot] == posObjectY[i] && i != slot) {
                    if(replaceMode || objects[slot] == objects[i])
                        objects[i] = 0;
                }
            }
        }
    } 
    catch(Exception e) {
        e.printStackTrace();
        error("Error 21",e);
    }
}

void mouseWheel(MouseEvent event)
{
    float e = event.getCount();
    if(menu == 10) {
        if(e < 0 && achievementMenuPos < 0)
            achievementMenuPos = achievementMenuPos + 30;
        else if(e > 0 && -achievementMenuPos < 90*nbOfAchievementsLoaded-height)
            achievementMenuPos = achievementMenuPos - 30;
    } else if(menu == 7)
        zoomLevel -= e;
}