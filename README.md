# HoverRace

Anti-gravity racing game built in Unreal Engine 5.6 

## Project Documents

| Document | Location |
|----------|----------|
| **Development Commentary** | Submitted as self contained html and available via GitHub Pages on link provided in submission|
| **Playable Windows Build** | https://github.com/AlexTreml/HoverRace/releases/tag/1.3 |
| **Video Talk** | You Tube Link available in Development commentary submission |
| **Unreal Files and source C++ files**| Available in this repository.|
| **C++ API Documentaion**|  https://alextreml.github.io/HoverRace/html/index.html|

## Project Structure

```
HoverVehicleSystem/
  Content/              — Blueprints, maps, materials, UI widgets
  Config/               — Project configuration
  Source/               — C++ source code
  Html/                 — Doxygen C++ Files
    HoverVehicleSystem/
      RaceManager.h/.cpp
      HoverAIRacer.h/.cpp
      RaceGate.h/.cpp
      BoostPad.h/.cpp
      RespawnVolume.h/.cpp
      HoverRaceUI.h/.cpp
      RaceResultsWidget.h/.cpp
      HoverVehiclePlayerController.h/.cpp
      HoverRaceSpline.h/.cpp
  Plugins/
    AdvancedMenuSystem/  — Third-party menu system plugin 
```

---



# HoverRace — Installation & Play Instructions

A standalone Windows build. No engine install or compilation required.


## Download

1. Go to the (https://github.com/AlexTreml/HoverRace/releases/tag/1.3) page.
2. Download the latest `HoverRace_Build.zip` 

## Install & Run

1. **Extract** the zip to a folder of your choice.
2. Open the extracted folder and **double-click `HoverRace.exe`**.
3. The main menu loads. Select a level from Level selection (City or Galaxy) to begin a race.

# Controls

## Keyboard

| Action | Controls |
|--------|---------|
| Throttle / accelerate | **W** |
| Brake / reverse | **S** |
| Left/Right | **A** / **D** |
| Pause | **Esc** or **P**|
| Reset | **R** |


| In Air Action | Controls |
|--------|---------|
| Pitch up / down | **Arrow keys** |
| Roll left | **Q** |
| Roll right| **E** |

## Gamepad

| Action | Controls |
|--------|---------|
| Throttle / accelerate | **RT** |
| Brake / reverse | **LT** |
| Left/Right | **LEFT STICK X** |
| Pause | **MENU**|
| Reset | **Y** |


| In Air Action | Controls |
|--------|---------|
| Pitch up / down | **LEFT STICK Y** |
| Roll left | **LB** |
| Roll right| **RB** |



## Troubleshooting

**The game won't launch / immediate crash on start**
Make sure you have the latest GPU drivers and that DirectX 12 is supported.

**Low framerate**
Lower graphics options via the in-game settings menu (Pause → Settings → Graphics). 

**Audio not playing**
Check Windows audio output device matches your speakers/headphones. Restart the game.


## Build Information

- Built with Unreal Engine 5.6
- Platform: Windows 64-bit (Development build)
- Engine source not included; this is a packaged executable.
