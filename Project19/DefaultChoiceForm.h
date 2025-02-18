#pragma once

#include "Resources.h"
#include "LevelForm.h"

using namespace System::Runtime::InteropServices;

namespace Project19 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

    /// <summary>
    /// ������ ��� DefaultChoiceForm
    /// </summary>
    public ref class DefaultChoiceForm : public System::Windows::Forms::Form
    {
    private: String^ APP_USER_NAME;
    private: System::Windows::Forms::Form^ APP_PREV_FORM;
    public:
        DefaultChoiceForm(Form^ prev_form, String^ username)
        {
            APP_USER_NAME = username;
            APP_PREV_FORM = prev_form;
            InitializeComponent();
            //
            //TODO: �������� ��� ������������
            //
        }

    protected:
        /// <summary>
        /// ���������� ��� ������������ �������.
        /// </summary>
        ~DefaultChoiceForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: ArrayList^ buttonArray;
    private: String^ selected_level;
    private: int buttonArraySize = 10;

    private: delegate void ManagedCallback(const string& response);
    private: void myResponseHandler(const string& response) {
        String^ managedResponse = ""; //marshal_as<String^>(response);
        for (char c : response)
            managedResponse += (Char)c;

        try
        {
            vector<string> resultVector(0);
            parseJsonString(resultVector, response);

            for (int i = 0; i < resultVector.size(); i++)
            {
                if (i < buttonArraySize)
                {
                    String^ resultString = "";
                    for (char c : resultVector[i])
                        resultString += (Char)c;
                    ((Button^)this->buttonArray[i])->Text = resultString;
                    ((Button^)this->buttonArray[i])->Enabled = true;
                }
            }

            this->button1->Enabled = true;
            this->button2->Enabled = true;
        }
        catch (exception e)
        {
            System::Windows::Forms::MessageBox::Show("Failed to format server response: " + managedResponse, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
            this->button2->Enabled = true;
        }
    }


    private:
        /// <summary>
        /// ������������ ���������� ������������.
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// ��������� ����� ��� ��������� ������������ � �� ��������� 
        /// ���������� ����� ������ � ������� ��������� ����.
        /// </summary>
        void InitializeComponent(void)
        {
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->buttonArray = (gcnew ArrayList());
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->Enabled = false;
            this->button1->Location = System::Drawing::Point(200, 375);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(100, 50);
            this->button1->TabIndex = buttonArraySize + 1;
            this->button1->Text = L"������ ����!";
            this->button1->Enabled = false;
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button1_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(200, 440);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(100, 50);
            this->button2->TabIndex = buttonArraySize + 2;
            this->button2->Text = L"�����";
            this->button2->Enabled = false;
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button2_Click);
            // 
            // buttonArray
            //
            for (int i = 0; i < this->buttonArraySize; i++)
            {
                Button^ curButton = gcnew System::Windows::Forms::Button();
                this->Controls->Add(curButton);
                curButton->Name = L"button" + i;
                curButton->TabIndex = i;
                curButton->Text = L"";
                curButton->Enabled = false;
                curButton->Size = System::Drawing::Size(150, 50);
                Int16 x, y;
                y = 30 + 60 * (i / 2);
                if (i % 2)
                {
                    x = 75;
                }
                else
                {
                    x = 275;
                }
                curButton->Location = System::Drawing::Point(x, y);
                curButton->UseVisualStyleBackColor = true;
                curButton->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button_Click);
                this->buttonArray->Add(curButton);
            }
            // 
            // DefaultChoiceForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_BACKGROUND_PATH))));
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->ClientSize = System::Drawing::Size(500, 500);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->button2);
            this->DoubleBuffered = true;
            //this->Icon = (cli::safe_cast<System::Drawing::Icon^>(System::Drawing::Icon::ExtractAssociatedIcon(GetResourcesDirectory(RES_ICON_PATH))));
            this->Name = L"DefaultChoiceForm";
            this->Text = L"�������� - ����� ������";
            this->ResumeLayout(false);

            this->getUserKeywordPuzzles();
        }

#pragma endregion
    private: System::Void button_Click(System::Object^ sender, System::EventArgs^ e) {
        this->selected_level = ((Button^)sender)->Text;
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        if (String::IsNullOrEmpty(this->selected_level))
        {
            MessageBox::Show(this, "���� �� ��� ������.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        LevelForm^ ActualGame = gcnew LevelForm(APP_PREV_FORM, APP_USER_NAME, selected_level);
        ActualGame->Show();
        this->Close();
    }

    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        this->APP_PREV_FORM->Show();
        this->Close();
    }

    private: System::Void getUserKeywordPuzzles() {
        int requestType = CURL_REQUEST_TYPE_PUZZLES_GET;
        vector<pair<string, string>> requestData(0);

        string username = "";
        for (int i = 0; i < APP_USER_NAME->Length; i++)
            username += ((char)APP_USER_NAME[i]);

        requestData.push_back(pair<string, string>("username", username));

        // Create a managed delegate instance
        ManagedCallback^ managedCallback = gcnew ManagedCallback(this, &DefaultChoiceForm::myResponseHandler);
        // Convert managed delegate to unmanaged function pointer
        IntPtr ptr = Marshal::GetFunctionPointerForDelegate(managedCallback);
        ResponseCallback nativeCallback = (ResponseCallback)ptr.ToPointer();
        // Call the function
        curlClient().performCurlRequest(nativeCallback, requestType, requestData);
    }
    };
}
