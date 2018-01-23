String serverData = "";

public class Multiplayer extends Thread {

    public String getData()
    {
        String toReturn = null;
        try {
            toReturn = din.readLine();
        } catch(Exception e) {
            if(menu >= 10) {
                errorMsg("La connexion a été interompue",SFX[1],e);
                menu = -1;
            }
        }
        return toReturn;
    }
    
    public Multiplayer(String name)
    {
        super(name);
        this.start();
    }
   
   
    public void run()
    {
        while(true)
            serverData = getData();
    }
}

String transformInt(int number,int nmberOfChars)
{
    String result = "";
    result = number+"";
    while(result.length() < nmberOfChars)
        result = "0"+result;
    return result;
}

String transformFloat(float number,int nmberOfChars)
{
    String result = "";
    String buffer = "";
    result = number+"";
    while(result.length() < nmberOfChars)
        result = "0"+result;
    if(result.length() > nmberOfChars) {
        for(int i = 0 ; i < nmberOfChars ; i++)
            buffer = buffer + result.charAt(i);
        result = buffer;
    }
    return result;
}