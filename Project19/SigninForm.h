#pragma once

#include "Resources.h"
#include "StartForm.h"

using namespace System::Runtime::InteropServices;

namespace Project19 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

    //void EnableConsole() {
    //    AllocConsole();  // Create a new console window
    //    freopen("CONOUT$", "w", stdout);  // Redirect stdout to console
    //    freopen("CONOUT$", "w", stderr);  // Redirect stderr to console
    //    cout << "Console is now attached!" << endl;
    //}

    /// <summary>
    /// Сводка для SigninForm
    /// </summary>
    public ref class SigninForm : public System::Windows::Forms::Form
    {
    private: String^ APP_USER_NAME;
    public:
        SigninForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~SigninForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::TextBox^ text1;
    private: System::Windows::Forms::TextBox^ text2;
    private: System::Windows::Forms::TextBox^ text3;
    private: System::Windows::Forms::TextBox^ text4;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label4;
    private: System::ComponentModel::IContainer^ components;
    private: System::Windows::Forms::Timer^ timer1;
    private: bool registrationMode = false;
    
    private: delegate void ManagedCallback(const string& response);
    private: void myResponseHandler1(const string& response) {
        if (response.find("\"result\":true") != -1)
        {
            this->Hide();
            StartForm^ start_form = gcnew StartForm(this, APP_USER_NAME);
            start_form->Show();
        }
        this->button1->Enabled = true;
        this->button2->Enabled = true;
    }
    private: void myResponseHandler2(const string& response) {
        if (response.find("\"result\":true") != -1)
        {
            this->Hide();
            StartForm^ start_form = gcnew StartForm(this, APP_USER_NAME);
            start_form->Show();
        }
        else
        {
            String^ managedResponse = ""; //marshal_as<String^>(response);
            for (char c : response)
                managedResponse += (Char)c;

            System::Windows::Forms::MessageBox::Show("Server Response: " + managedResponse);
        }
        this->button1->Enabled = true;
        this->button2->Enabled = true;
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
            this->registrationMode = false;
            this->components = (gcnew System::ComponentModel::Container());
            this->text1 = (gcnew System::Windows::Forms::TextBox());
            this->text2 = (gcnew System::Windows::Forms::TextBox());
            this->text3 = (gcnew System::Windows::Forms::TextBox());
            this->text4 = (gcnew System::Windows::Forms::TextBox());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            //
            // textBox1
            //
            this->text1->Location = System::Drawing::Point(150, 80);
            this->text1->Name = L"textBox1";
            this->text1->Multiline = false;
            this->text1->Size = System::Drawing::Size(200, 50);
            this->text1->Text = "";
            this->text1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SigninForm::textBox_KeyPress);
            this->text1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->text1->ReadOnly = false;
            this->text1->TabIndex = 0;
            //
            // textBox2
            //
            this->text2->Location = System::Drawing::Point(150, 155);
            this->text2->Name = L"textBox2";
            this->text2->Multiline = false;
            this->text2->Size = System::Drawing::Size(200, 50);
            this->text2->Text = "";
            this->text2->UseSystemPasswordChar = true;
            this->text2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SigninForm::textBox_KeyPress);
            this->text2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->text2->ReadOnly = false;
            this->text2->TabIndex = 0;
            //
            // textBox3
            //
            this->text3->Location = System::Drawing::Point(150, 230);
            this->text3->Name = L"textBox3";
            this->text3->Multiline = false;
            this->text3->Size = System::Drawing::Size(200, 50);
            this->text3->Text = "";
            this->text3->UseSystemPasswordChar = true;
            this->text3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SigninForm::textBox_KeyPress);
            this->text3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->text3->ReadOnly = false;
            this->text3->TabIndex = 0;
            this->text3->Enabled = false;
            this->text3->Visible = false;
            //
            // textBox4
            //
            this->text4->Location = System::Drawing::Point(150, 305);
            this->text4->Name = L"textBox4";
            this->text4->Multiline = false;
            this->text4->Size = System::Drawing::Size(200, 50);
            this->text4->Text = "";
            this->text4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SigninForm::textBox_KeyPress);
            this->text4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->text4->ReadOnly = false;
            this->text4->TabIndex = 0;
            this->text4->Enabled = false;
            this->text4->Visible = false;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(150, 405);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(200, 50);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Далее";
            this->button1->Click += gcnew System::EventHandler(this, &SigninForm::button1_Click);
            this->button1->Enabled = false;
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(375, 450);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(125, 50);
            this->button2->TabIndex = 2;
            this->button2->Text = L"Регистрация";
            this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serthis->if", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->button2->Click += gcnew System::EventHandler(this, &SigninForm::button2_Click);
            this->button2->Enabled = false;
            // 
            // label1
            // 
            this->label1->BackColor = System::Drawing::Color::Transparent;
            this->label1->Location = System::Drawing::Point(150, 55);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(200, 30);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Имя пользователя";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label2
            // 
            this->label2->BackColor = System::Drawing::Color::Transparent;
            this->label2->Location = System::Drawing::Point(150, 130);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(200, 30);
            this->label2->TabIndex = 0;
            this->label2->Text = L"Пароль";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label3
            // 
            this->label3->BackColor = System::Drawing::Color::Transparent;
            this->label3->Location = System::Drawing::Point(150, 205);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(200, 30);
            this->label3->TabIndex = 0;
            this->label3->Text = L"Подтвердить пароль";
            this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label3->Visible = false;
            // 
            // label4
            // 
            this->label4->BackColor = System::Drawing::Color::Transparent;
            this->label4->Location = System::Drawing::Point(150, 280);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(200, 30);
            this->label4->TabIndex = 0;
            this->label4->Text = L"Имя/фамилия";
            this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label4->Visible = false;
            // 
            // SigninForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->BackColor = System::Drawing::SystemColors::Control;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_BACKGROUND_PATH))));
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->ClientSize = System::Drawing::Size(500, 500);
            this->Controls->Add(this->text1);
            this->Controls->Add(this->text2);
            this->Controls->Add(this->text3);
            this->Controls->Add(this->text4);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label4);
            this->DoubleBuffered = true;
            //this->Icon = (cli::safe_cast<System::Drawing::Icon^>(System::Drawing::Icon::ExtractAssociatedIcon(GetResourcesDirectory(RES_ICON_PATH))));
            this->Name = L"SigninForm";
            this->Text = L"Ключворд - Вход";
            this->ResumeLayout(false);

            this->SetupDelay();
        }
