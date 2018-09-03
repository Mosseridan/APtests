# 1016
static unsigned short int
__bswap_16 (unsigned short int __bsx)
{ 
  return ((unsigned short int) ((((__bsx) >> 8) & 0xff) | (((__bsx) & 0xff) << 8))); 
}
