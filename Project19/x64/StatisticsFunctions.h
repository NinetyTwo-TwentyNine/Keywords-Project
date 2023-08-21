#pragma once

namespace Project19 {

    using namespace System;
    using namespace System::IO;
    using namespace System::Collections;

    String^ GetStatisticsDirectory()
    {
        return "vics&defs.txt";
    }

    Void WriteStatisticsFile(int vics_amount, int defs_amount)
    {
        String^ FileName = GetStatisticsDirectory();
        StreamWriter^ outFile = gcnew StreamWriter(FileName);
        outFile->Write(vics_amount + "/" + defs_amount);
        outFile->Close();
    }

    ArrayList^ ReadStatisticsFile() {
        Int16 vics_amount;
        Int16 defs_amount;

        String^ FileContent;
        String^ FileName = GetStatisticsDirectory();

        Boolean any_errors = false;
        try {
            StreamReader^ file = File::OpenText(FileName);
            FileContent = file->ReadToEnd();
            file->Close();
        }
        catch (Exception^ e) {
            FileContent = "0/0";
            any_errors = true;
        }
        try {
            vics_amount = Convert::ToInt16(FileContent->Substring(0, FileContent->IndexOf('/')));
        }
        catch (Exception^ e) {
            vics_amount = 0;
            any_errors = true;
        }
        try {
            defs_amount = Convert::ToInt16(FileContent->Substring(FileContent->IndexOf('/') + 1, FileContent->Length - FileContent->IndexOf('/') - 1));
        }
        catch (Exception^ e) {
            defs_amount = 0;
            any_errors = true;
        }

        if (any_errors)
        {
            WriteStatisticsFile(vics_amount, defs_amount);
        }

        ArrayList^ statistics_array = gcnew ArrayList();
        statistics_array->Add(vics_amount);
        statistics_array->Add(defs_amount);
        return statistics_array;
    }
}