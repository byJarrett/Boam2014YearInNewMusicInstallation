#include <MPR121_MOD.h>
#include <Wire.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>

#define baudRate 57600
#define cap1Addr 0x5A
#define cap2Addr 0x5B
#define cap3Addr 0x5C  //Touch board

#define STOP_PLAY 0

SFEMP3Shield MP3player;
SdFat sd;

MPR121_MOD_t cap = MPR121_MOD_t();
MPR121_MOD_t cap2 = MPR121_MOD_t();
MPR121_MOD_t cap3 = MPR121_MOD_t();

unsigned long touchPoints = 0;
unsigned long lastTouchPoints = 0;

#define TRACK_COUNT 60
const unsigned long _SongIds[TRACK_COUNT] = {
131073, 524289, 262146, 524290, 132096, 263168, 525312, 133120,
264192, 526336, 135168, 266240, 528384, 139264, 270336, 532480,
147456, 278528, 540672, 163840, 294912, 557056, 196608, 131076,
262148, 524292, 2228224, 1179648, 1310720, 1572864, 4325376,
4456448, 4718592, 16908288, 17039360, 17301504, 33685504,
33816576, 34078720, 67239936, 67371008, 67633152, 262152,
524296, 262160, 524304, 131104, 262208, 131200, 262272,
524416, 131328, 262400, 524544, 131584, 262656, 524800,
8519680, 8650752, 8912896
};


void setup() {
    if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
   
    Wire.begin();
    beginCap(&cap, cap1Addr);
    beginCap(&cap2, cap2Addr);
    beginCap(&cap3, cap3Addr);  

    delay(1000);
    byte result = MP3player.begin();   
    MP3player.setVolume(10, 10);   
}


void loop()
{
    updateCapTouchPoints();
  
    if(touchPoints != lastTouchPoints) {
        playSong();  
    }
    
    delay(500);
}


void beginCap(MPR121_MOD_t *cap, int addr)
{
    if (cap->begin(addr)) {
        cap->setTouchThreshold(12);
        cap->setReleaseThreshold(5);
    }
}


void playSong() {
    if(touchPoints == STOP_PLAY)
    {
        MP3player.stopTrack();            
    }  
    else
    {   
        bool isValidTrack = false;     
        for(int i = 0; i < TRACK_COUNT; i++)
        {
            if(_SongIds[i] == touchPoints)
            {
                MP3player.playTrack(i);
                isValidTrack = true;
                break;  
            }
        }    
        
        if(!isValidTrack)
        {
            MP3player.stopTrack();  
        }      
    }  
}


void updateCapTouchPoints() {
    unsigned long touchInput = 0;
    lastTouchPoints = touchPoints;
    
    /* 
     * 
     *  There are only 27 input (panel 1: 3, panel 2: 17, panel 3: 7).
     *  A 32-bit (unsigned long) is used to hold the input. 
     *  The input at address A will be bits 0-11; address B is 12-23; and address C is 24-26.
     *  Bits 27-31 of the variable will be unused.  The input board at address C will 
     *  have 9 unused leads. 
     *
     *  
     *
     */
    
    touchPoints = 0;
    
    cap.updateTouchData();    
    touchPoints = cap.getRawTouchData();

    cap2.updateTouchData();
    touchInput = cap2.getRawTouchData();
    touchPoints += touchInput << 12;

    cap3.updateTouchData();    
    touchInput = cap3.getRawTouchData();
    touchPoints += (touchInput & 0xFF) << 24;
}
