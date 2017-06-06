#include "Arduino.h"

#ifndef DatashowNEC_h
#define DatashowNEC_h


const int nbits = 32;
const unsigned long  POWER_ON    = 0x189710EF;
const unsigned long  POWER_OFF   = 0x189728D7;
const unsigned long  AUTO_ADJ    = 0x1897609F;
const unsigned long  NUM0        = 0x1897827D;
const unsigned long  NUM1        = 0x189720DF;
const unsigned long  NUM2        = 0x1897A05F;
const unsigned long  NUM3        = 0x1897AA55;
const unsigned long  NUM4        = 0x1897C03F;
const unsigned long  NUM5        = 0x1897639C;
const unsigned long  NUM6        = 0x18972AD5;
const unsigned long  NUM7        = 0x1897E41B;
const unsigned long  NUM8        = 0x18976A95;
const unsigned long  NUM9        = 0x18974AB5;
const unsigned long  ID_SET      = 0x189752AD;
const unsigned long  CLEAR       = 0x189742BD;
const unsigned long  AV_MUTE     = 0x1897E21D;
const unsigned long  FREEZE      = 0x189732CD;
const unsigned long  EXIT        = 0x1897A45B;
const unsigned long  MENU        = 0x1897629D;
const unsigned long  ARROW_UP    = 0x18971DE2;
const unsigned long  ARROW_DOWN  = 0x18973DC2;
const unsigned long  ARROW_LEFT  = 0x18977D82;
const unsigned long  ARROW_RIGHT = 0x18975DA2;
const unsigned long  ENTER       = 0x1897E817;
const unsigned long  ZOOM_PLUS   = 0x1897916E;
const unsigned long  ZOOM_MINUS  = 0x189751AE;
const unsigned long  PAGE_UP     = 0x189754AB;
const unsigned long  PAGE_DOWN   = 0x1897D42B;
const unsigned long  L_CLICK     = 0x189734CB;
const unsigned long  R_CLICK     = 0x1897B44B;
const unsigned long  ECO         = 0x18976897;
const unsigned long  KEYSTONE    = 0x189701FE;
const unsigned long  PICTURE     = 0x1897B04F;
const unsigned long  HELP        = 0x1897728D;
const unsigned long  FOCUS       = 0x189705FA;
const unsigned long  ASPECT      = 0x189708F7;
const unsigned long  VOL_UP      = 0x189712ED;
const unsigned long  VOL_DOWN    = 0x1897926D;



class DatashowNEC{

  private:
    IRsend irsend;
  public:
    DatashowNEC();
    void btn_powerOn();
    void btn_powerOff();
    void btn_autoAdj();
    void btn_num0();
    void btn_num1();
    void btn_num2();
    void btn_num3();
    void btn_num4();
    void btn_num5();
    void btn_num6();
    void btn_num7();
    void btn_num8();
    void btn_num9();
    void btn_idSet();
    void btn_clear();
    void btn_avMute();
    void btn_freeze();
    void btn_exit();
    void btn_menu();
    void btn_arrowUp();
    void btn_arrowDown();
    void btn_arrowLeft();
    void btn_arrowRight();
    void btn_enter();
    void btn_zoomPlus();
    void btn_zoomMinus();
    void btn_pageUp();
    void btn_pageDown();
    void btn_lClick();
    void btn_rClick();
    void btn_echo();
    void btn_keystone();
    void btn_picture();
    void btn_help();
    void btn_focus();
    void btn_aspect();
    void btn_volUp();
    void btn_volDown();



};

#endif

