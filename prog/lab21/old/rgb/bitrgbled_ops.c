#include <stdlib.h> // malloc, free
#include "bitrgbled_ops.h"

// malloc new structure
rgbled_ops *rgbled_ops_create(void) {
  rgbled_ops* rgbled = (rgbled_ops*)malloc(sizeof(rgbled_ops));
  rgbled->data = 0;
  return rgbled;
}

// free memory
void rgbled_ops_free(rgbled_ops* rgbled) {
  free(rgbled);
}

// some functions to get a specific value from rgbled_ops structure
unsigned char rgbled_ops_get_red(rgbled_ops* rgbled) {
  return (rgbled->data >> RED_OFFSET) & RED_MASK;
}

unsigned char rgbled_ops_get_green(rgbled_ops* rgbled) {
  return (rgbled->data >> GREEN_OFFSET) & GREEN_MASK;
}

unsigned char rgbled_ops_get_blue(rgbled_ops* rgbled) {
  return (rgbled->data >> BLUE_OFFSET) & BLUE_MASK;
}

unsigned char rgbled_ops_get_bright(rgbled_ops* rgbled) {
  return (rgbled->data >> BRIGHT_OFFSET) & BRIGHT_MASK;
}

unsigned short rgbled_ops_get_temp(rgbled_ops* rgbled) {
  return (rgbled->data >> TEMP_OFFSET) & TEMP_MASK;
}

unsigned char rgbled_ops_get_type(rgbled_ops* rgbled) {
  return (rgbled->data >> TYPE_OFFSET) & TYPE_MASK;
}

unsigned char rgbled_ops_get_mode(rgbled_ops* rgbled) {
  return (rgbled->data >> MODE_OFFSET) & MODE_MASK;
}

// some functions to set a specific value from rgbled_ops structure
void rgbled_ops_set_red(rgbled_ops* rgbled, unsigned char red) {
  rgbled->data &= ~(RED_MASK << RED_OFFSET);
  rgbled->data |= ((red & RED_MASK) << RED_OFFSET);
}

void rgbled_ops_set_green(rgbled_ops* rgbled, unsigned char green) {
  rgbled->data &= ~(GREEN_MASK << GREEN_OFFSET);
  rgbled->data |= ((green & GREEN_MASK) << GREEN_OFFSET);
}

void rgbled_ops_set_blue(rgbled_ops* rgbled, unsigned char blue) {
  rgbled->data &= ~(BLUE_MASK << BLUE_OFFSET);
  rgbled->data |= ((blue & BLUE_MASK) << BLUE_OFFSET);
}

void rgbled_ops_set_bright(rgbled_ops* rgbled, unsigned char bright) {
  rgbled->data &= ~(BRIGHT_MASK << BRIGHT_OFFSET);
  rgbled->data |= ((bright & BRIGHT_MASK) << BRIGHT_OFFSET);
}

void rgbled_ops_set_temp(rgbled_ops* rgbled, unsigned short temp) {
  rgbled->data &= ~(TEMP_MASK << TEMP_OFFSET);
  rgbled->data |= ((temp & TEMP_MASK) << TEMP_OFFSET);
}

void rgbled_ops_set_type(rgbled_ops* rgbled, unsigned char type) {
  rgbled->data &= ~(TYPE_MASK << TYPE_OFFSET);
  rgbled->data |= ((type & TYPE_MASK) << TYPE_OFFSET);
}

void rgbled_ops_set_mode(rgbled_ops* rgbled, unsigned char mode) {
  rgbled->data &= ~(MODE_MASK << MODE_OFFSET);
  rgbled->data |= ((mode & MODE_MASK) << MODE_OFFSET);
}
