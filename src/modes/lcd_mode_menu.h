#ifndef __LCD_MODE_MENU__
#define __LCD_MODE_MENU__

#include "lcd_mode.h"

class LCDModeMenu : public LCDMode
{
public:
    LCDModeMenu();
    virtual ~LCDModeMenu();
    virtual void buttonPressed();
    virtual void rotatedLeft();
    virtual void rotatedRight();
};
#endif