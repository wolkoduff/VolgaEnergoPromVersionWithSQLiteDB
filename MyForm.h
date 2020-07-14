#pragma once

#ifdef CreateFile
#undef CreateFile
#endif // CreateFile


namespace WorkWithSqlite {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Data::SQLite;
	using namespace System::Text;


	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	private: System::Windows::Forms::MonthCalendar^ monthCalendar1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	public: bool flag = false;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	public: SQLiteConnection^ db;
	public: static String^ path;
	public: static String^ sernumber;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	private: System::Windows::Forms::DataGridView^ dataGridView3;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Label^ label4;

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public:
	protected:

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea7 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea8 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea9 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->BeginInit();
			this->SuspendLayout();
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->Location = System::Drawing::Point(1721, 13);
			this->monthCalendar1->Margin = System::Windows::Forms::Padding(7);
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->TabIndex = 1;
			// 
			// dataGridView1
			// 
			this->dataGridView1->Location = System::Drawing::Point(423, 262);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->Size = System::Drawing::Size(423, 238);
			this->dataGridView1->TabIndex = 3;
			this->dataGridView1->Visible = false;
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->button1->Location = System::Drawing::Point(12, 206);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(372, 143);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Испытания";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 40));
			this->button5->Location = System::Drawing::Point(12, 576);
			this->button5->Margin = System::Windows::Forms::Padding(2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(372, 143);
			this->button5->TabIndex = 6;
			this->button5->Text = L"Архив/БД";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 40));
			this->button3->Location = System::Drawing::Point(12, 855);
			this->button3->Margin = System::Windows::Forms::Padding(2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(372, 143);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Закрыть";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->button4->Location = System::Drawing::Point(1462, 123);
			this->button4->Margin = System::Windows::Forms::Padding(2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(239, 53);
			this->button4->TabIndex = 9;
			this->button4->Text = L"Найти";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36));
			this->label1->Location = System::Drawing::Point(413, 119);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(722, 55);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Введите серийный № прибора:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->label2->Location = System::Drawing::Point(1766, 179);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(119, 46);
			this->label2->TabIndex = 15;
			this->label2->Text = L"16:27";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label3->Location = System::Drawing::Point(1458, 981);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(413, 24);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Версия программы 2. Дата выпуска: сегодня";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->textBox1->Location = System::Drawing::Point(1139, 123);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(221, 53);
			this->textBox1->TabIndex = 10;
			this->textBox1->Text = L"125478";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// chart1
			// 
			chartArea7->AxisX->Title = L"Ток";
			chartArea7->AxisX->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			chartArea7->AxisY->Title = L"Напряжение";
			chartArea7->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			chartArea7->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea7);
			legend7->Alignment = System::Drawing::StringAlignment::Center;
			legend7->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			legend7->ItemColumnSpacing = 20;
			legend7->Name = L"Legend1";
			this->chart1->Legends->Add(legend7);
			this->chart1->Location = System::Drawing::Point(423, 540);
			this->chart1->Name = L"chart1";
			series7->ChartArea = L"ChartArea1";
			series7->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series7->IsValueShownAsLabel = true;
			series7->IsXValueIndexed = true;
			series7->Legend = L"Legend1";
			series7->Name = L"Ток/Напряжение";
			this->chart1->Series->Add(series7);
			this->chart1->Size = System::Drawing::Size(423, 321);
			this->chart1->TabIndex = 11;
			this->chart1->Text = L"chart1";
			title7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			title7->Name = L"Title1";
			title7->Text = L"График прибора в режиме MMA";
			this->chart1->Titles->Add(title7);
			this->chart1->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->checkBox1->Location = System::Drawing::Point(423, 206);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(132, 50);
			this->checkBox1->TabIndex = 12;
			this->checkBox1->Text = L"MMA";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->checkBox2->Location = System::Drawing::Point(937, 206);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(215, 50);
			this->checkBox2->TabIndex = 13;
			this->checkBox2->Text = L"MIG/MAG";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->checkBox3->Location = System::Drawing::Point(1462, 206);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(104, 50);
			this->checkBox3->TabIndex = 14;
			this->checkBox3->Text = L"TIG";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox3_CheckedChanged);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(13, 13);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(371, 161);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 17;
			this->pictureBox1->TabStop = false;
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Location = System::Drawing::Point(937, 262);
			this->dataGridView2->Margin = System::Windows::Forms::Padding(2);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->ReadOnly = true;
			this->dataGridView2->Size = System::Drawing::Size(423, 238);
			this->dataGridView2->TabIndex = 18;
			this->dataGridView2->Visible = false;
			// 
			// dataGridView3
			// 
			this->dataGridView3->AllowUserToAddRows = false;
			this->dataGridView3->AllowUserToDeleteRows = false;
			this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView3->Location = System::Drawing::Point(1462, 262);
			this->dataGridView3->Name = L"dataGridView3";
			this->dataGridView3->ReadOnly = true;
			this->dataGridView3->Size = System::Drawing::Size(423, 238);
			this->dataGridView3->TabIndex = 19;
			this->dataGridView3->Visible = false;
			// 
			// chart2
			// 
			chartArea8->AxisX->Title = L"Ток";
			chartArea8->AxisX->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			chartArea8->AxisY->Title = L"Напряжение";
			chartArea8->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			chartArea8->Name = L"ChartArea2";
			this->chart2->ChartAreas->Add(chartArea8);
			legend8->Alignment = System::Drawing::StringAlignment::Center;
			legend8->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			legend8->Name = L"Legend2";
			this->chart2->Legends->Add(legend8);
			this->chart2->Location = System::Drawing::Point(937, 540);
			this->chart2->Name = L"chart2";
			series8->ChartArea = L"ChartArea2";
			series8->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series8->IsValueShownAsLabel = true;
			series8->IsXValueIndexed = true;
			series8->Legend = L"Legend2";
			series8->Name = L"Ток/Напряжение";
			this->chart2->Series->Add(series8);
			this->chart2->Size = System::Drawing::Size(423, 321);
			this->chart2->TabIndex = 20;
			this->chart2->Text = L"chart2";
			title8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			title8->Name = L"Title2";
			title8->Text = L"График прибора в режиме MIG/MAG";
			this->chart2->Titles->Add(title8);
			this->chart2->Visible = false;
			// 
			// chart3
			// 
			chartArea9->AxisX->Title = L"Ток";
			chartArea9->AxisX->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			chartArea9->AxisY->Title = L"Напряжение";
			chartArea9->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			chartArea9->Name = L"ChartArea3";
			this->chart3->ChartAreas->Add(chartArea9);
			legend9->Alignment = System::Drawing::StringAlignment::Center;
			legend9->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			legend9->Name = L"Legend3";
			this->chart3->Legends->Add(legend9);
			this->chart3->Location = System::Drawing::Point(1462, 540);
			this->chart3->Name = L"chart3";
			series9->ChartArea = L"ChartArea3";
			series9->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series9->IsValueShownAsLabel = true;
			series9->IsXValueIndexed = true;
			series9->Legend = L"Legend3";
			series9->Name = L"Ток/Напряжение";
			this->chart3->Series->Add(series9);
			this->chart3->Size = System::Drawing::Size(423, 321);
			this->chart3->TabIndex = 21;
			this->chart3->Text = L"chart3";
			title9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			title9->Name = L"Title1";
			title9->Text = L"График прибора в режиме TIG";
			this->chart3->Titles->Add(title9);
			this->chart3->Visible = false;
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->button2->Location = System::Drawing::Point(12, 391);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(372, 143);
			this->button2->TabIndex = 22;
			this->button2->Text = L"Зарегистрировать\r\nприбор";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button6
			// 
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->button6->Location = System::Drawing::Point(423, 885);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(423, 93);
			this->button6->TabIndex = 23;
			this->button6->Text = L"Увеличить";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Visible = false;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button7
			// 
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->button7->Location = System::Drawing::Point(937, 885);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(423, 93);
			this->button7->TabIndex = 24;
			this->button7->Text = L"Увеличить";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// button8
			// 
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->button8->Location = System::Drawing::Point(1462, 885);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(423, 93);
			this->button8->TabIndex = 25;
			this->button8->Text = L"Увеличить";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Visible = false;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 40));
			this->label4->Location = System::Drawing::Point(662, 13);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(904, 63);
			this->label4->TabIndex = 26;
			this->label4->Text = L"Я Вас категорически приветствую!";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(1904, 1041);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->chart3);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->dataGridView3);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->monthCalendar1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->pictureBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Приложение для стенда АНС-500. Главный экран";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e);	
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}
