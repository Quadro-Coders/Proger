// fields for red 
#define RED_OFFSET 0
#define RED_BITS 8
#define RED_MASK ((1ULL << RED_BITS) - 1)

// fields for green
#define GREEN_OFFSET 8
#define GREEN_BITS 8
#define GREEN_MASK ((1ULL << GREEN_BITS) - 1)

// fields for blue 
#define BLUE_OFFSET 16
#define BLUE_BITS 8
#define BLUE_MASK ((1ULL << BLUE_BITS) - 1)

// fields for bright 
#define BRIGHT_OFFSET 24
#define BRIGHT_BITS 8
#define BRIGHT_MASK ((1ULL << BRIGHT_BITS) - 1)

// fields for temp 
#define TEMP_OFFSET 32
#define TEMP_BITS 14
#define TEMP_MASK ((1ULL << TEMP_BITS) - 1)

// fields for type
#define TYPE_OFFSET 46
#define TYPE_BITS 2
#define TYPE_MASK ((1ULL << TYPE_BITS) - 1)

// fields for mode
#define MODE_OFFSET 48
#define MODE_BITS 2
#define MODE_MASK ((1ULL << MODE_BITS) - 1)

// structure
typedef struct {
  unsigned long long data;
} rgbled_ops;

// memory functions
rgbled_ops *rgbled_ops_create(void); // malloc new structure
void rgbled_ops_free(rgbled_ops*); // free memory

// some functions to get a specific value from rgbled_ops structure
unsigned char rgbled_ops_get_red(rgbled_ops*);
unsigned char rgbled_ops_get_green(rgbled_ops*);
unsigned char rgbled_ops_get_blue(rgbled_ops*);
unsigned char rgbled_ops_get_bright(rgbled_ops*);
unsigned short rgbled_ops_get_temp(rgbled_ops*);
unsigned char rgbled_ops_get_type(rgbled_ops*);
unsigned char rgbled_ops_get_mode(rgbled_ops*);

// some functions to set a specific value from rgbled_ops structure
void rgbled_ops_set_red(rgbled_ops*, unsigned char);
void rgbled_ops_set_green(rgbled_ops*, unsigned char);
void rgbled_ops_set_blue(rgbled_ops*, unsigned char);
void rgbled_ops_set_bright(rgbled_ops*, unsigned char);
void rgbled_ops_set_temp(rgbled_ops*, unsigned short);
void rgbled_ops_set_type(rgbled_ops*, unsigned char);
void rgbled_ops_set_mode(rgbled_ops*, unsigned char);
