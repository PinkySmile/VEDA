void testKeys()
{
    for (int k = 0 ; k < pressedKeysCode.length ; k++) {
        if(camMoving && menu == 7) {
            int camGoToX = camBuffer[0]-width/2;
            int camGoToY = camBuffer[1] + height/2;
            if(camBuffer[0] < 0)
                camGoToX -= width;
            if(camBuffer[1] < 0)
                camGoToY -= height;
            camGoToX = -camGoToX + (camGoToX % width);
            camGoToY = -camGoToY + (camGoToY % height);
            camMove(true,camGoToX,camGoToY);
            camMoving = false;
        }
        if(!camMoving) {
            try {
                //Mouvement
                if (!dead && !inDialog && (menu == 0 || menu == 1)) {
                    stepSoundPriority = 0;
                    stepSound = SFX[0];
                    for(int i = 0 ; i < characters.length ; i++) {
                        if(characters[i]) {
                            if (playerY+34 >= characterY[i] + 16 && playerY+16 <= characterY[i] + 16 && playerX+3 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28)
                              down = false;
                            if (playerY+16 >= characterY[i] + 16 && playerY <= characterY[i] + 16 && playerX+3 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28)
                              up = false;
                            if (playerY+33 >= characterY[i] + 16 && playerY+1 <= characterY[i] + 16 && playerX + 2 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28)
                              left = false;
                            if (playerY+33 >= characterY[i] + 16 && playerY+1 <= characterY[i] + 16 && playerX <= characterX[i] + 16-18 && playerX >= characterX[i] + 16-30)
                              right = false;
                        }
                    }
                    for(int i = 0 ; i <= nbOfObjects ; i++) {
                        int flag = -1;
                        if(objects[i] != 0)
                            for(int j = 0 ; j < solidObjectsPlayer.length ; j++)
                                if(objects[i] == solidObjectsPlayer[j])
                                    flag = j;
                        if(flag != -1) {
                            if (hitboxType[flag] == 0) {
                                if (playerY+32 >= posObjectY[i] * 16-16 && playerY+playerHeight/2 <= posObjectY[i] * 16-16 && playerX+1 <= posObjectX[i] * 16-16 +16 && playerX+playerWidth-1 >= posObjectX[i] * 16-16)
                                    down = false;
                                if (playerY+16 >= posObjectY[i] * 16-16 && playerY+playerHeight/2-1 <= posObjectY[i] * 16 && playerX+1 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX+playerWidth-1)
                                    up = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX)
                                    left = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX+playerWidth <= posObjectX[i] * 16 && playerX+playerWidth >= posObjectX[i] * 16-16)
                                    right = false;
                            } else if (hitboxType[flag] == 1) {
                                if (playerY+32 >= posObjectY[i] * 16-16 && playerY+playerHeight/2 <= posObjectY[i] * 16-16 && playerX+1 <= posObjectX[i] * 16-16+16 && playerX+playerWidth-1 >= posObjectX[i] * 16-16)
                                    down = false;
                                if (playerY+16 >= posObjectY[i] * 16-16 && playerY+playerHeight/2-1 <= posObjectY[i] * 16 && playerX+1 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX+playerWidth-1)
                                    up = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX)
                                    left = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX+playerWidth <= posObjectX[i] * 16 && playerX+playerWidth >= posObjectX[i] * 16-16)
                                    right = false;
                            } else if (hitboxType[flag] == 2) {
                                if (playerY+32 >= posObjectY[i] * 16-16 && playerY+playerHeight/2 <= posObjectY[i] * 16-16 && playerX+1 <= posObjectX[i] * 16-16 +16 && playerX+playerWidth-1 >= posObjectX[i] * 16-16 + 8)
                                    down = false;
                                if (playerY+16 >= posObjectY[i] * 16-16 && playerY+playerHeight/2-1 <= posObjectY[i] * 16 - 8 && playerX+1 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 + 8 <= playerX+playerWidth-1)
                                    up = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 - 8 && playerX <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX)
                                    left = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 - 8 && playerX+playerWidth <= posObjectX[i] * 16 && playerX+playerWidth >= posObjectX[i] * 16-16+8)
                                    right = false;
                            } else if (hitboxType[flag] == 3) {
                                if (playerY+32 >= posObjectY[i] * 16-16 && playerY+playerHeight/2 <= posObjectY[i] * 16-16 && playerX+1 <= posObjectX[i] * 16-16 +16 && playerX+playerWidth-1 >= posObjectX[i] * 16-16)
                                    down = false;
                                if (playerY+16 >= posObjectY[i] * 16-16 && playerY+playerHeight/2-1 <= posObjectY[i] * 16 && playerX+1 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX+playerWidth-1)
                                    up = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX)
                                    left = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX+playerWidth <= posObjectX[i] * 16 && playerX+playerWidth >= posObjectX[i] * 16-16)
                                    right = false;
                            } else if (hitboxType[flag] == 4) {
                                if (playerY+32 >= posObjectY[i] * 16-16 && playerY+playerHeight/2 <= posObjectY[i] * 16-16 && playerX+1 <= posObjectX[i] * 16-16 +16 && playerX+playerWidth-1 >= posObjectX[i] * 16-16)
                                    down = false;
                                if (playerY+16 >= posObjectY[i] * 16-16 && playerY+playerHeight/2-1 <= posObjectY[i] * 16 && playerX+1 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX+playerWidth-1)
                                    up = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX)
                                    left = false;
                                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX+playerWidth <= posObjectX[i] * 16 && playerX+playerWidth >= posObjectX[i] * 16-16)
                                    right = false;
                            }
                        }
                        if(objects[i] == 2) {
                            if(playerY+47 >= posObjectY[i] * 16 && playerY < posObjectY[i] * 16-16 && playerX+3 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= playerX + 29 && stepSoundPriority <= 1) {
                                stepSound = SFX[4+int(random(0, 4))];
                                stepSoundPriority = 1;
                            }
                        }
                        if(objects[i] == 4) {
                            if(playerY+47 >= posObjectY[i] * 16 && playerY < posObjectY[i] * 16-16 && playerX+3 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= playerX + 29 && stepSoundPriority <= 2) {
                                stepSound = SFX[8+int(random(0, 4))];
                                stepSoundPriority = 2;
                            }
                        }
                        if(objects[i] == 5) {
                            if(playerY+47 >= posObjectY[i] * 16 && playerY < posObjectY[i] * 16-16 && playerX+3 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= playerX + 29 && stepSoundPriority <= 3) {
                                stepSound = SFX[12+int(random(0, 4))];
                                stepSoundPriority = 3;
                            }
                        }
                    }
                    if (menu == 0) {
                        if (!SFXDisabled)
                            stepSound.setGain(-50+50*SFXVolume/100);
                        if (pressedKeysCode[k] == keys[0] && !shiftPressed) {
                            direction = "up";
                            if (up) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                                playerY = playerY - 1;
                                statusBuffer = 0;
                                status = "moving";
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        } else if (pressedKeysCode[k] == keys[1] && !shiftPressed) {
                            direction = "down";
                            if (down) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                                playerY = playerY + 1;
                                status = "moving";
                                statusBuffer = 0;
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        } else if (pressedKeysCode[k] == keys[2] && !shiftPressed) {
                            direction = "left";
                            if (left) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                                statusBuffer = 0;
                                playerX = playerX - 1;
                                status = "moving";
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        } else if (pressedKeysCode[k] == keys[3] && !shiftPressed) {
                            direction = "right";
                            if (right) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                                statusBuffer = 0;
                                playerX = playerX + 1;
                                status = "moving";
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        } else if (pressedKeysCode[k] == keys[0]) {
                            direction = "up";
                            if (up) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                                if(energy > 0) {
                                    playerY = playerY - sprintSpeed;
                                    energy--;
                                    energyReloadBuffer = 0;
                                } else
                                    playerY = playerY - 1;
                                statusBuffer = 0;
                                status = "moving";
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        } else if (pressedKeysCode[k] == keys[1]) {
                            direction = "down";
                            if (down) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!musicDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                                if(energy > 0) {
                                    playerY = playerY + sprintSpeed;
                                    energy--;
                                    energyReloadBuffer = 0;
                                } else
                                    playerY = playerY + 1;
                                status = "moving";
                                statusBuffer = 0;
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        } else if (pressedKeysCode[k] == keys[2]) {
                            direction = "left";
                            if (left) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                                statusBuffer = 0;
                                if(energy > 0) {
                                    playerX = playerX - sprintSpeed;
                                    energy--;
                                    energyReloadBuffer = 0;
                                } else
                                    playerX = playerX - 1;
                                status = "moving";
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!musicDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        } else if (pressedKeysCode[k] == keys[3]) {
                            direction = "right";
                            if (right) {
                                if (animation == 1 && status == "static" && animationBuffer != 10) {
                                    if (!SFXDisabled) {
                                      stepSound.rewind();
                                      stepSound.play();
                                    }
                                }
                                statusBuffer = 0;
                                if(energy > 0) {
                                    playerX = playerX + sprintSpeed;
                                    energy--;
                                    energyReloadBuffer = 0;
                                } else
                                    playerX = playerX + 1;
                                status = "moving";
                                animationBuffer = animationBuffer + 1;
                                if (animationBuffer == 10) {
                                    animation = animation + 1;
                                    animationBuffer = 0;
                                    if (!SFXDisabled) {
                                        stepSound.rewind();
                                        stepSound.play();
                                    }
                                }
                            }
                        }
                    }
                    int inWall = -1;
                    for(int i = 0 ; i <= nbOfObjects ; i++) {
                        int flag = -1;
                        if(objects[i] != 0)
                            for(int j = 0 ; j < upperObjects.length ; j++)
                                if(objects[i] == solidObjectsPlayer[j])
                                    flag = j;
                        if (flag != -1)
                            if(hitboxType[flag] == 0 && playerY+32 > posObjectY[i] * 16-16 && playerY+17 < posObjectY[i] * 16 && playerX < posObjectX[i] * 16 && posObjectX[i] * 16-16 < playerX+16)
                                inWall = i;
                        if(objects[i] == 8) {
                            if(playerY+32 >= posObjectY[i] * 16-16 && playerY+16 <= posObjectY[i] * 16 && playerX+8 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 < playerX+8) {
                                if(music != "Mysterious" && !musicDisabled) {
                                    music = "Mysterious";
                                    addingChar = true;
                                    Music.pause();
                                    Music.rewind();
                                    Music = Musics[2];
                                    Music.play();
                                    addingChar = false;
                                }
                            }
                        }
                        if(objects[i] == 9) {
                            if(playerY+32 >= posObjectY[i] * 16-16 && playerY+16 <= posObjectY[i] * 16 && playerX+8 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 < playerX+8) {
                                if(music != "Macabre" && !musicDisabled) {
                                    music = "Macabre";
                                    addingChar = true;
                                    Music.pause();
                                    Music.rewind();
                                    Music = Musics[1];
                                    Music.play();
                                    addingChar = false;
                                }
                            }
                        }
                        if(objects[i] == 10) {
                            if(playerY+32 >= posObjectY[i] * 16-16 && playerY+16 <= posObjectY[i] * 16 && playerX+8 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 < playerX+8) {
                                if(music != "EpicBattle" && !musicDisabled) {
                                    println(music);
                                    music = "EpicBattle";
                                    addingChar = true;
                                    Music.pause();
                                    Music.rewind();
                                    Music = Musics[5];
                                    Music.play();
                                    addingChar = false;
                                }
                            }
                        }
                        if(objects[i] == 12) {
                            if(playerY + 32 >= posObjectY[i] * 16 - 16 && playerY + 16 <= posObjectY[i] * 16 && playerX+8 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 < playerX+8) {
                                if(music != "eugrt" && !musicDisabled) {
                                    music = "eugrt";
                                    addingChar = true;
                                    Music.pause();
                                    Music.rewind();
                                    Music = Musics[10];
                                    Music.play();
                                    addingChar = false;
                                }
                            }
                        }
                    }
                    if(inWall >= 0) {
                        if(direction == "down")
                            playerY = posObjectY[inWall] * 16-16-32;
                        if(direction == "up")
                            playerY = posObjectY[inWall] * 16-16;
                        if(direction == "left")
                            playerX = posObjectX[inWall] * 16;
                        if(direction == "right")
                            playerX = posObjectX[inWall] * 16-16-16;
                    }
                }
                //Skip le gameover après un certain temps
            } catch(Exception e) {
                e.printStackTrace();
                error("Error 16",e);
            }
        }
        key = 0;
    }
}


