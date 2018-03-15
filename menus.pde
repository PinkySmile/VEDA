void audioMenu()
{
    int temp1 = pressedMusicBar ? 0 : 125;
    int temp2 = pressedSFXBar ? 0 : 125;

    printMenuBackground();

    disableMenus();
    enableMenus(11, 12);
    
    fill(122);
    noStroke();
    rect(0, 0, 12 * 32, 3 * 32);
    if (musicLoaded) {
        noStroke();
        fill(125);
        rect(100, 23, 200, 20);
        fill(150);
        rect(101, 24, 198, 18);
        fill(175);
        rect(102, 25, 196, 16);
        fill(200);
        rect(103, 26, 194, 14);
        fill(215);
        rect(104, 27, 192, 12);
        fill(235);
        rect(105, 28, 190, 10);
        fill(255);
        rect(106, 29, 188, 8);
  
        //Bouton
        fill(125 - temp1, 0, 0);
        rect(90 + 2 * musicVolume, 13, 20, 40);
        fill(150 - temp1, 0, 0);
        rect(91 + 2 * musicVolume, 14, 18, 38);
        fill(165 - temp1, 0, 0);
        rect(92 + 2 * musicVolume, 15, 16, 36);
        fill(185 - temp1, 0, 0);
        rect(93 + 2 * musicVolume, 16, 14, 34);
        fill(200 - temp1, 0, 0);
        rect(94 + 2 * musicVolume, 17, 12, 32);
        fill(220 - temp1, 0, 0);
        rect(95 + 2 * musicVolume, 18, 10, 30);
        fill(235 - temp1, 0, 0);
        rect(96 + 2 * musicVolume, 19, 8, 28);
        fill(255 - temp1, 0, 0);
        rect(97 + 2 * musicVolume, 20, 6, 26);
        
        textSize(20);
        fill(255);
        text(musicVolume + "%", 320, 41);
        
        fill(255);
        fill(125);
        rect(100, 73, 200, 20);
        fill(150);
        rect(101, 74, 198, 18);
        fill(175);
        rect(102, 75, 196, 16);
        fill(200);
        rect(103, 76, 194, 14);
        fill(215);
        rect(104, 77, 192, 12);
        fill(235);
        rect(105, 78, 190, 10);
        fill(255);
        rect(106, 79, 188, 8);
  
        //Bouton
        fill(125 - temp2, 0, 0);
        rect(90 + 2 * SFXVolume, 63, 20, 40);
        fill(150 - temp2, 0, 0);
        rect(91 + 2 * SFXVolume, 64, 18, 38);
        fill(165 - temp2, 0, 0);
        rect(92 + 2 * SFXVolume, 65, 16, 36);
        fill(185 - temp2, 0, 0);
        rect(93 + 2 * SFXVolume, 66, 14, 34);
        fill(200 - temp2, 0, 0);
        rect(94 + 2 * SFXVolume, 67, 12, 32);
        fill(220 - temp2, 0, 0);
        rect(95 + 2 * SFXVolume, 68, 10, 30);
        fill(235 - temp2, 0, 0);
        rect(96 + 2 * SFXVolume, 69, 8, 28);
        fill(255 - temp2, 0, 0);
        rect(97 + 2 * SFXVolume, 70, 6, 26);
        
        textSize(20);
        fill(255);
        text(SFXVolume + "%", 320, 91);
    } else {
        textSize(20);
        if(compareStrings(language,"fr")) {
            text("Désactivé", 100, 37);
            text("Désactivé", 100, 87);
        } else {
            text("Disabled", 100, 37);
            text("Disabled", 100, 87);
        }
    }
    textFont(Arial);
    textSize(25);
    if (compareStrings(language, "yolo"))
        textSize(random(1, 50));
    if (!musicLoaded)
        fill(255, 0, 0);
    else
        fill(255, 255, 255);
    text("Music : ", 10, 40);
    text("SFX   : ", 10, 90);
    for (int i = 0 ; i < Musics.length ; i++)
        if (Musics[i] != null)
            Musics[i].setGain(-50+50*musicVolume/100+baseGain[i]);
    textFont(FreeMono);
}

void optionsMenu()
{
    printMenuBackground();
    disableMenus();
    textSize(15);
    fill(122);
    rect(0, 0, 288, 58);
    fill(255);
    if (compareStrings(language, "yolo"))
        textSize(random(1, 50));
    text("Camera scrolling disabled : ", 10, 25, 200, 200);
    menuContent[25] = camScrollingDisabled+"";
    enableMenus(12, 12);
    enableMenus(24, 25); 
}

void languageMenu()
{
    printMenuBackground();

    disableMenus();
    enableMenus(11, 12);
    enableMenus(currentButton, currentButton + languagesNb);
}

void dispArmor(int temp, boolean death)
{
    for (int i = 0; i < wornItems.length; i++)
        if (wornItems[i] != null && wornItems[i].id >= 0 && wornItems[i].id < armorTextures.length)
            if (!death)
                if (armorTextures[wornItems[i].id][temp][chara[0]][chara[1]][animation - 1] != null)
                    image(armorTextures[wornItems[i].id][temp][chara[0]][chara[1]][animation - 1], playerX + camPosX, playerY + camPosY);
                else
                    println("No such index [" + wornItems[i].id + "][" + temp + "][" + chara[0] + "][" + chara[1] + "][" + (animation - 1) + "]");
            else if (armorTextures[wornItems[i].id][temp][0][0][1] != null)
                image(armorTextures[wornItems[i].id][temp][0][0][1], playerX + camPosX, playerY + camPosY + 16);
            else
                println("No such index [" + wornItems[i] + "][" + temp + "][0][0][1]");
}

