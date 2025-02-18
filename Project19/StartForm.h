#pragma once

#include "Resources.h"
#include "DefaultChoiceForm.h"
#include "CustomChoiceForm.h"

using namespace System::Runtime::InteropServices;

namespace Project19 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

    /// <summary>
    /// Сводка для StartForm
    /// </summary>
    public ref class StartForm : public System::Windows::Forms::Form
    {
    private: String^ APP_USER_NAME;
    private: Form^ APP_PREV_FORM;
    public:
        StartForm(Form^ prev_form, String^ username)
        {
            APP_USER_NAME = username;
            APP_PREV_FORM = prev_form;
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~StartForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Timer^ timer1;
    private: System::ComponentModel::IContainer^ components;

    private: delegate void ManagedCallback(const string& response);
    private: void myResponseHandler(const string& response) {
        String^ managedResponse = ""; //marshal_as<String^>(response);
        for (char c : response)
            managedResponse += (Char)c;

        try
        {
            vector<pair<string, int>> resultVector(0);
            parseJsonString(resultVector, response);

            for (pair<string, int> kvPair : resultVector)
            {
                if (kvPair.first == "victories")
                {
                    this->label1->Text = L"Количество побед: " + (kvPair.second);
                }
                if (kvPair.first == "defeats")
                {
                    this->label2->Text = L"Количество поражений: " + (kvPair.second);
                }
                if (kvPair.first == "place")
                {
                    this->label3->Text = L"Место: " + (kvPair.second) + "-е";
                }
            }

            this->button1->Enabled = true;
            this->button2->Enabled = true;
            this->button3->Enabled = true;
        }
        catch (exception e)
        {
            System::Windows::Forms::MessageBox::Show("Failed to format server response: " + managedResponse, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }


    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>


#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(50, 440);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(200, 50);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Создать свой собственный уровень";
            this->button1->Click += gcnew System::EventHandler(this, &StartForm::button1_Click);
            this->button1->Enabled = false;
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(250, 440);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(200, 50);
            this->button2->TabIndex = 2;
            this->button2->Text = L"Выбрать существующий уровень";
            this->button2->Click += gcnew System::EventHandler(this, &StartForm::button2_Click);
            this->button2->Enabled = false;
            // 
            // button3
            // 
            this->button3->Location = System::Drawing::Point(375, 0);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(125, 50);
            this->button3->TabIndex = 3;
            this->button3->Text = L"Выйти из аккаунта";
            this->button3->Click += gcnew System::EventHandler(this, &StartForm::button3_Click);
            this->button3->Enabled = false;
            // 
            // label1
            // 
            this->label1->BackColor = System::Drawing::Color::Transparent;
            this->label1->Location = System::Drawing::Point(65, 70);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(200, 30);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Количество побед: -";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label2
            // 
            this->label2->BackColor = System::Drawing::Color::Transparent;
            this->label2->Location = System::Drawing::Point(65, 100);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(200, 30);
            this->label2->TabIndex = 0;
            this->label2->Text = L"Количество поражений: -";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label3
            // 
            this->label3->BackColor = System::Drawing::Color::Transparent;
            this->label3->Location = System::Drawing::Point(65, 130);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(200, 30);
            this->label3->TabIndex = 0;
            this->label3->Text = L"Место: -";
            this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // StartForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->BackColor = System::Drawing::SystemColors::Control;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_BACKGROUND_PATH))));
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->ClientSize = System::Drawing::Size(500, 500);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label3);
            this->DoubleBuffered = true;
            this->VisibleChanged += gcnew System::EventHandler(this, &StartForm::MyForm_VisibleChanged);
            //this->Icon = (cli::safe_cast<System::Drawing::Icon^>(System::Drawing::Icon::ExtractAssociatedIcon(GetResourcesDirectory(RES_ICON_PATH))));
            this->Name = L"StartForm";
            this->Text = L"Ключворд - Главное меню";
            this->ResumeLayout(false);

            //this->getUserStatistics();
        }
#pragma endregion
    private: System::Void MyForm_VisibleChanged(System::Object^ sender, System::EventArgs^ e) {
        if (this->Visible) {
            //MessageBox::Show("The form is now visible!");
            this->getUserStatistics();
        }
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Hide();
        CustomChoiceForm^ choose_form = gcnew CustomChoiceForm(this, APP_USER_NAME);
        choose_form->Show();
    }
    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Hide();
        DefaultChoiceForm^ choose_form = gcnew DefaultChoiceForm(this, APP_USER_NAME);
        choose_form->Show();
    }
    private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
        WriteUserFile("");
        this->APP_PREV_FORM->Show();
        this->Close();
    }

    public: System::Void getUserStatistics() {
        int requestType = CURL_REQUEST_TYPE_STATISTICS_GET;
        vector<pair<string, string>> requestData(0);

        string username = "";
        for (int i = 0; i < APP_USER_NAME->Length; i++)
            username += ((char)APP_USER_NAME[i]);

        requestData.push_back(pair<string, string>("username", username));


        // Create a managed delegate instance
        ManagedCallback^ managedCallback = gcnew ManagedCallback(this, &StartForm::myResponseHandler);
        // Convert managed delegate to unmanaged function pointer
        IntPtr ptr = Marshal::GetFunctionPointerForDelegate(managedCallback);
        ResponseCallback nativeCallback = (ResponseCallback)ptr.ToPointer();
        // Call the function
        curlClient().performCurlRequest(nativeCallback, requestType, requestData);
    }
};
}