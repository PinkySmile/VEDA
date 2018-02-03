//*****************************************Affichage d'une erreur*********************************************
void errorMsg(String errorMessage,AudioPlayer sound,Exception exc)
{
    String[] _temp = loadStrings("errors.log");
    output = createWriter("errors.log");
    fatalError = false;
    theErrorMessage = "[ERROR] : " + errorMessage;
    if(exc != null) {
        theErrorMessage = theErrorMessage + " :   "+exc+"\n";
        for(int i = 0 ; i < exc.getStackTrace().length ; i++)
            theErrorMessage = theErrorMessage + "        "+exc.getStackTrace()[i] + "\n";
    } else {
        theErrorMessage = theErrorMessage + ""+"\n";
    }
    if (output != null) {
        for(int i = 0 ; _temp != null && i < _temp.length ; i++)
            output.println(_temp[i]);
        output.print("["+transformInt(day(), 2)+"/"+transformInt(month(), 2)+"/"+transformInt(year(), 2)+"]["+transformInt(hour(), 2)+":"+transformInt(minute(), 2)+":"+transformInt(second(), 2)+"] "+theErrorMessage);
        output.flush();
        output.close();
    }
    try {
        Music.pause();
        Musics[4].pause();
    } catch(Exception e) {}
    if(sound != null) {
        sound.rewind();
        sound.play();
    }
    if(errorBuffer > 500)
        errorBuffer = 0;
    else if(errorBuffer > 150)
        errorBuffer = 150;
    //JOptionPane.showMessageDialog(null, "[ERROR] : "+errorMessage, "Error" , 2);
}

//*****************************************Affichage d'une erreur ramenant au menu principal*********************************************
void error(String errorMessage, Exception exc){
    String[] _temp = loadStrings("../errors.log");
    output = createWriter("errors.log");
    try {
        Music.pause();
        Musics[4].pause();
    } catch(Exception e) {}
    if(SFX[1] != null) {
        SFX[1].rewind();
        SFX[1].play();
    }
    fatalError = true;
    if(errorBuffer > 500)
        errorBuffer = 0;
    else if(errorBuffer > 150)
        errorBuffer = 150;
    theErrorMessage = "[FATAL] : " + errorMessage;
    try {
        for(int i = 0 ; i < _temp.length ; i ++)
            output.println(_temp[i]);
    } catch(Exception e) {}
    if(exc != null) {
        theErrorMessage = theErrorMessage + "\n"+exc+"\n";
        for(int i = 0 ; i < exc.getStackTrace().length ; i++)
            theErrorMessage = theErrorMessage + "        "+exc.getStackTrace()[i] + "\n";
    } else
        theErrorMessage = theErrorMessage + ""+"\n";
    try {
    output.print("["+transformInt(day(), 2)+"/"+transformInt(month(), 2)+"/"+transformInt(year(), 2)+"]["+transformInt(hour(), 2)+":"+transformInt(minute(), 2)+":"+transformInt(second(), 2)+"] "+theErrorMessage);
    output.flush();
    output.close();
    } catch(Exception e) {}
    //JOptionPane.showMessageDialog(null, "[FATAL] : "+errorMessage+"\n\nSwitching back to main menu", "Error" , JOptionPane.ERROR_MESSAGE);
    menu = -1;
}