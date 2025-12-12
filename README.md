# DoomGeneric_Project

DoomOS – A Bare-Metal DOOM Unikernel

DoomOS is a 32-bit operating system kernel designed to boot directly into the original DOOM game.
It began as an expansion of our PeachOS kernel (complete with shell + filesystem), but was later redesigned into a unikernel that gives the DOOM engine direct access to hardware—for maximum speed and simplicity.

This OS runs DOOM with:

Direct VGA Mode 13h graphics

Raw keyboard scancode input

PIT timer-driven game loop

A minimalistic, game-focused kernel

Features
| Component     | Original PeachOS                | New DoomOS                                 |
| ------------- | ------------------------------- | ------------------------------------------ |
| **Boot Mode** | VGA Text Mode (0xB8000)         | VGA Graphics Mode 13h (0xA0000)            |
| **Kernel**    | Multitasking, Shell, Filesystem | Single-task Game Loop                      |
| **Input**     | ASCII character stream          | Raw scancode → DOOM event queue            |
| **Memory**    | 16 MB Heap                      | 48 MB Heap (for DOOM binary + WAD loading) |
| **Storage**   | Full Disk Driver                | Lightweight PIO WAD Loader                 |
| **Libraries** | Custom minimal libc             | Slimmed stdlib/stdio/string                |


Prerequisites
You need a Linux system (Ubuntu, Debian, or WSL2) with:

Build Tools
make
nasm
gcc
bison
flex
libgmp3-dev
libmpc-dev
libmpfr-dev
texinfo

Emulator
qemu-system-x86

Game Assets

DOOM1.WAD (shareware WAD)

🛠 Installation — Ubuntu/Debian/WSL
sudo apt-get update
sudo apt-get install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo nasm qemu-system-x86

🔧 Step 1 — Build the Cross Compiler

You must build an i686-elf cross-compiler.
This project will not compile using your system GCC.

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p $HOME/src
cd $HOME/src

Download Sources

Binutils: https://ftp.gnu.org/gnu/binutils

GCC: https://ftp.lip6.fr/pub/gcc/releases/gcc-10.2.0

Build Binutils
mkdir build-binutils
cd build-binutils
../binutils-2.35/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

Build GCC
mkdir build-gcc
cd build-gcc
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-werror
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

🔧 Step 2 — Download DoomGeneric

The kernel links against DoomGeneric.

From the project root:

git clone https://github.com/ozkl/doomgeneric.git src/doomgeneric

🔧 Step 3 — Add DOOM WAD

Place DOOM1.WAD (shareware allowed) in the project root:

./DOOM1.WAD

🏗️ Building DoomOS

Make sure the cross-compiler is active in your PATH:

export PATH="$HOME/opt/cross/bin:$PATH"

Build:
./build.sh


Or:

make all

Output:

A bootable OS image is generated at:

./bin/os.bin

Running DoomOS in QEMU
qemu-system-i386 -drive format=raw,file=./bin/os.bin -m 512M

Controls
Action	Key
Move / Turn	Arrow Keys
Fire	Left Ctrl
Open / Use	Space
Menu Select	Enter

Summary of Architectural Changes

DoomOS evolved from a learning OS into a full game unikernel for DOOM.
By removing the shell, filesystem, multitasking, and desktop abstractions, the DOOM engine runs directly on hardware with maximum determinism.
