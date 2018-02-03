void takeDamages(int damages, int damageType)
{
    float buffer = life;
    float res = 0;

    if (damageType > 0 && damageType < 7) {
        for (int i = 0; i < wornItems.length; i++)
            if (wornItems[i] != null) {
                res += wornItems[i].resistances[damageType - 1];
                println(wornItems[i].durability);
                if (allItems[wornItems[i].id].resistances[damageType - 1] > 0) {
                    wornItems[i].durability -= damages / 10;
                    if (wornItems[i].durability <= 0)
                        wornItems[i] = null;
                    for (int j = 0; wornItems[i] != null && j < wornItems[i].resistances.length; j++)
                        wornItems[i].resistances[j] = allItems[wornItems[i].id].resistances[j] * wornItems[i].durability / allItems[wornItems[i].id].durability;
                }
            }
        life -= damages * (20 / (sqrt(abs(res)) + 20));
    } else
        life -= damages;
    if (life > lifeMax * 10)
        life = lifeMax * 10;
    if (life < 0)
        life = 0;
    if (life - buffer != 0) {
        damageDisplay[damageType] -= buffer - life;
        damageBuffer[damageType] = 0;
    }
}

void printCharacters()
{
    boolean u = true, d = true, l = true, r = true;
    if(menu == 7) {
        float _temp = zoomLevel;
        scale(1 + _temp / 20);
    } else
        zoomLevel = 0;
    for(int i = 0 ; i < characters.length ; i++) {
        if(characters[i]) {
            try {
                image(characterTextures[characterTextureNames[i]][characterStatus[i]][characterDir[i]][characterAnim[i]], characterX[i] + camPosX, characterY[i] + camPosY);
            } catch(Exception e){
                image(glitched_character, characterX[i] + camPosX, characterY[i] + camPosY);
            }
            if(characterMovingBuffer[i] >= 10) {
                characterMovingBuffer[i] = 0;
                characterAnim[i]++;
            }
            if (characterStatus[i] == 1 && characterAnim[i] >= 2)
                characterAnim[i] = 0;
            if(characterStatusBuffer[i] >= 10)
                characterStatus[i] = 0;
            if(characterStatus[i] == 1)
                characterStatusBuffer[i]++;
            else {
                characterStatusBuffer[i] = 0;
                characterAnim[i] = 0;
            }
            if (debugMode) {
                for(int j = 0 ; j <= nbOfObjects ; j++) {
                    boolean flag = false;
                    if(objects[j] != 0)
                        for(int k = 0 ; k < upperObjects.length ; k++)
                            if(objects[j] == solidObjectsChars[k])
                                flag = true;
                    if(flag) {
                        if (characterY[i] + 48 >= posObjectY[j] * 16 && characterY[i] + 32 <= posObjectY[j] * 16 && characterX[i] + 3 <= posObjectX[j] * 16 && posObjectX[j] * 16 <= characterX[i] + 28)
                          d = false;
                        if (characterY[i] + 32 >= posObjectY[j] * 16 && characterY[i] + 16 <= posObjectY[j] * 16 && characterX[i] + 3 <= posObjectX[j] * 16 && posObjectX[j] * 16 <= characterX[i] + 28)
                          u = false;
                        if (characterY[i] + 47 >= posObjectY[j] * 16 && characterY[i] + 17 <= posObjectY[j] * 16 && characterX[i] + 2 <= posObjectX[j] * 16 && posObjectX[j] * 16 <= characterX[i] + 28)
                          l = false;
                        if (characterY[i] + 47 >= posObjectY[j] * 16 && characterY[i] + 17 <= posObjectY[j] * 16 && characterX[i] <= posObjectX[j] * 16-18 && characterX[i] >= posObjectX[j] * 16-30)
                          r = false;
                    }
                }
                if (characterY[i] + 32 >= playerY + 16 && characterY[i] + 16 <= playerY + 16 && characterX[i] + 3 <= playerX + 16 && playerX + 16 <= characterX[i] + 28)
                    d = false;
                if (characterY[i] + 16 >= playerY + 16 && characterY[i] <= playerY +16 && characterX[i] + 3 <= playerX +16 && playerX +16 <= characterX[i] + 28)
                    u = false;
                if (characterY[i] + 33 >= playerY + 16 && characterY[i] + 1 <= playerY +16 && characterX[i] + 2 <= playerX +16 && playerX +16 <= characterX[i] + 28)
                    l = false;
                if (characterY[i] + 33 >= playerY + 16 && characterY[i] + 1 <= playerY +16 && characterX[i] <= playerX +16 - 18 && characterX[i] >= playerX +16-30)
                    r = false;
                stroke(0);
                noFill();
                rect(characterX[i] + camPosX, characterY[i] + playerHeight / 2 - 1 + camPosY, playerWidth, playerHeight / 2 - 2);
                stroke(255, 0, 0);
                fill(255, 0, 0);
                rect(characterX[i] + 15 + camPosX, characterY[i] - 1 + camPosY, 2, 2);
                rect(characterX[i] + 15 + camPosX, characterY[i] + 31 + camPosY, 2, 2);
                rect(characterX[i] - 1 + camPosX, characterY[i] + 31 + camPosY, 2, 2);
                stroke(0, 255, 0);
                rect(characterX[i] - 1 + camPosX, characterY[i] - 1 + camPosY, 2, 2);
                noFill();
                if (u)
                    stroke(0);
                else
                    stroke(255, 0, 0);
                line(characterX[i] + playerWidth/2+camPosX, characterY[i]-2+camPosY, characterX[i] + playerWidth/2+camPosX, characterY[i]-8+camPosY);
                if (d)
                    stroke(0);
                else
                    stroke(255, 0, 0);
                line(characterX[i] + playerWidth/2+camPosX, characterY[i] + playerHeight + 2+camPosY, characterX[i] + playerWidth/2+camPosX, characterY[i] + playerHeight+8+camPosY);
                if (r)
                    stroke(0);
                else
                    stroke(255, 0, 0);
                line(characterX[i] + playerWidth + 2+camPosX, characterY[i] + playerHeight/2+camPosY, characterX[i] + playerWidth+8+camPosX, characterY[i] + playerHeight/2+camPosY);
                if (l)
                    stroke(0);
                else
                    stroke(255, 0, 0);
                line(characterX[i]-2+camPosX, characterY[i] + playerHeight/2+camPosY, characterX[i]-8+camPosX, characterY[i] + playerHeight/2+camPosY);
                fill(255);
            }
        }
    }
    if(menu == 7) {
        float _temp = zoomLevel;
        scale(1 / (1+_temp/20));
    }
}

