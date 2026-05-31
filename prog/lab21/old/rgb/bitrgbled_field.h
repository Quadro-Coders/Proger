typedef struct {
    unsigned int red : 8;
    unsigned int green : 8;
    unsigned int blue : 8;
    unsigned int bright : 8;
    unsigned int temp : 14;
    unsigned int type : 2;
    unsigned int mode : 2;
} rgbled_field;

rgbled_field *rgbled_field_create(void); // malloc new structure
void rgbled_field_free(rgbled_field*); // free memory

// some functions to get a specific value from rgbled_field structure
unsigned char rgbled_field_get_red(rgbled_field*);
unsigned char rgbled_field_get_green(rgbled_field*);
unsigned char rgbled_field_get_blue(rgbled_field*);
unsigned char rgbled_field_get_bright(rgbled_field*);
unsigned short rgbled_field_get_temp(rgbled_field*);
unsigned char rgbled_field_get_type(rgbled_field*);
unsigned char rgbled_field_get_mode(rgbled_field*);

// some functions to set a specific value from rgbled_field structure
void rgbled_field_set_red(rgbled_field*, unsigned char);
void rgbled_field_set_green(rgbled_field*, unsigned char);
void rgbled_field_set_blue(rgbled_field*, unsigned char);
void rgbled_field_set_bright(rgbled_field*, unsigned char);
void rgbled_field_set_temp(rgbled_field*, unsigned short);
void rgbled_field_set_type(rgbled_field*, unsigned char);
void rgbled_field_set_mode(rgbled_field*, unsigned char);
