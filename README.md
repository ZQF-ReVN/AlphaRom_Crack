# AlphaRom_Crack
a project to show how to crack a alpharom protected game

## Quick Start
An example of how to use this library

- requires
  - [git](https://git-scm.com/) `>=any`
  - [xmake](https://xmake.io/)  `>=v2.9.1`
  - [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)(with c++)  `>=v17.9.6`
- clone project
```shell
> git clone --depth=1 https://github.com/Dir-A/AlphaRom_Crack.git
```
- cd to `quick-start` dir
  - you can copy `quick-start` folder anywhere
```shell
> cd /d test/quick-start/
```
- open with vs
  - allows you to use it like a sln project
```shell
> xmake_open_vs.dat
```
- build
  - binary file is output to `quick-start/build/windows/x86/`
```shell
> xmake_build.bat
```

## Debug or modify library
If you want to debug or modify the library
- install all requires described in Quick Start
- clone project
- familiar with xmake
  - do what you need to do.
- never heard of xmake
  - click xmake_open_vs.bat than work with vs
## How AlphaRom works？
first we need to know the game that protected by alpharom uses themida protection, at game's exe startup use winapi VirtualAlloc to allocate memory used to load a dll from memory instead of loading from dll file, and this dll named sarcheck.dll. alpharom's validation algorithm is placed in sarcheck.dll, so alpharom is actually a dll named sarcheck.dll, the reason why we don't see sarcheck.dll file in game directory is because it's using themida to bind the dll in to game's exe and load this dll at startup from memory.  
So if we can prevent the loading of sarcheck.dll we can bypass alpharom，or just modify the dll to disable alpharom's checker.
 
## Guide to remove Alpharom from executable:
Run game.exe with compiled `version.dll`, then use [Magicmida](https://github.com/Hendi48/Magicmida) to unpack the execuatable.
[Example video](https://mega.nz/file/euwWFLpZ#N_3AtnjEzjuPy3hhaLHr-Xg7B0FvHBoNWsatX1lz7_k)
+ Optional: You can shrink the executable back to smaller size after unpacking.

## Tested games:
+ パサージュ！ ～passage of life～
+ Kajiri Kamui Kagura Akebono no Hikari
+ Aonatsu Line
