//**********************************************Affichage du niveau**********************************************************
void printLevel()
{
    //Affichage du fond
    try {
        for (int j = 0; j <= height; j += 16) {
            for (int i = 0; i <= width; i += 16) {
                noStroke();
                fill(0);
                image(blue_sky, i, j);
            }
        }
    } catch (Exception e) {
        for (int j = 0; j <= height; j += 16) {
            for (int i = 0; i <= width; i += 16) {
                noStroke();
                fill(0);
                image(glitched_texture, i, j);
            }
        }
    }
    if (menu == 7) {
        float _temp = zoomLevel;
        scale(1 + _temp / 20);
    } else
        zoomLevel = 0;
    right = true;
    left = true;
    down = true;
    up = true;
    int i = 0;
    //Affichage des objects et hitboxs
    while (i != nbOfObjects) {
        boolean flag = true;
        if (objects[i] != 0)
            for (int j = 0 ; j < upperObjects.length ; j++) {
                if (objects[i] == upperObjects[j])
                    flag = false;
            }
        else
            flag = false;
        if (flag) {
            PImage picture = textures[objects[i] + 1];
            if ((menu == 7 || menu == 8 || debugMode) && (objects[i] <= 10 && objects[i]>= 8 || objects[i] == 12))
                picture = textures[0];
            if (compareStrings(language, "yolo") && isGlitched[i])
                picture = glitched_texture;
            if ((menu == 7 || menu == 8 || debugMode) && objects[i] == 13)
                picture = redCross;
            try {
                float _temp = zoomLevel;
                if ((posObjectX[i] * 16 + camPosX) * (1 + _temp / 20) >= 0 && (posObjectX[i] * 16 - 16 + camPosX) * (1 + _temp / 20) <= width && (posObjectY[i] * 16 + camPosY) * (1 + _temp / 20) >= 0 && (posObjectY[i] * 16 - 16 + camPosY) * (1 + _temp / 20) <= height) {
                    image(picture, posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 - 16 + camPosY);
                    if (debugMode || compareStrings(language, "yolo")) {
                        textSize(14);
                        fill(255);
                        text(objects[i], posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 + camPosY);
                    }
                    if (menu >= 7 && menu <= 8 && objects[i] == 14)
                        image(redCross, posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 - 16 + camPosY);
                }
            } catch (Exception e) {
                try {
                    image(glitched_texture, posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 - 16 + camPosY);
                } catch (Exception f) {
                    f.printStackTrace();
                    error("Error 14", e);
                }
            }
            if (objects[i] == 5 && !camMoving)
                if (playerY + 47 >= posObjectY[i] * 16 && playerY + 16 < posObjectY[i] * 16 && playerX + 3 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= playerX + 29 && hitBuffer == 0 && menu == 0 && !dead) {
                    takeDamages(10, 1);
                    hitBuffer = 20;
                }
            if (objects[i] == 11 && !camMoving)
                if (playerY + 47 >= posObjectY[i] * 16 && playerY + 16 < posObjectY[i] * 16 && playerX + 3 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= playerX + 29 && life > 0 && menu == 0 && !dead)
                    takeDamages(-3, 7);
        }
        i = i + 1;
    }
    if (menu == 7) {
        float _temp = zoomLevel;
        scale(1 / (1 + _temp / 20));
    }
    try {
        if (!musicDisabled && !Music.isLooping() && !Music.isPlaying() && music != "EpicBattle"  && music != "eugrt" && menu != 7 && !inCutscene){
            Music.setLoopPoints(0, Music.length());
            Music.loop();
        }
    } catch(Exception e) {
        e.printStackTrace();
        error("Error 15", e);
    }
}

//**********************************************Affichage de la couche superieur**********************************************************
void printUpperLayer()
{
    if (menu == 7) {
      float _temp = zoomLevel;
      scale(1 + _temp / 20);
    }
    //Affichage des objects et hitboxs
    for (int i = 0 ; i != nbOfObjects ; i++) {
        boolean flag = false;
        if (objects[i] != 0)
            for (int j = 0 ; j < upperObjects.length ; j++)
                if (objects[i] == upperObjects[j])
                    flag = true;
        if (flag) {
            PImage picture = textures[objects[i] + 1];
            if (compareStrings(language, "yolo") && isGlitched[i])
                picture = glitched_texture;
            try {
                float _temp = zoomLevel;
                if ((posObjectX[i] * 16 + camPosX) * (1 +_temp / 20) >= 0 && (posObjectX[i] * 16 - 16 +camPosX) * (1 + _temp / 20) <= width && (posObjectY[i] * 16 + camPosY) * (1 + _temp / 20) >= 0 && (posObjectY[i] * 16 - 16 + camPosY) * (1 + _temp / 20) <= height) {
                    image(picture, posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 - 16 + camPosY);
                    if (debugMode || compareStrings(language, "yolo")) {
                        textSize(14);
                        fill(255, 0, 0);
                        text(objects[i], posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 + camPosY);
                    }
                    if (menu >= 7 && menu <= 8 && objects[i] == 14)
                        image(redCross, posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 - 16 + camPosY);
                }
            } catch (Exception e) {
                try {
                    image(glitched_texture, posObjectX[i] * 16 - 16 + camPosX, posObjectY[i] * 16 - 16 + camPosY);
                } catch (Exception f) {
                    f.printStackTrace();
                    error("Error 14", e);
                }
            }
        }
    }
    fill(0);
    if (menu == 7) {
        float _temp = zoomLevel;
        scale(1 / (1 + _temp / 20));
    }
}

void printMenuBackground()
{
    background(122);
    try {
        for (int i = 0 ; i < width ; i += menuBackground.width)
            for (int j = 0 ; j < height ; j += menuBackground.height)
                image(menuBackground, i, j);
    } catch (Exception e) {
        e.printStackTrace();
        textSize(14);
        if(compareStrings(language, "yolo"))
            textSize(random(1, 50));
        fill(255, 0, 0);
        text("[ERROR]:Background File Missing", 230, 30);
    }
}

boolean camMove(boolean tp, int xPointToGo, int yPointToGo)
{
    boolean arrived = false;
    if (tp) {
        camPosX = xPointToGo;
        camPosY = yPointToGo;
        arrived = true;
    } else {
        if (camPosX < xPointToGo)
            camPosX += 4;
        else if (camPosX > xPointToGo)
            camPosX -= 4;
        else if (camPosY < yPointToGo)
            camPosY += 4;
        else if (camPosY > yPointToGo)
            camPosY -= 4;
        else
            arrived = true;
    }
    return arrived;
}

boolean isOnUpperLayer(int objectID)
{
    boolean flag = false;
    if (objects[objectID] != 0)
        for (int j = 0 ; j < upperObjects.length ; j++)
            if (objects[objectID] == upperObjects[j])
                flag = true;
    return flag;
}