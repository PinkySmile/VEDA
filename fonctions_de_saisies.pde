import javax.swing.* ; // cela importe la bibliothèque « javax.swing » des boites de dialogues

//fonction pour lire un entier saisi au clavier
int lireUnEntier(String message,String title)
{
    String realMessage = message;
    boolean chiffre = false;
    int nombre = 0;
    while(!chiffre) {
        String s =(String)JOptionPane.showInputDialog(null , realMessage , title , JOptionPane.OK_OPTION);
        try {
            nombre =Integer.parseInt(s) ; // On déclare la variable « nombre » et on y met la valeur de s en tant que nombre entier
            chiffre = true;
        } catch(Exception e) {
            chiffre = false;
            realMessage = "Ceci n'est pas un entier.\n\n" + message;
        }
    }
    return nombre;
}

//fonction pour lire un décimal saisi au clavier
float lireUnReel(String message,String title)
{
    String realMessage = message;
    boolean chiffre = false;
    float nombre = 0;
    while(!chiffre) {
        String s =(String)JOptionPane.showInputDialog(null , realMessage , title , JOptionPane.PLAIN_MESSAGE);
        try {
            nombre =Float.parseFloat(s) ; // On déclare la variable « nombre » et on y met la valeur de s
            chiffre = true;
        } catch(Exception e) {
            chiffre = false;
            realMessage = "Ceci n'est pas un réel.\n\n" + message;
        }
    }
    return nombre;
}

//fonction pour lire une chaîne de caractères saisie au clavier
String lireUnTexte(String message,String title)
{
    String s =(String)JOptionPane.showInputDialog(null , message , title , JOptionPane.PLAIN_MESSAGE);
    return s;
}

Boolean lireUnBooleen(String message,String title)
{
    int s =(int)JOptionPane.showOptionDialog(null , message, title, JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null);
    Boolean nombre ;  
    if (s == JOptionPane.YES_OPTION) {
        nombre = true;
    } else {
        nombre = false;
    }
    return nombre;
}