# 1023
static unsigned int
__bswap_32 (unsigned int __bsx)
{ 
  return ((((__bsx) & 0xff000000) >> 24) | (((__bsx) & 0x00ff0000) >> 8) | (((__bsx) & 0x0000ff00) << 8) | (((__bsx) & 0x000000ff) << 24)); 
}
