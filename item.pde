class Item {
    int id;
    int ability;
    int[] damages = new int[6];
    float[] resistances = new float[6];
    float durability;
    String name;
    String type;
}

Item copyItemObject(Item itemObj)
{
    Item copy = null;

    if (itemObj != null) {
        copy = new Item();
        copy.id = itemObj.id;
        copy.name = itemObj.name;
        copy.durability = itemObj.durability;
        copy.type = itemObj.type;
        copy.ability = itemObj.ability;
        for (int i = 0; i < 6; i++) {
            copy.damages[i] = itemObj.damages[i];
            copy.resistances[i] = itemObj.resistances[i];
        }
    }
    return (copy);
}