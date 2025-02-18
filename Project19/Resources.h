#pragma once

const int RES_BACKGROUND_PATH = 0, RES_VICTORY_PATH = 1, RES_DEFEAT_PATH = 2, RES_ICON_PATH = 3;

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

    String^ GetUserInfoDirectory()
    {
        String^ directory = directory = "\\user.txt";
        return Directory::GetParent(Environment::CurrentDirectory)->FullName + GetTextFilesBaseDirectory() + directory;
    }


    Void WriteUserFile(String^ username)
    {
        String^ FileName = GetUserInfoDirectory();
        StreamWriter^ outFile = gcnew StreamWriter(FileName);

        outFile->Write(username);
        outFile->Close();
    }

    String^ ReadUserFile() {
        String^ FileContent;
        String^ FileName = GetUserInfoDirectory();

        Boolean any_errors = false;
        try {
            StreamReader^ file = File::OpenText(FileName);
            FileContent = file->ReadToEnd();
            file->Close();
        }
        catch (Exception^ e) {
            FileContent = "";
            any_errors = true;
        }

        String^ FileContentFinal = "";
        for (int i = 0; i < FileContent->Length; i++)
        {
            if (Char::IsLetterOrDigit(FileContent[i]))
            {
                FileContentFinal += FileContent[i];
            }
        }

        if (any_errors)
        {
            WriteUserFile(FileContentFinal);
        }
        return FileContentFinal;
    }
}