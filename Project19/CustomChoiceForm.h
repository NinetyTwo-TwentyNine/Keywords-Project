#pragma once

#include "Resources.h"
#include "LevelForm.h"

namespace Project19 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

    /// <summary>
    /// Сводка для CustomChoiceForm
    /// </summary>
    public ref class CustomChoiceForm : public System::Windows::Forms::Form
    {
    private: System::Windows::Forms::Form^ APP_PREV_FORM;
    public:
        CustomChoiceForm(Form^ prev_form)
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
        ~CustomChoiceForm()
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
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown3;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown4;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown5;
    private: System::Windows::Forms::NumericUpDown^ numericUpDown6;

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
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->BeginInit();
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(200, 375);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(100, 50);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Начать игру!";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &CustomChoiceForm::button1_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(200, 440);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(100, 50);
            this->button2->TabIndex = 2;
            this->button2->Text = L"Назад";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &CustomChoiceForm::button2_Click);
            // 
            // label1
            // 
            this->label1->BackColor = System::Drawing::Color::Transparent;
            this->label1->Location = System::Drawing::Point(50, 125);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(200, 30);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Время на игру";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // label2
            // 
            this->label2->BackColor = System::Drawing::Color::Transparent;
            this->label2->Location = System::Drawing::Point(250, 125);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(200, 30);
            this->label2->TabIndex = 0;
            this->label2->Text = L"Количество проверок";
            this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // label3
            // 
            this->label3->BackColor = System::Drawing::Color::Transparent;
            this->label3->Location = System::Drawing::Point(50, 175);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(200, 30);
            this->label3->TabIndex = 0;
            this->label3->Text = L"Количество подсказок";
            this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // label4
            // 
            this->label4->BackColor = System::Drawing::Color::Transparent;
            this->label4->Location = System::Drawing::Point(250, 175);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(200, 30);
            this->label4->TabIndex = 0;
            this->label4->Text = L"Размер поля";
            this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // label5
            // 
            this->label5->BackColor = System::Drawing::Color::Transparent;
            this->label5->Location = System::Drawing::Point(50, 225);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(200, 30);
            this->label5->TabIndex = 0;
            this->label5->Text = L"Количество попыток";
            this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // label6
            // 
            this->label6->BackColor = System::Drawing::Color::Transparent;
            this->label6->Location = System::Drawing::Point(250, 225);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(200, 30);
            this->label6->TabIndex = 0;
            this->label6->Text = L"Начальные буквы";
            this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            // 
            // numericUpDown1
            // 
            this->numericUpDown1->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown1->Location = System::Drawing::Point(100, 150);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 300, 0, 0, 0 });
            this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(100, 22);
            this->numericUpDown1->TabIndex = 3;
            this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 300, 0, 0, 0 });
            // 
            // numericUpDown2
            // 
            this->numericUpDown2->Location = System::Drawing::Point(300, 150);
            this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
            this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->numericUpDown2->Name = L"numericUpDown2";
            this->numericUpDown2->Size = System::Drawing::Size(100, 22);
            this->numericUpDown2->TabIndex = 4;
            this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            // 
            // numericUpDown3
            // 
            this->numericUpDown3->Location = System::Drawing::Point(100, 200);
            this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
            this->numericUpDown3->Name = L"numericUpDown3";
            this->numericUpDown3->Size = System::Drawing::Size(100, 22);
            this->numericUpDown3->TabIndex = 5;
            this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
            // 
            // numericUpDown4
            // 
            this->numericUpDown4->Location = System::Drawing::Point(300, 200);
            this->numericUpDown4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
            this->numericUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
            this->numericUpDown4->Name = L"numericUpDown4";
            this->numericUpDown4->Size = System::Drawing::Size(100, 22);
            this->numericUpDown4->TabIndex = 6;
            this->numericUpDown4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
            // 
            // numericUpDown5
            // 
            this->numericUpDown5->Location = System::Drawing::Point(100, 250);
            this->numericUpDown5->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->numericUpDown5->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->numericUpDown5->Name = L"numericUpDown5";
            this->numericUpDown5->Size = System::Drawing::Size(100, 22);
            this->numericUpDown5->TabIndex = 7;
            this->numericUpDown5->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
            // 
            // numericUpDown6
            // 
            this->numericUpDown6->Location = System::Drawing::Point(300, 250);
            this->numericUpDown6->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown6->Name = L"numericUpDown6";
            this->numericUpDown6->Size = System::Drawing::Size(100, 22);
            this->numericUpDown6->TabIndex = 8;
            this->numericUpDown6->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            // 
            // CustomChoiceForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_BACKGROUND_PATH))));
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->ClientSize = System::Drawing::Size(500, 500);
            this->Controls->Add(this->numericUpDown6);
            this->Controls->Add(this->numericUpDown5);
            this->Controls->Add(this->numericUpDown4);
            this->Controls->Add(this->numericUpDown3);
            this->Controls->Add(this->numericUpDown2);
            this->Controls->Add(this->numericUpDown1);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->button2);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(System::Drawing::Icon::ExtractAssociatedIcon(GetResourcesDirectory(RES_ICON_PATH))));
            this->Name = L"CustomChoiceForm";
            this->Text = L"Ключворд - Настройки уровня";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->EndInit();
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        int max_time = Convert::ToInt16(this->numericUpDown1->Value);
        int max_checks = Convert::ToInt16(this->numericUpDown2->Value);
        int max_hints = Convert::ToInt16(this->numericUpDown3->Value);
        int field_size = Convert::ToInt16(this->numericUpDown4->Value);
        int max_attempts = Convert::ToInt16(this->numericUpDown5->Value);
        int first_letters = Convert::ToInt16(this->numericUpDown6->Value);

        OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
        openFileDialog1->Filter = "txt files (*.txt)|*.txt";
        openFileDialog1->RestoreDirectory = true;

        String^ FileContent;
        String^ FileName = "";
        if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
            FileName = openFileDialog1->FileName;
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

    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        this->APP_PREV_FORM->Show();
        this->Close();
    }
    };
}
