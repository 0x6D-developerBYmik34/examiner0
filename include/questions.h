#pragma once 

#include <avr/pgmspace.h>

#define MAX_QUESTIONS 30

static const char str1[] PROGMEM = "razreshen li proezd na krasnyj?";
static const char str2[] PROGMEM = "razreshen li proezd na zelenyj?";
static const char str3[] PROGMEM = "razreshen li proezd na zhyoltyj?";
static const char str4[] PROGMEM = "Razreshen li obgon po obochine?";
static const char str5[] PROGMEM = "Mozhno li buksirovat' ts bez voditelya?";
static const char str6[] PROGMEM = "Razreshen li signal v zhilyh zonah?";
static const char str7[] PROGMEM = "razreshen li povort slevo napravo?";
static const char str8[] PROGMEM = "razreshen li povort spravoj nalevo?";
static const char str9[] PROGMEM = "Razreshen li obgon posle OBGON ZAPRESHCHEN?";
static const char str10[] PROGMEM = "razresheno li dvzhienie posle zka KIRPICH?";
static const char str11[] PROGMEM = "Razresheno li dvizhenie posle ODNOSTOR DVIZHENIE?";
static const char str12[] PROGMEM = "Obyazan li voditel predostavit TS spec sluzbam?";
static const char str13[] PROGMEM = "Nalichie svet otrazh zhileta v TS?";
static const char str14[] PROGMEM = "Podchinyaetsya li vodtel' regulirovshchiku?";
static const char str15[] PROGMEM = "Obyazan voditel' ostanov pri VOENPOLICI?";
static const char str16[] PROGMEM = "Ustupayut li dorogo avto spravo?";
static const char str17[] PROGMEM = "S kategoriej V mozhno li pricep ceplyat?";
static const char str18[] PROGMEM = "Razreshen li obgon po obochine?";
static const char str19[] PROGMEM = "Daet li V kategorie upravlenie mopedom?";
static const char str20[] PROGMEM = "Daet li V kategorie upravlenie motocikl?";
static const char str21[] PROGMEM = "Daet li A kategorie upravlenie motocikl?";
static const char str22[] PROGMEM = "Mozhno li proezzhat' na krasnyj svet?";
static const char str23[] PROGMEM = "Razresheno li peresekat' dv sploshnuyu?";
static const char str24[] PROGMEM = "Razreshen li razvorot dv sploshnuyu?";
static const char str25[] PROGMEM = "Nuzhnye li ponyatye pri osmotre ts?";
static const char str26[] PROGMEM = "Mozhno li peredvigat'sya bez prav?";
static const char str27[] PROGMEM = "Obyazan li voditel' pristegnut'sya?";
static const char str28[] PROGMEM = "Mozhno li ezdit' bez vkl far?";
static const char str29[] PROGMEM = "Mozhno li ezdit' bez strahovki?";
static const char str30[] PROGMEM = "Mozhno li ezdit' bez dvornikov?";

const char * const mystrs[] = {
  str1, str2, str3, str4, str5, str6, 
  str7, str8, str8, str9, str10,
  str11, str12, str13, str14, str15, 
  str16, str17, str18, str19, str20,
  str21, str22, str23, str23, str24, 
  str25, str26, str27, str28, str29, str30
};
