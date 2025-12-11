typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;
typedef unsigned long uint64;
typedef uint64 pde_t;
struct datetime {
  uint8 hour;
  uint8 minute;
  uint8 second;
  uint16 year;
  uint8 month;
  uint8 day;
};