void keyPressed()
{
    try {
        if (deathBuffer >= 150 && menu == 0)
            if (!musicDisabled)
                Musics[0].pause();
        if (keyCode == CONTROL)
            controlPressed = true;
        if (menu == 12 && changingKey != -1) {
            if (keyCode == 0)
                keyCode = -1;
            keys[changingKey] = keyCode;
            changingKey = -1;
        }
        if (keyCode == keys[19])
            shiftPressed = true;
        boolean flag = false;
        for (int k = 0 ; k < pressedKeysCode.length ; k++)
            if (keyCode == pressedKeysCode[k])
                flag = true;
        if (!flag)
            pressedKeysCode[findSpace()] = keyCode;
        if(key == '²' && menu == 7) {
            camMoving = true;
            camBuffer[0] = -camPosX;
            camBuffer[1] = -camPosY;
        } else if(key == '&' && menu == 7) {
            savedMessageShown = true;
            savingBuffer = 0;
            saveLevel();
            new saveEverything(true, false, false);
            Music.pause();
        } else if(key == 'é' && menu == 7)
            menu = 8;
        else if(key == '"' && menu == 7)
            replaceMode = !replaceMode;
        else if(key == '\'' && menu == 7)
            buttonsDisabled = !buttonsDisabled;
        else if(key == '(' && menu == 7)
            upperLayerShown = !upperLayerShown;
        else if(key == '-' && menu == 7)
            zoomLevel = 0;
        else if(key == 'è' && menu == 7)
            gridShown = !gridShown;
        //Touches de debug
        if (debugMode && menu != 1) {
            if (key == ';' && menu == 7) {
                selectedObject = lireUnEntier("Id of an object : ", "ID");
            } else if (key == ',') {
                giveAchievement(0);
            } else if (key == '/') {
                playerX = lireUnEntier("Position X", "Changer la position du joueur");
                playerY = lireUnEntier("Position Y", "Changer la position du joueur");
            } else if (key == ':') {
                int xBuffer = camPosX;
                int yBuffer = camPosY;
                camPosX = lireUnEntier("CamX", "CamX");
                camPosY = lireUnEntier("CamY", "CamY");
                playerX = playerX - camPosX + xBuffer;
                playerY = playerY - camPosY + yBuffer;
            } else if (key == 'w') {
                takeDamages(1, 0);
                hitBuffer = 5;
            } else if (key == 't') {
                itemsQuantity = new int[12];
                items = new Item[12];
            } else if (key == 'u') {
                int toDel = lireUnEntier("Which object to delete ?", "Del object");
                items[toDel] = null;
                itemsQuantity[toDel] = 0;
                tidyInventory();
            } else if (key == '¤') {
                language = lireUnTexte("Language", "Language");
                delMenus();
                classicButtons();
            } else if (key == '@') {
                giveAchievement(lireUnEntier("Enter an achievement ID", "ID"));
            } else if (key == '€') {
                if (character == "male")
                    character = "female";
                else
                    character = "male";
            } else if (key == '!') {
                menu = lireUnEntier("Menu", "Menu");
                if(menu == -10) {
                    for (int i = 0; i < Musics.length; i++) {
                        try {
                            Musics[i].setLoopPoints(mdrdbar.position(),mdrdbar.position()+50);
                            Musics[i].loop();
                        } catch(Exception e) {
                            e.printStackTrace();
                        }
                    }
                    for (int i = 0; i < SFX.length; i++) {
                        try {
                            SFX[i].setLoopPoints(mdrdbar.position(),mdrdbar.position()+50);
                            SFX[i].loop();
                        } catch(Exception e) {
                            e.printStackTrace();
                        }
                    }
                }
            } else if (key == 'y') {
                int mdrsd = findInventoryEmptySpace();
                if (mdrsd >= items.length)
                    new Popup("L'inventaire est plein !", "Error", JOptionPane.QUESTION_MESSAGE, null);
                else {
                    items[mdrsd] = copyItemObject(allItems[lireUnEntier("Entrer un ID d'objet", "objet")]);
                    itemsQuantity[mdrsd] = lireUnEntier("Combien ?", "quantité");
                }
            } else if (key == 'b') {
                disableMenus();
                enableMenus(16, 16);
                menu = 7;
                levelPath = lireUnTexte("Entrez un nom de niveau", "Charger un niveau");
                if (levelPath != null) {
                    file = new File(levelPath);
                    if (!file.exists()) {
                        try {
                            FileWriter fileWriter = new FileWriter(file);
                            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
                            bufferedWriter.close();
                        } 
                        catch(IOException e) {
                            e.printStackTrace();
                        }
                    }
                    loadLevelPath(levelPath, floor);
                }
            } else if (key == '*') {
                nameColor++;
            } else if (key == '?') {
                debugMode = false;
            } else if (key == '$') {
                String temp = lireUnTexte("Enter an ID", "Enter an ID");
                dialogBox("uyzgfedipyqgdqoyzfgqizfguzquifgyqpizfguqizfgqizfgbqjzbdlqv zdlqzvdlqyvzdlqvzdlqvzdqzdlqvzdjqgvzdugqvzdqjzhdboquzvydbqidbgzouydquozduofv§answer'battle''clear''kill''other'§(0)DAH§battle" + temp + "§(1)1§clear§2(2);[§kill" + temp + "§(3)  §answer'setLife''cutscene'§(0)Life : §setLife" + temp + "§(1)Coming soon§cutscene" + temp + "§");
            } else if (key == 'W') {
                energy = energy - 1;
                energyReloadBuffer = 0;
            } else if (key == 'X') {
                energy = energy + 1;
            } else if (key == 'C') {
                energyMax = energyMax - 1;
            } else if (key == 'V') {
                energyMax = energyMax + 1;
            } else if (key == 'µ') {
                nameColor--;
            } else if (key == 'x') {
                takeDamages(-1, 7);
            } else if (key == 'r') {
                file = new File("save/left");
                if (file.exists())
                    file.delete();
                setup();
            } else if (key == 'p') {
                glitchMode = !glitchMode;
            } else if (key == 'k') {
                if (!compareStrings(language, "yolo")) {
                    mdrdbar = Musics[8];
                    try {
                        SFX[0].pause();
                        Musics[0].pause();
                        Musics[2].pause();
                        Musics[1].pause();
                        Musics[3].pause();
                        SFX[1].pause();
                        SFX[2].pause();
                    } 
                    catch(Exception e) {
                        e.printStackTrace();
                    }
                    try {
                        mdrdbar.play();
                    } catch(Exception e) {
                        e.printStackTrace();
                    }
                    String test[] = {"Something wrong !"};
                    cd = new ImageIcon("data/misc/{YES}.png");
                    JOptionPane.showOptionDialog(null, "", "What have you done !", JOptionPane.OK_OPTION, 3, cd, test, test[0]);
                    language = "yolo";
                    SFXVolume = 500;
                    musicVolume = 500;
                    for (int i = 0 ; i < SFX.length ; i++)
                        if (SFX[i] != null)
                            SFX[i].setGain(-50 + 50 * SFXVolume / 100);
                    for (int i = 0 ; i < Musics.length ; i++)
                        if (Musics[i] != null)
                            Musics[i].setGain(-50 + 50 * musicVolume / 100 + baseGain[i]);
                    nameColor = 0;
                    musicDisabled = true;
                    delMenus();
                    fightingCharacter = -1;
                    classicButtons();
                    dialogBox("What have you done !");
                    menuBackground = loadImage("misc/{4FTSZ-ZE67D8}.wav", "png");
                    inDialog = false;
                    cd = null;
                } else {
                    try {
                        textFont(FreeMono);
                    } catch(Exception e) {
                        e.printStackTrace();
                    }
                    language = "fr";
                    try {
                        mdrdbar.pause();
                    } catch(Exception e) {
                        e.printStackTrace();
                    }
                    delMenus();
                    classicButtons();
                    menuBackground = loadImage("misc/background.png");
                    inDialog = false;
                    dialogText = null;
                    if (musicLoaded)
                        musicDisabled = false;
                }
            } else if (key+'e' == 200)
                lifeMax = lifeMax - 1;
            else if (key+'e' == 219)
                lifeMax = lifeMax + 1;
            else if (key == 'm') {
                String levelPath = lireUnTexte("Entrez un nom de niveau", "Charger un niveau");
                if (levelPath != null)
                    loadLevelPath(levelPath, floor);
            }
        }
        if(!camMoving) {
            try {
                if(menu == 8 || menu == 9) {
                    if(keyCode == 37 && menuPosition > 0)
                        menuPosition--;
                    else if(keyCode == 39 && menuPosition < (textures.length) / (floor(mouseX / 24) + floor(mouseY / 24) * floor((width - 8) / 24) + floor((width - 8) / 24) * floor((height - 50) / 24)))
                        menuPosition++;
                }
                if(inDialog && !dead && (menu == 0 || menu == 1)) {
                    println(keyCode+":"+selectedAnswer+":"+answers[1] + ":"+answers[0]);
                    if(keyCode == 39 && selectedAnswer < 3 && answers[selectedAnswer+1] != null)
                        selectedAnswer++;
                    else if(keyCode == 37 && selectedAnswer > 0 && answers[selectedAnswer-1] != null)
                        selectedAnswer--;
                }
                if(keys[6] == keyCode && !dead && (menu == 0 || menu == 1))
                    if(!inDialog)
                        for(int i = 0 ; i < characters.length ; i++) {
                            if(characters[i]) {
                                if (playerY+32 >= characterY[i] + 16 && playerY+16 <= characterY[i] + 16 && playerX+3 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28) {
                                    down = false;
                                    fightingCharacter = i;
                                    if(direction == "down") {
                                        characterDir[i] = 0;
                                        dialogBox(dialogs[i][dialogID][dialogsVariante[i]]);
                                        if(dialogsVariante[i] < 14)
                                            dialogsVariante[i]++;
                                    }
                                }
                                if (playerY+16 >= characterY[i] + 16 && playerY <= characterY[i] + 16 && playerX+3 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28) {
                                    up = false;
                                    fightingCharacter = i;
                                    if(direction == "up") {
                                        characterDir[i] = 1;
                                        dialogBox(dialogs[i][dialogID][dialogsVariante[i]]);
                                        if(dialogsVariante[i] < 14)
                                            dialogsVariante[i]++;
                                    }
                                }
                                if (playerY+33 >= characterY[i] + 16 && playerY+1 <= characterY[i] + 16 && playerX + 2 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28) {
                                    left = false;
                                    fightingCharacter = i;
                                    if(direction == "left") {
                                        characterDir[i] = 3;
                                        dialogBox(dialogs[i][dialogID][dialogsVariante[i]]);
                                        if(dialogsVariante[i] < 14)
                                            dialogsVariante[i]++;
                                    }
                                }
                                if (playerY+33 >= characterY[i] + 16 && playerY+1 <= characterY[i] + 16 && playerX <= characterX[i] + 16-18 && playerX >= characterX[i] + 16-30){
                                    right = false;
                                    fightingCharacter = i;
                                    if(direction == "right") {
                                        characterDir[i] = 2;
                                        dialogBox(dialogs[i][dialogID][dialogsVariante[i]]);
                                        if(dialogsVariante[i] < 14)
                                            dialogsVariante[i]++;
                                    }
                                }
                            }
                        }
                    else {
                        if(dialogEnd) {
                            inDialog = false;
                            dialogText = null;
                            dialogEnd = false;
                            if(dialogDeathBuffer > -1) {
                                characterX[dialogDeathBuffer] = 10100;
                                characterY[dialogDeathBuffer] = 10100;
                                dialogDeathBuffer = -2;
                            } else if(dialogDeathBuffer == -1) {
                                life = 0;
                                dialogDeathBuffer = -2;
                            }
                            if(goInBattle) {
                                goInBattle = false;
                                menu = 11;
                            }
                        } else if(stickDialog) {
                            dialogStart = dialogLetters+8;
                            dialogLetters = dialogStart;
                            stickDialog = false;
                        } else if(answers[selectedAnswer] != null) {
                            dialogStart = cases[selectedAnswer][0];
                            dialogLetters = dialogStart;
                            theDialogEnd = cases[selectedAnswer][1];
                            println(dialogStart+" --> "+theDialogEnd+"    "+subString(dialogText,dialogStart,theDialogEnd));
                            answers = new String[4];
                            cases = new int[4][2];
                            selectedAnswer = 0;
                        } else {
                            while(dialogLetters < dialogText.length()-1 && !dialogEnd && !stickDialog) {
                                dialogLetters++;
                                if(dialogText.charAt(dialogLetters) == '§') {
                                    int _temp = dialogLetters + 1;
                                    String command = "";
                                    while(dialogText.charAt(_temp) != '§') {
                                        command = command + dialogText.charAt(_temp);
                                        _temp++;
                                    }
                                    dialogLetters--;
                                    dialogEnd = true;
                                    execDialogCommand(command, _temp);
                                    if (command.startsWith("answer"))
                                        break;
                                }
                            }
                        }
                    }
                if (keys[4] == keyCode) {
                    status = "static";
                    showItemDetails = false;
                    choosingInInventory = false;
                    if (menu == 2)
                        menu = 0;
                    else if (menu == 0)
                        menu = 2;
                }
                if (keys[5] == keyCode && menu == 0) {
                    menu = -1;
                    new saveEverything(true,true,false);
                    if (!musicDisabled) {
                        Music.pause();
                        Music.rewind();
                        Musics[0].pause();
                        Musics[0].rewind();
                    }
                    for(int i = 0 ; i < Musics.length ; i++) {
                        try {
                            Musics[i].pause();
                        } catch(Exception e) {}
                    }
                } else if (keys[5] == keyCode && menu == 7) {
                    menu = -1;
                    disableMenus();
                    enableMenus(0, 2);
                }
                if(keyCode == RIGHT && menu == 7) {
                    camPosX = camPosX - 16;
                } else if(keyCode == DOWN && menu == 7) {
                    camPosY = camPosY - 16;
                } else if(keyCode == UP && menu == 7) {
                    camPosY = camPosY + 16;
                } else if(keyCode == LEFT && menu == 7)
                    camPosX = camPosX + 16;
                //*************************************"Invite de commandes"**********************************************
                if (menu == 1 && !inShell && keyCode == LEFT)
                    selectedRespawn = true;
                if (menu == 1 && !inShell && keyCode == RIGHT)
                    selectedRespawn = false;
                if (menu == 1 && !inShell && key == '\n' && keyCode == '\n') {
                    if (selectedRespawn) {
                        direction = "up";
                        status = "static";
                        textTyped = "";
                        oldCommands = "";
                        cursor = "";
                        statusBuffer = 0;
                        animation = 1;
                        playerX = 0;
                        playerY = 0;
                        animationBuffer = 0;
                        volume = 70;
                        life = 10*lifeMax;
                        lifeBuffer = 0;
                        camPosX = 0;
                        camPosY = 0;
                        menu = 0;
                        deathBuffer = 0;
                        cursorBuffer = 0;
                        inShell = true;
                        for (int j = 0; j < commandLines.length; j++)
                            commandLines[j] = null;
                        if (!musicDisabled) {
                            Music.rewind();
                            Musics[0].rewind();
                            Musics[3].pause();
                            Musics[3].rewind();
                        }
                        menu = 0;
                    } else
                        menu = -1;
                }
                if (inShell)
                    if ((musicDisabled || Musics[3].position() >= 2300) && keyCode != 10 && keyCode != 8 && key < 60000)
                        if (!controlPressed && key >= ' ')
                            textTyped = textTyped + key;
                        else
                            textTyped = textTyped + char(str(key).toUpperCase().charAt(0) + 60000);
                    else if ((musicDisabled || Musics[3].position() >= 2300) && key == 8) {
                        textTyped = subString(textTyped, 0, textTyped.length() - 2);
                    } else if ((musicDisabled || Musics[3].position() >= 2300) && key == '\n') {
                       addLine(prompt + textTyped);
                       execShellCommand(textTyped);
                       textTyped = "";
                    }
            } catch(Exception e) {
                e.printStackTrace();
                error("Unexpected error occured",e);
            }
        }
        if (key == '' && menu == 1 && inShell && gameoverDisplayed)
            for (int j = 0; j < commandLines.length; j++)
                commandLines[j] = null;
        if (key == '' && menu == 1) {
            if (inShell) {
                addLine(prompt + textTyped + (gameoverDisplayed ? "" : "^C"));
                Musics[3].skip(Musics[3].length());
            } else
                addLine((selectedRespawn ? "> " : "  ") + "Respawn  " + (selectedRespawn ? "  " : "> ") + "Quit^C");
            inShell = true;
            textTyped = "";
            gameoverDisplayed = true;
        }
        if(keyCode == RIGHT && inventoryPage < items.length / 12 - 1) {
            inventoryPage--;
        } else if(keyCode == DOWN && menu == 2) {
            if (!showItemDetails && !choosingInInventory) {
                selectedSlotInventory++;
                if (selectedSlotInventory < 12 && items[selectedSlotInventory] == null)
                    selectedSlotInventory = 12;
                if (selectedSlotInventory > 17)
                    selectedSlotInventory = (items[0] == null ? 12 : 0);
            } else if (!showItemDetails) {
                selectedAnswerInventory++;
                if (selectedAnswerInventory > 3)
                    selectedAnswerInventory = 0;
            }
        } else if(keyCode == UP && menu == 2) {
            if (!showItemDetails && !choosingInInventory) {
                selectedSlotInventory--;
                while (selectedSlotInventory >= 0 && selectedSlotInventory < 12 && items[selectedSlotInventory] == null)
                    selectedSlotInventory--;
                if (selectedSlotInventory < 0)
                    selectedSlotInventory = 17;
            } else if (!showItemDetails) {
                selectedAnswerInventory--;
                if (selectedAnswerInventory < 0)
                    selectedAnswerInventory = 3;
            }
        } else if(keyCode == LEFT && menu == 2 && inventoryPage > 0)
            inventoryPage++;
        else if (keyCode == ENTER && menu == 2) {
            boolean bool = true;;
            if (showItemDetails)
                showItemDetails = bool = false;
            if (choosingInInventory) {
                if (selectedAnswerInventory == 0)
                    equip(selectedSlotInventory);
                else if (selectedAnswerInventory == 1) {
                    if ((selectedSlotInventory < 12 ? items[selectedSlotInventory] : wornItems[selectedSlotInventory - 12]) != null) {
                        showItemDetails = true;
                        selectedAnswerInventory = 0;
                        choosingInInventory = !choosingInInventory;
                    }
                } else if (selectedAnswerInventory == 2) {
                    if (selectedSlotInventory < 12) {
                        items[selectedSlotInventory] = null;
                        itemsQuantity[selectedSlotInventory] = 0;
                        tidyInventory();
                        while (selectedSlotInventory >= 0 && items[selectedSlotInventory] == null)
                            selectedSlotInventory--;
                        if (selectedSlotInventory < 0)
                            selectedSlotInventory = 17;
                    } else {
                        wornItems[selectedSlotInventory - 12] = null;
                    }
                }
            }
            if (!showItemDetails && bool && selectedAnswerInventory != 1) {
                selectedAnswerInventory = 0;
                choosingInInventory = !choosingInInventory;
            }
        } else if(keyCode == TAB)
            displayAttack = true;
        keyCode = 0;
        key = 0;
    } catch (Exception e) {
        error("Unexpected error occured", e);
    }
}

void keyReleased()
{
    if (keyCode == CONTROL)
        controlPressed = false;
    if (keyCode == keys[19])
        shiftPressed = false;
    for (int k = 0 ; k < pressedKeysCode.length ; k++)
        if (keyCode == pressedKeysCode[k])
            pressedKeysCode[k] = 0;
    if(keyCode == TAB)
        displayAttack = false;
}

int findSpace()
{
    int jeucepa = 0;

    try {
        while(jeucepa != pressedKeysCode.length && pressedKeysCode[jeucepa] != 0)
            jeucepa++;
    } 
    catch(Exception e) {
        e.printStackTrace();
        error("Unexpected error occured",e);
    }
    return jeucepa;
}