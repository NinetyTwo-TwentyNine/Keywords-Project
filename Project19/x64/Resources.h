#pragma once

const int RES_BACKGROUND_PATH = 0;
const int RES_VICTORY_PATH = 1;
const int RES_DEFEAT_PATH = 2;
const int RES_ICON_PATH = 3;

namespace Project19 {

    using namespace System;
    using namespace System::IO;
    using namespace System::Collections;

    String^ GetResourcesDirectory(int type)
    {
        String^ directory = "";
        switch (type)
        {
        case RES_BACKGROUND_PATH:
            directory = "\\background.png";
            break;
        case RES_VICTORY_PATH:
            directory = "\\win_screen.jpg";
            break;
        case RES_DEFEAT_PATH:
            directory = "\\lose_screen.jpg";
            break;
        case RES_ICON_PATH:
            directory = "\\icon_keyword.ico";
            break;
        }
        return Directory::GetParent(Environment::CurrentDirectory)->FullName + "\\Resources" + directory;
    }
}