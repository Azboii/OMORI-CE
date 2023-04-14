/*
 *--------------------------------------
 * Program Name: OMORI
 * Author: Devon Shoutz
 * License:
 * Description: OMORI for the TI-84 Plus CE
 *--------------------------------------
*/

#include <graphx.h>
#include <sys/rtc.h>
#include <keypadc.h>

#include "utils.h"
#include "title.h"

int main(void)
{
    setup();

    int x = 0;
    int y = 0;

    int seconds = 0;
    
    int menu = 1;
    bool menu_lock = false;
    int selected = 0;
    int Hand_pos = 135;

    rtc_Enable(RTC_SEC_INT);

    Utils::drawTitleScreen(0,Hand_pos);

    while (rtc_IsBusy());

    rtc_AckInterrupt(RTC_INT_MASK);

    MENU:do {

        if (rtc_ChkInterrupt(RTC_SEC_INT))
        {
            seconds++;
            if (seconds > 3) {
                seconds = 1;
            }
            rtc_AckInterrupt(RTC_SEC_INT);
        }

        if (seconds == 1) {
            Utils::drawTitleScreen(0,Hand_pos);
        } else if (seconds == 2) {
            Utils::drawTitleScreen(1,Hand_pos);
        } else if (seconds == 3) {
            Utils::drawTitleScreen(2,Hand_pos);
        }
        
        if (!Utils::getButtonDown(0) && !Utils::getButtonDown(1)) {
            menu_lock = false;
        }

        if (Utils::getButtonDown(0) && !Utils::getButtonDown(1) && !menu_lock) {
            menu--; 
            menu_lock = true;
        } else if (Utils::getButtonDown(1) && !Utils::getButtonDown(0) && !menu_lock) {
            menu++; 
            menu_lock = true;
        }

        if (menu < 0) {
            menu = 2;
        }
        if (menu > 2) {
            menu = 0;
        }

        if (menu == 0) {
            Hand_pos = 25 + 100 * menu;
        } else {
            Hand_pos = 35 + 100 * menu;
        }
        
        bool key = false;
        bool prevkey = false;
        key = kb_Data[1] == kb_2nd;

        if (key != prevkey) {
            selected = (menu + 1);
        }
        prevkey = key;

    } while (selected == 0);

    if (selected == 3) {
        goto MENU;
    }

    // while (rtc_IsBusy());

    // rtc_AckInterrupt(RTC_INT_MASK);

    /*while (seconds < 5)
    {
        if (rtc_ChkInterrupt(RTC_SEC_INT))
        {
            seconds++;

            rtc_AckInterrupt(RTC_SEC_INT);
        }
    }*/

    Utils::drawCharacter(x, y, None);

    do {

        kb_Scan();

        if (Utils::getButtonDown(0) && !Utils::getButtonDown(1))
        {
            x--; // Left
            Utils::drawCharacter(x, y, None);
        } else if (Utils::getButtonDown(1) && !Utils::getButtonDown(0)) {
            x++; // Right
            Utils::drawCharacter(x, y, None);
        }

        if (Utils::getButtonDown(2) && !Utils::getButtonDown(3))
        {
            y--; // Up
            Utils::drawCharacter(x, y, None);
        } else if (Utils::getButtonDown(3) && !Utils::getButtonDown(2))
        {
            y++; // Down
            Utils::drawCharacter(x, y, Down);
        }

    } while( kb_Data[6] != kb_Clear);
    
    gfx_End();
    
    return 0;
}
