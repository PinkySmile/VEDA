String[] getVar(String file_content)
{
    String[] return_values = {"", ""};
    int i = 0;
    boolean q = false;
    
    for (; q || (int(file_content.charAt(i)) >= int('a') && int(file_content.charAt(i)) <= int('z')) ||
           (int(file_content.charAt(i)) >= int('A') && int(file_content.charAt(i)) <= int('Z')) ||
           (int(file_content.charAt(i)) >= int('0') && int(file_content.charAt(i)) <= int('9')) ||
           file_content.charAt(i) == '"' || file_content.charAt(i) == '_' || file_content.charAt(i) == '-' || file_content.charAt(i) == '+'; i++)
        if (file_content.charAt(i) == '"')
            q = !q;
    if (file_content.charAt(0) == '=' || file_content.charAt(0) == '{' || file_content.charAt(0) == '}' || file_content.charAt(0) == ',') {
        return_values[0] = str(file_content.charAt(i));
        return_values[1] = subString(file_content, 1, file_content.length() - 1);
    } else {
        return_values[0] = subString(file_content, 0, i - 1);
        return_values[1] = subString(file_content, i, file_content.length() - 1);
    }
    return (return_values);
}

String deleteSpaces(String file_content)
{
    String result = "";
    char current_char = 0;
    boolean q = false;

    for (int i = 0; i < file_content.length(); i++) {
        current_char = file_content.charAt(i);
        if (current_char == '"')
            q = !q;
        if (q || current_char != ' ' && current_char != '\t' && current_char != '\n')
            result += current_char;
    }
    return (result);
}

String getType(String value)
{
    boolean is_int = true;

    if (value.charAt(0) == '"' || value.charAt(value.length() - 1) == '"') {
        if (value.charAt(0) == '"' && value.charAt(value.length() - 1) == '"')
            return ("String");
        return ("Unfinished string");
    }
    if (value.charAt(0) == '\'' || value.charAt(value.length() - 1) == '\'') {
        if (value.charAt(0) == '\'' && value.charAt(2) == '\'')
            return ("Char");
        return ("Unfinished char");
    }
    for (int i = 0; i < value.length(); i++)
        if ((value.charAt(i) > '9' || value.charAt(i) < '0') && value.charAt(i) != '-' && value.charAt(i) != '+') {
            is_int = false;
            break;
        }
    if (is_int)
        return ("Int");
    return ("Variable");
}

String clean(String str)
{
    if (str != null) {
        if (str.charAt(0) == '"')
            str = subString(str, 1, str.length() - 1);
        if (str.charAt(str.length() - 1) == '"')
            str = subString(str, 0, str.length() - 2);
    }
    return (str);
}

