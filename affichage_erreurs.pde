//*****************************************Affichage d'une erreur*********************************************
void errorMsg(String errorMessage,AudioPlayer sound,Exception exc)
{
    String[] _temp = loadStrings("errors.log");
    output = createWriter("errors.log");
    fatalError = false;
    theErrorMessage = "[ERROR] : "+errorMessage;
    try {
        for(int i = 0 ; i < _temp.length ; i ++)
            output.println(_temp[i]);
    } catch(Exception e) {}
    if(exc != null) {
        theErrorMessage = theErrorMessage + " :   "+exc+"\n";
        for(int i = 0 ; i < exc.getStackTrace().length ; i++)
            theErrorMessage = theErrorMessage + "        "+exc.getStackTrace()[i]+"\n";
    } else {
        theErrorMessage = theErrorMessage + ""+"\n";
    }
    output.print("["+transformInt(day(),2)+"/"+transformInt(month(),2)+"/"+transformInt(year(),2)+"]["+transformInt(hour(),2)+":"+transformInt(minute(),2)+":"+transformInt(second(),2)+"] "+theErrorMessage);
    output.flush();
    output.close();
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
            theErrorMessage = theErrorMessage + "        "+exc.getStackTrace()[i]+"\n";
    } else
        theErrorMessage = theErrorMessage + ""+"\n";
    output.print("["+transformInt(day(),2)+"/"+transformInt(month(),2)+"/"+transformInt(year(),2)+"]["+transformInt(hour(),2)+":"+transformInt(minute(),2)+":"+transformInt(second(),2)+"] "+theErrorMessage);
    output.flush();
    output.close();
    //JOptionPane.showMessageDialog(null, "[FATAL] : "+errorMessage+"\n\nSwitching back to main menu", "Error" , JOptionPane.ERROR_MESSAGE);
    menu = -1;
}

public class Error extends Thread
{
  String errorMessage;
  boolean crash;
  String[] button;
  
  public Error(String errorMessagse, boolean toCrash, String[] buttons)
  {
      super(name);
      errorMessage = errorMessagse;
      crash = toCrash;
      button = buttons;
      this.start();
  }
 
 
  public void run()
  {
      if(SFX[1] != null) {
          SFX[1].rewind();
          SFX[1].play();
      }
      if(crash)
          errorMessage = errorMessage+"\n\nThis program will now exit";
      JOptionPane.showOptionDialog(null, "[FATAL] : "+errorMessage, "Error" , JOptionPane.ERROR_MESSAGE, JOptionPane.OK_OPTION, null, button, "default");
      if(crash)
          System.exit(0);
  }
}