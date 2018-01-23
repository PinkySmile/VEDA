boolean compareStrings(String a , String b)
{
    boolean same = true;

    try {
        if(a == null && b == null)
            same = true;
        else if(a == null || b == null)
            same = false;
        else
            if(a.length() != b.length())
                same = false;
            else
                for(int i = 0 ; i < a.length() ; i++)
                    if(a.charAt(i) != b.charAt(i))
                        same = false;
    } catch(Exception e) {
        e.printStackTrace();
        error("Error 17",e);
    }
    return same;
}

int getWidth(String string)
{
    int _temp = 0;
    for(int i = 0 ; i < string.length() ; i++) {
        _temp = _temp + string.charAt(i);
        char z = 'a';
    }
    return _temp;
}

String subString(String toSub, int start, int end)
{
    String toReturn = "";
    try {
        for(int i = start ; i <= end ; i++)
            toReturn = toReturn + toSub.charAt(i);
    } catch(Exception e) {}
    return toReturn;
}