void inGame()
{
    if(inCutscene)
        camMoving = true;
    if(oldSecond != second()) {
        oldSecond = second();
        playTime++;
    }
    if(!camMoving)
        a++;
    if (a == 120 && !camMoving) {
        new saveEverything(true,true,false);
        a = 0;
    }
    if(inCutscene && !inDialog)
        if(doCommand(cutscenesCommands[commandID]))
            commandID++;
    if(!camMoving) {
        if(energyReloadBuffer >= 150 && energy < 10*energyMax)
            energy = energy + 2;
        else
            energyReloadBuffer++;
        for(int i = 0 ; i < characterPointsBuffer.length ; i++) {
            if(characterPointToGo[i][0] == 0 && characterPointToGo[i][1] == 0)
                characterPointsBuffer[i]++;
            else if(findPath(i,characterPointToGo[i][0],characterPointToGo[i][1])) {
                characterPointToGo[i][0] = 0;
                characterPointToGo[i][1] = 0;
            }
            if(characterPointsBuffer[i] >= 200 && int(random(0, 100)) == 1) {
                characterDir[i] = int(random(0, 4));
                characterPointsBuffer[i] = 0;
            }
            else if(characterPointsBuffer[i] >= 300) {
                int temp = int(random(0, 4));
                characterPointsBuffer[i] = 0;
                if(temp == 0) {
                    characterPointToGo[i][0] = characterX[i];
                    characterPointToGo[i][1] = characterY[i]-16;
                } else if(temp == 1) {
                    characterPointToGo[i][0] = characterX[i];
                    characterPointToGo[i][1] = characterY[i] + 16;
                } else if(temp == 2) {
                    characterPointToGo[i][0] = characterX[i]-16;
                    characterPointToGo[i][1] = characterY[i];
                } else {
                    characterPointToGo[i][0] = characterX[i] + 16;
                    characterPointToGo[i][1] = characterY[i];
                }
            }
        }
    }
    printLevel();
    printCharacters();
    try {
        if (!musicDisabled) {
            Musics[3].pause();
            Musics[3].rewind();
        }
    }
    catch(Exception e) {
        e.printStackTrace();
        error("Error 1",e);
    }
    volume = 70;
    deathBuffer = 0;
    menu = 0;
    if (music == "EpicBattle" && !Music.isPlaying() && !addingChar) {
        Music.pause();
        Music.rewind();
        Music = Musics[6];
        Music.setLoopPoints(0, Music.length());
        Music.loop();
    }
    if (music == "eugrt" && !Music.isPlaying() && !addingChar) {
        Music.pause();
        Music.rewind();
        Music = Musics[11];
        Music.setLoopPoints(100, Music.length());
        Music.loop();
    }
    try {
        if (!musicDisabled) {
            try {
                for (int i = 0 ; i < Musics.length ; i++)
                    Musics[i].setGain(-50+50*musicVolume/100+baseGain[i]);
            } catch(Exception e) {}
            try {
                Musics[0].pause();
                Musics[0].rewind();
            }
            catch(Exception e) {
                e.printStackTrace();
                error("Error 2",e);
            }
        }
    }
    catch(Exception e) {
        e.printStackTrace();
        error("Error 3",e);
    }
    //buffer pour la détéction de quand le joueur reste immobile
    if(!camMoving) {
        if (statusBuffer == 10) {
            statusBuffer = 0;
            status = "static";
        }
        if (status == "moving")
            statusBuffer = statusBuffer + 1;
        else
            statusBuffer = 0;
    }
    //Mort si tu sort de l'écran
    //if (playerX+camPosX <= -16 || playerX+camPosX >= width+16 || playerY+camPosY <= -32 || playerY+camPosY >= height+32)
    //    life = 0;
    
    
    //buffer pour l'animation du mouvement
    if (status == "static") {
        animation = 1;
        chara[0] = 0;
    } else
        chara[0] = 1;
    if(direction == "up")
        chara[1] = 0;
    else if (direction == "down")
        chara[1] = 1;
    else if (direction == "left")
        chara[1] = 2;
    else
        chara[1] = 3;
    if (status == "moving" && animation >= 3)
        animation = 1;
        
    //Affichage du perso
    try {
        int temp = 0;
        if (character == "female")
            temp = 1;
        if (compareStrings(language, "yolo") && animation == 2 && hitBuffer % 2 == 0) {
            image(glitched_character, playerX+camPosX, playerY+camPosY);
            dispArmor(temp, false);
        } else if (hitBuffer % 2 == 0) {
            image(character_image[temp][chara[0]][chara[1]][animation-1], playerX+camPosX, playerY+camPosY);
            dispArmor(temp, false);
        }
    }
    catch(Exception e) {
        e.printStackTrace();
        try {
            image(glitched_character, playerX+camPosX, playerY+camPosY);
        }
        catch(Exception f) {
            f.printStackTrace();
            error("Can't find file "+character+"_character_"+status+"_"+direction+"_"+animation+".png",e);
        }
    }
    printUpperLayer();

    //Dialogues
    showDialogBox();
    
    //Déplacement de la caméra lors de la sortie de l'écran
    if(!inCutscene) {
        int camGoToX = int(playerX + 8);
        int camGoToY = int(playerY + 17);
        if(playerX < 0)
            camGoToX -= width;
        if(playerY < 0)
            camGoToY -= height;
        camGoToX = -camGoToX + (camGoToX % width);
        camGoToY = -camGoToY + (camGoToY % height);
        camMoving = !camMove(camScrollingDisabled,camGoToX,camGoToY);
    }
    float hours = floor(playTime / 3600);
    float minutes = floor(playTime % 3600 / 60);
    float seconds = playTime % 60;
    textSize(15);
    text("Play time : " + int(hours) + ":" + transformInt(int(minutes), 2) + ":" + transformInt(int(seconds), 2), width - 200, 15);
}

void dispDamages()
{
    for (int i = 0; i < damageDisplay.length; i++) {
        if (damageDisplay[i] != 0) {
            textSize(15);
            switch (i) {
            case 0:
                fill(255, 255 - damageBuffer[i] / 2);
                break;
            case 1:
                fill(255, 205, 0, 255 - damageBuffer[i] / 2);
                break;
            case 2:
                fill(0, 0, 255, 255 - damageBuffer[i] / 2);
                break;
            case 3:
                fill(255, 0, 0, 255 - damageBuffer[i] / 2);
                break;
            case 4:
                fill(170, 0, 170, 255 - damageBuffer[i] / 2);
                break;
            case 5:
                fill(0, 100, 0, 255 - damageBuffer[i] / 2);
                break;
            case 6:
                fill(150, 100, 255, 255 - damageBuffer[i] / 2);
                break;
            case 7:
                fill(0, 255, 0, 255 - damageBuffer[i] / 2);
            }
            text((damageDisplay[i] > 0 ? "+" : "") + floor(damageDisplay[i]), playerX + camPosX + 8 - str(floor(damageDisplay[i])).length() * 5, playerY + camPosY - 10 + (damageBuffer[i] * damageBuffer[i] - 255 * damageBuffer[i]) / 1000);
            damageBuffer[i] += 10;
            if (damageBuffer[i] >= 255)
                damageDisplay[i] = 0;
        }
    }
}

