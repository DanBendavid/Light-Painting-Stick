



//******Palette Animation Globals*******************************************

uint8_t colorIndex;
String anim_direction = "forward";
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
//TBlendType    currentBlending;
//long paletteMillis = 0; 

void FillLEDsFromPaletteColors(long time, uint8_t colorIndex)
{
       // t6_1  , thirtyseven_waves_gp , 
        
        if(targetpicker == 1){ targetPalette = bhw1_purplered_gp;}
        if(targetpicker == 2){ targetPalette = bhw1_sunconure_gp;}
        if(targetpicker == 3){ targetPalette = Lindaa07_gp;}
        if(targetpicker == 4){ targetPalette = patriot_gp;}
        if(targetpicker == 5){ targetPalette = beading_gp;}
        if(targetpicker == 6){ targetPalette = sorcery_2_gp;}
        if(targetpicker == 7){ targetPalette = usa1_gp;}
        if(targetpicker == 8){ targetPalette = faewing3_gp;}
        if(targetpicker == 9){ targetPalette = starrynite_gp;}
        if(targetpicker == 10){ targetPalette = blueeyedgal_gp;}
        if(targetpicker == 11){ targetPalette = fs2010_gp;} 
        if(targetpicker == 12){ targetPalette = water1_gp;}
        if(targetpicker == 13){ targetPalette = brightsong2_gp;}
        if(targetpicker == 14){ targetPalette = Lucy_in_the_Sky_gp;}
        if(targetpicker == 15){ targetPalette = temperature_gp;}
        if(targetpicker == 16){ targetPalette = bhw1_purpgreen_gp;}
        if(targetpicker == 17){ targetPalette = bud2_gp;}
        if(targetpicker == 18){ targetPalette = blue_waves_gp;}
        if(targetpicker == 19){ targetPalette = twilight_gp;}
        if(targetpicker == 20){ targetPalette = plasma_gp;}
        if(targetpicker == 21){ targetPalette = sls_gp;}
        if(targetpicker == 22){ targetPalette = bhw1_29_gp;}


        currentPalette = targetPalette;

  
 // uint8_t brightness = 255;
 unsigned long currentTime = millis();
 if (!blynk) {time =1000;}
 while (millis()< currentTime + (time) ) {
  for( int i = 0; i < NUM_LEDS; i++) {
    colorIndex = round((255 / NUM_LEDS)*i);
    //leds[i] = ColorFromPalette( currentPalette, colorIndex + sin8(i*16), brightness);
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS);

   // if (anim_direction == "forward") {colorIndex += 3;}
   // if (anim_direction == "back") {colorIndex -= 3;}
  }
  FastLED.show();
  delay (500);
  
  if (blynk) {
    set_black();
  delay (500);
  }
  }
  //Serial.println ("Fast show");
  //Serial.println (currentPalette);
}

uint8_t gHue = 0;

void rainbow() {
//  pattern_lcd ="Raibow";
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  FastLED.show();
  delay (500);
  }


void Blue_flower(long time, int frame){
unsigned long currentTime = millis();
while (millis()< currentTime + (time)) {
 byte Counter;
 for(Counter=0;Counter < NUM_LEDS; Counter++)
 {
   leds[Counter].setRGB(0,0,0);
   leds[Counter].setRGB(0,0,255);
FastLED.show();
//delayMicroseconds(100);
delay(1);
}  
// Show a colour bar going down from 9 to 0
byte Counter2;
for(Counter2=NUM_LEDS;Counter2 > 0; Counter2--)
{
leds[Counter2-1].setRGB(255,0,0);
if(Counter2>3){
leds[Counter2-3].setRGB(0,255,0);}
FastLED.show();
//delayMicroseconds(100);
delay(1);
}  
}
}

void set_black() {
for(int x=0;x<NUM_LEDS;x++){
leds[x] = CRGB::Black;}
FastLED.show();
  }

  
void upDown(unsigned long time){
   unsigned long currentTime = millis();
 while (millis()< currentTime + (time)) {
 
   for (int i=0;i<NUM_LEDS;i++) { 
  leds[i].setRGB(255,0,0); 
  FastLED.show();    
   delay(1);
  leds[i].setRGB(0,0,0); 
     }
    for (int i=NUM_LEDS-1;i>0;i--) { 
  leds[i].setRGB(255,0,0); 
  FastLED.show();    
   delay(1);
   leds[i].setRGB(0,0,0); 
    }
 }
 }
