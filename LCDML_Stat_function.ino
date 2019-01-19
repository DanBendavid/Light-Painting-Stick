/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== */


void select_folder(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
  root = SD_MMC.open("/");
    // setup
    // is called only if it is started
  GetFileNamesFromSD(root);
  //isort(m_FileNames, m_NumberOfFiles);
  m_CurrentFoldername = m_FolderName[m_FolderIndex];
  
  char buf [30];
  char buff [30];
  //m_NumberOfFiles.toCharArray(buf, 30);
 sprintf (buf, "Total Folder: %d", m_NumberOfFolder);
 m_CurrentFoldername.toCharArray(buff, 30);
 
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "Current folder");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
    } while( u8g2.nextPage() );  
  
    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }
  
  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function 
  

    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed    
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        m_FolderIndex--;
         if (m_FolderIndex < 0 ) { m_FolderIndex = m_NumberOfFolder; }
       
        // update lcd content
        char buf[20];
        sprintf (buf, "Folder: %d", m_FolderIndex);

        char buff[20];
        m_FolderName[m_FolderIndex].toCharArray(buff, 20);


        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press Up or Down");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
        } while( u8g2.nextPage() );        
      }    

    if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed    
      {
        LCDML.BT_resetRight(); // reset the left button
        LCDML.BT_resetDown(); // reset the left button
        m_FolderIndex++;
        if (m_FolderIndex > m_NumberOfFolder - 1 ) {
          m_FolderIndex  = 0;}
        // update lcd content
        char buf[20];
        sprintf (buf, "Folder: %d", m_FolderIndex);

        char buff[20];
        m_FolderName[m_FolderIndex].toCharArray(buff, 20);

        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press Up or Down");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);          
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
        } while( u8g2.nextPage() );        
      } 


         if (LCDML.BT_checkEnter() )
         {
          char buff[20];
          String StringF = m_FolderName[m_FolderIndex];
          //Serial.println(StringF);
          //Serial.println(StringF+"/");
          root = SD_MMC.open(StringF);
          select_image(0);
         }
    }
  
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 

  } 
}


void select_image(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started
 //root = SD_MMC.open("/fire");
 GetFileNamesFromSD(root);
  isort(m_FileNames, m_NumberOfFiles);
  m_CurrentFilename = m_FileNames[m_FileIndex];
  char buf [30];
  char buff [30];
  //m_NumberOfFiles.toCharArray(buf, 30);
 sprintf (buf, "Total File: %d", m_NumberOfFiles);
 m_CurrentFilename.toCharArray(buff, 30);
 
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "Current file");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
    } while( u8g2.nextPage() );  
  
    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }
  
  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function 
  

    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed    
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        m_FileIndex--;
         if (m_FileIndex < 0 ) { m_FileIndex = m_NumberOfFiles; }
       
        // update lcd content
        char buf[20];
        sprintf (buf, "File: %d", m_FileIndex);

        char buff[20];
        m_FileNames[m_FileIndex].toCharArray(buff, 20);


        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press Up or Down");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
        } while( u8g2.nextPage() );        
      }    

    if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed    
      {
        LCDML.BT_resetRight(); // reset the left button
        LCDML.BT_resetDown(); // reset the left button
        m_FileIndex++;
        if (m_FileIndex > m_NumberOfFiles - 1 ) {
          m_FileIndex  = 0;}
        // update lcd content
        char buf[20];
        sprintf (buf, "File: %d", m_FileIndex);

        char buff[20];
        m_FileNames[m_FileIndex].toCharArray(buff, 20);

        
        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press Up or Down");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);          
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
        } while( u8g2.nextPage() );        
      } 


         if (LCDML.BT_checkEnter() )
         {
          char buff[20];
          String StringF = m_FileNames[m_FileIndex]+".bmp";
          StringF.toCharArray(buff, 20);
          bmpDraw (buff,g_dynParam);
          delay(1000);
          set_black();
         }
    }
  
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 

  } 
}

void draw_bmp(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 millisecounds
    LCDML.FUNC_setLoopInterval(100); 
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {
    // loop
    // is called when it is triggert
    // - with LCDML_DISP_triggerMenu( millisecounds ) 
    // - with every button status change

    // check if any button is presed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {         
      LCDML.FUNC_goBackToMenu();
    } 

          char buff[20];
          String StringF = m_FileNames[m_FileIndex]+".bmp";
          StringF.toCharArray(buff, 20);
          bmpDraw (buff,g_dynParam);
          delay(1000);
          set_black();

    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
set_black(); 
  } 
}

