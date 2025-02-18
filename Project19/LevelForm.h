#pragma once

#include "Resources.h"
#include "StartForm.h"
#include "CurlManagement.cpp"

using namespace System::Runtime::InteropServices;

using namespace std;

const int DIR_HORIZONTAL = 0, DIR_VERTICAL = 1;
const int DIR_UP = 0, DIR_DOWN = 1, DIR_LEFT = 2, DIR_RIGHT = 3;

vector <vector<char>> GAME_MATRIX;
vector <vector<vector<bool>>> GAME_MATRIX_ORIGINS;
vector <vector<vector<bool>>> GAME_MATRIX_DIRECTIONS;


namespace Project19 {

    using namespace System;
    using namespace System::IO;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;



    /// <summary>
    /// Сводка для LevelForm
    /// </summary>
    public ref class LevelForm : public System::Windows::Forms::Form
    {
    private: int GAME_MAX_HINTS, GAME_MAX_CHECKS, GAME_MAX_TIME, GAME_MAX_ATTEMPTS, GAME_FIRST_LETTERS, GAME_FIELD_SIZE;
    private: String^ APP_USER_NAME;
    private: String^ APP_FILE_NAME;
    private: Form^ APP_PREV_WINDOW;

    public:
        LevelForm(Form^ prev_window, String^ username, String^ filecontent)
        {
            APP_USER_NAME = username;
            APP_FILE_NAME = filecontent;
            APP_PREV_WINDOW = prev_window;
            this->getKeywordPuzzle();
            //InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~LevelForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Panel^ panel1;
    private: System::Windows::Forms::Panel^ panel2;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Button^ button4;
    private: System::Windows::Forms::Button^ button5;
    private: System::Windows::Forms::Button^ button6;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Timer^ timer1;
    private: System::Drawing::Image^ lose_image;
    private: System::Drawing::Image^ win_image;
    private: ArrayList^ labelArray;
    private: ArrayList^ textBoxArray;
    private: ArrayList^ directionsArray;
    private: ArrayList^ matrixCharArray;
    private: const int textBoxSize = 42;
    private: int textArraySize, panelSize, formSize;
    private: int game_hints, game_checks, game_time, game_attempts;
    private: bool checkEnabled = false;

    private: delegate void ManagedCallback(const string& response);
    private: void myResponseHandler1(const string& response) {
        String^ managedResponse = ""; //marshal_as<String^>(response);
        for (char c : response)
            managedResponse += (Char)c;

        try
        {
            vector <int> gameParams(0);
            GAME_MATRIX_DIRECTIONS = vector <vector<vector<bool>>> (0, vector<vector<bool>>(0)); // first bool for horizontal, second bool for vertical
            GAME_MATRIX_ORIGINS = vector <vector<vector<bool>>>(0, vector<vector<bool>>(0));
            GAME_MATRIX = vector<vector<char>>(0, vector<char>(0));
            
            parseJsonString(GAME_MATRIX_DIRECTIONS, GAME_MATRIX_ORIGINS, GAME_MATRIX, gameParams, response);

            GAME_MAX_TIME = gameParams[0];
            GAME_MAX_CHECKS = gameParams[1];
            GAME_MAX_HINTS = gameParams[2];
            GAME_FIELD_SIZE = gameParams[3];
            GAME_MAX_ATTEMPTS = gameParams[4];
            GAME_FIRST_LETTERS = gameParams[5];

            //cout << "Results:" << endl;
            //cout << "gameParams size = " << gameParams.size() << endl;
            //cout << "directionsArr size: " << GAME_FIELD_SIZE << " vs " << GAME_MATRIX_DIRECTIONS.size() << "/" << GAME_MATRIX_DIRECTIONS[0].size() << endl;
            //cout << "originsMatrix size: " << GAME_FIELD_SIZE << " vs " << GAME_MATRIX_ORIGINS.size() << "/" << GAME_MATRIX_ORIGINS[0].size() << endl;
            //cout << "gameMatrix size: " << GAME_FIELD_SIZE << " vs " << GAME_MATRIX.size() << "/" << GAME_MATRIX[0].size() << endl;

            if (GAME_MATRIX_DIRECTIONS.size() != GAME_FIELD_SIZE || GAME_MATRIX_DIRECTIONS[0].size() != GAME_FIELD_SIZE)
            {
                throw(exception("DirectionsArray size mismatch."));
            }
            if (GAME_MATRIX_ORIGINS.size() != GAME_FIELD_SIZE || GAME_MATRIX_ORIGINS[0].size() != GAME_FIELD_SIZE)
            {
                throw(exception("OriginsMatrix size mismatch."));
            }
            if (GAME_MATRIX.size() != GAME_FIELD_SIZE || GAME_MATRIX[0].size() != GAME_FIELD_SIZE)
            {
                throw(exception("GameMatrix size mismatch."));
            }

            InitializeComponent();
        }
        catch (exception e)
        {
            System::Windows::Forms::MessageBox::Show("Failed to format server response: " + managedResponse, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            this->APP_PREV_WINDOW->Show();
            this->Close();
        }
    }
    private: void myResponseHandler2(const string& response) {
        String^ managedResponse = ""; //marshal_as<String^>(response);
        for (char c : response)
            managedResponse += (Char)c;

        System::Windows::Forms::MessageBox::Show("Server response: " + managedResponse);
        this->panel2->Enabled = true;
    }


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
            game_time = GAME_MAX_TIME;
            game_hints = GAME_MAX_HINTS;
            game_checks = GAME_MAX_CHECKS;
            game_attempts = GAME_MAX_ATTEMPTS;
            textArraySize = GAME_FIELD_SIZE * GAME_FIELD_SIZE;
            panelSize = textBoxSize * GAME_FIELD_SIZE;
            formSize = panelSize + 200;

            this->lose_image = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_DEFEAT_PATH))));
            this->win_image = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile(GetResourcesDirectory(RES_VICTORY_PATH))));
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->button6 = (gcnew System::Windows::Forms::Button());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->timer1 = (gcnew System::Windows::Forms::Timer());
            this->matrixCharArray = (gcnew ArrayList());
            this->directionsArray = (gcnew ArrayList());
            this->textBoxArray = (gcnew ArrayList());
            this->labelArray = (gcnew ArrayList());
            this->SuspendLayout();
            //
            // panel1
            //
            this->panel1->Location = System::Drawing::Point((this->formSize - this->panelSize) / 2, (this->formSize - this->panelSize) / 2);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(this->panelSize, this->panelSize);
            this->panel1->TabIndex = 0;
            //
            // panel2
            //
            this->panel2->Location = System::Drawing::Point((this->formSize - 500) / 2, (this->formSize - 300) / 2);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(500, 300);
            this->panel2->TabIndex = 0;
            this->panel2->Enabled = false;
            this->panel2->Visible = false;
            this->panel2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            //
            // button1
            //
            this->button1->Location = System::Drawing::Point((this->formSize - 450) / 2, 0);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(150, 50);
            this->button1->Text = "Проверка (" + Convert::ToString(this->game_checks) + "/" + Convert::ToString(GAME_MAX_CHECKS) + ")";
            this->button1->Enabled = (GAME_MAX_CHECKS > 0);
            this->button1->TabIndex = 0;
            this->button1->Click += gcnew System::EventHandler(this, &LevelForm::button1_OnClick);
            //
            // button2
            //
            this->button2->Location = System::Drawing::Point((this->formSize + 150) / 2, 0);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(150, 50);
            this->button2->Text = "Подсказка (" + Convert::ToString(this->game_hints) + "/" + Convert::ToString(GAME_MAX_HINTS) + ")";
            this->button2->Enabled = (GAME_MAX_HINTS > 0);
            this->button2->TabIndex = 0;
            this->button2->Click += gcnew System::EventHandler(this, &LevelForm::button2_OnClick);
            //
            // button3
            //
            this->button3->Location = System::Drawing::Point((this->formSize - 150) / 2, this->formSize - 50);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(150, 50);
            this->button3->Text = "Назад";
            this->button3->TabIndex = 0;
            this->button3->Click += gcnew System::EventHandler(this, &LevelForm::button3_OnClick);
            //
            // button4
            //
            this->button4->Location = System::Drawing::Point(100, 200);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(100, 30);
            this->button4->Text = "Выйти";
            this->button4->TabIndex = 0;
            this->button4->Click += gcnew System::EventHandler(this, &LevelForm::button4_OnClick);
            this->panel2->Controls->Add(this->button4);
            //
            // button5
            //
            this->button5->Location = System::Drawing::Point(300, 200);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(100, 30);
            this->button5->Text = "Вернуться";
            this->button5->TabIndex = 0;
            this->button5->Click += gcnew System::EventHandler(this, &LevelForm::button3_OnClick);
            this->panel2->Controls->Add(this->button5);
            //
            // button6
            //
            this->button6->Location = System::Drawing::Point(125, 240);
            this->button6->Name = L"button6";
            this->button6->Size = System::Drawing::Size(250, 45);
            this->button6->Text = "Использовать ещё попытку";
            this->button6->TabIndex = 0;
            this->button6->Click += gcnew System::EventHandler(this, &LevelForm::button6_OnClick);
            this->panel2->Controls->Add(this->button6);
            //
            // textBox1
            //
            this->textBox1->Location = System::Drawing::Point((this->formSize - 150) / 2, 0);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Multiline = true;
            this->textBox1->Size = System::Drawing::Size(150, 50);
            this->textBox1->Text = "Время";
            this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            this->textBox1->ReadOnly = true;
            this->textBox1->TabIndex = 0;
            //
            // timer1
            //
            this->timer1->Interval = 1000;
            this->timer1->Tick += gcnew System::EventHandler(this, &LevelForm::timer1_Tick);
            //
            // textBoxArray
            //
            for (int i = 0; i < this->textArraySize; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    TextBox^ curDirection = gcnew System::Windows::Forms::TextBox();
                    this->panel1->Controls->Add(curDirection);
                    curDirection->Name = L"direction" + Convert::ToString(i * 4 + j);
                    curDirection->TabIndex = 0;
                    curDirection->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
                    curDirection->ReadOnly = true;
                    curDirection->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
                    curDirection->BackColor = System::Drawing::Color::GreenYellow;
                    curDirection->Multiline = true;
                    curDirection->Enabled = false;
                    curDirection->Visible = false;
                    curDirection->Size = System::Drawing::Size(this->textBoxSize / 3, this->textBoxSize / 3);
                    if (j == DIR_DOWN)
                    {
                        curDirection->Location = System::Drawing::Point(i % GAME_FIELD_SIZE * this->textBoxSize + this->textBoxSize / 3, i / GAME_FIELD_SIZE * this->textBoxSize - this->textBoxSize / 3);
                        curDirection->Text = "v";
                    }
                    if (j == DIR_UP)
                    {
                        curDirection->Location = System::Drawing::Point(i % GAME_FIELD_SIZE * this->textBoxSize + this->textBoxSize / 3, i / GAME_FIELD_SIZE * this->textBoxSize + this->textBoxSize);
                        curDirection->Text = "^";
                    }
                    if (j == DIR_RIGHT)
                    {
                        curDirection->Location = System::Drawing::Point(i % GAME_FIELD_SIZE * this->textBoxSize - this->textBoxSize / 3, i / GAME_FIELD_SIZE * this->textBoxSize + this->textBoxSize / 3);
                        curDirection->Text = ">";
                    }
                    if (j == DIR_LEFT)
                    {
                        curDirection->Location = System::Drawing::Point(i % GAME_FIELD_SIZE * this->textBoxSize + this->textBoxSize, i / GAME_FIELD_SIZE * this->textBoxSize + this->textBoxSize / 3);
                        curDirection->Text = "<";
                    }
                    this->directionsArray->Add(curDirection);
                }
            }
            for (int i = 0; i < this->textArraySize; i++)
            {
                TextBox^ curLabel = gcnew System::Windows::Forms::TextBox();
                this->panel1->Controls->Add(curLabel);
                curLabel->Name = L"label" + i;
                curLabel->TabIndex = 0;
                curLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serthis->if", 5, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
                curLabel->Visible = false;
                curLabel->ReadOnly = true;
                curLabel->Enabled = false;
                curLabel->BackColor = System::Drawing::Color::LightPink;
                curLabel->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
                curLabel->Multiline = true;
                curLabel->Size = System::Drawing::Size(18, 18);
                curLabel->Location = System::Drawing::Point(i % GAME_FIELD_SIZE * this->textBoxSize, i / GAME_FIELD_SIZE * this->textBoxSize + (this->textBoxSize - 18));
                this->labelArray->Add(curLabel);

                TextBox^ curTextBox = gcnew System::Windows::Forms::TextBox();
                this->panel1->Controls->Add(curTextBox);
                curTextBox->Name = L"textBox" + i;
                curTextBox->TabIndex = i;
                curTextBox->Enabled = false;
                curTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
                curTextBox->Multiline = true;
                curTextBox->Size = System::Drawing::Size(this->textBoxSize, this->textBoxSize);
                curTextBox->Location = System::Drawing::Point(i % GAME_FIELD_SIZE * this->textBoxSize, i / GAME_FIELD_SIZE * this->textBoxSize);
                curTextBox->TextChanged += gcnew System::EventHandler(this, &LevelForm::textBox_TextChanged);
                curTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &LevelForm::textBox_KeyPress);
                this->textBoxArray->Add(curTextBox);
            }
            //
            // LevelForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(this->formSize, this->formSize);
            this->Controls->Add(this->panel2);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->textBox1);
            this->Margin = System::Windows::Forms::Padding(4);
            this->Name = L"LevelForm";
            this->Text = L"Ключворд - Игра";
            //this->Icon = (cli::safe_cast<System::Drawing::Icon^>(System::Drawing::Icon::ExtractAssociatedIcon(GetResourcesDirectory(RES_ICON_PATH))));
            this->Load += gcnew System::EventHandler(this, &LevelForm::LevelForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

#pragma endregion
    private: System::Void LevelForm_Load(System::Object^ sender, System::EventArgs^ e) {
        const int ARR_SIZE = GAME_FIELD_SIZE;

            for (int i = 0; i < ARR_SIZE; i++)
            {
                for (int j = 0; j < ARR_SIZE; j++)
                {
                    if (GAME_MATRIX[i][j] != '-')
                    {
                        if (!this->matrixCharArray->Contains(GAME_MATRIX[i][j]))
                        {
                            this->matrixCharArray->Add(GAME_MATRIX[i][j]);
                        }
                        ((TextBox^)this->textBoxArray[i * ARR_SIZE + j])->Enabled = true;
                        ((TextBox^)this->labelArray[i * ARR_SIZE + j])->Visible = true;
                        for (int k = 0; k < this->matrixCharArray->Count; k++)
                        {
                            if (((char)this->matrixCharArray[k]) == GAME_MATRIX[i][j])
                            {
                                ((TextBox^)this->labelArray[i * ARR_SIZE + j])->Text = Convert::ToString(k + 1);
                                break;
                            }
                        }

                        for (int k = 0; k < 4; k++)
                        {
                            if (GAME_MATRIX_ORIGINS[i][j][k])
                            {
                                ((TextBox^)directionsArray[(i * ARR_SIZE + j) * 4 + k])->Visible = true;
                            }
                        }
                    }
                }
            }

        for (int i = 0; i < GAME_FIRST_LETTERS; i++)
        {
            this->hint_Visualize(false);
        }

        game_attempts--;
        this->button6->Enabled = (game_attempts > 0);
        this->timer1->Start();
    }

    private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
        if (game_time == 0)
        {
            this->gameOver_Visualize(!this->check_Visualize(true));
            return;
        }
        game_time--;
        int sec = game_time % 60, min = game_time / 60;
        String^ string_sec = Convert::ToString(sec);
        if (string_sec->Length < 2)
        {
            string_sec = "0" + string_sec;
        }
        String^ string_min = Convert::ToString(min);
        if (string_min->Length < 2)
        {
            string_min = "0" + string_min;
        }
        this->textBox1->Text = "Время" + System::Environment::NewLine + string_min + ":" + string_sec;
    }

    private: System::Void textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        this->check_Visualize(false);

        const int ARR_SIZE = GAME_FIELD_SIZE;
        for (int i = 0; i < ARR_SIZE; i++)
        {
            for (int j = 0; j < ARR_SIZE; j++)
            {
                if (GAME_MATRIX[i][j] == GAME_MATRIX[((TextBox^)sender)->TabIndex / ARR_SIZE][((TextBox^)sender)->TabIndex % ARR_SIZE])
                {
                    if (((TextBox^)this->textBoxArray[i * ARR_SIZE + j])->Text->Length != 0)
                    {
                        if (((TextBox^)this->textBoxArray[i * ARR_SIZE + j])->Text == ((TextBox^)sender)->Text)
                        {
                            continue;
                        }
                    }
                    ((TextBox^)this->textBoxArray[i * ARR_SIZE + j])->Text = ((TextBox^)sender)->Text;
                }
            }
        }
    }

    private: System::Void textBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
        e->Handled = false;
        if (e->KeyChar == 8)
        {
            return;
        }

        if (!(((TextBox^)sender)->Text->Length < 1 && Char::IsLetter(e->KeyChar)))
        {
            e->Handled = true;
        }
        else
        {
            String^ higher = Convert::ToString(e->KeyChar)->ToUpper();
            e->KeyChar = higher[0];
        }
    }

    private: System::Void button1_OnClick(System::Object^ sender, System::EventArgs^ e) {
               Boolean any_errors = this->check_Visualize(!this->checkEnabled);
               if (this->checkEnabled)
               {
                   this->game_checks--;
                   this->button1->Text = "Проверка(" + Convert::ToString(this->game_checks) + "/" + Convert::ToString(GAME_MAX_CHECKS) + ")";
                   if (!any_errors)
                   {
                       this->gameOver_Visualize(true);
                   }
                   else if (game_checks <= 0)
                   {
                       this->gameOver_Visualize(false);
                   }
               }
           }

    private: System::Void button2_OnClick(System::Object^ sender, System::EventArgs^ e) {
        this->hint_Visualize(true);
        this->button2->Text = "Подсказка (" + Convert::ToString(this->game_hints) + "/" + Convert::ToString(GAME_MAX_HINTS) + ")";
        this->button2->Enabled = (this->game_hints > 0);
    }

    private: System::Void button3_OnClick(System::Object^ sender, System::EventArgs^ e) {
        APP_PREV_WINDOW->Show();
        this->Close();
    }

    private: System::Void button4_OnClick(System::Object^ sender, System::EventArgs^ e) {
        Application::Exit();
    }

    private: System::Void button6_OnClick(System::Object^ sender, System::EventArgs^ e) {
        this->gameReload_Visualize();
        this->game_attempts--;
    }

    private: System::Void hint_Visualize(bool isahint) {
        srand(time(0));
        ArrayList^ wrongLetters = gcnew ArrayList();
        const int ARR_SIZE = GAME_FIELD_SIZE;
        for (int i = 0; i < ARR_SIZE; i++)
        {
            for (int j = 0; j < ARR_SIZE; j++)
            {
                if (GAME_MATRIX[i][j] == '-')
                {
                    continue;
                }

                if (((TextBox^)this->textBoxArray[i * ARR_SIZE + j])->Text->Length == 0)
                {
                    if (!wrongLetters->Contains(((Char)GAME_MATRIX[i][j])))
                    {
                        wrongLetters->Add(((Char)GAME_MATRIX[i][j]));
                    }
                }
                else if (((Char)GAME_MATRIX[i][j]) != ((TextBox^)this->textBoxArray[i * ARR_SIZE + j])->Text[0])
                {
                    if (!wrongLetters->Contains(((Char)GAME_MATRIX[i][j])))
                    {
                        wrongLetters->Add(((Char)GAME_MATRIX[i][j]));
                    }
                }
            }
        }
        if (wrongLetters->Count == 0)
        {
            return;
        }
        else if (isahint)
        {
            this->game_hints--;
        }

        int rand_pos = rand() % wrongLetters->Count;
        for (int i = 0; i < ARR_SIZE; i++)
        {
            for (int j = 0; j < ARR_SIZE; j++)
            {
                if (((Char)GAME_MATRIX[i][j]) == ((Char)wrongLetters[rand_pos]))
                {
                    ((TextBox^)textBoxArray[i * ARR_SIZE + j])->Text = Convert::ToString(wrongLetters[rand_pos]);
                    if (isahint)
                    {
                        ((TextBox^)textBoxArray[i * ARR_SIZE + j])->BackColor = System::Drawing::Color::Blue;
                    }
                }
            }
        }
    }

    private: System::Boolean check_Visualize(bool enabled) {
        Boolean any_errors = false;
        this->checkEnabled = enabled;
        const int ARR_SIZE = GAME_FIELD_SIZE;
        for (int i = 0; i < ARR_SIZE; i++)
        {
            for (int j = 0; j < ARR_SIZE; j++)
            {
                if (!((TextBox^)textBoxArray[i * ARR_SIZE + j])->Enabled)
                {
                    continue;
                }

                    if (!this->checkEnabled)
                    {
                        ((TextBox^)textBoxArray[i * ARR_SIZE + j])->BackColor = System::Drawing::Color::White;
                    }
                    else if (((TextBox^)textBoxArray[i * ARR_SIZE + j])->Text->Length != 0)
                    {
                        if (((Char)GAME_MATRIX[i][j]) == ((TextBox^)textBoxArray[i * ARR_SIZE + j])->Text[0])
                        {
                            ((TextBox^)textBoxArray[i * ARR_SIZE + j])->BackColor = System::Drawing::Color::Green;
                        }
                        else
                        {
                            ((TextBox^)textBoxArray[i * ARR_SIZE + j])->BackColor = System::Drawing::Color::Red;
                            any_errors = true;
                        }
                    }
                    else
                    {
                        any_errors = true;
                    }
            }
        }
        return any_errors;
    }

    private: System::Void gameOver_Visualize(bool win) {
        timer1->Stop();
        this->button6->Text = "Использовать ещё попытку" + System::Environment::NewLine
            + "Осталось: " + this->game_attempts + "/" + GAME_MAX_ATTEMPTS;
        this->panel1->Enabled = false;
        this->button1->Enabled = false;
        this->button2->Enabled = false;
        this->button3->Enabled = false;

        this->panel2->Visible = true;
        this->panel2->Enabled = true;

        if (win)
        {
            this->panel2->BackgroundImage = this->win_image;
            this->button6->Visible = false;
            this->button6->Enabled = false;

            this->panel2->Enabled = false;
            updateUserStatistics(true);
        }
        else
        {
            this->panel2->BackgroundImage = this->lose_image;
            this->button6->Visible = true;
            this->button6->Enabled = (this->game_attempts > 0);
            if (this->game_attempts <= 0) {
                this->panel2->Enabled = false;
                updateUserStatistics(false);
            }
        }
    }

    private: System::Void gameReload_Visualize() {
        this->game_time = 60 + (GAME_MAX_TIME - 60) / 2;
        this->game_hints = GAME_MAX_HINTS / 2;
        this->game_checks = 1 + (GAME_MAX_CHECKS - 1) / 2;
        this->button1->Enabled = (game_hints > 0);
        this->button1->Text = "Проверка (" + Convert::ToString(this->game_checks) + "/" + Convert::ToString(GAME_MAX_CHECKS) + ")";
        this->button2->Enabled = true;
        this->button2->Text = "Подсказка (" + Convert::ToString(this->game_hints) + "/" + Convert::ToString(GAME_MAX_HINTS) + ")";
        this->button3->Enabled = true;
        this->panel1->Enabled = true;
        this->panel2->Enabled = false;
        this->panel2->Visible = false;
        timer1->Start();
    }

    private: System::Void getKeywordPuzzle() {
        string username = "";
        for (int i = 0; i < APP_USER_NAME->Length; i++)
            username += ((char)APP_USER_NAME[i]);
        string filename = "";
        for (int i = 0; i < APP_FILE_NAME->Length; i++)
            filename += ((char)APP_FILE_NAME[i]);

        int requestType = CURL_REQUEST_TYPE_PUZZLE_FROMFILE;
        vector<pair<string, string>> requestData(0);
        requestData.push_back(pair<string, string>("username", username));
        requestData.push_back(pair<string, string>("filename", filename));


        // Create a managed delegate instance
        ManagedCallback^ managedCallback = gcnew ManagedCallback(this, &LevelForm::myResponseHandler1);
        // Convert managed delegate to unmanaged function pointer
        IntPtr ptr = Marshal::GetFunctionPointerForDelegate(managedCallback);
        ResponseCallback nativeCallback = (ResponseCallback)ptr.ToPointer();
        // Call the function
        curlClient().performCurlRequest(nativeCallback, requestType, requestData);
    }

    private: System::Void updateUserStatistics(bool win) {
        string username = "";
        for (int i = 0; i < APP_USER_NAME->Length; i++)
            username += ((char)APP_USER_NAME[i]);

        int requestType;
        if (win)
        {
            requestType = CURL_REQUEST_TYPE_STATISTICS_UPLOAD_VICTORY;
        }
        else
        {
            requestType = CURL_REQUEST_TYPE_STATISTICS_UPLOAD_DEFEAT;
        }

        vector<pair<string, string>> requestData(0);
        requestData.push_back(pair<string, string>("username", username));


        // Create a managed delegate instance
        ManagedCallback^ managedCallback = gcnew ManagedCallback(this, &LevelForm::myResponseHandler2);
        // Convert managed delegate to unmanaged function pointer
        IntPtr ptr = Marshal::GetFunctionPointerForDelegate(managedCallback);
        ResponseCallback nativeCallback = (ResponseCallback)ptr.ToPointer();
        // Call the function
        curlClient().performCurlRequest(nativeCallback, requestType, requestData);
    }
    };
}