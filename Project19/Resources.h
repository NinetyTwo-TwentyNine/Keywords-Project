#pragma once

const int RES_BACKGROUND_PATH = 0, RES_VICTORY_PATH = 1, RES_DEFEAT_PATH = 2, RES_ICON_PATH = 3;
const int GAME_LEVEL_SPORT = 0, GAME_LEVEL_STANDARTIZATION = 1, GAME_LEVEL_MEASUREMENT = 2, GAME_LEVEL_MEDICINE = 3;

namespace Project19 {

    using namespace System;
    using namespace System::IO;
    using namespace System::Collections;

    String^ GetResourcesBaseDirectory()
    {
        return "\\Resources";
    }

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
        return Directory::GetParent(Environment::CurrentDirectory)->FullName + GetResourcesBaseDirectory() + directory;
    }




    String^ GetTextFilesBaseDirectory()
    {
        return "\\TextResources";
    }

    String^ GetDefaultLevelDirectory(int type)
    {
        String^ directory = "";
        switch (type)
        {
        case GAME_LEVEL_SPORT:
            directory = "\\default_level_sport.txt";
            break;
        case GAME_LEVEL_MEDICINE:
            directory = "\\default_level_medicine.txt";
            break;
        case GAME_LEVEL_STANDARTIZATION:
            directory = "\\default_level_standartization.txt";
            break;
        case GAME_LEVEL_MEASUREMENT:
            directory = "\\default_level_measurement.txt";
            break;
        }
        return Directory::GetParent(Environment::CurrentDirectory)->FullName + GetTextFilesBaseDirectory() + directory;
    }
}