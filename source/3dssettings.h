#ifndef _3DSSETTINGS_H_
#define _3DSSETTINGS_H_

#include <array>
#include <3ds.h>

#include "port.h"

enum class EmulatedFramerate {
    UseRomRegion = 0,
    ForceFps50 = 1,
    ForceFps60 = 2,
    Match3DS = 3,
    Count = 4
};

template <int Count>
struct ButtonMapping {
    std::array<uint32, Count> MappingBitmasks;

    bool operator==(const ButtonMapping& other) const {
        return this->MappingBitmasks == other.MappingBitmasks;
    }

    bool IsHeld(uint32 held3dsButtons) const {
        for (uint32 mapping : MappingBitmasks) {
            if (mapping != 0 && (mapping & held3dsButtons) == mapping) {
                return true;
            }
        }

        return false;
    }

    void SetSingleMapping(uint32 mapping) {
        SetDoubleMapping(mapping, 0);
    }

    void SetDoubleMapping(uint32 mapping0, uint32 mapping1) {
        if (Count > 0) {
            MappingBitmasks[0] = mapping0;
        }
        if (Count > 1) {
            MappingBitmasks[1] = mapping1;
        }
        if (Count > 2) {
            for (size_t i = 2; i < MappingBitmasks.size(); ++i) {
                MappingBitmasks[i] = 0;
            }
        }
    }
};

#define CONTENT_NONE 0
#define CONTENT_IMAGE 1
#define CONTENT_INFO 2

#define SAVESLOTS_MAX   5

#define HOTKEY_OPEN_MENU            0
#define HOTKEY_DISABLE_FRAMELIMIT   1
#define HOTKEY_SWAP_CONTROLLERS     2
#define HOTKEY_QUICK_SAVE           3
#define HOTKEY_QUICK_LOAD           4
#define HOTKEY_SAVE_SLOT_NEXT       5
#define HOTKEY_SAVE_SLOT_PREV       6
#define HOTKEY_SCREENSHOT           7
#define HOTKEYS_COUNT   8

#define OPACITY_STEPS   20

typedef struct S9xSettings3DS
{
    gfxScreen_t GameScreen = GFX_TOP;

    int     MaxFrameSkips = 1;              // 0 - disable,
                                            // 1 - enable (max 1 consecutive skipped frame)
                                            // 2 - enable (max 2 consecutive skipped frames)
                                            // 3 - enable (max 3 consecutive skipped frames)
                                            // 4 - enable (max 4 consecutive skipped frames)

    int     SecondScreenContent = CONTENT_IMAGE;
    int     SecondScreenOpacity = OPACITY_STEPS / 2;    // Default opacity
                                                        // 20 - Maxium opacity
    
    int     ShowGameBorder = 0;             // show/hide game border.
    int     GameBorderOpacity = OPACITY_STEPS / 2;

    int     Font = 0;                       // 0 - Tempesta, 1 - Ronda, 2 - Arial
    int     ScreenStretch = 6;              // 0 - no stretch, 1 - stretch full, 2 - aspect fit

    EmulatedFramerate ForceFrameRate = EmulatedFramerate::UseRomRegion;

    int     StretchWidth, StretchHeight;
    int     CropPixels;

    std::array<int, 8> Turbo = {0, 0, 0, 0, 0, 0, 0, 0};
                                            // Turbo buttons: 0 - No turbo, 1 - Release/Press every alt frame.
                                            // Indexes: 0 - A, 1 - B, 2 - X, 3 - Y, 4 - L, 5 - R

    int     Volume = 4;                     // 0: 100% Default volume,
                                            // 1: 125%, 2: 150%, 3: 175%, 4: 200%
                                            // 5: 225%, 6: 250%, 7: 275%, 8: 300%

    long    TicksPerFrame;                  // Ticks per frame. Will change depending on PAL/NTSC

    int     PaletteFix;                     // Palette In-Frame Changes
                                            //   1 - Enabled - Default.
                                            //   2 - Disabled - Style 1.
                                            //   3 - Disabled - Style 2.

    int     AutoSavestate = 0;              // Automatically save the the current state when the emulator is closed
                                            // or the game is changed, and load it again when the game is loaded.
                                            //   0 - Disabled
                                            //   1 - Enabled

    int     CurrentSaveSlot;                // remember last used save slot (1 - 5)

    int     SRAMSaveInterval;               // SRAM Save Interval
                                            //   1 - 1 second.
                                            //   2 - 10 seconds
                                            //   3 - 60 seconds
                                            //   4 - Never

    int     ForceSRAMWriteOnPause;          // If the SRAM should be written to SD even when no change was detected.
                                            // Some games (eg. Yoshi's Island) don't detect SRAM writes correctly.
                                            //   0 - Disabled
                                            //   1 - Enabled

    int     BindCirclePad = 1;              // Use Circle Pad as D-Pad for gaming      
                                            //   0 - Disabled
                                            //   1 - Enabled

    // Using the original button mapping to map the 3DS button
    // to the console buttons. This is for consistency with the
    // other EMUS for 3DS.
    //
    std::array<std::array<int, 4>, 10> GlobalButtonMapping = {};
    std::array<std::array<int, 4>, 10> ButtonMapping = {};

    std::array<::ButtonMapping<1>, HOTKEYS_COUNT> ButtonHotkeys;
    std::array<::ButtonMapping<1>, HOTKEYS_COUNT> GlobalButtonHotkeys;

    int     UseGlobalButtonMappings = 0;    // Use global button mappings for all games
                                            // 0 - no, 1 - yes

    int     UseGlobalTurbo = 0;             // Use global button mappings for all games
                                            // 0 - no, 1 - yes

    int     UseGlobalVolume = 0;            // Use global button mappings for all games
                                            // 0 - no, 1 - yes

    int     UseGlobalEmuControlKeys = 0;    // Use global emulator control keys for all games

    std::array<int, 8> GlobalTurbo = {0, 0, 0, 0, 0, 0, 0, 0};
                                            // Turbo buttons: 0 - No turbo, 1 - Release/Press every alt frame.
                                            // Indexes for 3DS buttons: 0 - A, 1 - B, 2 - X, 3 - Y, 4 - L, 5 - R, 6 - ZL, 7 - ZR

    int     GlobalVolume = 4;               // 0: 100%, 4: 200%, 8: 400%

    int     GlobalBindCirclePad = 1;         // Use Circle Pad as D-Pad for gaming      
                                            //   0 - Disabled
                                            //   1 - Enabled

    bool    RomFsLoaded = false;            // Stores whether we successfully opened the RomFS.

    int     Disable3DSlider = 0;              // Disable 3DSlider

    bool operator==(const S9xSettings3DS& other) const;
    bool operator!=(const S9xSettings3DS& other) const;
} S9xSettings3DS;

extern S9xSettings3DS settings3DS;

#define SCREEN_TOP_WIDTH        400
#define SCREEN_BOTTOM_WIDTH     320
#define SCREEN_HEIGHT           240

#define SCREEN_IMAGE_WIDTH      400

typedef struct
{
    gfxScreen_t GameScreen = GFX_TOP;
    gfxScreen_t SecondScreen = GFX_BOTTOM;
    int GameScreenWidth = SCREEN_TOP_WIDTH;
    int SecondScreenWidth = SCREEN_BOTTOM_WIDTH;
} ScreenSettings;

extern ScreenSettings screenSettings;

#endif