/*
void your_function_name(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 millisecounds
    LCDML.FUNC_setLoopInterval(100); 
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {    
    // loop
    // is called when it is triggert
    // - with LCDML_DISP_triggerMenu( millisecounds ) 
    // - with every button status change

    // check if any button is presed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {         
      LCDML.FUNC_goBackToMenu();
    } 
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // loop end
    // you can here reset some global vars or delete it 
  } 
}

 
 * ===================================================================== * 
 */

// *********************************************************************
void mFunc_information(uint8_t param)
// *********************************************************************
{
  char value_s[20];
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {  
    // setup function
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "To close this");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "function press");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "any button or use");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 4), "back button");
    } while( u8g2.nextPage() );
  }

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  { 
    uint16_t value =analogRead(36);  
    char NumberOfFiles [30];
    char Brighness_s [30];
    char Blynk_s [30];
    sprintf (value_s, "Value: %d", value);
    sprintf (NumberOfFiles, "BMP Files in SD: %d", m_NumberOfFiles);
    sprintf (Brighness_s, "Brightness: %d", BRIGHTNESS);
    sprintf (Blynk_s, "Blynk", blynk);

// setup function
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), value_s);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), Brighness_s);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), NumberOfFiles);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 4), Blynk_s);
    } while( u8g2.nextPage() );
    
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function   
    if(LCDML.BT_checkAny()) // check if any button is presed (enter, up, down, left, right)
    { 
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    } 
  }
  
  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // you can here reset some global vars or do nothing 
  } 
}  


// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (globale variable)
void mFunc_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP ********* 
  { 
     g_func_timer_info = 20;       // reset and set timer   
    
    char buf[20];
    sprintf (buf, "wait %d secounds", g_func_timer_info);
    
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "or press back button");
    } while( u8g2.nextPage() );
  
       
    
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 millisecounds

    LCDML.TIMER_msReset(g_timer_1);  
  }

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  { 
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function 

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

     // this function is called every 100 millisecounds
    
    // this method checks every 1000 millisecounds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000)) 
    { 
      g_timer_1 = millis();   
      g_func_timer_info--;                // increment the value every secound
      char buf[20];
      sprintf (buf, "wait %d secounds", g_func_timer_info);
      
      u8g2.setFont(_LCDML_DISP_font);
      u8g2.firstPage();  
      do {
        u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
        u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "or press back button");
      } while( u8g2.nextPage() );   
         
    }
        
    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normaly
    if (g_func_timer_info <= 0)
    {
      // leave this function
      LCDML.FUNC_goBackToMenu();  
    } 
  } 

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // you can here reset some global vars or do nothing
  }  
}

// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)

void mFunc_p2(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {   
    // setup function
    // print lcd content
    char buf[17];
    sprintf (buf, "count: %d of 3", 0);
    
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press a or w button");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
    } while( u8g2.nextPage() );  
  
    // Reset Button Value
    g_button_value = 0; 

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();
  }
  
  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function 
  
    // the quit button works in every DISP function without any checks; it starts the loop_end function  
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        g_button_value++;
      
        // update lcd content
        char buf[20];
        sprintf (buf, "count: %d of 3", g_button_value);
        
        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press a or w button");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
        } while( u8g2.nextPage() );        
      }    
    }
  
   // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function  
    }    
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
void mFunc_screensaver(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // setup function
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "screensaver");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "press any key");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "to leave it");
    } while( u8g2.nextPage() );
    
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 millisecounds
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {      
      LCDML.FUNC_goBackToMenu();  // leave this function   
    }
  } 

  if(LCDML.FUNC_close())          // ****** STABLE END *********
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  } 
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // go to root and display menu
    LCDML.MENU_goRoot();    
  } 
}

// *********************************************************************
void mFunc_jumpTo_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // Jump to Initscreen
    if(!LCDML.OTHER_jumpToFunc(mFunc_timer_info)) 
    {
      // function not found or not callable
      LCDML.MENU_goRoot();           
    }
  }
}


