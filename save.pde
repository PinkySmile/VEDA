public class saveEverything extends Thread {
    boolean game;
    boolean ch;
    boolean ach;
    int boxType;
    
    public saveEverything(boolean c,boolean g,boolean a)
    {
        super("Popup");
        game = g;
        ch = c;
        ach = a;
        this.start();
    }
   
    public void run()
    {
        if(game)
            saveGame();
        if(ch)
            saveCharactersState();
        if(ach)
            saveAchievementsGot();
    }
}