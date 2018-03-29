//<>// æ®†•“‘¶«¡ø—–Ø»å’”„Æ‚™ªŒ∏‰ﬂﬁƒ·∂∆∑‡Ω‹›≈⁄©¢◊√ß∫~ı∞…•÷≠±💪🏻👀👄🐌//<>//█▓
//Importation des librairies {} 
import java.util.Map;
import ddf.minim.*;
import java.io.*;
import java.nio.file.*;
import javax.swing.*;
import java.net.*;
import java.awt.Desktop;
import java.awt.Graphics;

//credits : "Trophy Cups Pixel Pack" by Vsio NeithR

//MenuMusic.setGain(exp(musicVolume*log(41)/100)-41);
//menus (-12 : blue screen , -11 : nyan cat , -2 : Unix, -1 : menu principal , 0 : jeu , 1 : gameover , 2 : inventaire , 3 : options , 4 : Options générales , 5 : Audio , 6 : Langue , 7 : lvlcreator , 8 : menu des objets , 9 : menu des personnages , 10 : achievements , 11 : battle , 12 : Controles)

//****************************************************************************
//Déclaration des variables
int[] upperObjects = {
    18,
    19,
    29,
    30,
    31
};

int[] solidObjectsPlayer = {
    1,
    14,
    27,
    20,
    0
};

int[] solidObjectsChars = {
    1,
    13,
    27,
    20,
    5
};

int[] hitboxType = {
    0,
    0,
    0,
    2,
    0
};