boolean findPath(int characterID,int x,int y)
{
    //println(guardID+":"+x+":"+y+"  "+characterX[guardID] + ":"+characterY[guardID]);
    boolean arrived = false;
    if(characterX[characterID] >= x-(60 / frameRate + 2) && characterX[characterID] <= x + (60 / frameRate + 2) && characterY[characterID] >= Y - (60 / frameRate + 2) && characterY[characterID] <= y + (60 / frameRate + 2))
        arrived = true;
    else {
        if(characterX[characterID] < x - (60 / frameRate + 2) && moveCharacter(characterID, 3)) {
        } else if(characterX[characterID] > x + (60 / frameRate + 2) && moveCharacter(characterID, 2)) {
        } else if(characterY[characterID] < y - (60 / frameRate + 2) && moveCharacter(characterID, 1)) {
        } else if(characterY[characterID] > y + (60 / frameRate + 2) && moveCharacter(characterID, 0)) {
        } else {
            arrived = true;
        }
    }
    return arrived;
}

boolean moveCharacter(int characterID,int direction)
{
    boolean u = true,d = true,l = true,r = true;
    boolean returned = false;
    for(int i = 0 ; i <= nbOfObjects ; i++) {
        boolean flag = false;
        if(objects[i] != 0)
            for(int j = 0 ; j < upperObjects.length ; j++)
                if(objects[i] == solidObjectsChars[j])
                    flag = true;
        if(flag) {
            if (characterY[characterID] + 48 >= posObjectY[i] * 16 && characterY[characterID] + 32 <= posObjectY[i] * 16 && characterX[characterID] + 3 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= characterX[characterID] + 28)
              d = false;
            if (characterY[characterID] + 32 >= posObjectY[i] * 16 && characterY[characterID] + 16 <= posObjectY[i] * 16 && characterX[characterID] + 3 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= characterX[characterID] + 28)
              u = false;
            if (characterY[characterID] + 47 >= posObjectY[i] * 16 && characterY[characterID] + 17 <= posObjectY[i] * 16 && characterX[characterID] + 2 <= posObjectX[i] * 16 && posObjectX[i] * 16 <= characterX[characterID] + 28)
              l = false;
            if (characterY[characterID] + 47 >= posObjectY[i] * 16 && characterY[characterID] + 17 <= posObjectY[i] * 16 && characterX[characterID] <= posObjectX[i] * 16-18 && characterX[characterID] >= posObjectX[i] * 16-30)
              r = false;
        }
    }
    if(characters[characterID]) {
        if (characterY[characterID] + 34 >= playerY +16 && characterY[characterID] + 16 <= playerY +16 && characterX[characterID] + 3 <= playerX +16 && playerX +16 <= characterX[characterID] + 28)
            d = false;
        if (characterY[characterID] + 16 >= playerY +16 && characterY[characterID] <= playerY +16 && characterX[characterID] + 3 <= playerX +16 && playerX +16 <= characterX[characterID] + 28)
            u = false;
        if (characterY[characterID] + 33 >= playerY +16 && characterY[characterID] + 1 <= playerY +16 && characterX[characterID] + 2 <= playerX +16 && playerX +16 <= characterX[characterID] + 28)
            l = false;
        if (characterY[characterID] + 33 >= playerY +16 && characterY[characterID] + 1 <= playerY +16 && characterX[characterID] <= playerX +16-18 && characterX[characterID] >= playerX +16-30)
            r = false;
    }
    characterDir[characterID] = direction;
    switch(characterDir[characterID]) {
    case (0): 
        if(u) {
            characterY[characterID] --;
            returned = true;
        }
        break;
    case (1): 
        if(d) {
            characterY[characterID] ++;
            returned = true;
        }
        break;
    case (2): 
        if(l) {
            characterX[characterID] --;
            returned = true;
        }
        break;
    case (3): 
        if(r) {
          characterX[characterID] ++;
            returned = true;
        }
        break;
    }
    characterStatus[characterID] = 1;
    characterMovingBuffer[characterID]++;
    characterStatusBuffer[characterID] = 0;
    return returned;
}