#include <string.h>
#include "w_file.h"
#include "z_zone.h"

// External reference to embedded WAD
extern unsigned char doom1_wad[];
extern unsigned int doom1_wad_len;

typedef struct
{
    wad_file_t wad;
    unsigned char* data;
    unsigned int length;
    unsigned int position;
} mem_wad_file_t;

static wad_file_t *W_Mem_OpenFile(char *path)
{
    mem_wad_file_t *result;
    
    // Allocate structure
    result = Z_Malloc(sizeof(mem_wad_file_t), PU_STATIC, 0);
    
    result->data = doom1_wad;
    result->length = doom1_wad_len;
    result->position = 0;
    
    return &result->wad;
}

static void W_Mem_CloseFile(wad_file_t *wad)
{
    mem_wad_file_t *mem_wad = (mem_wad_file_t *)wad;
    Z_Free(mem_wad);
}

static size_t W_Mem_Read(wad_file_t *wad, unsigned int offset,
                         void *buffer, size_t buffer_len)
{
    mem_wad_file_t *mem_wad = (mem_wad_file_t *)wad;
    
    if (offset >= mem_wad->length)
        return 0;
    
    if (offset + buffer_len > mem_wad->length)
        buffer_len = mem_wad->length - offset;
    
    memcpy(buffer, mem_wad->data + offset, buffer_len);
    return buffer_len;
}

wad_file_class_t mem_wad_file = 
{
    W_Mem_OpenFile,
    W_Mem_CloseFile,
    W_Mem_Read,
};