#include <stdio.h>
#include "bitrgbled_field.h"
#include "bitrgbled_ops.h"

void print_field(rgbled_field* rgbled) {
  printf("size: %zu bytes\n", sizeof(rgbled_field));
  printf("red = %u\n", rgbled_field_get_red(rgbled));
  printf("green = %u\n", rgbled_field_get_green(rgbled));
  printf("blue = %u\n", rgbled_field_get_blue(rgbled));
  printf("bright = %u\n", rgbled_field_get_bright(rgbled));
  printf("temp = %u\n", rgbled_field_get_temp(rgbled));
  printf("type = %u\n", rgbled_field_get_type(rgbled));
  printf("mode = %u\n", rgbled_field_get_mode(rgbled));
}

void print_ops(rgbled_ops* rgbled) {
  printf("size: %zu bytes\n", sizeof(rgbled_field));
  printf("red = %u\n", rgbled_ops_get_red(rgbled));
  printf("green = %u\n", rgbled_ops_get_green(rgbled));
  printf("blue = %u\n", rgbled_ops_get_blue(rgbled));
  printf("bright = %u\n", rgbled_ops_get_bright(rgbled));
  printf("temp = %u\n", rgbled_ops_get_temp(rgbled));
  printf("type = %u\n", rgbled_ops_get_type(rgbled));
  printf("mode = %u\n", rgbled_ops_get_mode(rgbled));
}

int main() {
  rgbled_field* rgbled_field = rgbled_field_create();
  printf("Rgbled with bit FIELD\n\n");
  print_field(rgbled_field);
  putchar('\n');
  
  rgbled_field_set_temp(rgbled_field, 17000);
  printf("temp = %u\n", rgbled_field_get_temp(rgbled_field));
  putchar('\n');
  
  rgbled_field_set_mode(rgbled_field, 2);
  rgbled_field_set_red(rgbled_field, 255);
  rgbled_field_set_green(rgbled_field, 256);
  rgbled_field_set_blue(rgbled_field, 255);
  rgbled_field_set_bright(rgbled_field, 175);
  rgbled_field_set_type(rgbled_field, 4);
  rgbled_field_set_temp(rgbled_field, 10000);

  print_field(rgbled_field);

  putchar('\n');
  putchar('\n');
  putchar('\n');

  rgbled_ops* rgbled_ops = rgbled_ops_create();
  printf("Rgbled with bitwise OPERATIONS\n");
  print_ops(rgbled_ops);
  putchar('\n');
  
  rgbled_ops_set_temp(rgbled_ops, 17000);
  printf("temp = %u\n", rgbled_ops_get_temp(rgbled_ops));
  putchar('\n');
  
  rgbled_ops_set_mode(rgbled_ops, 2);
  rgbled_ops_set_red(rgbled_ops, 255);
  rgbled_ops_set_green(rgbled_ops, 256);
  rgbled_ops_set_blue(rgbled_ops, 255);
  rgbled_ops_set_bright(rgbled_ops, 175);
  rgbled_ops_set_type(rgbled_ops, 4);
  rgbled_ops_set_temp(rgbled_ops, 10000);

  print_ops(rgbled_ops);
  
  rgbled_field_free(rgbled_field);
  rgbled_ops_free(rgbled_ops);

  return 0;
}
