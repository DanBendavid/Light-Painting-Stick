// 
// Autor : Dan BENDAVID
// Inspired by Fotorgear
// Library : Fastled, U8GLIB, LCDMenuLib2, MD_Encoder

// Wiring with ESP32 with SD builtin Card 

/* SD Card | ESP32
 *    D2       12
 *    D3       13
 *    CMD      15
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      14
 *    VSS      GND
 *    D0       2  (add 1K pull up after flashing)
 *    D1       4
 */
// SDA 23 / SCL 19 / LED DATA 21 / LED CLK 18 / En A 5 / En B 17 / En Btn 27
                      
// ============================================================
// LCDMenu Source
// Autor:       Nils Feldkämper
// Last update: 21.01.2018
// License:     MIT                                     
// ============================================================ 
 

  // include libs
  #include <LCDMenuLib2.h>

  // U8g2lib
  #include <Arduino.h>
  #include <U8g2lib.h>

  #define SDA 23
  #define SCL 19
  
  #ifdef U8X8_HAVE_HW_SPI
  #include <SPI.h>
  #endif
  #ifdef U8X8_HAVE_HW_I2C
  #include <Wire.h>
  #endif

/*
This code uses the T3.6 onboard sd card slot, BMP stored on the card are light painted using a cheap strip of ws2811 leds using FastLed
 code derived from lightpainting sketch:
 https://forum.pjrc.com/threads/24535...P-from-SD-card
 and this post:
  ------> https://forum.pjrc.com/threads/40871...file-read-fail
*/

#include <SPI.h>
//#include <SD.h>
#include <SD_MMC.h>
//#include <FS.h>
#include <FastLED.h>

File bmpFile;
File root;
String m_CurrentFilename = "";
String m_CurrentFoldername = "";
int m_FileIndex = 0;
int m_FolderIndex = 0;
int m_NumberOfFiles = 0;
int m_NumberOfFolder = 0;
String m_FileNames[300];
String m_FolderName[300];


//const int chipSelect = BUILTIN_SDCARD;

// you can remove all Serial.print when you have your paint staff 
// set up, this is just for debug

int bmpWidth, bmpHeight;

uint8_t bmpDepth, bmpImageoffset;
#define BUFFPIXEL 512 // Number of Led times 3

unsigned int Color(byte b, byte r, byte g); //placed here to avoid compiler error

// How many leds in your strip?
#define DATA_PIN 21
#define CLOCK_PIN 18
#define COLOR_ORDER BGR
#define CHIPSET     APA102
#define NUM_LEDS    144


int BRIGHTNESS = 50;
int n_palette = 22;
bool blynk = false;

CRGB leds[NUM_LEDS];







// *********************************************************************
// U8GLIB
// *********************************************************************
  // U8g2 Contructor List (Frame Buffer)
  // The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
  // Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
  //U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 53, /* reset=*/ U8X8_PIN_NONE);     // (MEGA, ...
  //U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 12, /* reset=*/ U8X8_PIN_NONE);   // (Uno and co
  U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
  //U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
  //U8G2_SSD1306_128X64_NONAME_F_SW_I2C
  // settings for u8g lib and lcd
  #define _LCDML_DISP_w                 128            // lcd width
  #define _LCDML_DISP_h                 64             // lcd height
  // font settings
  #define _LCDML_DISP_font              u8g2_font_6x12_tr  // u8glib font (more fonts under u8g.h line 1520 ...)u8g2_font_6x12_tr u8g_font_6x13
  #define _LCDML_DISP_font_w            6              // font width
  #define _LCDML_DISP_font_h            12             // font heigt  
  // cursor settings
  #define _LCDML_DISP_cursor_char       ">"            // cursor char
  #define _LCDML_DISP_cur_space_before  1              // cursor space between
  #define _LCDML_DISP_cur_space_behind  2              // cursor space between  
  // menu position and size
  #define _LCDML_DISP_box_x0            0              // start point (x0, y0)
  #define _LCDML_DISP_box_y0            0              // start point (x0, y0)
  #define _LCDML_DISP_box_x1            128            // width x  (x0 + width)
  #define _LCDML_DISP_box_y1            64             // hight y  (y0 + height)
  #define _LCDML_DISP_draw_frame        1              // draw a box around the menu
   // scrollbar width
  #define _LCDML_DISP_scrollbar_w       6  // scrollbar width (if this value is < 3, the scrollbar is disabled)    

  // nothing change here
  #define _LCDML_DISP_cols_max          ((_LCDML_DISP_box_x1-_LCDML_DISP_box_x0)/_LCDML_DISP_font_w) 
  #define _LCDML_DISP_rows_max          ((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0)/_LCDML_DISP_font_h))/_LCDML_DISP_font_h) 

  // rows and cols 
  // when you use more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
  // the program needs more ram with this changes
  #define _LCDML_DISP_rows              _LCDML_DISP_rows_max  // max rows 
  #define _LCDML_DISP_cols              20                   // max cols
 
 
// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display(); 
  void lcdml_menu_clear(); 
  void lcdml_menu_control();   


// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);
  

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0 
  // LCDML_0_X      => layer 1 
  // LCDML_0_X_X    => layer 2 
  // LCDML_0_X_X_X  => layer 3 
  // LCDML_0_...      => layer ... 

  // For beginners
  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)  
  LCDML_add         (0  , LCDML_0         , 1  , "Information"      , mFunc_information);       // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (1  , LCDML_0         , 2  , "Patern"        , NULL);        // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (2  , LCDML_0         , 3  , "Image"        , NULL);                    // NULL = no menu function    
  LCDML_add         (12 , LCDML_0         , 4  , "Circular"          , NULL);                    // NULL = no menu function 
  LCDML_addAdvanced (13 , LCDML_0         , 5  , NULL,          "Brightness"      , NULL,                0,            _LCDML_TYPE_default);                    // NULL = no menu function
  

  LCDML_add         (3 , LCDML_0_3       , 1  , "Start"               , draw_bmp);                    // 
  LCDML_add         (7 , LCDML_0_3       , 2  , "Select image"        , select_image);                // 
  LCDML_add         (8 , LCDML_0_3       , 3  , "Select folder"       , select_folder);                // 
  LCDML_add         (24 , LCDML_0_3      , 4  , "Back"                , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
  
  LCDML_add         (4  , LCDML_0_2     , 1  , "Blue_flower"         , f_Blue_flower);                    // 
  LCDML_add         (5  , LCDML_0_2     , 2  , "upDown"              , f_upDown);                    // 
  LCDML_add         (6  , LCDML_0_2     , 3  , "Palette"              , f_palette);                    //  
  LCDML_add         (19 , LCDML_0_2     , 4  , "Rainbow"              , f_rainbow);                    //  
  LCDML_add         (20 , LCDML_0_2     , 5  , "Back"                 , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab 
  
//  LCDML_add         (6  , LCDML_0_3_1_2   , 1  , "Warm"             , NULL);                    //  
//  LCDML_add         (7  , LCDML_0_3_1_2   , 2  , "Cold"             , NULL);                    //  
//  LCDML_add         (8  , LCDML_0_3_1_2   , 3  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab 

  LCDML_add         (9 , LCDML_0_4       , 1  , "go to Root"       , mFunc_goToRootMenu);      // 
  LCDML_add         (10 , LCDML_0_4      , 2  , "jump to Time info", mFunc_jumpTo_timer_info); // 
  LCDML_add         (11 , LCDML_0_4      , 3  , "Back"             , mFunc_back);              // 


  // Advanced menu (for profis) part with more settings
  // Example for one function and different parameters
  // It is recommend to use parameters for switching settings like, (small drink, medium drink, big dring) or (200ml, 400ml, 600ml, 800ml) ... 
  // the parameter change can also be released with dynParams on the next example
  // LCDMenuLib_add(id, prev_layer,     new_num, condetion,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  
  LCDML_addAdvanced (14 , LCDML_0_5       , 1  , NULL,          "Brightness 30"      , mFunc_para,       1,            _LCDML_TYPE_default);                    // NULL = no menu function
  LCDML_addAdvanced (15 , LCDML_0_5       , 2  , NULL,          "Brightness 60"      , mFunc_para,       2,            _LCDML_TYPE_default);                    // NULL = no menu function
  LCDML_addAdvanced (16 , LCDML_0_5       , 3  , NULL,          "Brightness 90"      , mFunc_para,       3,            _LCDML_TYPE_default);                    // NULL = no menu function
  LCDML_addAdvanced (21 , LCDML_0_5       , 4  , NULL,          "Brightness 150"      , mFunc_para,      4,            _LCDML_TYPE_default);                    // NULL = no menu function
  LCDML_addAdvanced (22 , LCDML_0_5       , 5  , NULL,          "Brightness 200"      , mFunc_para,      5,            _LCDML_TYPE_default);                    // NULL = no menu function
  LCDML_addAdvanced (23 , LCDML_0_5       , 6  , NULL,          "Blink Togle"         , mFunc_para,      6,            _LCDML_TYPE_default);                    // NULL = no menu function
  // Example for dynamic content 
  // 1. set the string to ""
  // 2. use type  _LCDML_TYPE_dynParam   instead of    _LCDML_TYPE_default
  // this functiontype can not be used in combination with different parameters 
  // LCDMenuLib_add(id, prev_layer,     new_num, condition,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  LCDML_addAdvanced (17 , LCDML_0         , 6  , NULL,          "Image Speed"         , mDyn_para,       0,   _LCDML_TYPE_dynParam);                     // NULL = no menu function
  
  // Example for condetions (for example for a screensaver)  
  // 1. define a condetion as a function of a boolean type -> return false = not displayed, return true = displayed
  // 2. set the function name as callback (remove the braces '()' it gives bad errors)
  // LCDMenuLib_add(id, prev_layer,     new_num, condetion,   lang_char_array, callback_function, parameter (0-255), menu function type  )
  LCDML_addAdvanced (18 , LCDML_0         , 7  , COND_hide,  "screensaver"        , mFunc_screensaver,        0,   _LCDML_TYPE_default);       // this menu function can be found on "LCDML_display_menuFunction" tab 
  
  // ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu elment.
  
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    24  
  
  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);




// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  { 



     
    u8g2.begin();
    
    // serial init; only be needed if serial control is used     
    Serial.begin(115200);                // start serial    
    Serial.println(F(_LCDML_VERSION)); // only for examples
      
    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Enable Menü Rollover 
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    //LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 secounds 
    //LCDML.SCREEN_disable();

    // Some needfull methods 
    
    // You can jump to a menu function from anywhere with 
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name 



  
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

//test our led strip - you can remove this to the comment line "// if you dont get ..."
for(int x=0;x<NUM_LEDS;x++){
leds[x] = CRGB::Green;}
  FastLED.show();
  delay(750);
for(int x=0;x<NUM_LEDS;x++){
leds[x] = CRGB::Red;}
  FastLED.show();
  delay(750);
for(int x=0;x<NUM_LEDS;x++){
leds[x] = CRGB::Blue;}
  FastLED.show();
  delay(750);
  for(int x=0;x<NUM_LEDS;x++){
  leds[x] = CRGB::Black;}
  FastLED.show();
  delay(1000);
// if you dont get all leds lighting red then going off, check your wiring

  Serial.println("init");
  delay(500);
  Serial.print("Initializing SD card...");
 
  if (!SD_MMC.begin()) {
    Serial.println("initialization failed!");
    
    for(int x=0;x<NUM_LEDS;x++){
    leds[x] = CRGB::Pink;}
    FastLED.show();
    delay(750);

    return;
  }
  Serial.println("SD OK!");

//listDir(SD_MMC, "/", 0);
root = SD_MMC.open("/");

//GetFileNamesFromSD(root);
//Serial.println("Total file" + m_NumberOfFiles);
//isort(m_FileNames, m_NumberOfFiles);
//m_CurrentFilename = m_FileNames[0];
//m_CurrentFilename = m_FileNames[m_FileIndex];
//Serial.println(m_CurrentFilename + ".BMP");

//FillLEDsFromPaletteColors(0);


  
  }


// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    // this function must called here, do not delete it
    LCDML.loop();

  }


// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib2.h
# endif

# if(_LCDML_glcd_tft_box_x1 > _LCDML_glcd_tft_w)
# error _LCDML_glcd_tft_box_x1 is to big
# endif

# if(_LCDML_glcd_tft_box_y1 > _LCDML_glcd_tft_h)
# error _LCDML_glcd_tft_box_y1 is to big
# endif
