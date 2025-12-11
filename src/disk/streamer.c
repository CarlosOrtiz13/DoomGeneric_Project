#include "streamer.h"
#include "memory/heap/kheap.h"
#include "config.h"
/*create a new disk stream for the given disk*/
struct disk_stream* diskstreamer_new(int disk_id)
{
    struct disk* disk = disk_get(disk_id);
    if (!disk)
    {
        return 0;
    }
/*allocate and initialize stream*/
    struct disk_stream* streamer = kzalloc(sizeof(struct disk_stream));
    streamer->pos = 0;
    streamer->disk = disk;
    return streamer;
}
/*move the stream position*/
int diskstreamer_seek(struct disk_stream* stream, int pos)
{
    stream->pos = pos;
    return 0;
}
/*read bytes from disk starting at current stream poistion*/
int diskstreamer_read(struct disk_stream* stream, void* out, int total)
{
    /*figure out which sector and offset we are at*/
    int sector = stream->pos / PEACHOS_SECTOR_SIZE;
    int offset = stream->pos % PEACHOS_SECTOR_SIZE;
    char buf[PEACHOS_SECTOR_SIZE];

    /*read one sector into a temp buffer*/    
    int res = disk_read_block(stream->disk, sector, 1, buf);
    if (res < 0)
    {
        goto out;
    }
    /*dont read past the sector boundary*/
    int total_to_read = total > PEACHOS_SECTOR_SIZE ? PEACHOS_SECTOR_SIZE : total;
    for (int i = 0; i < total_to_read; i++)
    {
        *(char*)out++ = buf[offset+i];
    }

    // Adjust the stream
    stream->pos += total_to_read;
    /*if we need more data, continue into the next sector*/
    if (total > PEACHOS_SECTOR_SIZE)
    {
        res = diskstreamer_read(stream, out, total-PEACHOS_SECTOR_SIZE);
    }
out:
    return res;
}
/*free the stream structure*/
void diskstreamer_close(struct disk_stream* stream)
{
    kfree(stream);
}
