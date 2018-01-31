public class Popup extends Thread {
    String boxTitle;
    String boxContent;
    int boxType;
    
    public Popup(String content, String title, int type, AudioPlayer sound)
    {
        super("Popup");
        boxTitle = title;
        boxContent = content;
        boxType = type;
        if (sound != null) {
            sound.rewind();
            sound.play();
        }
        this.start();
    }
   
   
    public void run()
    {
        JOptionPane.showMessageDialog(null , boxContent , boxTitle , boxType);
    }
}