void gameover()
{
    background(0);
    if (statusBuffer == 10) {
        statusBuffer = 0;
        status = "static";
    }
    if (status == "moving")
        statusBuffer = statusBuffer + 1;
    else
        statusBuffer = 0;
    if (playerX+camPosX <= -16 || playerX+camPosX >= width+16 || playerY+camPosY <= -32 || playerY+camPosY >= height+32)
        life = 0;
    printLevel();
    printCharacters();
    printUpperLayer();
    if (status == "static")
        animation = 1;
    if (status == "moving" && animation >= 3)
        animation = 1;
    if (compareStrings(language, "yolo")) {
        lifeBuffer = 0;
        try {
            mdrdbar.setLoopPoints(mdrdbar.position(), mdrdbar.position()+50);
            mdrdbar.loop();
        } 
        catch(Exception e) {
            e.printStackTrace();
        }
    }
    tint(255, 255 - 255 / (1 +  sqrt(deathBuffer)));
    gameoverDisplayed = false;
    Musics[3].rewind();
    selectedRespawn = true;
    try {
        if(inCutscene && !inDialog)
            if(doCommand(cutscenesCommands[commandID]))
                commandID++;
        try {
            if (!musicDisabled)
                for (int i = 0 ; i < Musics.length ; i++)
                    Musics[i].setGain(-50+50*musicVolume/100+baseGain[i]);
        }
        catch(Exception e) {}
        deathBuffer = deathBuffer + 1;
        if (!Musics[0].isPlaying() && deathBuffer >= 50 && !compareStrings(language, "yolo")) {
            menu = 1;
            cursorBuffer = 30;
            textTyped = "";
            oldCommands = "";
        } else if (!musicDisabled) {
            for (int i = 0 ; i < Musics.length ; i++)
                if (Musics[i] != null)
                    Musics[i].setGain(-50+50*musicVolume/100+baseGain[i]);
            try {
                if (!Musics[0].isPlaying())
                    Musics[0].play();
                for (int i = 1 ; i < Musics.length ; i++)
                    if (Musics[i] != null)
                        Musics[i].pause();
            }
            catch(Exception e) {
                e.printStackTrace();
                error("Error 4",e);
            }
        }
    }
    catch(Exception e) {
        e.printStackTrace();
        error("Error 5",e);
    }
    if (compareStrings(language, "yolo"))
        try {
            if (deathBuffer >= 300) {
                menu = -12;
                glitchPrint(true, 20);
            }
        }
        catch(Exception e) {
            e.printStackTrace();
            mdrdbar.setLoopPoints(mdrdbar.position(), mdrdbar.position()+50);
            mdrdbar.loop();
            menu = -12;
            glitchPrint(true, 20);
        }
    if (volume != 0)
        volume = volume - 1;
    for (int j = 0; j <= width/16; j++) {
        for (int k = 0; k <= height/16; k++) {
            if (!(j >= 13 && j <= 24 && k >= 12 && k <= 16)) {
                try {
                    image(gameover_font, j * 16, k * 16);
                }
                catch(Exception e) {
                    e.printStackTrace();
                    error("Error 6",e);
                }
            }
        }
    }
    try {
        image(gameover, 208, 192);
        if (compareStrings(language, "yolo"))
            image(godEater, random(-10, width-16), random(-10, height-16));
    }
    catch(Exception e) {
        e.printStackTrace();
        error("Error 7",e);
    }
    tint(255, 255);
    try {
        int temp = 0;
        if (character == "female")
            temp = 1;
        if (compareStrings(language, "yolo"))
            image(glitched_character, playerX + camPosX, playerY + camPosY);
        else
            image(character_image[temp][0][0][1], playerX + camPosX, playerY + camPosY + 16);
        dispArmor(temp, true);
    }
    catch(Exception e) {
        e.printStackTrace();
        try {
            image(glitched_character, playerX+camPosX, playerY+camPosY);
        } 
        catch(Exception f) {
            f.printStackTrace();
            error("Can't find file " + character + "_character_" + status + "_" + direction + "_" + animation  +".png", e);
        }
    }
}

void equip(int item)
{
    Item newItem = (item < 12 ? items[item] : wornItems[item - 12]);
    Item buffer = null;
    int slot = -1;
    
    if (newItem == null)
        return;
    switch (newItem.type) {
    case "weapon":
        slot++;
    case "glove":
        slot++;
    case "shoe":
        slot++;
    case "legs":
        slot++;
    case "chest":
        slot++;
    case "head":
        slot++;
    }
    if (slot == -1)
        return;
    if (item < 12) {
        if (wornItems[slot] != null)
            buffer = wornItems[slot];
        wornItems[slot] = newItem;
        items[item] = buffer;
        itemsQuantity[item] = (items[item] == null ? 0 : -1);
            
        tidyInventory();
        while (selectedSlotInventory >= 0 && items[selectedSlotInventory] == null)
            selectedSlotInventory--;
        if (selectedSlotInventory < 0)
            selectedSlotInventory = 17;
    } else {
        int mdrsd = findInventoryEmptySpace();
        if (mdrsd >= items.length)
            new Popup("L'inventaire est plein !", "Error", JOptionPane.QUESTION_MESSAGE, null);
        else {
            items[mdrsd] = wornItems[item - 12];
            itemsQuantity[mdrsd] = -1;
            wornItems[item - 12] = null;
        }
    }
}

String getTextInventory(Item item)
{
    if (item == null)
        return ("null");
    switch (item.type) {
    case "glove":
    case "shoe":
    case "legs":
    case "chest":
    case "head":
    case "weapon":
        return("Equip");
    }
    return ("Use");
}