int parseFile(String file_content)
{
    int      id = 0;
    String   name = null;
    String   type = null;
    int      life = 0;
    int      texture = 0;
    int      battle = 0;
    int      x = 0;
    int      y = 0;
    int      attack = 0;
    int      resistance = 0;
    int      pw_ID = 0;
    int      bracket = 0;
    int      weapon_ID = 0;
    String[] array = {"", file_content};
    boolean  assigned = false;
    boolean  charac = false;
    String   currentVar = "";

    array[1] = deleteSpaces(array[1]);
    while (array[1].length() > 0) {
        array = getVar(array[1]);
        println("Found : " + array[0]);
        if (compareStrings(array[0], "characters"))
            charac = true;
        if (compareStrings(array[0], "=")) {
            if (assigned) {
                println("Missing ',' in array declaration");
                errorMsg("Error while loading characters' file : Missing ',' in array declaration", SFX[1], null);
                return (-1);
            }
            assigned = true;
            array = getVar(array[1]);
            println("Assigned : " + array[0]);
            if (compareStrings(array[0], "}")) {
                println("Bracket mismatched (Unexpected closed bracket)");
                errorMsg("Error while loading characters' file : Unexpected closed bracket", SFX[1], null);
                return (-1);
            }
            if (!compareStrings(array[0], "{") && charac && bracket != 2) {
                println("Bad type for \"characters\". Expected Character[].");
                errorMsg("Error while loading characters' file : Bad type for \"characters\". Expected Character[].", SFX[1], null);
                return (-1);
            }
            if (charac && bracket == 2)
                switch (currentVar) {
                case "id":
                    if (getType(array[0]) == "Int")
                        id = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "name":
                    if (getType(array[0]) == "String")
                        name = array[0];
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected String  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected String", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "type":
                    if (getType(array[0]) == "String")
                        type = array[0];
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected String  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected String", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "base_life":
                    if (getType(array[0]) == "Int")
                        life = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "battle_type":
                    if (getType(array[0]) == "Int")
                        battle = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "sprite_id":
                    if (getType(array[0]) == "Int")
                        texture = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "x_pos":
                    if (getType(array[0]) == "Int")
                        x = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "y_pos":
                    if (getType(array[0]) == "Int")
                        y = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "attack":
                    if (getType(array[0]) == "Int")
                        attack = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "resistance":
                    if (getType(array[0]) == "Int")
                        resistance = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                case "power_id":
                    if (getType(array[0]) == "Int")
                        pw_ID = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                case "weapon_id":
                    if (getType(array[0]) == "Int")
                        weapon_ID = int(array[0]);
                    else {
                        println("Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int  (" + array[0] + ")");
                        errorMsg("Error while loading characters' file : Bad type for " + currentVar + ". Got " + getType(array[0]) + " but expected Int", SFX[1], null);
                        return (-1);
                    }
                    break;
                default:
                    println("No field " + currentVar + " for characters");
                    errorMsg("Error while loading characters' file : No field " + currentVar + " for characters", SFX[1], null);
                    return (-1);
                }
        } else {
            assigned = false;
            currentVar = array[0];
        }
        if (compareStrings(array[0], "{")) {
            bracket++;
            currentVar = "";
        } else if (compareStrings(array[0], "}")) {
            bracket--;
            if (bracket == 1 && charac) {
                if (texture <= -1 || texture >= maxNbOfCharacters) {
                    println("Invalid or not set texture ID '" + texture + "'");
                    errorMsg("Error while loading characters' file : Invalid or not set texture ID '" + texture + "'", SFX[1], null);
                } else if (id <= -1 || id >= maxNbOfCharacters) {
                    println("Invalid or not set character ID '" + id + "'");
                    errorMsg("Error while loading characters' file : Invalid or not set character ID '" + id + "'", SFX[1], null);
                } else {
                    println("Creating character " + id, name, type, life, texture, battle, x, y, attack, resistance, pw_ID, weapon_ID);
                    characters[id] = true;
                    characterName[id] = clean(name);
                    characterType[id] = clean(type);
                    characterLife[id] = life;
                    characterTextureNames[id] = texture;
                    characterBattleID[id] = battle;
                    characterX[id] = x;
                    characterY[id] = y;
                    characterAttack[id] = attack;
                    characterResistance[id] = resistance;
                    characterPowerID[id] = pw_ID;
                    characterWeaponID[id] = weapon_ID;
                }
                id = -1;
                name = null;
                type = null;
                life = 0;
                texture = -1;
                battle = 0;
                x = 0;
                y = 0;
                attack = 0;
                resistance = 0;
                pw_ID = 0;
                weapon_ID = 0;
            }
            if (bracket == 0)
                charac = false;
            currentVar = "";
        }
        if (bracket < 0) {
            println("Bracket mismatched (Missing opened bracket)");
            errorMsg("Error while loading characters' file : Missing opened bracket", SFX[1], null);
            return (-1);
        }
    }
    if (bracket != 0) {
        println("Bracket mismatched (missing closed bracket) "+bracket);
        errorMsg("Error while loading characters' file : missing closed bracket", SFX[1], null);
        return (-1);
    }
    return (0);
}