void saveLevel() {
    try {
        output = createWriter(levelPath +"/level/floor0.lvl");
        output.print(background+"\n");
        for(int i = 0 ; i < nbOfObjects ; i++)
            if(objects[i] != 0)
                output.print(objects[i] + "\n"+posObjectX[i] + "\n"+posObjectY[i] + "\n");
        output.flush();
        output.close();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Unhandled exception occured while saving this level",SFX[1],e);
    }
}

void saveCharacters(String theLevelPath) {
    println("saving characters");
    try {
        String dirName = theLevelPath + "/level";
        output = createWriter(dirName + "/characters.chr");
        output.print("characters = {");
        for(int i = 0 ; i < characters.length ; i++)
            if(characters[i]) {
                output.print("\n\t{");
                output.print("\n\t\tid = " + i + ",");
                output.print("\n\t\tname = \"" + characterName[i] + "\",");
                output.print("\n\t\ttype = \"" + characterType[i] + "\",");
                output.print("\n\t\tbase_life = " + characterLife[i] + ",");
                output.print("\n\t\tsprite_id = " + characterTextureNames[i] + ",");
                if (!compareStrings(characterType[i], "ALLY"))
                    output.print("\n\t\tbattle_type = " + characterBattleID[i] + ",");
                output.print("\n\t\tx_pos = " + characterX[i] + ",");
                output.print("\n\t\ty_pos = " + characterY[i] + ",");
                output.print("\n\t\tattack = " + characterAttack[i] + ",");
                output.print("\n\t\tresistance = " + characterResistance[i] + ",");
                if (characterPowerID[i] >= 0) {
                    output.print("\n\t\tpower_id = " + characterPowerID[i] + ",");
                }
                if (characterWeaponID[i] >= 0) {
                    output.print("\n\t\tweapon_id = " + characterWeaponID[i]);
                }
                output.print("\n\t},");
            }
        output.print("\n}");
        output.flush();
        output.close();
    } catch(Exception e) {
        e.printStackTrace();
        errorMsg("Unhandled exception occured while saving this level",SFX[1],e);
    } 
}