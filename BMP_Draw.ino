//------- HELPER FUNCTION------//
// Create a 24 bit color value from R,G,B ////these strips are BRG, but you might need to change this
unsigned int Color_hex(byte b/*r*/, byte g, byte /*b*/r)
{
  //Take the lowest 8 bits of each value and append them end to end
return( ((unsigned int)g & 0x1F )<<16 | ((unsigned int)r & 0x1F)<<8 | (unsigned int)b & 0x1F);
  }
//end of helper function



//////////////////Function to read BMP and send to Led strip a row at a time/////////////////////
void bmpDraw(char* filename,int g_dynParam ){

  File   bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must report 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel) 
  uint32_t povbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)//////mg/////this needs to be 24bit per pixel////////
  uint32_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  int  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint16_t povidx = 0;
  boolean  first = true;
  int delay_image_scroll;
 
  // Open requested file on SD card
  bmpFile = SD_MMC.open(filename);
  Serial.println(filename);
  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print("File size: "); 
    Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print("Image Offset: "); 
    Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print("Header size: "); 
    Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print("Bit Depth: "); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
 
        goodBmp = true; // Supported BMP format -- proceed!
    Serial.print("Image size: ");
    Serial.print(bmpWidth);
    Serial.print('x');
    Serial.println(bmpHeight);
    
        // BMP rows are padded (if needed) to 4-byte boundary
       rowSize = (bmpWidth * 3 + 3) & ~3;

 
        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        w = bmpWidth;
        h = bmpHeight;

     for (row=0; row<h; row++) 
     {       
         if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }
         
          for (col=0; col<w; col++) { // For each column...
            // read more pixel data
           if (buffidx >= sizeof(sdbuffer)) { 
             povidx = 0;         
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
           }
            // set pixel
            r = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            b = sdbuffer[buffidx++];
          //Serial.print(r);Serial.print(" ");Serial.print(g);Serial.print(" ");Serial.println(b);
          //we need to output GRB 24bit colour//
            //povbuffer[povidx++] =(g<<16) + (r<<8) +b; //original code is b r g, should be g r b? 
            povbuffer[povidx++] =(b<<16) + (g<<8) +r; //original code is b r g, should be g r b? 
            //povbuffer[povidx++] = Color_hex (r,g,b);
            //Serial.print(povbuffer[povidx++]);
          }
          
        for(int i=0;i<NUM_LEDS;i++){
          leds[i]=povbuffer[i];}
           FastLED.show();
           delay_image_scroll = g_dynParam * 2;
           //Serial.print (delay_image_scroll);
           delay(delay_image_scroll);// change the delay time depending effect required
          } // end scanline
 
      } // end goodBmp
    }
  }//end of IF BMP
  //Serial.println();
   
  bmpFile.close();
}

//*************Support Funcitons****************//
// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.
uint16_t read16(File& f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}
uint32_t read32(File& f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}




