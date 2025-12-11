#include <stdint.h>

extern unsigned char doom1_wad[];
extern unsigned int doom1_wad_len;

const unsigned char* PeachOS_GetWadData(uint32_t* size_out)
{
    if (size_out)
        *size_out = doom1_wad_len;

    return doom1_wad;
}