void inventory()
{
    image(inventoryFrame, 0, 0);
    textSize(20);
    if (compareStrings(language, "yolo"))
        textSize(random(1, 50));
    color balaic;
    if (nameColor == 3)
        balaic = color(255, 0, 0);
    else if (nameColor == 2)
        balaic = color(255, 255, 0);
    else if (nameColor == 1)
        balaic = color(0, 255, 0);
    else if (nameColor == 0)
        balaic = color(int(random(0, 256)), int(random(0, 256)), int(random(0, 256)));
    else
        balaic = 255;
    fill(balaic);
    text(name, width - 220, 30);
    fill(255);
    text("PV :\n " + (float(floor(life * 100)) / 100) + "/" + lifeMax * 10, width - 220, 60);
    text("Energie :\n " + int(energy) + "/" + energyMax * 10, width - 220, 110);
    if (!choosingInInventory) {
        if (displayAttack)
            text("Attack : ", width - 220, 265);
        else
            text("Resistances : ", width - 220, 265);
        for (int i = 0; i < 6; i++) {
            float res = 0;
    
            for (int j = 0; j < wornItems.length; j++)
                if (wornItems[j] != null)
                    if (displayAttack)
                        res += wornItems[j].damages[i];
                    else
                        res += wornItems[j].resistances[i];
            switch (i + 1) {
            case 1:
                fill(255, 205, 0);
                break;
            case 2:
                fill(0, 0, 255);
                break;
            case 3:
                fill(255, 0, 0);
                break;
            case 4:
                fill(170, 0, 170);
                break;
            case 5:
                fill(0, 100, 0);
                break;
            case 6:
                fill(150, 100, 255);
                break;
            }
            textSize(17);
            text(damagesName[i] + ":\n " + (float(floor(res * 100)) / 100), width - 220, 280 + 32 * i);
        }
    } else {
        fill(0);
        if (selectedSlotInventory >= 12)
            text("Unequip", width - 200, 265);
        else
            text(getTextInventory(items[selectedSlotInventory]), width - 200, 265);
        text("Inspect", width - 200, 295);
        text("Toss", width - 200, 325);
        text("Back", width - 200, 355);
        fill(255);
        stroke(125);
        triangle(width - 220, 30 * selectedAnswerInventory + 255, width - 220, 30 * selectedAnswerInventory + 265, width - 212, 30 * selectedAnswerInventory + 260);
    }
    textSize(20);
    fill(255);
    if (showItemDetails) {
        PImage sprite = null;
        Item theItem = (selectedSlotInventory >= 12 ? wornItems[selectedSlotInventory - 12] : items[selectedSlotInventory]);
        
        if (theItem != null && theItem.id < itemSprites.length && theItem.id >= 0)
            sprite = itemSprites[theItem.id];
        if (sprite == null)
            sprite = item_glitch;
        if (sprite != null)
            image(sprite, 30, 15);
        else
            text("?", 30, 30 + 39);
        if (theItem != null && allItems[theItem.id].durability != 0) {
            if (theItem.durability / allItems[theItem.id].durability > 0.5)
                fill(0, 200, 0);
            else if (theItem.durability / allItems[theItem.id].durability > 0.25)
                fill(200, 200, 0);
            else
                fill(200, 0, 0);
            noStroke();
            rect(25, 32, 24 * theItem.durability / allItems[theItem.id].durability, 5);
            stroke(125);
            noFill();
            rect(25, 32, 24, 5);
        }
        if (theItem != null) {
            fill(0);
            text("Name : " + theItem.name, 60, 30);
            text("Type : " + theItem.type, 60, 65);
            text("Durability : " + theItem.durability + "/" + allItems[theItem.id].durability, 60, 100);
            text("Resistances : ", 10, 135);
            for (int i = 0; i < 6; i++) {
                switch (i + 1) {
                case 1:
                    fill(255, 205, 0);
                    break;
                case 2:
                    fill(0, 0, 255);
                    break;
                case 3:
                    fill(255, 0, 0);
                    break;
                case 4:
                    fill(170, 0, 170);
                    break;
                case 5:
                    fill(0, 100, 0);
                    break;
                case 6:
                    fill(150, 100, 255);
                    break;
                }
                text(damagesName[i] + ":\n " + (float(floor(theItem.resistances[i] * 100)) / 100), 20, 170 + 50 * i);
            }
            fill(0);
            text("Attaques : ", 200, 135);
            for (int i = 0; i < 6; i++) {
                switch (i + 1) {
                case 1:
                    fill(255, 205, 0);
                    break;
                case 2:
                    fill(0, 0, 255);
                    break;
                case 3:
                    fill(255, 0, 0);
                    break;
                case 4:
                    fill(170, 0, 170);
                    break;
                case 5:
                    fill(0, 100, 0);
                    break;
                case 6:
                    fill(150, 100, 255);
                    break;
                }
                text(damagesName[i] + ":\n " + (float(floor(theItem.damages[i] * 100)) / 100), 210, 170 + 50 * i);
            }
        }
    } else {
        for (int i = 0; i < items.length; i++) {
            PImage sprite = null;
            
            if (items[i] != null && items[i].id < itemSprites.length && items[i].id >= 0)
                sprite = itemSprites[items[i].id];
            if (sprite == null)
                sprite = item_glitch;
            if (itemsQuantity[i] > 0)
                quan = "x" + itemsQuantity[i];
            else
                quan = "";
            if (items[i] != null && itemsQuantity[i] == 0)
                items[i] = null;
            if (items[i] != null)
                item = "Item " + (items[i].id + 1);
            else
                item = "";
            if (items[i] == null && compareStrings(language, "yolo"))
                item = "e̷̲̦̖͉̘͊ͩ͌̓ͫr̹̤̳̾͑͗͛̚͠r̬̖̱o̢͇̹̠̼͎̰ͯ͋ͥ̾r̸͔̘̥͎̘̩";
            if (items[i] != null && items[i].name != null)
                item = items[i].name;
            if (itemsQuantity[i] == 0 && compareStrings(language, "yolo"))
                quan = "@░¶½█▓";
            text(item, 60, 30 + 39 * i);
            text(quan, 350, 30 + 39 * i);
            if (items[i] != null) {
                if (sprite != null)
                    image(sprite, 30, 15 + 39 * i);
                else
                    text("?", 30, 30 + 39 * i);
                if (allItems[items[i].id].durability != 0) {
                    if (items[i].durability / allItems[items[i].id].durability > 0.5)
                        fill(0, 200, 0);
                    else if (items[i].durability / allItems[items[i].id].durability > 0.25)
                        fill(200, 200, 0);
                    else
                        fill(200, 0, 0);
                    noStroke();
                    rect(25, 39 * i + 32, 24 * items[i].durability / allItems[items[i].id].durability, 5);
                    stroke(125);
                    noFill();
                    rect(25, 39 * i + 32, 24, 5);
                }
                fill(255);
            }
        }
        if (selectedSlotInventory < 12)
            triangle(12, 39 * selectedSlotInventory + 20, 12, 39 * selectedSlotInventory + 28, 20, 39 * selectedSlotInventory + 24);
        for (int i = 0; i < wornItems.length; i++) {
            int x = width - 60;
            int y = 50 * i + 17;
            
            if (i >= 4) {
                y = 167;
                x = width - 60 - 70 * (i - 3);
            }
            stroke((selectedSlotInventory - 12 == i ? color(255, 0, 0) : 0));
            noFill();
            rect(x, y - 1, 34, 34);
            if (wornItems[i] != null) {
                PImage sprite = null;
                if (wornItems[i] != null && wornItems[i].id < itemSprites.length && wornItems[i].id >= 0)
                    sprite = itemSprites[wornItems[i].id];
                if (sprite == null) 
                    sprite = item_glitch;
                if (sprite != null)
                    image(sprite, x + 1, y, 32, 32);
                else {
                    fill(0, 0, 255);
                    rect(x + 1, y, 32, 32);
                }
                if (allItems[wornItems[i].id].durability != 0) {
                    if (wornItems[i].durability / allItems[wornItems[i].id].durability > 0.5)
                        fill(0, 200, 0);
                    else if (wornItems[i].durability / allItems[wornItems[i].id].durability > 0.25)
                        fill(200, 200, 0);
                    else
                        fill(200, 0, 0);
                    noStroke();
                    rect(x - 7,  y + 35, 48.0 * wornItems[i].durability / allItems[wornItems[i].id].durability, 10);
                    stroke(125);
                    noFill();
                    rect(x - 8,  y + 35, 49, 10);
                }
            }
        }
    }
    //Affichage du perso
    try {
        int temp = 0;
        if (character == "female")
            temp = 1;
        if (character_image[temp][1][0][0] == null) {
            image(glitched_character, width - 90, 10, 24, 48);
            for (int i = 0; i < wornItems.length; i++)
                if (wornItems[i] != null && wornItems[i].id >= 0 && wornItems[i].id < armorTextures.length)
                    if (armorTextures[wornItems[i].id][temp][0][1][0] != null)
                        image(armorTextures[wornItems[i].id][temp][0][1][0], width - 90, 10, 24, 48);
        } else {
            image(character_image[temp][0][1][0], width - 90, 10, 24, 48);
            for (int i = 0; i < wornItems.length; i++)
                if (wornItems[i] != null && wornItems[i].id >= 0 && wornItems[i].id < armorTextures.length)
                    if (armorTextures[wornItems[i].id][temp][0][1][0] != null)
                        image(armorTextures[wornItems[i].id][temp][0][1][0], width - 90, 10, 24, 48);
        }
    }
    catch(Exception e) {
        e.printStackTrace();
        try {
            image(glitched_character, width - 80, 10);
        }
        catch(Exception f) {
            f.printStackTrace();
            error("Can't find file "+character+"_character_"+status+"_"+direction+"_"+animation+".png",e);
        }
    }
    if (compareStrings(language, "yolo"))
        for (int i = 0; i < items.length; i++)
            glitchPrint(true, 20);
}