#pragma endregion
    private: void OnDelayElapsed(System::Object^ sender, System::EventArgs^ e) {
        timer1->Stop();
        checkIfAlreadySignedIn();
    }
    private: void SetupDelay() {
        timer1 = gcnew System::Windows::Forms::Timer();
        timer1->Interval = 300;
        timer1->Tick += gcnew System::EventHandler(this, &SigninForm::OnDelayElapsed);
        timer1->Start();
    }


    private: System::Void textBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
        e->Handled = false;
        if (e->KeyChar == 8)
        {
            return;
        }

        if (!Char::IsLetterOrDigit(e->KeyChar))
        {
            e->Handled = true;
        }
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        if ( (this->text1->Text->Length == 0) || (this->text2->Text->Length == 0) || (registrationMode && (this->text3->Text->Length == 0) ))
        {
            MessageBox::Show(this, "Не все поля заполнены", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (registrationMode && ( (this->text2->Text) != (this->text3->Text) ))
        {
            MessageBox::Show(this, "Пароли не совпадают", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        this->button1->Enabled = false;
        this->button2->Enabled = false;

        APP_USER_NAME = this->text1->Text;
        WriteUserFile(APP_USER_NAME);
        sendUserData();
    }
    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        this->registrationMode = !registrationMode;

        this->text3->Enabled = registrationMode;
        this->text3->Visible = registrationMode;
        this->label3->Visible = registrationMode;

        this->text4->Enabled = registrationMode;
        this->text4->Visible = registrationMode;
        this->label4->Visible = registrationMode;

        if (registrationMode)
        {
            this->button2->Text = "Войти";
        }
        else
        {
            this->button2->Text = "Регистрация";
        }
    }

    private: System::Void checkIfAlreadySignedIn() {
        string username = "";

        String^ readString = ReadUserFile();
        if (readString->Length == 0)
        {
            this->button1->Enabled = true;
            this->button2->Enabled = true;
            return;
        }

        APP_USER_NAME = readString;
        for (int i = 0; i < readString->Length; i++)
            username += (char)readString[i];

        int requestType = CURL_REQUEST_TYPE_LOGIN;
        vector<pair<string, string>> requestData(0);
        requestData.push_back(pair<string, string>("username", username));

        // Create a managed delegate instance
        ManagedCallback^ managedCallback = gcnew ManagedCallback(this, &SigninForm::myResponseHandler1);
        // Convert managed delegate to unmanaged function pointer
        IntPtr ptr = Marshal::GetFunctionPointerForDelegate(managedCallback);
        ResponseCallback nativeCallback = (ResponseCallback)ptr.ToPointer();
        // Call the function
        curlClient().performCurlRequest(nativeCallback, requestType, requestData);
    }

    private: System::Void sendUserData() {
        string username = "", password = "", first_name = "", last_name = "";

        for (int i = 0; i < text1->Text->Length; i++)
            username += ((char)text1->Text[i]);
        for (int i = 0; i < text2->Text->Length; i++)
            password += ((char)text2->Text[i]);

        if (registrationMode) {
            if (!this->text4->Text->Empty)
            {
                string text4_string = "";
                for (int i = 0; i < text4->Text->Length; i++)
                {
                    if (Char::IsLetter(text4->Text[i]) || Char::IsDigit(text4->Text[i]))
                    {
                        text4_string += ((char)text4->Text[i]);
                    }
                    else
                    {
                        text4_string += ' ';
                    }
                }
                vector<string> words = createVectorFromContent(text4_string);
                if (!words.empty()) {
                    first_name = words[0];
                    if (words.size() > 1)
                    {
                        last_name = words[1];
                    }
                }
            }
        }

        int requestType;
        vector<pair<string, string>> requestData(0);
        requestData.push_back(pair<string, string>("username", username));
        requestData.push_back(pair<string, string>("password", password));
        if (registrationMode)
        {
            requestData.push_back(pair<string, string>("first_name", first_name));
            requestData.push_back(pair<string, string>("last_name", last_name));
            requestType = CURL_REQUEST_TYPE_REGISTER;
        }
        else
        {
            requestType = CURL_REQUEST_TYPE_LOGIN;
        }


        // Create a managed delegate instance
        ManagedCallback^ managedCallback = gcnew ManagedCallback(this, &SigninForm::myResponseHandler2);
        // Convert managed delegate to unmanaged function pointer
        IntPtr ptr = Marshal::GetFunctionPointerForDelegate(managedCallback);
        ResponseCallback nativeCallback = (ResponseCallback)ptr.ToPointer();
        // Call the function
        curlClient().performCurlRequest(nativeCallback, requestType, requestData);
    }
};
}