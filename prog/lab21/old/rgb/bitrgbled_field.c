#include <stdlib.h> // malloc, free
#include "bitrgbled_field.h"

// malloc new structure
rgbled_field *rgbled_field_create(void) {
  rgbled_field* rgbled = (rgbled_field*)malloc(sizeof(rgbled_field));
  rgbled->red = 0;
  rgbled->green = 0;
  rgbled->blue = 0;
  rgbled->bright = 0;
  rgbled->temp = 0;
  rgbled->type = 0;
  rgbled->mode = 0;
  return rgbled;
}

// free memory
void rgbled_field_free(rgbled_field* rgbled) {
  free(rgbled);
}

// some functions to get a specific value from rgbled_field structure
unsigned char rgbled_field_get_red(rgbled_field* rgbled) {
  return rgbled->red;
}

unsigned char rgbled_field_get_green(rgbled_field* rgbled) {
  return rgbled->green;
}

unsigned char rgbled_field_get_blue(rgbled_field* rgbled) {
  return rgbled->blue;
}

unsigned char rgbled_field_get_bright(rgbled_field* rgbled) {
  return rgbled->bright;
}

unsigned short rgbled_field_get_temp(rgbled_field* rgbled) {
  return rgbled->temp;
}

unsigned char rgbled_field_get_type(rgbled_field* rgbled) {
  return rgbled->type;
}

unsigned char rgbled_field_get_mode(rgbled_field* rgbled) {
  return rgbled->mode;
}

// some functions to set a specific value from rgbled_field structure
void rgbled_field_set_red(rgbled_field* rgbled, unsigned char red) {
  rgbled->red = red;
}

void rgbled_field_set_green(rgbled_field* rgbled, unsigned char green) {
  rgbled->green = green;
}

void rgbled_field_set_blue(rgbled_field* rgbled, unsigned char blue) {
  rgbled->blue = blue;
}

void rgbled_field_set_bright(rgbled_field* rgbled, unsigned char bright) {
  rgbled->bright = bright;
}

void rgbled_field_set_temp(rgbled_field* rgbled, unsigned short temp) {
  rgbled->temp = temp;
}

void rgbled_field_set_type(rgbled_field* rgbled, unsigned char type) {
  rgbled->type = type;
}

void rgbled_field_set_mode(rgbled_field* rgbled, unsigned char mode) {
  rgbled->mode = mode;
}