void lvlCreator()
{
    printLevel();
    if(upperLayerShown)
        printUpperLayer();
    printCharacters();
    disableMenus();
    if(!buttonsDisabled) {
        enableMenus(16, 16);
        enableMenus(20, 21);
    }
    if (music == "EpicBattle" && !Music.isPlaying() && !addingChar) {
        Music.pause();
        Music.rewind();
        Music = Musics[6];
        Music.setLoopPoints(0, Music.length());
        Music.loop();
    }
    if (music == "eugrt" && !Music.isPlaying() && !addingChar) {
        Music.pause();
        Music.rewind();
        Music = Musics[11];
        Music.setLoopPoints(100, Music.length());
        Music.loop();
    }
    fill(0);
    textSize(15);
    float temp = zoomLevel;
    float _temp = (1+temp/20);
    text("x:"+round(mouseX/_temp-camPosX)+" y:"+round(mouseY/_temp-camPosY),width-130, 15);
    text("Zoom : "+round((1+temp/20) * 100)+"%", 2, 15);
    if(replaceMode)
        text("Mode remplacement : actif", 100, 15);
    else
        text("Mode remplacement : inactif", 100, 15);
    if(upperLayerShown)
        text("Couche supérieur affiché", 2, 30);
    else
        text("Couche supérieur cachée", 2, 30);
    if(savedMessageShown) {
        savingBuffer++;
        text("Sauvegardé !",width/2-50,height/2-5);
    }
    if(savingBuffer > 100) {
        savingBuffer = 0;
        savedMessageShown = false;
    }
    if(gridShown) {
        stroke(0);
        float _temps = zoomLevel;
        float tempo = 1+_temps/20;
        int loops = 0;
        for(float i = (16 - camPosX % 16)*tempo ; i <= width && loops <= 150 ; i += 16*tempo) {
            line(i, 0,i,height);
            loops++;
        }
        for(float j = (16 - camPosX % 16)*tempo ; j <= height && loops <= 300; j += 16*tempo) {
            line(0,j,width,j);
            loops++;
        }
    }
}

void mainMenu()
{
    printMenuBackground();
    disableMenus();
    enableMenus(0, 4);

    //Affichage des stats
    String texts[] = new String[5];
    if (compareStrings(language, "fr")) {
        texts[0] = "Progression : ";
        texts[1] = "Vie : ";
    } else if (compareStrings(language, "en")) {
        texts[0] = "Progress : ";
        texts[1] = "Life : ";
    } else if (compareStrings(language, "de")) {
        texts[0] = "Progression : ";
        texts[1] = "Leben : ";
    } else {
        texts[0] = "";
        texts[1] = "";
    }
    fill(122);
    noStroke();
    rect(width - 160, 0, 160, 65);
    fill(255);
    textSize(15);
    text(name, width - 160, 20);
    text(texts[0] + progress + "%", width - 160, 40);
    text(texts[1] + int(life) + "/"+lifeMax * 10, width - 160, 60);

    //Affichage de la version
    textSize(10);
    if (compareStrings(language, "yolo"))
        textSize(random(1, 50));
    fill(255);
    text("v"+version, 1, height-2);
    try {
        for (int i = 0 ; i < Musics.length ; i++)
            Musics[i].setGain(-50+50*musicVolume/100+baseGain[i]);
    } catch(Exception e) {}
}

void objMenu()
{
    try {
        for (int j=0; j<=height; j = j+16) {
            for (int i=0; i<=width; i = i+16) {
                noStroke();
                fill(0);
                image(blue_sky, i, j);
            }
        }
    }
    catch(Exception e) {
        for (int j=0; j<=height; j = j+16) {
            for (int i=0; i<=width; i = i+16) {
                noStroke();
                fill(0);
                image(glitched_texture, i, j);
            }
        }
    }
    disableMenus();
    enableMenus(22, 22);
    int x = 4;
    int y = 4;
    for (int i = floor((width-8)/24)*floor((height-50)/24)*menuPosition; i <= textures.length-2; i++) {
        if (x >= width - 20) {
            x = 4;
            y = y + 24;
        }
        if (y <= height - 50 - 24) {
            try {
                image(textures[i + 2], x, y);
                if((i >= 7 && i <= 9) || i == 11)
                    image(textures[0], x, y);
                if(i == 12 || i == 13)
                    image(redCross, x, y);
            }
            catch(Exception e) {
                image(glitched_texture, x, y);
            }
            stroke(0);
            noFill();
            rect(x-1,y-1, 17, 17);
        }
        x = x + 24;
    }
    try {
      image(textures[1+selectedObject], 10,height-26);
      if(selectedObject <= 10 && selectedObject >= 8 || selectedObject == 12) {
          image(textures[0], 10,height-26);
      }
      if(selectedObject == 13 || selectedObject == 14) {
          image(redCross, 10,height-26);
      }
    } catch(Exception e) {
        image(glitched_texture, 10,height-26);
    }
    if (music == "EpicBattle" && !Music.isPlaying() && !addingChar) {
        Music.pause();
        Music.rewind();
        Music = Musics[6];
        Music.setLoopPoints(0, Music.length());
        Music.loop();
    }
    if (music == "eugrt" && !Music.isPlaying() && !addingChar) {
        Music.pause();
        Music.rewind();
        Music = Musics[11];
        Music.setLoopPoints(100, Music.length());
        Music.loop();
    }
}

