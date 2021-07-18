#include <M5Core2.h>
#include "MyConfig.h"

void setup() {
    M5.begin();
    myConfig.setup();
}

void loop() {
    myConfig.show();
    M5.update(); 
    if (M5.BtnA.wasPressed()) {                     
        myConfig.pageDown();
    }
    if (M5.BtnB.wasPressed()) {                     
        myConfig.pageTurn0();
    }
    if (M5.BtnC.wasPressed()) {                     
        myConfig.pageUp();
    }    
}
