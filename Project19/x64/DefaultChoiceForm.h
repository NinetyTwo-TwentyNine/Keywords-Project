#pragma once

#include "LevelForm.h"
#include "Resources.h"

namespace Project19 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

    /// <summary>
    /// Сводка для DefaultChoiceForm
    /// </summary>
    public ref class DefaultChoiceForm : public System::Windows::Forms::Form
    {
    private: System::Windows::Forms::Form^ APP_PREV_FORM;
    public:
        DefaultChoiceForm(Form^ prev_form)
        {
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
        ~DefaultChoiceForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Button^ button4;
    private: System::Windows::Forms::Button^ button5;
    private: System::Windows::Forms::Button^ button6;
    private: String^ selected_level;

    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->button6 = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(75, 150);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(150, 50);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Спорт";
            this->button1->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button1_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(275, 150);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(150, 50);
            this->button2->TabIndex = 2;
            this->button2->Text = L"Стандартизация";
            this->button2->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button2_Click);
            // 
            // button3
            // 
            this->button3->Location = System::Drawing::Point(75, 225);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(150, 50);
            this->button3->TabIndex = 3;
            this->button3->Text = L"Измерения";
            this->button3->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button3_Click);
            // 
            // button4
            // 
            this->button4->Location = System::Drawing::Point(275, 225);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(150, 50);
            this->button4->TabIndex = 4;
            this->button4->Text = L"Медицина";
            this->button4->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button4_Click);
            // 
            // button5
            // 
            this->button5->Enabled = false;
            this->button5->Location = System::Drawing::Point(200, 375);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(100, 50);
            this->button5->TabIndex = 5;
            this->button5->Text = L"Начать игру!";
            this->button5->UseVisualStyleBackColor = true;
            this->button5->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button5_Click);
            // 
            // button6
            // 
            this->button6->Location = System::Drawing::Point(200, 440);
            this->button6->Name = L"button6";
            this->button6->Size = System::Drawing::Size(100, 50);
            this->button6->TabIndex = 6;
            this->button6->Text = L"Назад";
            this->button6->UseVisualStyleBackColor = true;
            this->button6->Click += gcnew System::EventHandler(this, &DefaultChoiceForm::button6_Click);
            // 
            // DefaultChoiceForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_BACKGROUND_PATH))));
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->ClientSize = System::Drawing::Size(500, 500);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->button4);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->button6);
            this->DoubleBuffered = true;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(System::Drawing::Icon::ExtractAssociatedIcon(GetResourcesDirectory(RES_ICON_PATH))));
            this->Name = L"DefaultChoiceForm";
            this->Text = L"Ключворд - Выбор уровня";
            this->ResumeLayout(false);

        }

#pragma endregion
    private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
        this->APP_PREV_FORM->Show();
        this->Close();
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        this->selected_level = "default_level_sport.txt";
        this->button5->Enabled = true;
    }
    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        this->selected_level = "default_level_standartization.txt";
        this->button5->Enabled = true;
    }
    private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
        this->selected_level = "default_level_measurement.txt";
        this->button5->Enabled = true;
    }
    private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
        this->selected_level = "default_level_medicine.txt";
        this->button5->Enabled = true;
    }

    private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
        int max_time = 300;
        int max_checks = 10;
        int max_hints = 15;
        int field_size = 15;
        int max_attempts = 3;
        int first_letters = 5;

        String^ FileName = this->selected_level;
        String^ FileContent;
        try {
            StreamReader^ file = File::OpenText(FileName);
            FileContent = file->ReadToEnd();
        }
        catch (Exception^ e) {
            MessageBox::Show(this, "Не удалось открыть файл.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        FileContent = FileContent->ToUpper();

        this->Hide();
        LevelForm^ ActualGame = gcnew LevelForm(this, max_time, max_checks, max_hints, max_attempts, first_letters, field_size, FileContent);
        ActualGame->Show();
    }
    };
}