void charObj()
{
    dirBuffer++;
    if(dirBuffer >= 120) {
        dirBuffer = 0;
        dir++;
        if(dir == 4)
            dir = 0;
    }
    try {
        for (int j = 0; j <= height; j += 16) {
            for (int i = 0; i <= width; i += 16) {
                noStroke();
                fill(0);
                image(blue_sky, i, j);
            }
        }
    }
    catch(Exception e) {
        for (int j = 0; j <= height; j += 16) {
            for (int i = 0; i <= width; i += 16) {
                noStroke();
                fill(0);
                image(glitched_texture, i, j);
            }
        }
    }
    disableMenus();
    enableMenus(22, 22);
    int x = 4;
    int y = 4;
    int maxi = 0;
    for (int i = floor((width - 8) / 16) * floor((height - 50) / 32) * menuPosition; i <= characterTextures.length; i++) {
        if (x >= width - 20) {
            x = 4;
            y = y + 32;
        }
        if (y <= height - 50 - 32) {
            maxi = i;
            try {
                image(characterTextures[i][0][dir][0], x, y);
            }
            catch(Exception e) {
                image(glitched_character, x, y);
            }
        }
        x = x + 16;
    }
    println(maxi);
}

void achievements()
{
    printMenuBackground();
    disableMenus();
    enableMenus(24, 24);
    
    if(lastMenu == 0 || lastMenu == 1) {
        if (music == "EpicBattle" && !Music.isPlaying() && !addingChar) {
            Music.pause();
            Music.rewind();
            Music = Musics[6];
            Music.setLoopPoints(0, Music.length());
            Music.loop();
        }
        if (music == "eugrt" && !Music.isPlaying() && !addingChar) {
            Music.pause();
            Music.rewind();
            Music = Musics[11];
            Music.setLoopPoints(100, Music.length());
            Music.loop();
        }
    }
    
    noStroke();
    fill(0);
    rect(48, 0, width - 96, height);
    fill(150);
    rect(32, 0, 16, height);
    rect(width - 48, 0, 16, height);
    for(int i = 0 ; i < nbOfAchievementsLoaded ; i++) {
        if(i != nbOfAchievementsLoaded-1) {
            stroke(150);
            line(128, 90 * i + achievementMenuPos + 56 + 45, width - 128, 90 * i + achievementMenuPos + 56 + 45);
            noStroke();
        }
        if(achievementsGot[i]) {
            fill(150);
            try {
                rect(135 - achievementImage[i].width / 2, 90 * i + achievementMenuPos + 56 - achievementImage[i].height / 2, achievementImage[i].width, achievementImage[i].height);
                image(achievementImage[i], 135 - achievementImage[i].width / 2, 90 * i + achievementMenuPos + 56 - achievementImage[i].height / 2);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            textSize(20);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            fill(255);
            try {
                text(achievements[i], 170, 90 * i + achievementMenuPos + 56);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            textSize(12);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            try {
                text(achievementsContent[i], 170, 90 * i + achievementMenuPos + 70, 330, height);
            }
            catch(Exception e) {
              e.printStackTrace();
            }
        } else {
            try {
                image(locked, 135 - locked.width / 2, 90 * i + achievementMenuPos + 56 - locked.height / 2);
            } 
            catch(Exception e) {
                e.printStackTrace();
            }
            fill(255);
            textSize(20);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            try {
                text("?????????", 170, 90 * i + achievementMenuPos + 56);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            textSize(12);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            text("??????????????????????????????????????", 170, 90 * i + achievementMenuPos + 70, 260, height);
        }
    }
}

void battle()
{
    int an = 0;

    if(compareStrings(language,"fr"))
        an = JOptionPane.showOptionDialog(null,"Battle started.","",JOptionPane.OK_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, new String[]{"Gagner", "Perdre"}, "default");
    else
        an = JOptionPane.showOptionDialog(null, "Battle started.", "", JOptionPane.OK_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, new String[]{"Win", "Loose"}, "default");
    if(an == 0) {
        menu = 0;
        inDialog = false;
        dialogText = null;
        dialogEnd = false;
        dialogBox(dialogs[fightingCharacter][49][1]);
    } else {
        menu = 0;
        inDialog = false;
        dialogText = null;
        dialogEnd = false;
        dialogBox(dialogs[fightingCharacter][49][0]);
    }
}

void controls()
{
    int xPos = 0;
    int yPos = 0;
    textFont(Arial);
    printMenuBackground();
    disableMenus();
    for (int k = 0; k < keys.length; k++) {
        textSize(15);
        if (compareStrings(language, "yolo"))
            textSize(random(1, 50));
        noStroke();
        fill(122);
        rect(xPos * 192, yPos * 32, 192, 32);
        
        String keyName = findKey(keys[k]);
        int current_color = 150;
        int textColor = color(0, 255, 0);
        if (mouseX > 115 + xPos * 192 && mouseX < 186 + xPos * 192 && mouseY > yPos * 32 + 5 && mouseY < yPos * 32 + 25 || k == changingKey) {
            textColor = 0;
            current_color += 100;
        }
        if (k == changingKey)
            keyName = "Press a key";
        fill(current_color-150);
        rect(115 + xPos * 192, yPos * 32 + 5, 71, 20);
        fill(current_color-125);
        rect(115 + xPos * 192+1, yPos * 32 + 5+1, 71-2, 20-2);
        fill(current_color-100);
        rect(115 + xPos * 192 + 2, yPos * 32 + 5 + 2, 71-4, 20-4);
        fill(current_color-80);
        rect(115 + xPos * 192+3, yPos * 32 + 5+3, 71-6, 20-6);
        fill(current_color-60);
        rect(115 + xPos * 192+4, yPos * 32 + 5+4, 71-8, 20-8);
        fill(current_color-40);
        rect(115 + xPos * 192+5, yPos * 32 + 5+5, 71-10, 20-10);
        fill(current_color-25);
        rect(115 + xPos * 192+6, yPos * 32 + 5+6, 71-12, 20-12);
        fill(current_color-10);
        rect(115 + xPos * 192+7, yPos * 32 + 5+7, 71-14, 20-14);
        fill(current_color);
        rect(115 + xPos * 192+8, yPos * 32 + 5+8, 71-16, 20-16);
        if (textColor == color(0, 255, 0))
            fill(0);
        else
            fill(255);
        text(keyUsage[k] + "", 10 + xPos * 192, yPos * 32 + 20);
        for (int i = 0; i < keys.length; i++)
            if (keys[k] == 0 || keys[k] != -1 && k != i && keys[k] == keys[i])
                textColor = color(255, 0, 0);
        if (k == changingKey)
            textSize(12);
        fill(textColor);
        text(keyName, 120 + xPos * 192, yPos * 32 + 20);
        if (yPos * 32 > height - 128) {
            yPos = -1;
            xPos++;
        }
        yPos++;
    }
    enableMenus(11, 12);
    textFont(FreeMono);
}

void addLine(String lineContent)
{
    if (lineContent.length() <= 65) {
        int i = 0;

        for (i = 0; i < commandLines.length && commandLines[i] != null; i++);
        if (i == commandLines.length) {
            commandLines = shift(commandLines, "up");
            commandLines[commandLines.length - 1] = lineContent;
        } else
            commandLines[i] = lineContent;
    } else
        for (int i = 0; i < lineContent.length(); i += 65)
            addLine(subString(lineContent, i, i + 64));
}

String[] parseCommand(String content) {
    String[] args = new String[100];
    int tab = 1;
    boolean q = false;
    boolean s_q = false;
    int i = 0;
    int start = 0;
    
    while (i < content.length() && content.charAt(i) != ' ')
        i++;
    args[0] = subString(content, 0, i - 1);
    i++;
    while (i < content.length()) {
        start = i;
        if (i < content.length() && content.charAt(i) == '"') {
            start = start + 1;
            i = i + 1;
            q = true;
        } else if (i < content.length() && content.charAt(i) == '\'') {
            start = start + 1;
            i = i + 1;
            s_q = true;
        }
        while (i < content.length() && (content.charAt(i) != ' ' || q || s_q) && (content.charAt(i) != '\"' || s_q) && (content.charAt(i) != '\'' || q)) {
            i = i + 1;
            if (i < content.length() && content.charAt(i) == '\"')
                q = false;
            else if (i < content.length() && content.charAt(i) == '\'')
                s_q = false;
        }
        args[tab] = subString(content, start, i - 1);
        if (i < content.length() - 1 && (content.charAt(i) != '\'' || content.charAt(i) != '"') && content.charAt(i + 1) == ' ')
            i = i + 1;
        tab = tab + 1;
        i = i + 1;
    }
    return args;
}

boolean[] getFlags(String[] args)
{
    boolean[] flags = {false, false, false};
    
    for (int i = 0; i < args.length && args[i] != null; i++)
        if (args[i].charAt(0) == '-')
            for (int j = 1; j < args[i].length(); j++)
                switch(args[i].charAt(j)) {
                case 'a':
                    flags[0] = true;
                    break;
                case 'l':
                    flags[1] = true;
                    break;
                case 'R':
                    flags[2] = true;
                    break;
                default:
                    addLine("ls: Unknown parameter '" + args[i].charAt(j) + "'");
                    return (null);
                }
    return flags;
}

String[] getPaths(String[] args)
{
    String[] paths = new String[args.length];
    int index = 0;
    
    for (int i = 0; i < args.length && args[i] != null; i++)
        if (args[i].charAt(0) != '-')
            paths[index++] = args[i];
    return paths;
}

String delFolder(String path)
{
    int end = path.length() - 1;

    for (; end > 0 && path.charAt(end) == '/'; end--);
    for (; end > 0 && path.charAt(end) != '/'; end--);
    return (subString(path, 0, end));
}

String resolvePath(String path)
{
    String realPath = "";
    String folder = "";
    int start = 0;
    int i = 0;

    realPath += (path.charAt(0) == '/' ? "/" : currentPath);
    start = (path.charAt(0) == '/' ? 1 : 0);
    i = start;
    println("Resolving path " + path);
    while (i < path.length()) {
        if (path.charAt(i) == '/') {
            if (start == i)
                start++;
            else {
                folder = subString(path, start, i - 1);
                println("Found folder " + folder);
                if (compareStrings(folder, "..")) {
                    realPath = delFolder(realPath);
                    if (compareStrings(realPath, ""))
                        realPath = "/";
                } else if (!compareStrings(folder, ".") && !compareStrings(folder, ""))
                    realPath += (realPath.charAt(realPath.length() - 1) != '/' ? "/" : "") + folder;
                start = i + 1;
            }
        }
        i++;
    }
    if (start != i) {
        folder = subString(path, start, i - 1);
        println("Found folder " + folder);
        if (compareStrings(folder, "..")) {
            realPath = delFolder(realPath);
            if (compareStrings(realPath, ""))
                realPath = "/";
        } else if (!compareStrings(folder, ".") && !compareStrings(folder, ""))
            realPath += (realPath.charAt(realPath.length() - 1) != '/' ? "/" : "") + folder;
    }
    return (realPath);
}

void ls(String[] args)
{
    try {
        boolean[] flags = getFlags(args);
        String[] paths = getPaths(args);
        String[] dirs = null;
        String line = "";
        File file = null;

        if (flags == null)
            return;
        if (paths[0] == null)
            paths[0] = currentPath;
        for (int j = 0; j < paths.length && paths[j] != null; j++) {
            file = new File("./" + resolvePath(paths[j]));
            if (file.isDirectory()) {
                dirs = file.list();
                line = "";
                if (dirs == null)
                    addLine("ls: " + paths[j] + ": No such file or directory");
                else {
                    addLine(paths[j] + ":");
                    for(int i = 0 ; i < dirs.length ; i++) {
                        if (flags[1])
                            addLine(dirs[i]);
                        else
                            line += dirs[i] + (i == dirs.length - 1 ? "" : " ");
                      /*
                        File files = new File("." + currentPath + "/" + paths[i] + "/" + dirs[i]);
                        if(files.isDirectory() && flags[2])
                            getNbOfFiles(new File(paths[i] +  "/" + dirs[i]).getAbsolutePath());*/
                    }
                    if (!flags[1])
                        addLine(line);
                }
            } else
                addLine(paths[j]);
        }
    } catch(Exception e) {
        addLine("ls: " + e);
    }
}

void execShellCommand(String commandLine)
{
    String[] args = parseCommand(commandLine);
    String command = args[0];

    args = shift(args, "up");
    if (compareStrings(command, ""))
        return;
    if (compareStrings(command, "shutdown"))
        System.exit(0);
    else if (compareStrings(command, "exit")) {
        menu = 0;
        for (int i = 0; i < commandLines.length; i++)
            commandLines[i] = null;
        deathBuffer = 0;
        printLevel();
    } else if (compareStrings(command, "gameover")) {
        if (onWindows)
            addLine("gameover: Wrong Architechture");
        else
            inShell = false;
    } else if (compareStrings(command, "gameover.exe")) {
        if (!onWindows)
            addLine("gameover.exe: Wrong Architechture");
        else
            inShell = false;
    } else if (compareStrings(command, "ls")) {
        ls(args);
    } else if (compareStrings(command, "cd")) {
        if (args[0] == null)
            args[0] = "/";
        file = new File("./" + resolvePath((args[0].charAt(0) == '/' ? "" : currentPath) + "/" + args[0]));
        if (file.exists())
            currentPath = resolvePath((args[0].charAt(0) == '/' ? "" : currentPath) + "/" + args[0]);
        else
            addLine("cd: " + resolvePath((args[0].charAt(0) == '/' ? "" : currentPath) + "/" + args[0]) + ": No such file or directory");
    } else
        addLine(command + ": Command not found.");
}

void shell()
{
    String display = "";
    String displayedText = "";

    prompt = "[" + currentPath + "]" + classicPrompt;
    if(inCutscene && !inDialog)
        if(doCommand(cutscenesCommands[commandID]))
            commandID++;
    try {
        background(0);
        if (!musicDisabled && Musics[3] != null) {
            Musics[3].play();
        }
    }
    catch(Exception e) {
        e.printStackTrace();
        error("Error 8",e);
    }
    cursor = "";
    fill(255);
    if (!gameoverDisplayed)
        if (musicDisabled || Musics[3].position() >= 2300) {
            addLine(prompt + "gameover" + (onWindows ? ".exe" : ""));
            gameoverDisplayed = true;
            inShell = false;
            textTyped = "";
        } else if (musicDisabled || Musics[3].position() >= 1680)
            textTyped =  "gameover";
        else if (musicDisabled || Musics[3].position() >= 1250)
            textTyped = "gameove";
        else if (musicDisabled || Musics[3].position() >= 1050)
            textTyped = "gameov";
        else if (musicDisabled || Musics[3].position() >= 900)
            textTyped = "gameo";
        else if (musicDisabled || Musics[3].position() >= 750)
            textTyped = "game";
        else if (musicDisabled || Musics[3].position() >= 590)
            textTyped = "gam";
        else if (musicDisabled || Musics[3].position() >= 430)
            textTyped = "ga";
        else if (musicDisabled || Musics[3].position() >= 270)
            textTyped = "g";
    if (cursorBuffer >= 30 && (musicDisabled || Musics[3].position() >= 2300))
        cursor = "_";
    if (cursorBuffer >= 60)
        cursorBuffer = 0;
    cursorBuffer++;
    textSize(15);
    if (compareStrings(language, "yolo"))
        textSize(random(1, 50));
    for (int i = 0; i < commandLines.length && commandLines[i] != null; i++)
        display += commandLines[i] + "\n";
    displayedText = prompt + textTyped + cursor;
    for (int i = 0; i < displayedText.length() && inShell; i += 65)
        display += subString(displayedText, i, i + 64) + "\n";
    if (!inShell)
        display += (selectedRespawn ? "> " : "  ") + "Respawn  " + (selectedRespawn ? "  " : "> ") + "Quit";
    for (int i = 0; i < display.length(); i++) {
        if (int(display.charAt(i)) >= 60000) {
            display = subString(display, 0, i - 1) + "^" + char(display.charAt(i) - 60001 + 'A') + subString(display, i + 1, display.length());
            i++;
        }
    }
    text(display, 20, 40);
    cursorBuffer++;
}

void drawLife()
{
    if (life > 10*lifeMax) 
        life = 10*lifeMax;
    lifeBuffer = floor(life);
    //Affichage des coeurs
    if (menu == 0 && !dead && !inDialog) {
        int x = 0;
        int y = 0;
        int h = 0;
        int b = 0;
        for (int i = 1 ; i <= lifeMax ; i++) {
            if (lifeBuffer <= 10 && lifeBuffer >= 0)
                life_image = hearts[h][(10-lifeBuffer)];
            else if (lifeBuffer >= 10)
                life_image = hearts[h][0];
            else
                life_image = hearts[h][10];
            try {
                image(life_image, x, height-15-y);
                image(hearts[h][10], x, height-15-y);
            }
            catch(Exception e) {
                e.printStackTrace();
                if (!errorDisplayed)
                    errorMsg("Error 9", SFX[0], e);
            }
            if (b == 0)
                x = x + 15;
            if (b == 1) {
                h++;
                if (h == hearts.length) {
                    h = 0;
                    x += 15;
                }
            }
            if (x >= 15 * 10) {
                x = 0;
                y += 15;
            }
            if (b == 0 && y >= 3 * 15) {
                h++;
                y = 0;
            } 
            if (h == hearts.length && b == 0) {
                x = 0;
                b = 1;
                h = 0;
                y = y + hearts.length * 15;
            }
            lifeBuffer = lifeBuffer - 10;
        }
    }
}

void drawNRJ()
{
    if (energy > 10*energyMax) 
        energy = 10*energyMax;
    energyBuffer = floor(energy);
    //Affichage des éclairs
    if (menu == 0 && !dead && !inDialog) {
        int x = 0;
        int y = 0;
        int h = 0;
        int b = 0;
        for (int i = 1 ; i <= energyMax ; i++) {
            if (energyBuffer <= 10 && energyBuffer >= 0)
                energy_image = thunderbolts[h][(10-energyBuffer)];
            else if (energyBuffer >= 10)
                energy_image = thunderbolts[h][0];
            else
                energy_image = thunderbolts[h][10];
            try {
                image(energy_image, width-x-14, height-15-y);
                image(thunderbolts[h][10], width-x-14, height-15-y);
            }
            catch(Exception e) {
                e.printStackTrace();
                if (!errorDisplayed)
                    errorMsg("Error 9", SFX[0], e);
            }
            if (b == 0)
                x = x + 15;
            if (b == 1) {
                h++;
                if (h == thunderbolts.length) {
                    h = 0;
                    x += 15;
                }
            }
            if (x >= 15 * 10) {
                x = 0;
                y += 15;
            }
            if (b == 0 && y >= 3 * 15) {
                h++;
                y = 0;
            } 
            if (h == thunderbolts.length && b == 0) {
                x = 0;
                b = 1;
                h = 0;
                y = y + thunderbolts.length * 15;
            }
            energyBuffer = energyBuffer - 10;
        }
    }
}