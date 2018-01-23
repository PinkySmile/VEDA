public class popUp extends Thread {
    String boxTitle;
    String boxContent;
    int boxType;
    
    public popUp(String content,String title,int type,AudioPlayer sound)
    {
        super("popUp");
        boxTitle = title;
        boxContent = content;
        boxType = type;
        sound.rewind();
        sound.play();
        this.start();
    }
   
   
    public void run()
    {
        JOptionPane.showMessageDialog(null , boxContent , boxTitle , boxType);
    }
}