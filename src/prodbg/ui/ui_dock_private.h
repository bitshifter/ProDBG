#pragma once

#include "api/plugin_instance.h"
#include <vector> // TODO: replace with custom arrays

const int g_sizerSize = 4; // TODO: Move to settings
const int g_sizerSnapSize = 4; // TODO: Move to settings

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum UIDockType
{
    UIDockType_Docked,
    UIDockType_Floating,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum UIDockSide
{
    UIDockSide_Top,
    UIDockSide_Bottom,
    UIDockSide_Right,
    UIDockSide_Left,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct UIDock;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct UIDockSizer
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline void addDock(UIDock* dock)
    {
        cons.push_back(dock);
    }

    std::vector<UIDock*> cons;  // connected docks
    UIDockSizerDir dir;
    Rect rect;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct UIDock
{
    inline UIDock(ViewPluginInstance* inView) :
        topSizer(0), bottomSizer(0), rightSizer(0), leftSizer(0), view(inView), type(UIDockType_Docked)
    {
    }

    enum
    {
        Top,
        Bottom,
        Right,
        Left,
        Sizers_Count,
    };

    union
    {
        struct
        {
            UIDockSizer* topSizer;
            UIDockSizer* bottomSizer;
            UIDockSizer* rightSizer;
            UIDockSizer* leftSizer;
        };

        UIDockSizer* sizers[Sizers_Count];
    };

    ViewPluginInstance* view;

    UIDockType type;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum UIDockStatus
{
    UIDockStatus_ok,
    UIDockStatus_fail,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct UIDockingGrid
{
    std::vector<UIDock*> docks;
    std::vector<UIDockSizer*> sizers;
    UIDockSizer topSizer;
    UIDockSizer bottomSizer;
    UIDockSizer rightSizer;
    UIDockSizer leftSizer;
    Rect rect;
};



