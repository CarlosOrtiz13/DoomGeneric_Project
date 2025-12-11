#ifndef DISKSTREAMER_H
#define DISKSTREAMER_H

#include "disk.h"
/*simple stream abstraction for reading from a disk*/
struct disk_stream
{
    int pos; /*current position in bytes*/
    struct disk* disk; /*disk this stream reads from*/
};
/*create a new stream for the given disk*/
struct disk_stream* diskstreamer_new(int disk_id);
/*set the current position of the stream*/
int diskstreamer_seek(struct disk_stream* stream, int pos);
/*read bytes from the disk into the output buffer*/
int diskstreamer_read(struct disk_stream* stream, void* out, int total);
/*close the stream and free its memory*/
void diskstreamer_close(struct disk_stream* stream);

#endif