int[] baseGain = {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int maxNbOfCharacters = 200;
int maxNbOfAchievement = 100;
int maxNbOfObjectsPerLevel = 50000;
int maxNbOfDialogs = 50;
int maxMovingAnimations;
PImage blue_sky = null;
PImage gameover = null;
PImage gameover_font = null;
PImage life_image = null;
PImage bugRed;
PImage bugImage;
PImage energy_image = null;
PImage bug = null;
PImage glitched_texture = null;
PImage youtube = null;
PImage menuBackground = null;
PImage inventoryFrame = null;
PImage xywt = null;
PImage bsod = null;
PImage achievementFrame;
PImage yololelo;
PImage godEater;
PImage troll;
PImage glitched_character;
PImage achievementButtonImage;
PImage locked;
PImage redCross;
PImage item_glitch;
PImage[] trophys = new PImage[4];
PImage[] achievementImage = new PImage[20000];
PImage[] itemSprites = new PImage[100];
PImage[] textures = new PImage[2000];
PImage[][] hearts = new PImage[3][11];
PImage[][] thunderbolts= new PImage[3][11];
PImage[][][][] character_image = new PImage[2][2][4][2];
PImage[][][][] characterTextures = new PImage[maxNbOfCharacters][2][4][2];
PImage[][][][][] armorTextures = new PImage[100][2][2][4][2];
String direction = "up";
String character = "male";
String status = "static";
String textTyped = "";
String oldCommands = "";
String cursor = "";
String version = "";
String music = "Mysterious";
String language = "en";
String name = "";
String dialogText;
String lang;
String item;
String quan;
String classicPrompt = "> ";
String prompt = "> ";
String dialogPrinted;
String levelPath;
String godEaterMode;
String godEaterPath;
String title = "VEDA";
String theErrorMessage;
String background;
String levelToLoad;
String currentPath = "/";
String username = null;
String[] languagesFound = new String[50];
String[] cutscenesCommands = new String[2000];
String[] keyUsage = new String[20];

String[] damagesName = {
    "Fire",
    "Sharp",
    "Pierce",
    "Impact",
    "Poison",
    "Electricity"
};

String[] trollFiles = 
{
    "data/misc/none.png", 
    "data/misc/sqrt(-1).png", 
    "data/misc/sqrt(-2).png", 
    "data/fonts/Wingdings-Regular-48.vlw", 
    "data/misc/OMG.png", 
    "levels/What have you done !.lvl",
    "lib/Simon.dll", 
    "lib/unix.dll", 
    "misc/{4FTSZ-ZE67D8}"
};

/*String[] filesToLoad = 
{
    //Achievements
    "data/achievements/0h.png", 
    "data/achievements/achievements_en.txt",
    "data/achievements/achievements_fr.txt",
    "data/achievements/'-'.png",
    "data/achievements/bronze_trophy_24x24_1.png",
    "data/achievements/gold_trophy_24x24_1.png",
    "data/achievements/locked.png",
    "data/achievements/peace.png",
    "data/achievements/silhoutte_trophy_1_24x24.png",
    "data/achievements/silver_trophy_24x24_1.png",
    "data/achievements/sword.png",
  
    //Polices
    "data/fonts/ArialMT-48.vlw", 
    "data/fonts/BodoniOrnamentsITCTT-48.vlw", 
    "data/fonts/Cracked-48.vlw", 
    "data/fonts/FinaleAlphaNotes-48.vlw", 
    "data/fonts/FinaleMallets-48.vlw", 
    "data/fonts/Jazz-48.vlw", 
    "data/fonts/MesquiteStd-48.vlw", 
    "data/fonts/Parchment-Regular-48.vlw", 
  
    //Levels
    "levels/test.lvl", 
    "levels/test.chr", 
  
    //godEater
    "data/godEater", 
    "data/godEater/godEater.ico", 
    "data/godEater/godEater.png", 
    "data/godEater/godEater.exe", 
    "data/godEater/mode.txt", 
  
    //Textures
    "data/misc/bug.png", 
    "data/misc/achievement_box.png", 
    "data/misc/dialog_box.png", 
    "data/misc/background.png", 
    "data/misc/youtube.png", 
  
    //Game over
    "data/misc/gameover.png", 
    "data/misc/gameover_font.png", 
  
    //Texture de la vie
    "data/lifeBar/heart_1.1.png", 
    "data/lifeBar/heart_2.1.png", 
    "data/lifeBar/heart_3.1.png", 
    "data/lifeBar/heart_4.1.png", 
    "data/lifeBar/heart_5.1.png", 
    "data/lifeBar/heart_6.1.png", 
    "data/lifeBar/heart_7.1.png", 
    "data/lifeBar/heart_8.1.png", 
    "data/lifeBar/heart_9.1.png", 
    "data/lifeBar/heart_10.1.png", 
    "data/lifeBar/heart_border1.png", 
    "data/lifeBar/heart_1.2.png", 
    "data/lifeBar/heart_2.2.png", 
    "data/lifeBar/heart_3.2.png", 
    "data/lifeBar/heart_4.2.png", 
    "data/lifeBar/heart_5.2.png", 
    "data/lifeBar/heart_6.2.png", 
    "data/lifeBar/heart_7.2.png", 
    "data/lifeBar/heart_8.2.png", 
    "data/lifeBar/heart_9.2.png", 
    "data/lifeBar/heart_10.2.png", 
    "data/lifeBar/heart_border2.png", 
    "data/lifeBar/heart_1.3.png", 
    "data/lifeBar/heart_2.3.png", 
    "data/lifeBar/heart_3.3.png", 
    "data/lifeBar/heart_4.3.png", 
    "data/lifeBar/heart_5.3.png", 
    "data/lifeBar/heart_6.3.png", 
    "data/lifeBar/heart_7.3.png", 
    "data/lifeBar/heart_8.3.png", 
    "data/lifeBar/heart_9.3.png", 
    "data/lifeBar/heart_10.3.png", 
    "data/lifeBar/heart_border3.png", 
  
    //Texture de l'énergie
    "data/NRJBar/thunderbolt_1.1.png", 
    "data/NRJBar/thunderbolt_2.1.png", 
    "data/NRJBar/thunderbolt_3.1.png", 
    "data/NRJBar/thunderbolt_4.1.png", 
    "data/NRJBar/thunderbolt_5.1.png", 
    "data/NRJBar/thunderbolt_6.1.png", 
    "data/NRJBar/thunderbolt_7.1.png", 
    "data/NRJBar/thunderbolt_8.1.png", 
    "data/NRJBar/thunderbolt_9.1.png", 
    "data/NRJBar/thunderbolt_10.1.png", 
    "data/NRJBar/thunderbolt_border1.png", 
    "data/NRJBar/thunderbolt_1.2.png", 
    "data/NRJBar/thunderbolt_2.2.png", 
    "data/NRJBar/thunderbolt_3.2.png", 
    "data/NRJBar/thunderbolt_4.2.png", 
    "data/NRJBar/thunderbolt_5.2.png", 
    "data/NRJBar/thunderbolt_6.2.png", 
    "data/NRJBar/thunderbolt_7.2.png", 
    "data/NRJBar/thunderbolt_8.2.png", 
    "data/NRJBar/thunderbolt_9.2.png", 
    "data/NRJBar/thunderbolt_10.2.png", 
    "data/NRJBar/thunderbolt_border2.png", 
    "data/NRJBar/thunderbolt_1.3.png", 
    "data/NRJBar/thunderbolt_2.3.png", 
    "data/NRJBar/thunderbolt_3.3.png", 
    "data/NRJBar/thunderbolt_4.3.png", 
    "data/NRJBar/thunderbolt_5.3.png", 
    "data/NRJBar/thunderbolt_6.3.png", 
    "data/NRJBar/thunderbolt_7.3.png", 
    "data/NRJBar/thunderbolt_8.3.png", 
    "data/NRJBar/thunderbolt_9.3.png", 
    "data/NRJBar/thunderbolt_10.3.png", 
    "data/NRJBar/thunderbolt_border3.png", 
  
    //Fichiers son
    "data/sound/SFX/iron.mp3", 
    "data/sound/SFX/dirt1.wav", 
    "data/sound/SFX/dirt2.wav", 
    "data/sound/SFX/dirt3.wav", 
    "data/sound/SFX/dirt4.wav", 
    "data/sound/SFX/grass1.wav", 
    "data/sound/SFX/grass2.wav", 
    "data/sound/SFX/grass3.wav", 
    "data/sound/SFX/grass4.wav", 
    "data/sound/SFX/mud1.wav", 
    "data/sound/SFX/mud2.wav", 
    "data/sound/SFX/mud3.wav", 
    "data/sound/SFX/mud4.wav", 
    "data/sound/SFX/Error.mp3", 
    "data/sound/SFX/Exclamation.mp3", 
    
    //Musiques
    "data/sound/Musics/Macabre.mp3", 
    "data/sound/Musics/Mysterious.mp3", 
    "data/sound/Musics/Clavier.mp3", 
    "data/sound/Musics/EpicBattle_start.mp3", 
    "data/sound/Musics/EpicBattle_loop.wav", 
    "data/sound/Musics/eugrt_full.mp3", 
    "data/sound/Musics/eugrt_start.mp3", 
    "data/sound/Musics/eugrt_loop.mp3", 
    "data/sound/Musics/Puzzle.mp3", 
    "data/sound/Musics/Umlaut.mp3", 
  
    //Textures des personnages
    "data/characters/character_glitched.png", 
    "data/characters/male_character_death.png", 
    "data/characters/male_character_moving_down_1.png", 
    "data/characters/male_character_moving_down_2.png", 
    "data/characters/male_character_moving_up_1.png", 
    "data/characters/male_character_moving_up_2.png", 
    "data/characters/male_character_moving_right_1.png", 
    "data/characters/male_character_moving_right_2.png", 
    "data/characters/male_character_moving_left_2.png", 
    "data/characters/male_character_moving_left_1.png", 
    "data/characters/male_character_static_down_1.png", 
    "data/characters/male_character_static_up_1.png", 
    "data/characters/male_character_static_left_1.png", 
    "data/characters/male_character_static_right_1.png", 
    "data/characters/female_character_death.png", 
    "data/characters/female_character_moving_down_1.png", 
    "data/characters/female_character_moving_down_2.png", 
    "data/characters/female_character_moving_up_1.png", 
    "data/characters/female_character_moving_up_2.png", 
    "data/characters/female_character_moving_right_1.png", 
    "data/characters/female_character_moving_right_2.png", 
    "data/characters/female_character_moving_left_2.png", 
    "data/characters/female_character_moving_left_1.png", 
    "data/characters/female_character_static_down_1.png", 
    "data/characters/female_character_static_up_1.png", 
    "data/characters/female_character_static_left_1.png", 
    "data/characters/female_character_static_right_1.png", 
    "data/characters/0_character_death.png", 
    "data/characters/0_character_moving_down_1.png", 
    "data/characters/0_character_moving_down_2.png", 
    "data/characters/0_character_moving_up_1.png", 
    "data/characters/0_character_moving_up_2.png", 
    "data/characters/0_character_moving_right_1.png", 
    "data/characters/0_character_moving_right_2.png", 
    "data/characters/0_character_moving_left_2.png", 
    "data/characters/0_character_moving_left_1.png", 
    "data/characters/0_character_static_down_1.png", 
    "data/characters/0_character_static_up_1.png", 
    "data/characters/0_character_static_left_1.png", 
    "data/characters/0_character_static_right_1.png", 
    "data/characters/1_character_death.png", 
    "data/characters/1_character_moving_down_1.png", 
    "data/characters/1_character_moving_down_2.png", 
    "data/characters/1_character_moving_up_1.png", 
    "data/characters/1_character_moving_up_2.png", 
    "data/characters/1_character_moving_right_1.png", 
    "data/characters/1_character_moving_right_2.png", 
    "data/characters/1_character_moving_left_2.png", 
    "data/characters/1_character_moving_left_1.png", 
    "data/characters/1_character_static_down_1.png", 
    "data/characters/1_character_static_up_1.png", 
    "data/characters/1_character_static_left_1.png", 
    "data/characters/1_character_static_right_1.png", 
    "data/characters/2_character_moving_down_1.png", 
    "data/characters/2_character_moving_down_2.png", 
    "data/characters/2_character_moving_up_1.png", 
    "data/characters/2_character_moving_up_2.png", 
    "data/characters/2_character_moving_right_1.png", 
    "data/characters/2_character_moving_right_2.png", 
    "data/characters/2_character_moving_left_2.png", 
    "data/characters/2_character_moving_left_1.png", 
    "data/characters/2_character_static_down_1.png", 
    "data/characters/2_character_static_up_1.png", 
    "data/characters/2_character_static_left_1.png", 
    "data/characters/2_character_static_right_1.png", 
    "data/characters/3_character_moving_down_1.png", 
    "data/characters/3_character_moving_down_2.png", 
    "data/characters/3_character_moving_up_1.png", 
    "data/characters/3_character_moving_up_2.png", 
    "data/characters/3_character_moving_right_1.png", 
    "data/characters/3_character_moving_right_2.png", 
    "data/characters/3_character_moving_left_2.png", 
    "data/characters/3_character_moving_left_1.png", 
    "data/characters/3_character_static_down_1.png", 
    "data/characters/3_character_static_up_1.png", 
    "data/characters/3_character_static_left_1.png", 
    "data/characters/3_character_static_right_1.png", 
  
    //Textures d'objets
    "data/objects/glitch.png", 
    "data/objects/trigger.png", 
    "data/objects/music.png", 
    "data/objects/cutscene.png", 
    "data/objects/blue_sky.png", 
    "data/objects/texture_1.png", 
    "data/objects/texture_2.png", 
    "data/objects/texture_3.png", 
    "data/objects/texture_4.png", 
    "data/objects/texture_5.png", 
    "data/objects/texture_6.png", 
    "data/objects/texture_7.png", 
    "data/objects/texture_8.png", 
    "data/objects/texture_9.png", 
    "data/objects/texture_10.png", 
    "data/objects/texture_11.png",
    "data/objects/texture_12.png",
    "data/objects/texture_13.png",
    "data/objects/texture_14.png",
    "data/objects/texture_15.png",
    "data/objects/texture_16.png",
    "data/objects/texture_17.png",
    "data/objects/texture_18.png",
    "data/objects/texture_19.png",
    "data/objects/texture_20.png",
    "data/objects/texture_21.png",
    "data/objects/texture_22.png",
    "data/objects/texture_23.png",
    "data/objects/texture_24.png",
    "data/objects/texture_25.png",
    "data/objects/texture_26.png",
    "data/objects/texture_27.png",
    "data/objects/texture_28.png",
    "data/objects/texture_29.png",
    "data/objects/texture_30.png",
    "data/objects/texture_31.png",
    "data/objects/texture_32.png"
};*/
//String[] filesMissing = new String[filesToLoad.length];
String[] menuContent = new String[100];
String[] achievements = new String[maxNbOfAchievement];
String[] achievementsContent = new String[maxNbOfAchievement];
String[] answers = new String[4];
String[] itemNames = new String[100];
String[] characterName = new String[maxNbOfCharacters];
String[] characterType = new String[maxNbOfCharacters];
String[] characterPowerName = new String[maxNbOfCharacters];
String[] characterPowerDesc = new String[maxNbOfCharacters];
String[] characterWeaponName = new String[maxNbOfCharacters];
String[] commandLines;
String[][][] dialogs = new String[maxNbOfCharacters][maxNbOfDialogs][15];
int statusBuffer = 0;
int totalNumberOfMusics = 7;
int totalNumberOfMusicsLoaded;
int animation = 1;
int animationBuffer = 0;
int volume = 70;
int lifeMax = 1;
int lifeBuffer = 0;
int energyMax = 1;
int energyBuffer = 0;
int camPosX = 0;
int camPosY = 0;
int menu = -1;
int deathBuffer = 0;
int cursorBuffer = 0;
int numberOfMenu = 0;
int hitBuffer = 0;
int musicVolume = 100;
int SFXVolume = 100;
int nbOfMissingFiles;
int nameColor = 2;
int dialogLetters;
int achievementBuffer = 201;
int achievementY;
int nbOfObjects;
int selectedObject;
int a;
int currentButton = 0;
int progress;
int achiev;
int slot;
int yoloBuffer;
int imageSize;
int godEaterBuffer;
int delBuffer;
int errorBuffer = 501;
int errorPos = width;
int dialogID = 0;
int menuPosition;
int nbOfChars;
int dir;
int dirBuffer;
int stepSoundPriority;
int nbOfAchievementsLoaded;
int nbOfAchievementsGot;
int lastMenu;
int achievementMenuPos;
int dialogStart;
int battleType;
int energyReloadBuffer;
int sprintSpeed = 2;
int selectedAnswer;
int theDialogEnd;
int fightingCharacter = -1;
int dialogDeathBuffer;
int cutsceneCommandToExec;
int zoomLevel;
int savingBuffer;
int waitingTime = 0;
int commandID;
int cutsceneID;
int playerWidth;
int playerHeight;
int playTime;
int oldSecond;
int changingKey = -1;
int floor = 0;
int languagesNb = 0;
int inventoryPage = 0;
int selectedSlotInventory = 12;
int selectedAnswerInventory = 0;
int camBuffer[] = new int[2];
int battleBuffer[] = new int[0];
int dialogsVariante[] = new int[maxNbOfCharacters];
int theDialogID[] = new int[maxNbOfCharacters];
int chara[] = new int[3];
int objects[] = new int[maxNbOfObjectsPerLevel];
int cases[][] = new int[4][2];
int[] baseStatsResistance = new int[6];
int[] damageBuffer = new int[8];
int[] keys = {
    90,
    83,
    81,
    68,
    69,
    27,
    32,
    67,
    65,
    87,
    88,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    16
};
int[] pressedKeysCode = new int[40];
int[] cutsceneStart = new int[200];
int[] jpp = new int[50];
int[] jpp2 = new int[50];
int[] jpp3 = new int[50];
int[] jpp4 = new int[50];
int[] jpp5 = new int[50];
int[] jpp6 = new int[50];
int[] posObjectX = new int[maxNbOfObjectsPerLevel];
int[] posObjectY = new int[maxNbOfObjectsPerLevel];
int[] menuPos = new int[200];
int[] menuColor = new int[100];
int[] menuSize = new int[200];
int[] itemsQuantity = new int[12];
int[] characterX = new int[maxNbOfCharacters];
int[] characterY = new int[maxNbOfCharacters]; 
int[] characterDir = new int[maxNbOfCharacters];
int[] characterAnim = new int[maxNbOfCharacters];
int[] characterStatus = new int[maxNbOfCharacters];
int[] characterStatusBuffer = new int[maxNbOfCharacters];
int[] characterMovingBuffer = new int[maxNbOfCharacters];
int[] characterStaticBuffer = new int[maxNbOfCharacters];
int[] characterTextureNames = new int[maxNbOfCharacters];
int[] characterPointsBuffer = new int[maxNbOfCharacters];
int[] characterLife = new int[maxNbOfCharacters];
int[] characterBattleID = new int[maxNbOfCharacters];
int[] characterAttack = new int[maxNbOfCharacters];
int[] characterResistance = new int[maxNbOfCharacters];
int[] characterPowerID = new int[maxNbOfCharacters];
int[] characterWeaponID = new int[maxNbOfCharacters];
int[][] cutscenesArgs = new int[2000][10];
int[][] characterPointToGo = new int[maxNbOfCharacters][2];
boolean inDialog = false;
boolean up, down, right, left;
boolean deathAnimation = false;
boolean dead = false;
boolean musicDisabled = false;
boolean SFXDisabled = false;
boolean musicLoaded = false;
boolean debugMode = false;
boolean musicBuffer;
boolean glitchMode;
boolean delete;
boolean godEaterActive;
boolean fatalError;
boolean addingChar;
boolean dialogEnd;
boolean stickDialog;
boolean isAnswering;
boolean goInBattle;
boolean camMoving;
boolean buttonsDisabled;
boolean replaceMode;
boolean upperLayerShown = true;
boolean savedMessageShown;
boolean camScrollingDisabled = false;
boolean inCutscene;
boolean gridShown;
boolean pressedSFXBar;
boolean pressedMusicBar;
boolean errorDisplayed;
boolean shiftPressed;
boolean controlPressed;
boolean onWindows;
boolean gameoverDisplayed;
boolean inShell = true;
boolean selectedRespawn = true;
boolean displayAttack = false;
boolean choosingInInventory = false;
boolean showItemDetails = false;
boolean[] isGlitched = new boolean[maxNbOfObjectsPerLevel];
boolean[] characters = new boolean[maxNbOfCharacters];
boolean[] achievementsGot = new boolean[maxNbOfAchievement];
boolean[] menuDisabled = new boolean[100];
Minim minim;//libraries pour le son
AudioPlayer Music;
AudioPlayer mdrdbar;
AudioPlayer stepSound;
AudioPlayer[] SFX = new AudioPlayer[20];
AudioPlayer[] Musics = new AudioPlayer[20];
File file;
PFont Wingdings;
PFont Parchment;
PFont MesquiteStd;
PFont Jazz;
PFont FreeMono;
PFont FinaleMallets;
PFont FinaleAlphaNotes;
PFont Cracked;
PFont BodoniOrnamentsITCTT;
PFont Arial;
ServerSocket ss;
Socket s;
PrintWriter output;
PrintWriter dout;
BufferedReader din;
ImageIcon cd = null;
Graphics g;
float playerSpeed = 1;
float sprintScale = 2;
float sprintCost = 1;
float playerX = 1;
float playerY = 1;
float life = 10;
float energy = 10;
float[] damageDisplay = new float[8];
Item[] allItems = new Item[100];
Item[] wornItems = new Item[6];
Item[] items = new Item[12];

//***************************************************************************
//Initialisation
void setup()
{
    String path;

    Map<String, String> env = System.getenv();
    for (String envName : env.keySet()) {
        if (compareStrings(envName, "USER") || compareStrings(envName, "USERNAME")) {
            onWindows = compareStrings(envName, "USERNAME");
            username = env.get(envName);
        }
    }
    //try {
    //  Runtime.getRuntime().exec("<exe>", null, new File("."));
    //} catch(Exception e) {}
    surface.setTitle(title);
    minim = new Minim(this);
    up = true;
    down = true;
    left = true;
    right = true;
    frameRate(60);
    surface.setSize(640, 480);
    textSize(20);
    background(0);
    fill(255);
    errorPos = width;

    try {
        Music.close();
    } catch(Exception e) {}
    for(int i = 0; i <= SFX.length; i++) {
        try {
            SFX[i].close();
        } catch(Exception e) {}
    }
    for(int i = 0; i <= Musics.length; i++) {
        try {
            Musics[i].close();
        } catch(Exception e) {}
    }

    //Chargement des fichiers audios
    text("Loading", 220, 30);
    try {
        SFX[2] = minim.loadFile("sound/SFX/Exclamation.mp3");
        SFX[1] = minim.loadFile("sound/SFX/Error.mp3");
    }
    catch(Exception e) {
        e.printStackTrace();
    }
    //wornItems[0] = 0;
    /*//Verification des fichiers
    String message = "";
    int a = 0;
    for (int i = 0; i <= filesToLoad.length - 1; i = i + 1) {
        path = filesToLoad[i];
        file = new File(path);
        if (!file.exists() && a <= 11) {
            message = message + "The file \"" + Paths.get(path).toAbsolutePath() + "\" is missing.\n";
            a++;
            filesMissing[nbOfMissingFiles] = path;
            nbOfMissingFiles++;
        } else if (!file.exists() && a == 12) {
            a++;
            filesMissing[nbOfMissingFiles] = path;
            nbOfMissingFiles++;
        } else if(!file.exists()){
            filesMissing[nbOfMissingFiles] = path;
            nbOfMissingFiles++;
        }
    }
    if (a > 12)
        message = message + "[" + (nbOfMissingFiles - 12) + " more]\n";
    if (message != "") {
        if (SFX[2] != null) {
            SFX[2].rewind();
            SFX[2].play();
        }
        int answer = JOptionPane.showConfirmDialog(null, message + "\nThis may prevent the game from working well.\nDo you want to continue anyway ?",  "File missing", JOptionPane.YES_NO_OPTION, JOptionPane.ERROR_MESSAGE);
        if (answer == 1)
            System.exit(0);
    }*/

    //Chargement du fichier de version
    path = "data/version.txt";
    try {
        BufferedReader bufferedReader = createReader(path);
        version = bufferedReader.readLine();
        bufferedReader.close();
    }
    catch(FileNotFoundException e) {
        e.printStackTrace();
        errorMsg("File \"" + Paths.get(path).toAbsolutePath() + "\" is missing.", SFX[2], e);
    }
    catch(Exception e) {
        e.printStackTrace();
        errorMsg("", SFX[2], e);
    }

    godEaterMode = "car-antenne";
    path = "data/godEater/godEater.exe";
    file = new File(path);
    if (file.exists())
        godEaterActive = true;
    //Chargement de godEater et initialisation
    if (godEaterActive)
        try {
            path = "data/godEater/mode.txt";
            file = new File(path);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            godEaterMode = bufferedReader.readLine();
            bufferedReader.close();
            fileReader.close();
        }
        catch(FileNotFoundException e) {
            e.printStackTrace();
            try {
                path = "data/godEater/";
                file = new File(path);
                file.mkdirs();
                path = "data/godEater/mode.txt";
                file = new File(path);
                FileWriter fileWriter = new FileWriter(file);
                BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
                bufferedWriter.write(godEaterMode);
                bufferedWriter.close();
                fileWriter.close();
            }
            catch(IOException f) {
                f.printStackTrace();
            }
        }
        catch(Exception e) {
            e.printStackTrace();
            errorMsg("", SFX[2], e);
        }

    file = new File(sketchPath("data/fonts/Wingdings-Regular-48.vlw"));
    if (file.exists())
        Wingdings = loadFont("fonts/Wingdings-Regular-48.vlw");
  
    file = new File(sketchPath("data/fonts/Parchment-Regular-48.vlw"));
    if (file.exists())
        Parchment = loadFont("fonts/Parchment-Regular-48.vlw");
  
    file = new File(sketchPath("data/fonts/MesquiteStd-48.vlw"));
    if (file.exists())
        MesquiteStd = loadFont("fonts/MesquiteStd-48.vlw");
  
    file = new File(sketchPath("data/fonts/Jazz-48.vlw"));
    if (file.exists())
        Jazz = loadFont("fonts/Jazz-48.vlw");
  
    file = new File(sketchPath("data/fonts/FinaleMallets-48.vlw"));
    if (file.exists())
        FinaleMallets = loadFont("fonts/FinaleMallets-48.vlw");
  
    file = new File(sketchPath("data/fonts/FinaleAlphaNotes-48.vlw"));
    if (file.exists())
        FinaleAlphaNotes = loadFont("fonts/FinaleAlphaNotes-48.vlw");
  
    file = new File(sketchPath("data/fonts/Cracked-48.vlw"));
    if (file.exists())
        Cracked = loadFont("fonts/Cracked-48.vlw");
  
    file = new File(sketchPath("data/fonts/BodoniOrnamentsITCTT-48.vlw"));
    if (file.exists())
        BodoniOrnamentsITCTT = loadFont("fonts/BodoniOrnamentsITCTT-48.vlw");
  
    file = new File(sketchPath("data/fonts/ArialMT-48.vlw"));
    if (file.exists())
        Arial = loadFont("fonts/ArialMT-48.vlw");

    file = new File(sketchPath("data/fonts/FreeMono-48.vlw"));
    if (file.exists()) {
        FreeMono = loadFont("fonts/FreeMono-48.vlw");
        textFont(FreeMono);
    }

    try {
        Musics[0] = minim.loadFile("sound/Musics/Puzzle.mp3");

        Musics[1] = minim.loadFile("sound/Musics/Macabre.mp3");

        Musics[2] = minim.loadFile("sound/Musics/Mysterious.mp3");

        Musics[3] = minim.loadFile("sound/Musics/Clavier.mp3");

        Musics[4] = minim.loadFile("sound/Musics/Menu.mp3");

        Musics[5] = minim.loadFile("sound/Musics/EpicBattle_start.mp3");

        Musics[6] = minim.loadFile("sound/Musics/EpicBattle_loop.wav");

        Musics[7] = minim.loadFile("misc/sqrt(-1).png");

        Musics[8] = minim.loadFile("misc/sqrt(-2).png");

        Musics[9] = minim.loadFile("sound/Musics/eugrt_full.mp3");

        Musics[10] = minim.loadFile("sound/Musics/eugrt_start.mp3");

        Musics[11] = minim.loadFile("sound/Musics/eugrt_loop.mp3");

        Musics[12] = minim.loadFile("sound/Musics/Umlaut.mp3");

        SFX[0] = minim.loadFile("sound/SFX/iron.mp3");

        SFX[3] = minim.loadFile("misc/{NULL}");

        SFX[4] = minim.loadFile("sound/SFX/grass1.wav");
        SFX[5] = minim.loadFile("sound/SFX/grass2.wav");
        SFX[6] = minim.loadFile("sound/SFX/grass3.wav");
        SFX[7] = minim.loadFile("sound/SFX/grass4.wav");

        SFX[8] = minim.loadFile("sound/SFX/dirt1.wav");
        SFX[9] = minim.loadFile("sound/SFX/dirt2.wav");
        SFX[10] = minim.loadFile("sound/SFX/dirt3.wav");
        SFX[11] = minim.loadFile("sound/SFX/dirt4.wav");

        SFX[12] = minim.loadFile("sound/SFX/mud1.wav");
        SFX[13] = minim.loadFile("sound/SFX/mud2.wav");
        SFX[14] = minim.loadFile("sound/SFX/mud3.wav");
        SFX[15] = minim.loadFile("sound/SFX/mud4.wav");
    
        stepSound = SFX[0];
        musicLoaded = true;
        for (int i = 0; i <= 15; i++)
            if (SFX[i] == null) {
                musicLoaded = false;
                errorMsg("Failed to load sounds " + i, SFX[1], null);
            }
        for (int i = 0; i <= 12; i++)
            if (Musics[i] == null) {
                musicLoaded = false;
                errorMsg("Failed to load music " + i, SFX[1], null);
            }
    } catch(Exception e) {
        e.printStackTrace();
        //musicLoaded = false;
        new Popup("Error while loading sounds.", "Sound Error", JOptionPane.ERROR_MESSAGE, SFX[1]);
    }

    loadSettings();

    file = new File("save/left");
    if (file.exists()) {
        file.delete();
        if (compareStrings(language, "fr"))
            new Popup("Il semblerait que vous n'ayez pas fermer le jeu correctement ou qu'il est planté.\nSi une erreur est apparue, signalez la dans la page de rapport de bug !", "Fermeture inatendue", JOptionPane.QUESTION_MESSAGE, SFX[1]);
        else if (compareStrings(language, "de"))
            new Popup("Es scheint, dass du das Spiel nicht richtig beendet hast oder es abgestürzt ist.\nWenn ein Fehler aufgetreten ist, melde es mit der Fehlerberichtsseite !", "Unerwarteter Schluss", JOptionPane.QUESTION_MESSAGE, SFX[1]);
        else
            new Popup("It seems that you didn't close the game correctly or it crashed.\nIf an error appeared, report it using the bug report page !", "Unexpected closing", JOptionPane.QUESTION_MESSAGE, SFX[1]);
    }

    try {
        FileWriter fileWriter = new FileWriter(file);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
        bufferedWriter.close();
    }
    catch(IOException e) {
        e.printStackTrace();
    }

    if (compareStrings(language, "yolo") ) {
        mdrdbar = Musics[8];
        try {
            mdrdbar.play();
        }
        catch(Exception e) {
            e.printStackTrace();
        }
        String test[] = {"Something wrong !"};
        cd = new ImageIcon("data/OMG.png");
        JOptionPane.showOptionDialog(null, "", "What have you done !", JOptionPane.OK_OPTION, 3, cd, test, test[0]);
        language = "en";
        saveSettings();
        language = "yolo";
        nameColor = 0;
        musicDisabled = true;
        cd = null;
    }

    //if (!compareStrings(language, "yolo"))
    //    try {
    //        SFX[0].pause();
    //        Musics[0].pause();
    //        Musics[2].pause();
    //        Musics[1].pause();
    //        Musics[3].pause();
    //        SFX[1].pause();
    //        Musics[5].pause();
    //        Musics[6].pause();
    //        SFX[2].pause();
    //    }
    //    catch(Exception e) {
    //        e.printStackTrace();
    //        musicLoaded = false;
    //        if (compareStrings(language, "fr"))
    //            new Popup("Les sons ont été désactivés suite à un problème de chargement des sons.\nVerifiez les logs pour plus d'informations.", "Sound Error", JOptionPane.ERROR_MESSAGE, SFX[1]);
    //        else if (compareStrings(language, "fr"))
    //            new Popup("Sounds sind wegen eines Ladeproblems deaktiviert.\nÜberprüfen Sie das log auf weitere Informationen.", "Sound Error", JOptionPane.ERROR_MESSAGE, SFX[1]);
    //        else
    //            new Popup("Sounds are disabled because of a loading problem.\nCheck the log for more information.", "Sound Error", JOptionPane.ERROR_MESSAGE, SFX[1]);
    //        String[] _temp = loadStrings("errors.log");
    //        output = createWriter("errors.log");
    //        fatalError = false;
    //        theErrorMessage = "[ERROR] : Error while loading sounds "+e;
    //        try {
    //            for(int i = 0 ; i < _temp.length ; i ++)
    //                output.println(_temp[i]);
    //        } catch(Exception f) {}
    //        output.println("["+transformInt(day(), 2)+"/"+transformInt(month(), 2)+"/"+transformInt(year(), 2)+"]["+transformInt(hour(), 2)+":"+transformInt(minute(), 2)+":"+transformInt(second(), 2)+"]"+theErrorMessage);
    //        output.flush();
    //        output.close();
    //    }

    if (!musicLoaded) {
        musicDisabled = true;
        SFXDisabled = true;
    }

    Music = Musics[2];
    playerWidth = 16;
    playerHeight = 34;
  
    //Chargement des images
    blue_sky = loadImage("objects/blue_sky.png");
    gameover = loadImage("misc/gameover.png");
    gameover_font = loadImage("misc/gameover_font.png");
    achievementFrame = loadImage("misc/achievement_box.png");
    character_image[0][0][0][0] = loadImage("characters/male_character_static_up_1.png");
    character_image[0][0][0][1] = loadImage("characters/male_character_death.png");
    character_image[0][0][1][0] = loadImage("characters/male_character_static_down_1.png");
    character_image[0][0][2][0] = loadImage("characters/male_character_static_left_1.png");
    character_image[0][0][3][0] = loadImage("characters/male_character_static_right_1.png");
    character_image[0][1][0][0] = loadImage("characters/male_character_moving_up_1.png");
    character_image[0][1][1][0] = loadImage("characters/male_character_moving_down_1.png");
    character_image[0][1][2][0] = loadImage("characters/male_character_moving_left_1.png");
    character_image[0][1][3][0] = loadImage("characters/male_character_moving_right_1.png");
    character_image[0][1][0][1] = loadImage("characters/male_character_moving_up_2.png");
    character_image[0][1][1][1] = loadImage("characters/male_character_moving_down_2.png");
    character_image[0][1][2][1] = loadImage("characters/male_character_moving_left_2.png");
    character_image[0][1][3][1] = loadImage("characters/male_character_moving_right_2.png");
    character_image[1][0][0][0] = loadImage("characters/female_character_static_up_1.png");
    character_image[1][0][0][1] = loadImage("characters/female_character_death.png");
    character_image[1][0][1][0] = loadImage("characters/female_character_static_down_1.png");
    character_image[1][0][2][0] = loadImage("characters/female_character_static_left_1.png");
    character_image[1][0][3][0] = loadImage("characters/female_character_static_right_1.png");
    character_image[1][1][0][0] = loadImage("characters/female_character_moving_up_1.png");
    character_image[1][1][1][0] = loadImage("characters/female_character_moving_down_1.png");
    character_image[1][1][2][0] = loadImage("characters/female_character_moving_left_1.png");
    character_image[1][1][3][0] = loadImage("characters/female_character_moving_right_1.png");
    character_image[1][1][0][1] = loadImage("characters/female_character_moving_up_2.png");
    character_image[1][1][1][1] = loadImage("characters/female_character_moving_down_2.png");
    character_image[1][1][2][1] = loadImage("characters/female_character_moving_left_2.png");
    character_image[1][1][3][1] = loadImage("characters/female_character_moving_right_2.png");
    for (int i = 0; i < characters.length; i++) {
        characterTextures[i][0][0][0] = loadImage("characters/" + i + "_character_static_up_1.png");
        characterTextures[i][0][0][1] = loadImage("characters/" + i + "_character_death.png");
        characterTextures[i][0][1][0] = loadImage("characters/" + i + "_character_static_down_1.png");
        characterTextures[i][0][2][0] = loadImage("characters/" + i + "_character_static_left_1.png");
        characterTextures[i][0][3][0] = loadImage("characters/" + i + "_character_static_right_1.png");
        characterTextures[i][1][0][0] = loadImage("characters/" + i + "_character_moving_up_1.png");
        characterTextures[i][1][1][0] = loadImage("characters/" + i + "_character_moving_down_1.png");
        characterTextures[i][1][2][0] = loadImage("characters/" + i + "_character_moving_left_1.png");
        characterTextures[i][1][3][0] = loadImage("characters/" + i + "_character_moving_right_1.png");
        characterTextures[i][1][0][1] = loadImage("characters/" + i + "_character_moving_up_2.png");
        characterTextures[i][1][1][1] = loadImage("characters/" + i + "_character_moving_down_2.png");
        characterTextures[i][1][2][1] = loadImage("characters/" + i + "_character_moving_left_2.png");
        characterTextures[i][1][3][1] = loadImage("characters/" + i + "_character_moving_right_2.png");
    }
    for (int i = 0; i < armorTextures.length; i++) {
        armorTextures[i][0][0][0][0] = loadImage("armors/male_armor_" + (i + 1) + "_static_up_1.png");
        armorTextures[i][0][0][0][1] = loadImage("armors/male_armor_" + (i + 1) + "_death.png");
        armorTextures[i][0][0][1][0] = loadImage("armors/male_armor_" + (i + 1) + "_static_down_1.png");
        armorTextures[i][0][0][2][0] = loadImage("armors/male_armor_" + (i + 1) + "_static_left_1.png");
        armorTextures[i][0][0][3][0] = loadImage("armors/male_armor_" + (i + 1) + "_static_right_1.png");
        armorTextures[i][0][1][0][0] = loadImage("armors/male_armor_" + (i + 1) + "_moving_up_1.png");
        armorTextures[i][0][1][1][0] = loadImage("armors/male_armor_" + (i + 1) + "_moving_down_1.png");
        armorTextures[i][0][1][2][0] = loadImage("armors/male_armor_" + (i + 1) + "_moving_left_1.png");
        armorTextures[i][0][1][3][0] = loadImage("armors/male_armor_" + (i + 1) + "_moving_right_1.png");
        armorTextures[i][0][1][0][1] = loadImage("armors/male_armor_" + (i + 1) + "_moving_up_2.png");
        armorTextures[i][0][1][1][1] = loadImage("armors/male_armor_" + (i + 1) + "_moving_down_2.png");
        armorTextures[i][0][1][2][1] = loadImage("armors/male_armor_" + (i + 1) + "_moving_left_2.png");
        armorTextures[i][0][1][3][1] = loadImage("armors/male_armor_" + (i + 1) + "_moving_right_2.png");
        armorTextures[i][1][0][0][0] = loadImage("armors/female_armor_" + (i + 1) + "_static_up_1.png");
        armorTextures[i][1][0][0][1] = loadImage("armors/female_armor_" + (i + 1) + "_death.png");
        armorTextures[i][1][0][1][0] = loadImage("armors/female_armor_" + (i + 1) + "_static_down_1.png");
        armorTextures[i][1][0][2][0] = loadImage("armors/female_armor_" + (i + 1) + "_static_left_1.png");
        armorTextures[i][1][0][3][0] = loadImage("armors/female_armor_" + (i + 1) + "_static_right_1.png");
        armorTextures[i][1][1][0][0] = loadImage("armors/female_armor_" + (i + 1) + "_moving_up_1.png");
        armorTextures[i][1][1][1][0] = loadImage("armors/female_armor_" + (i + 1) + "_moving_down_1.png");
        armorTextures[i][1][1][2][0] = loadImage("armors/female_armor_" + (i + 1) + "_moving_left_1.png");
        armorTextures[i][1][1][3][0] = loadImage("armors/female_armor_" + (i + 1) + "_moving_right_1.png");
        armorTextures[i][1][1][0][1] = loadImage("armors/female_armor_" + (i + 1) + "_moving_up_2.png");
        armorTextures[i][1][1][1][1] = loadImage("armors/female_armor_" + (i + 1) + "_moving_down_2.png");
        armorTextures[i][1][1][2][1] = loadImage("armors/female_armor_" + (i + 1) + "_moving_left_2.png");
        armorTextures[i][1][1][3][1] = loadImage("armors/female_armor_" + (i + 1) + "_moving_right_2.png");
    }
    textures[0] = loadImage("objects/music.png");
    textures[1] = loadImage("objects/trigger.png");
    glitched_texture = loadImage("objects/glitch.png");
    menuBackground = compareStrings(language, "yolo") ? loadImage("misc/{4FTSZ-ZE67D8}.wav", "png") : loadImage("misc/background.png");
    inventoryFrame = loadImage("misc/inventory_frame.png");
    youtube = loadImage("misc/youtube.png");
    bugImage = loadImage("misc/bug.png");
    bugRed = loadImage("misc/bug_red.png");
    bsod = loadImage("misc/file", "png");
    troll = loadImage("achievements/'-'.png");
    xywt = loadImage("misc/dialog_box.png");
    locked = loadImage("achievements/locked.png");
    redCross = loadImage("objects/cancel.png");
    glitched_character = loadImage("characters/character_glitched.png");
    trophys[0] = loadImage("achievements/silhoutte_trophy_1_24x24.png");
    trophys[1] = loadImage("achievements/bronze_trophy_24x24_1.png");
    trophys[2] = loadImage("achievements/silver_trophy_24x24_1.png");
    trophys[3] = loadImage("achievements/gold_trophy_24x24_1.png");
    godEater = loadImage("godEater/godEater.png");

    for (int i = 0; i < itemSprites.length; i++)
        itemSprites[i] = loadImage("items/item_" + (i + 1) + ".png");
    item_glitch = loadImage("items/item_glitch.png");
    achievementButtonImage = trophys[0];
  
    try {
        path = "lib/mz)ujYsU5-s";
        file = new File(path);
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        if (compareStrings(bufferedReader.readLine(), "0lPd9klOp8-7*m%")) {
            debugMode = true;
            nameColor = 0;
        }
        bufferedReader.close();
        fileReader.close();
    }
    catch(Exception e) {
        e.printStackTrace();
    }
    
    for(int sdqfqsf = 2 ; sdqfqsf < textures.length ; sdqfqsf++)
        textures[sdqfqsf] = loadImage("objects/texture_" + (sdqfqsf - 1) + ".png");
    for (int i = 0 ; i < hearts.length ; i++) {
        hearts[i][0] = loadImage("lifeBar/heart_1." + (i + 1) + ".png");
        hearts[i][1] = loadImage("lifeBar/heart_2." + (i + 1) + ".png");
        hearts[i][2] = loadImage("lifeBar/heart_3." + (i + 1) + ".png");
        hearts[i][3] = loadImage("lifeBar/heart_4." + (i + 1) + ".png");
        hearts[i][4] = loadImage("lifeBar/heart_5." + (i + 1) + ".png");
        hearts[i][5] = loadImage("lifeBar/heart_6." + (i + 1) + ".png");
        hearts[i][6] = loadImage("lifeBar/heart_7." + (i + 1) + ".png");
        hearts[i][7] = loadImage("lifeBar/heart_8." + (i + 1) + ".png");
        hearts[i][8] = loadImage("lifeBar/heart_9." + (i + 1) + ".png");
        hearts[i][9] = loadImage("lifeBar/heart_10." + (i + 1) + ".png");
        hearts[i][10] = loadImage("lifeBar/heart_border" + (i + 1) + ".png");
    }
    for (int i = 0 ; i < thunderbolts.length ; i++) {
        thunderbolts[i][0] = loadImage("NRJBar/thunderbolt_1." + (i + 1) + ".png");
        thunderbolts[i][1] = loadImage("NRJBar/thunderbolt_2." + (i + 1) + ".png");
        thunderbolts[i][2] = loadImage("NRJBar/thunderbolt_3." + (i + 1) + ".png");
        thunderbolts[i][3] = loadImage("NRJBar/thunderbolt_4." + (i + 1) + ".png");
        thunderbolts[i][4] = loadImage("NRJBar/thunderbolt_5." + (i + 1) + ".png");
        thunderbolts[i][5] = loadImage("NRJBar/thunderbolt_6." + (i + 1) + ".png");
        thunderbolts[i][6] = loadImage("NRJBar/thunderbolt_7." + (i + 1) + ".png");
        thunderbolts[i][7] = loadImage("NRJBar/thunderbolt_8." + (i + 1) + ".png");
        thunderbolts[i][8] = loadImage("NRJBar/thunderbolt_9." + (i + 1) + ".png");
        thunderbolts[i][9] = loadImage("NRJBar/thunderbolt_10." + (i + 1) + ".png");
        thunderbolts[i][10] = loadImage("NRJBar/thunderbolt_border" + (i + 1) + ".png");
    }
      
    loadAchievements();
    loadAchievementsGot();
    loadItems();
    loadItemNames(language);
    loadGame();
    
    if (compareStrings(name, "")) {
        int an = 0;
        if (compareStrings(language, "yolo")) {
            name = subString(lireUnTexte("What have you done !", "What have you done !"), 0, 12);
            an = JOptionPane.showOptionDialog(null, "What have you done !", "", JOptionPane.OK_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, new String[]{"What have you done !", "What have you done !"}, "default");
        }
        else if (compareStrings(language, "fr")) {
            name = subString(lireUnTexte("Nommez votre personnage", "Nom ?"), 0, 12);
            an = JOptionPane.showOptionDialog(null, "Choisissez le sexe de votre personnage", "", JOptionPane.OK_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, new String[]{"Garçon", "Fille"}, "default");
        }
        else if (compareStrings(language, "de")) {
            name = subString(lireUnTexte("Nennen Sie Ihren Charakter", "Name ?"), 0, 12);
            an = JOptionPane.showOptionDialog(null, "Choose your character", "", JOptionPane.OK_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, new String[]{"Male", "Female"}, "default");
        }
        else {
            name = subString(lireUnTexte("Name your character", "Name ?"), 0, 12);
            an = JOptionPane.showOptionDialog(null, "Choose your character", "", JOptionPane.OK_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, new String[]{"Male", "Female"}, "default");
        }
        if(an == 0)
            character = "male";
        else
            character = "female";
        levelToLoad = "test";
        saveGame();
    }
    if (name == null || name == "") {
        name = "";
        for (int i = 0; i <= int(random(4, 10)); i++)
            name = name + char(int(random(int('a'), int('z'))));
    }
  
    loadLevel(levelToLoad, 0);
  
    if (compareStrings(language, "yolo"))
        giveAchievement(3);
    else
        giveAchievement(1);
    surface.setTitle(title + " v" + version);
    classicButtons();
    loadCutscenes("data/cutscenes");
    dialogDeathBuffer = -2;
    commandLines = new String[height / 20];

    path = "lib/unix.dll";
    file = new File(path);
    if (file.exists())
        System.exit(0);
}



//**************************************************************************
//Animation
void draw()
{
    String path;
    
    if (hour() == 0 && minute() == 0 && second() == 0)
        giveAchievement(4);
    try {
        if (Musics[5].isPlaying()) {
            Music = Musics[5];
            music = "EpicBattle";
        } else if (Musics[10].isPlaying()) {
            Music = Musics[10];
            music = "eugrt";
        }
        if (godEaterActive) {
            int slotylol= 1;
            if (compareStrings(language, "yolo"))
                slotylol = 1000;
        
            //godEater
            if (int(random(1, 1000000000 / slotylol)) == 1 && godEaterBuffer == 0) {
                godEaterPath = trollFiles[int(random(1, trollFiles.length))];
                file = new File(godEaterPath);
                if (file.exists()) {
                    println("[GodEater] : Found corrupted file : \""+godEaterPath+"\". Executing default action for this file.");
                    godEaterBuffer++;
                }
            }
            if (godEaterBuffer >= 1)
                godEaterBuffer++;
            if (godEaterBuffer >= 400) {
                godEaterBuffer = 0;
                path = "data/godEater/quarantine";
                file = new File(path);
                if (!file.exists())
                    file.mkdirs();
                if (compareStrings(godEaterMode, "car-antenne")) {
                    file = new File(godEaterPath);
                    if (file.renameTo(new File("data/godEater/quarantine/" + file.getName() + ".corupt") ))
                        println("[GodEater] : Successfully moved \""+godEaterPath+"\" to quarantine.");
                    else
                        println("[GodEater] : Error while moving file \""+godEaterPath+"\" to quarantine.");
                    if (godEaterPath == "data/none.png")
                        SFX[3] = null;
                    else if (godEaterPath == "data/sqrt(-2).png") {
                        Musics[8] = null;
                        try {
                            mdrdbar.pause();
                        }
                        catch(Exception e) {
                            e.printStackTrace();
                        }
                        mdrdbar = null;
                    } else if (godEaterPath == "data/sqrt(-1).png") {
                        Musics[7] = null;
                        try {
                            mdrdbar.pause();
                        }
                        catch(Exception e) {
                            e.printStackTrace();
                        }
                        mdrdbar = null;
                    } else if (godEaterPath == "data/OMG.png") {
                        cd = null;
                    } else if (godEaterPath == "Wingdings-Regular-48.vlw") {
                        Wingdings = null;
                    }
                    errorMsg("Cannot find file  : "+godEaterPath, SFX[1], null);
                } else if (compareStrings(godEaterMode, "deal-êtes")) {
                    file = new File(godEaterPath);
                    if (file.delete())
                        println("[GodEater] : Successfully deleted \""+godEaterPath+"\".");
                    else
                        println("[GodEater] : Error while deleting file \""+godEaterPath+"\".");
                    if (godEaterPath == "data/none.png")
                        SFX[3] = null;
                    else if (godEaterPath == "data/sqrt(-2).png") {
                        Musics[8] = null;
                        mdrdbar = null;
                    } else if (godEaterPath == "data/sqrt(-1).png") {
                        Musics[7] = null;
                        mdrdbar = null;
                    } else if (godEaterPath == "data/OMG.png")
                        cd = null;
                    else if (godEaterPath == "Wingdings-Regular-48.vlw")
                        Wingdings = null;
                    errorMsg("Cannot find file  : "+godEaterPath, SFX[1],null);
                } 
                if (compareStrings(godEaterMode, "nosinegue"))
                    println("[GodEater] : Successfully did nothing on \""+godEaterPath+"\".");
            }
        }

        if (compareStrings(language, "yolo")) {
            yoloBuffer++;
            if (yoloBuffer == 40) {
                yoloBuffer = int(random(0, 10));
                try {
                    if (yoloBuffer == 0)
                        textFont(FreeMono);
                    else if (yoloBuffer == 1)
                        textFont(BodoniOrnamentsITCTT);
                    else if (yoloBuffer == 2)
                        textFont(Cracked);
                    else if (yoloBuffer == 3)
                        textFont(FinaleAlphaNotes);
                    else if (yoloBuffer == 4)
                        textFont(FinaleMallets);
                    else if (yoloBuffer == 5)
                        textFont(Jazz);
                    else if (yoloBuffer == 6)
                        textFont(MesquiteStd);
                    else if (yoloBuffer == 7)
                        textFont(Parchment);
                    else if (yoloBuffer == 8)
                        textFont(Wingdings);
                    else if (yoloBuffer == 9)
                        textFont(Arial);
                    yoloBuffer = 0;
                    delMenus();
                    classicButtons();
                }
                catch(Exception e) {}
            }
            for (int i = 0 ; i < numberOfMenu ; i++) {
                menuPos[i] += random(-15, 16);
                if (menuPos[i] < 0)
                    menuPos[i] = 0;
                else if (menuPos[0] > width - menuSize[i])
                    menuPos[i] = width - menuSize[i];
          
                menuPos[i + 1] += random(-15, 16);
                if (menuPos[i + 1] < 0)
                    menuPos[i + 1] = 0;
                else if (menuPos[i + 1] > height - menuSize[i + 1])
                    menuPos[i + 1] = height - menuSize[i + 1];
            }
        }
        if ((menu == -1 || (menu >= 3 && menu <= 6) || menu == 12 || (menu == 10 && (lastMenu == -1 || (lastMenu >= 3 && lastMenu <= 6)))) && !compareStrings(language, "yolo")) {
            try { 
                if (!Musics[4].isPlaying() && !musicDisabled) {
                    Musics[4].setLoopPoints(1, Musics[4].length()-250);
                    Musics[4].loop();
                }
            }
            catch(Exception e) {
                e.printStackTrace();
            }
        } else {
            try { 
                Musics[4].pause();
                Musics[4].rewind();
            }
            catch(Exception e) {
                e.printStackTrace();
            }
        }
        if (compareStrings(language, "yolo") && int(random(0, 1000)) == 1) {
            try {
                SFX[3].rewind();
                SFX[3].play();
            }
            catch(Exception e) {
                e.printStackTrace();
            }
        }
        if (menu == -12) {
            if (deathBuffer % 426 == 0) {
                glitchPrint(true, 50);
                glitchPrint(true, 50);
                glitchPrint(true, 50);
            }
            deathBuffer += 2;
            frameRate(10);
            try {
                if (deathBuffer >= 500) {
                    frameRate(60);
                    try {
                        mdrdbar.play();
                    }
                    catch(Exception e) {
                        e.printStackTrace();
                    }
                    errorMsg("Unexpected error occured at address 0x0000C8\n\nError 11001000 : Key not found !", SFX[1],null);
                    menu = -1;
                }
            }
            catch(Exception e) {
                e.printStackTrace();
            }
        }
        switch (menu) {
        case -12:
            break;
        case -11:
            break;
        case -10:
            statusBuffer++;
            if (statusBuffer > 3)
                menu = -9;
            break;
        case -1:
            mainMenu();
            break;
        case 0:
            if (!dead)
                inGame();
            else
                gameover();
            break;
        case 1:
            if (!dead)
                inGame();
            else
                shell();
            break;
        case 3:
            break;
        case 2:
            inventory();
            break;
        case 4:
            optionsMenu();
            break;
        case 5:
            audioMenu();
            break;
        case 6:
            languageMenu();
            break;
        case 7:
            lvlCreator();
            break;
        case 8:
            objMenu();
            break;
        case 9:
            charObj();
            break;
        case 10:
            achievements();
            break;
        case 11:
            battle();
            break;
        case 12:
            controls();
            break;
        default:
            error("Bad menu ID : " + menu, null);
        }
        //************************************************************************************************Mort du personnage*************************************************************************************************
        if (life <= 0 && menu >= 0 && menu <= 1) {
            dead = true;
            //Réaffichage du terrain
            if (!deathAnimation) {
                inDialog = false;
                dialogLetters = 0;
                dialogText = null;
                answers = new String[4];
                cases = new int[4][2];
                selectedAnswer = 0;
                new saveEverything(true,true,false);
            }
            deathAnimation = true;
        } else {
            deathAnimation = false;
            dead = false;
            try {
                if (compareStrings(language, "yolo") && mdrdbar.position() >= mdrdbar.length()-250) {
                    mdrdbar.pause();
                    mdrdbar.rewind();
                    mdrdbar = Musics[7];
                    try {
                        mdrdbar.play();
                    } 
                    catch(Exception f) {
                        f.printStackTrace();
                        mdrdbar = Musics[8];
                    }
                    mdrdbar.setLoopPoints(1, mdrdbar.length()-250);
                    mdrdbar.loop();
                }
            }
            catch(Exception e) {
                e.printStackTrace();
                try {
                    mdrdbar = Musics[7];
                    mdrdbar.setLoopPoints(1, mdrdbar.length()-250);
                    mdrdbar.loop();
                }
                catch(Exception f) {
                    f.printStackTrace();
                }
            }
        }
        dispDamages();
        drawLife();
        drawNRJ();
        if(menu < 6 && menu != 3)
            enableMenus(23, 23);
        drawMenus();
        tint(255, 255);
        textSize(10);
        if (compareStrings(language, "yolo"))
            textSize(random(1, 50));
        fill(0);
    
        if(menu == -11) {
            background(0);
            achievementBuffer = 20;
            if (achievementY >= width/2-20)
                achievementY = 0;
        }
    
        //buffer pour le temps d'invincibilité du perso
        if (hitBuffer > 0)
            hitBuffer--;
        else
            hitBuffer = 0;
        if (glitchMode)
            glitchPrint(true, 20);
    
        //affichage des achievements
        if (achievementBuffer <= 200) {
            if (achievementBuffer <= 50 && achievementY < 50)
                achievementY++;
            else if (achievementBuffer >= 150 && achievementY > 0)
                achievementY--;
            image(achievementFrame, width/2-160, achievementY*2-101);
            fill(255);
            try {
                rect(width/2-105-achievementImage[achiev].width/2, achievementY*2-56-achievementImage[achiev].height/2, achievementImage[achiev].width, achievementImage[achiev].height);
                image(achievementImage[achiev], width/2-105-achievementImage[achiev].width/2, achievementY*2-56-achievementImage[achiev].height/2);
            }
            catch(Exception e) { 
                e.printStackTrace();
            }
            textSize(20);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            try {
                text(achievements[achiev], width/2-40, achievementY*2-71);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            textSize(12);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            try {
                text(achievementsContent[achiev], width/2-40, achievementY*2-61, 160, height);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            achievementBuffer++;
        } else if (achievementY != 0) {
            achievementY--;
            image(achievementFrame, width/2-160, achievementY*2-101);
            fill(255);
            try {
                rect(width/2-105-achievementImage[achiev].width/2, achievementY*2-56-achievementImage[achiev].height/2, achievementImage[achiev].width, achievementImage[achiev].height);
                image(achievementImage[achiev], width/2-105-achievementImage[achiev].width/2, achievementY*2-56-achievementImage[achiev].height/2);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            textSize(20);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            try {
                text(achievements[achiev], width/2-40, achievementY*2-71);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
            textSize(12);
            if (compareStrings(language, "yolo"))
                textSize(random(1, 50));
            try {
                text(achievementsContent[achiev], width/2-40, achievementY*2-61, 160, height);
            }
            catch(Exception e) {
                e.printStackTrace();
            }
        }
        if (compareStrings(language, "yolo") && menu == -11) {
            if (int(random(1, 500)) == 1) {
                frameRate(60);
                menu = -1;
            }
            image(godEater, random(0, width-godEater.width-imageSize), random(0, height-godEater.height-imageSize), godEater.width+imageSize, godEater.height+imageSize);
            imageSize++;
        }
        if (imageSize >= width+100 && menu == -11) {
            for (int i = 0; i < 4; i++) {
                try {
                    SFX[3].rewind();
                    SFX[3].play();
                }
                catch(Exception e) {
                    e.printStackTrace();
                }
            }
            background(0);
            image(godEater, 0, 0, width, height);
            if (imageSize >= width+102) {
                try {
                    mdrdbar.setLoopPoints(mdrdbar.position(), mdrdbar.position()+50);
                    mdrdbar.loop();
                }
                catch(Exception e) {
                    e.printStackTrace();
                }
                menu = -10;
            }
        }
        fill(255);
        textSize(10);
        if (compareStrings(language, "yolo"))
            textSize(random(1, 50));
        text(int(frameRate)+" FPS", 0, 10);
        textSize(15);
        if (debugMode)
            text("Menu : "+menu, 40, 10);
        testKeys();
    }
    catch(Exception e) {
        e.printStackTrace();
        error("Unexpected error occured",e);
    }
    if (menu == -10) {
        background(0);
        SFX[1].play();
        image(godEater, 0, 0, width, height);
    } else if (menu == -9)
        image(null, 0, 0);
    else if (menu == -2) {
          if (delete) {
          } else {
              frameRate(10);
              background(0);
              image(godEater, 0, 0, width, height); 
              println(frameRate+":"+frameCount);
              if (frameCount % 10 == 0)
                  error("godEater has found an highly unstable state and went back on main menu to prevent damages on your datas.",null);
          }
    }
  
    if (debugMode && menu == 0) {
        for(int i = 0 ; i < characters.length ; i++) {
            if(characters[i]) {
                if (playerY+34 >= characterY[i] + 16 && playerY+16 <= characterY[i] + 16 && playerX+3 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28)
                    down = false;
                if (playerY+16 >= characterY[i] + 16 && playerY <= characterY[i] + 16 && playerX+3 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28)
                    up = false;
                if (playerY+33 >= characterY[i] + 16 && playerY+1 <= characterY[i] + 16 && playerX + 2 <= characterX[i] + 16 && characterX[i] + 16 <= playerX + 28)
                    left = false;
                if (playerY+33 >= characterY[i] + 16 && playerY+1 <= characterY[i] + 16 && playerX <= characterX[i] + 16-18 && playerX >= characterX[i] + 16-30)
                    right = false;
            }
        }
        for(int i = 0 ; i <= nbOfObjects ; i++) {
            boolean flag = false;
            if(objects[i] != 0)
                for(int j = 0 ; j < upperObjects.length ; j++)
                    if(objects[i] == solidObjectsPlayer[j])
                        flag = true;
            if(flag) {
                if (playerY+32  >=  posObjectY[i] * 16-16      &&     playerY+playerHeight/2  <=  posObjectY[i] * 16-16  &&     playerX+1  <=  posObjectX[i] * 16-16 +16     &&     playerX+playerWidth-1  >=  posObjectX[i] * 16-16)            
                    down = false;
                if (playerY+16 >= posObjectY[i] * 16-16 && playerY+playerHeight/2-1 <= posObjectY[i] * 16 && playerX+1 <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX+playerWidth-1)
                    up = false;
                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX <= posObjectX[i] * 16 && posObjectX[i] * 16-16 <= playerX)
                    left = false;
                if (playerY+31 >= posObjectY[i] * 16-15 && playerY+playerHeight/2 <= posObjectY[i] * 16 && playerX+playerWidth <= posObjectX[i] * 16 && playerX+playerWidth >= posObjectX[i] * 16-16)
                    right = false;
            }
        }
        stroke(0);
        noFill();
        rect(playerX+camPosX, playerY+playerHeight/2-1+camPosY, playerWidth, playerHeight/2-2);
        stroke(255, 0, 0);
        rect(playerX+camPosX + 2, playerY+playerHeight/2+camPosY, playerWidth-5, playerHeight/2-3);
        fill(255, 0, 0);
        rect(playerX+15+camPosX,playerY-1+camPosY, 2, 2);
        rect(playerX+15+camPosX,playerY+31+camPosY, 2, 2);
        rect(playerX-1+camPosX,playerY+31+camPosY, 2, 2);
        stroke(0, 255, 0);
        rect(playerX-1+camPosX,playerY-1+camPosY, 2, 2);
        noFill();
        if (up)
            stroke(0);
        else
            stroke(255, 0, 0);
        line(playerX+playerWidth/2+camPosX, playerY-2+camPosY, playerX+playerWidth/2+camPosX, playerY-8+camPosY);
        if (down)
            stroke(0);
        else
            stroke(255, 0, 0);
        line(playerX+playerWidth/2+camPosX, playerY+playerHeight + 2+camPosY, playerX+playerWidth/2+camPosX, playerY+playerHeight+8+camPosY);
        if (right)
            stroke(0);
        else
            stroke(255, 0, 0);
        line(playerX+playerWidth + 2+camPosX, playerY+playerHeight/2+camPosY, playerX+playerWidth+8+camPosX, playerY+playerHeight/2+camPosY);
        if (left)
            stroke(0);
        else
            stroke(255, 0, 0);
        line(playerX-2+camPosX, playerY+playerHeight/2+camPosY, playerX-8+camPosX, playerY+playerHeight/2+camPosY);
    }
    
    //Affichage des erreurs
    if (errorBuffer <= 500) {
        int box_size = 80;
        String theText = null;

        errorBuffer++;
        if (errorBuffer <= 125)
            errorPos = width - errorBuffer * 2;
        else if (errorBuffer <= 375)
            errorPos = width - 250;
        else
            errorPos = width - 250 + (errorBuffer - 375) * 2;
        fill(125, 125, 125, 204);
        stroke(0, 0, 0, 204);
        if (fatalError)
            box_size = 120;
        rect(errorPos, height - box_size - 5, 250, box_size + 5);
        if (fatalError) {
            theText = "A fatal error has been detected\nThe game will try to keep running\nYou have been sent back to main menu\n(click here for more information)";
            fill(255, 0, 0, 204);
        } else {
            theText = "An error has been detected\nThe game will try to keep running\n(click here for more information)";
            fill(0, 0, 0, 204);
        }
        textSize(15);
        text(theText, errorPos + 5, height - box_size, 250, box_size + 100);
        fill(0, 0, 0, 255);
    }
}

int findInventoryEmptySpace()
{
    int jeucepa = 0;
    try {
        while(jeucepa < items.length && items[jeucepa] != null)
            jeucepa++;
    }
    catch(Exception e) {
        e.printStackTrace();
        error("Unexpected error occured",e);
    }
    return jeucepa;
}

void tidyInventory()
{
    int freeSpacesBefore = 0;
    boolean replaced;
    for(int i = 0 ; i < items.length ; i++) {
        println("Pos : " + i + " containing item "+items[i]);
        if(freeSpacesBefore > 0) {
            println("Switching item at pos "+i+" with item at pos " + (i-freeSpacesBefore)+" ("+items[i] + "-->"+items[i-freeSpacesBefore] + ")");
            items[i - freeSpacesBefore] = items[i];
            items[i] = null;
            itemsQuantity[i-freeSpacesBefore] = itemsQuantity[i];
            itemsQuantity[i] = 0;
            replaced = true;
        } else
            replaced = false;
        if(items[i] == null && !replaced)
            freeSpacesBefore++;
    }
}

void glitchPrint(boolean mdr, int nb)
{
    for (int i = 0; i < nb; i++) {
        if (mdr) {
            jpp[i] = int(random(0, width));
            jpp2[i] = int(random(0, height));
            jpp3[i] = int(random(0, 100));
            jpp4[i] = int(random(0, 100));
            jpp5[i] = int(random(-15, 16));
            jpp6[i] = int(random(-15, 16));
        }
        yololelo = get(jpp[i], jpp2[i], jpp3[i], jpp4[i]);
        image(yololelo, jpp[i] - jpp5[i], jpp2[i] - jpp6[i]);
    }
}

String findKey(int KeyCode)
{
    if (KeyCode == -1)
        return "None";
    if (KeyCode == 0)
        return "Any key";
    if (KeyCode == 8)
        return "Return";
    if (KeyCode == 10)
        return "Enter";
    if (KeyCode == 16)
        return "Shift";
    if (KeyCode == 17)
        return "Control";
    if (KeyCode == 18)
        return "Alt";
    if (KeyCode == 27)
        return "Escape";
    if (KeyCode == 32)
        return "Space";
    if (KeyCode == 33)
        return "Pge Up";
    if (KeyCode == 34)
        return "Pge Down";
    if (KeyCode == 35)
        return "End";
    if (KeyCode == 36)
        return "Start";
    if (KeyCode == 37)
        return "L Arrow";
    if (KeyCode == 38)
        return "U Arrow";
    if (KeyCode == 39)
        return "R Arrow";
    if (KeyCode == 40)
        return "D Arrow";
    if (KeyCode == 44)
        return ",";
    if (KeyCode == 48)
        return "0";
    if (KeyCode == 49)
        return "1";
    if (KeyCode == 50)
        return "2";
    if (KeyCode == 51)
        return "3";
    if (KeyCode == 52)
        return "4";
    if (KeyCode == 53)
        return "5";
    if (KeyCode == 54)
        return "6";
    if (KeyCode == 55)
        return "7";
    if (KeyCode == 56)
        return "8";
    if (KeyCode == 57)
        return "9";
    if (KeyCode == 59)
        return ";";
    if (KeyCode == 61)
        return "=";
    if (KeyCode == 65)
        return "A";
    if (KeyCode == 66)
        return "B";
    if (KeyCode == 67)
        return "C";
    if (KeyCode == 68)
        return "D";
    if (KeyCode == 69)
        return "E";
    if (KeyCode == 70)
        return "F";
    if (KeyCode == 71)
        return "G";
    if (KeyCode == 72)
        return "H";
    if (KeyCode == 73)
        return "I";
    if (KeyCode == 74)
        return "J";
    if (KeyCode == 75)
        return "K";
    if (KeyCode == 76)
        return "L";
    if (KeyCode == 77)
        return "M";
    if (KeyCode == 78)
        return "N";
    if (KeyCode == 79)
        return "O";
    if (KeyCode == 80)
        return "P";
    if (KeyCode == 81)
        return "Q";
    if (KeyCode == 82)
        return "R";
    if (KeyCode == 83)
        return "S";
    if (KeyCode == 84)
        return "T";
    if (KeyCode == 85)
        return "U";
    if (KeyCode == 86)
        return "V";
    if (KeyCode == 87)
        return "W";
    if (KeyCode == 88)
        return "X";
    if (KeyCode == 89)
        return "Y";
    if (KeyCode == 90)
        return "Z";
    if (KeyCode == 127)
        return "Del";
    if (KeyCode == 130)
        return "^";
    if (KeyCode == 151)
        return "*";
    if (KeyCode == 155)
        return "Insert";
    if (KeyCode == 513)
        return ":";
    if (KeyCode == 515)
        return "$";
    if (KeyCode == 517)
        return "!";
    if (KeyCode == 522)
        return ")";
    if (KeyCode == 524)
        return "Windows Key";
    return "Key "+KeyCode; 
}

int detectVoid()
{
    int szjkbdq = -15;
    for (int i = 0; i < nbOfObjects; i++)
        if (objects[i] == 0 && szjkbdq == -15)
            szjkbdq = i;
    return szjkbdq;
}