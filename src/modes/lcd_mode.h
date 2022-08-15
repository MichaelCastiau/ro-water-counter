#ifndef __LCD_MODE__
#define __LCD_MODE__

class LCDMode
{
public:
    virtual void buttonPressed() = 0;
    virtual void rotatedLeft() = 0;
    virtual void rotatedRight() = 0;
};

#endif