// *********************************************************************
void mFunc_para(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {

    char buf[20];
    sprintf (buf, "Brightness: %d", param);
    
    // setup function
    u8g2.setFont(_LCDML_DISP_font);
    u8g2.firstPage();  
    do {
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "press any key");
      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "to leave it");
    } while( u8g2.nextPage() );
    
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 millisecounds
  }

  if(LCDML.FUNC_loop())               // ****** LOOP *********
  {
    // For example
    switch(param)
    {
      case 1:
        BRIGHTNESS = 30;
        FastLED.setBrightness(BRIGHTNESS);
        break;

      case 2:
        BRIGHTNESS = 60;
        FastLED.setBrightness(BRIGHTNESS);
        // do something
        break;

      case 3:
        BRIGHTNESS = 90;
        FastLED.setBrightness(BRIGHTNESS);
        break;

      case 4:
        BRIGHTNESS = 150;
        FastLED.setBrightness(BRIGHTNESS);
        break;
        
      case 5:
        BRIGHTNESS = 200;
        FastLED.setBrightness(BRIGHTNESS);
        break;

       case 6:
         if(blynk) {blynk = false;} else {blynk = true;} 
        break;

      default:
        // do nothing
        break;
    }

    
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {      
      LCDML.FUNC_goBackToMenu();  // leave this function   
    }
  } 

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


void f_upDown(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 millisecounds
    LCDML.FUNC_setLoopInterval(100); 
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {    
    upDown(5000);

    // check if any button is presed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {         
      LCDML.FUNC_goBackToMenu();
    } 
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // loop end
    // you can here reset some global vars or delete it 
    set_black();
  } 
}

void f_Blue_flower(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 millisecounds
    LCDML.FUNC_setLoopInterval(100); 
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {    
    
    // check if any button is presed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {         
      LCDML.FUNC_goBackToMenu();
    } 

Blue_flower(g_dynParam*1000,2);

    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // loop end
    // you can here reset some global vars or delete it 
    set_black();
  } 
}

void f_rainbow(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { 
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 millisecounds
    LCDML.FUNC_setLoopInterval(100); 
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {    
  

    // check if any button is presed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {         
      LCDML.FUNC_goBackToMenu();
    } 

      rainbow();
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // loop end
    // you can here reset some global vars or delete it 
    set_black();
  } 
}

int targetpicker = 1;
void f_palette(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  { char buf[20];
        sprintf (buf, "Palette: %d", targetpicker);
        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press Up or Down");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
         // u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
        } while( u8g2.nextPage() );   
    
    LCDML.FUNC_disableScreensaver();
  }     

  if(LCDML.FUNC_loop())           // ****** LOOP ********* 
  {    
             
        
 if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed    
      { 
        //LCDML.BT_resetLeft(); // reset the left button
        //LCDML.BT_resetUp(); // reset the left button
        
        targetpicker++;
        
        if (targetpicker > n_palette ) {
          targetpicker  = 1;}
        if (targetpicker == 0 ) 
          {targetpicker = n_palette; 
          }
        char buf[20];
        sprintf (buf, "Palette: %d", targetpicker);
        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press Up or Down");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
         // u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
        } while( u8g2.nextPage() );   
        
        FillLEDsFromPaletteColors(5000, 0);
        delay(100);
      }
    
    if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed    
      {
        //LCDML.BT_resetRight(); // reset the left button
        //LCDML.BT_resetDown(); // reset the left button
        targetpicker--;
        if (targetpicker == 0 ) 
          {targetpicker = n_palette; 
          }
        if (targetpicker > n_palette ) {
          targetpicker  = 1;}
          
        char buf[20];
        sprintf (buf, "Palette: %d", targetpicker);
        u8g2.setFont(_LCDML_DISP_font);
        u8g2.firstPage();  
        do {
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press Up or Down");
          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
         // u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), buff);
        } while( u8g2.nextPage() );   
          
        FillLEDsFromPaletteColors(5000,0);
        delay(100);
       
        } 
     
         if (LCDML.BT_checkEnter() )
         {
          FillLEDsFromPaletteColors(5000,0);
          delay(100);
         }
    }
  
 
    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END ********* 
  { 
    // loop end
    // you can here reset some global vars or delete it 
    set_black();
  } 
}
