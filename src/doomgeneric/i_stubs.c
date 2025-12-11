// Stub implementations for Doom platform functions
#include "doomtype.h"
#include "doomkeys.h"
#include <stdlib.h>

// Video buffer and graphics stubs
byte* I_VideoBuffer = NULL;
int usegamma = 0;
int screensaver_mode = 0;
int usemouse = 0;
float mouse_acceleration = 1.0f;
int mouse_threshold = 10;
int snd_musicdevice = 0;
int screenvisible = 1;

void I_StartTic(void)
{
    // Input handled in DG_GetKey
}

void I_UpdateNoBlit(void)
{
    // No-op for doomgeneric
}

void I_FinishUpdate(void)
{
    // Handled by DG_DrawFrame
}

void I_SetPalette(byte* palette)
{
    (void)palette;
    // Palette handled in rendering
}

void I_InitGraphics(void)
{
    // Graphics initialized in DG_Init
}

void I_ShutdownGraphics(void)
{
    // No cleanup needed
}

void I_StartFrame(void)
{
    // No-op
}

void I_BindVideoVariables(void)
{
    // No video variables to bind
}

void I_GraphicsCheckCommandLine(void)
{
    // No command line options
}

void I_SetGrabMouseCallback(void (*func)(void))
{
    (void)func;
    // No mouse grab
}

void I_EnableLoadingDisk(void)
{
    // No loading disk indicator
}

void I_SetWindowTitle(const char* title)
{
    (void)title;
    // No window title in kernel
}

void I_DisplayFPSDots(int dots_on)
{
    (void)dots_on;
    // No FPS display
}

int I_GetPaletteIndex(int r, int g, int b)
{
    // Simple palette index calculation
    return ((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6);
}

void I_ReadScreen(byte* scr)
{
    (void)scr;
    // No screen capture needed
}

// Sound stubs
void I_InitSound(void)
{
    // No sound support
}

void I_ShutdownSound(void)
{
    // No sound support
}

void I_InitMusic(void)
{
    // No music support
}

void I_ShutdownMusic(void)
{
    // No music support
}

void I_BindSoundVariables(void)
{
    // No sound variables
}

void I_SetMusicVolume(int volume)
{
    (void)volume;
}

void I_PauseSong(void)
{
}

void I_ResumeSong(void)
{
}

void I_UpdateSound(void)
{
}

int I_SoundIsPlaying(int handle)
{
    (void)handle;
    return 0;
}

void I_StopSound(int handle)
{
    (void)handle;
}

int I_GetSfxLumpNum(void* sfxinfo)
{
    (void)sfxinfo;
    return 0;
}

int I_StartSound(void* sfxinfo, int channel, int vol, int sep)
{
    (void)sfxinfo;
    (void)channel;
    (void)vol;
    (void)sep;
    return 0;
}

void I_UpdateSoundParams(int channel, int vol, int sep)
{
    (void)channel;
    (void)vol;
    (void)sep;
}

void I_PrecacheSounds(void* sounds, int num_sounds)
{
    (void)sounds;
    (void)num_sounds;
}

void* I_RegisterSong(void* data, int len)
{
    (void)data;
    (void)len;
    return NULL;
}

void I_UnRegisterSong(void* handle)
{
    (void)handle;
}

void I_PlaySong(void* handle, int looping)
{
    (void)handle;
    (void)looping;
}

void I_StopSong(void)
{
}

int I_MusicIsPlaying(void)
{
    return 0;
}

// File I/O stubs
void I_BeginRead(void)
{
}

void I_EndRead(void)
{
}

// System stubs
int I_CheckIsScreensaver(void)
{
    return 0;
}

// stdlib functions
int remove(const char* path)
{
    (void)path;
    return -1;
}

int rename(const char* old, const char* new)
{
    (void)old;
    (void)new;
    return -1;
}

int system(const char* command)
{
    (void)command;
    return -1;
}

// Math function for 64-bit division (required by FixedDiv)
long long __divdi3(long long a, long long b)
{
    return a / b;
}

// fabs - floating point absolute value
double fabs(double x)
{
    return x < 0.0 ? -x : x;
}