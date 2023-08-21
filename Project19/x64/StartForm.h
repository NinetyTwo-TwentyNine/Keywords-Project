#pragma once

#include "DefaultChoiceForm.h"
#include "CustomChoiceForm.h"
#include "Resources.h"
#include "StatisticsFunctions.h"

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
    public:
        StartForm(void)
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
        ~StartForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Timer^ timer1;
    private: System::ComponentModel::IContainer^ components;

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
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
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
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(250, 440);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(200, 50);
            this->button2->TabIndex = 2;
            this->button2->Text = L"Выбрать стандартный уровень";
            this->button2->Click += gcnew System::EventHandler(this, &StartForm::button2_Click);
            // 
            // label1
            // 
            this->label1->BackColor = System::Drawing::Color::Transparent;
            this->label1->Location = System::Drawing::Point(65, 70);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(200, 30);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Количество побед: 0";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // label2
            // 
            this->label2->BackColor = System::Drawing::Color::Transparent;
            this->label2->Location = System::Drawing::Point(65, 100);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(200, 30);
            this->label2->TabIndex = 0;
            this->label2->Text = L"Количество поражений: 0";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            // 
            // timer1
            // 
            this->timer1->Enabled = true;
            this->timer1->Tick += gcnew System::EventHandler(this, &StartForm::timer1_Tick);
            // 
            // StartForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::Control;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_BACKGROUND_PATH))));
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->ClientSize = System::Drawing::Size(500, 500);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->label2);
            this->DoubleBuffered = true;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(System::Drawing::Icon::ExtractAssociatedIcon(GetResourcesDirectory(RES_ICON_PATH))));
            this->Name = L"StartForm";
            this->Text = L"Ключворд - Главное меню";
            this->ResumeLayout(false);
        }
#pragma endregion
    private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
    {
        this->UpdateStatistics();
    }
    public: System::Void UpdateStatistics() {
        ArrayList^ stats_arr = ReadStatisticsFile();
        this->label1->Text = L"Количество побед: " + ((Int16)stats_arr[0]);
        this->label2->Text = L"Количество поражений: " + ((Int16)stats_arr[1]);
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Hide();
        CustomChoiceForm^ choose_form = gcnew CustomChoiceForm(this);
        choose_form->Show();
    }
    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Hide();
        DefaultChoiceForm^ choose_form = gcnew DefaultChoiceForm(this);
        choose_form->Show();
    }
};
}