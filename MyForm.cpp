#include "MyForm.h"
#include "Tests.h"
#include "Grafiki.h"
#include "Register.h"

#ifdef CreateFile
#undef CreateFile
#endif // CreateFile

using namespace System::Data::SQLite;
using namespace System::Text;
using namespace System::Drawing;
using namespace System::Windows::Forms::DataVisualization::Charting;
using namespace WorkWithSqlite;
using namespace System::IO;

bool flag_mma = false;
bool flag_mig = false;
bool flag_tig = false;

//------------------------------------------------------------------------
// Кнопка Испытания
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Tests^ f2 = gcnew Tests(this);
	f2->Show();
	this->Hide();
	return System::Void();
}

//------------------------------------------------------------------------
// Кнопка регистрации
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	Register^ f3 = gcnew Register(this);
	f3->Show();
	return System::Void();
}

//------------------------------------------------------------------------
// Кнопка "Архив"
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button5_Click(System::Object^ sender, System::EventArgs^ e)
{
	folderBrowserDialog1->ShowDialog();
	path = folderBrowserDialog1->SelectedPath;
	Directory::CreateDirectory(path + "\\mma");
	Directory::CreateDirectory(path + "\\migmag");
	Directory::CreateDirectory(path + "\\tig");
	Directory::SetCurrentDirectory(path);
	if (!System::IO::File::Exists("test.db"))
	{
		SQLiteConnection::CreateFile("test.db");
	}
	try
	{
		db = gcnew SQLiteConnection();
		db->ConnectionString = "Data Source = test.db";
		db->Open();
		flag = true;
		String^ sql_create_table = "" +
			"CREATE TABLE IF NOT EXISTS \"Devices\" (" +
			"\"id_device\"	INTEGER," +
			"\"name_dev\"	TEXT, " +
			"\"maker\"	TEXT," +
			"\"vladelets\"	TEXT," +
			"\"serial_number\"	TEXT, " +
			"\"invent_number\"	TEXT, " +
			"PRIMARY KEY(\"id_device\") " +
			");";
		SQLiteCommand^ cmdCreateTable = db->CreateCommand();
		cmdCreateTable->CommandText = sql_create_table;
		cmdCreateTable->ExecuteNonQuery();
		sql_create_table = "" +
			"CREATE TABLE IF NOT EXISTS \"MIGMAG\" (" +
			"\"num_cycle\"	INTEGER," +
			"\"step_cycle\"	INTEGER," +
			"\"amper_izm\"	REAL," +
			"\"volt_izm\"	REAL," +
			"\"num_prog\"	INTEGER," +
			"\"date_izm\"	TEXT," +
			"\"time_izm\"	TEXT," +
			"\"defence\"	INTEGER," +
			"\"id_device\"	INTEGER," +
			"FOREIGN KEY(\"id_device\") REFERENCES \"Devices\"(\"id_device\")" +
			");";
		cmdCreateTable->CommandText = sql_create_table;
		cmdCreateTable->ExecuteNonQuery();
		sql_create_table = "" +
			"CREATE TABLE IF NOT EXISTS \"MMA\" (" +
			"\"num_cycle\"	INTEGER," +
			"\"step_cycle\"	INTEGER," +
			"\"amper_izm\"	REAL," +
			"\"volt_izm\"	REAL," +
			"\"forsaj\"	INTEGER," +
			"\"date_izm\"	TEXT," +
			"\"time_izm\"	TEXT," +
			"\"defence\"	INTEGER," +
			"\"id_device\"	INTEGER," +
			"FOREIGN KEY(\"id_device\") REFERENCES \"Devices\"(\"id_device\")" +
			");";
		cmdCreateTable->CommandText = sql_create_table;
		cmdCreateTable->ExecuteNonQuery();
		sql_create_table = "" +
			"CREATE TABLE IF NOT EXISTS \"TIG\" (" +
			"\"num_cycle\"	INTEGER," +
			"\"step_cycle\"	INTEGER," +
			"\"amper_izm\"	REAL," +
			"\"volt_izm\"	REAL," +
			"\"amp_set\"	INTEGER," +
			"\"volt_set\"	REAL," +
			"\"date_izm\"	TEXT," +
			"\"time_izm\"	TEXT," +
			"\"defence\"	INTEGER," +
			"\"id_device\"	INTEGER," +
			"FOREIGN KEY(\"id_device\") REFERENCES \"Devices\"(\"id_device\")" +
			");";
		cmdCreateTable->CommandText = sql_create_table;
		cmdCreateTable->ExecuteNonQuery();
		db->Close();
		flag = false;
	}
	catch (Exception ^ ex) {
		MessageBox::Show(ex->Message);
	}
	finally
	{
		delete (IDisposable^)db;
	}
	button1->Enabled = true;
	button2->Enabled = true;
	button4->Enabled = true;
	return System::Void();
}

//------------------------------------------------------------------------
// Кнопка "Закрыть"
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	Close();
	return System::Void();
}

//------------------------------------------------------------------------
// Кнопка "Найти"
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	// тут главное прописать, что нет подключения
	if (textBox1->Text == "")
	{
		sernumber = "";
		MessageBox::Show("Пустое поле", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else
	{
		sernumber = textBox1->Text;
		// опустошаем все графики и таблицы на случай когда будет перезапуск
		dataGridView1->DataSource = nullptr;
		dataGridView2->DataSource = nullptr;
		dataGridView3->DataSource = nullptr;
		chart1->Series->Clear();
		chart2->Series->Clear();
		chart3->Series->Clear();
	}
	if (sernumber != "")
	{
		// включаем новые элементы управления
		if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == false)
		{
			dataGridView1->Visible = true;
			dataGridView2->Visible = false;
			dataGridView3->Visible = false;
			chart1->Visible = true;
			chart2->Visible = false;
			chart3->Visible = false;
			button6->Visible = true;
			button7->Visible = false;
			button8->Visible = false;
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			dataGridView1->Visible = false;
			dataGridView2->Visible = true;
			dataGridView3->Visible = false;
			chart1->Visible = false;
			chart2->Visible = true;
			chart3->Visible = false;
			button6->Visible = false;
			button7->Visible = true;
			button8->Visible = false;
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			dataGridView1->Visible = true;
			dataGridView2->Visible = true;
			dataGridView3->Visible = false;
			chart1->Visible = true;
			chart2->Visible = true;
			chart3->Visible = false;
			button6->Visible = true;
			button7->Visible = true;
			button8->Visible = false;
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			dataGridView1->Visible = false;
			dataGridView2->Visible = false;
			dataGridView3->Visible = true;
			chart1->Visible = false;
			chart2->Visible = false;
			chart3->Visible = true;
			button6->Visible = false;
			button7->Visible = false;
			button8->Visible = true;
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			dataGridView1->Visible = true;
			dataGridView2->Visible = false;
			dataGridView3->Visible = true;
			chart1->Visible = true;
			chart2->Visible = false;
			chart3->Visible = true;
			button6->Visible = true;
			button7->Visible = false;
			button8->Visible = true;
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			dataGridView1->Visible = false;
			dataGridView2->Visible = true;
			dataGridView3->Visible = true;
			chart1->Visible = false;
			chart2->Visible = true;
			chart3->Visible = true;
			button6->Visible = false;
			button7->Visible = true;
			button8->Visible = true;
		}
		else if(checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			dataGridView1->Visible = true;
			dataGridView2->Visible = true;
			dataGridView3->Visible = true;
			chart1->Visible = true;
			chart2->Visible = true;
			chart3->Visible = true;
			button6->Visible = true;
			button7->Visible = true;
			button8->Visible = true;
		}
		else
		{
			dataGridView1->DataSource = nullptr;
			dataGridView2->DataSource = nullptr;
			dataGridView3->DataSource = nullptr;
			chart1->Series->Clear();
			chart2->Series->Clear();
			chart3->Series->Clear();
			dataGridView1->Visible = false;
			dataGridView2->Visible = false;
			dataGridView3->Visible = false;
			chart1->Visible = false;
			chart2->Visible = false;
			chart3->Visible = false;
			button6->Visible = false;
			button7->Visible = false;
			button8->Visible = false;
		}
		
		// Невидимики
		DataTable^ tableMMA;
		DataTable^ tableMIG;
		DataTable^ tableTIG;
		DataColumn^ columnMMA;
		DataColumn^ columnMIG;
		DataColumn^ columnTIG;
		DataRow^ rowMMA;
		DataRow^ rowMIG;
		DataRow^ rowTIG;

		// Создаём невидимую таблицу данных
		tableMMA = gcnew DataTable();
		tableMIG = gcnew DataTable();
		tableTIG = gcnew DataTable();

		// Названия столбцов
		String^ nameFirstColumn = "Замер №";
		String^ nameSecondColumn = "Шаг цикла";
		String^ nameTrirdColumn = "I изм.";
		String^ nameFourthColumn = "U изм.";
		String^ nameFifthColumn;
		String^ nameSixthColumn;
		String^ nameSeventhColumn;
		String^ nameEigthColumn;
		String^ nameNinthColumn;

		// Создание и добавление 4 столбцов в 3 таблицы сразу
		columnMMA = gcnew DataColumn(nameFirstColumn, Int32::typeid);
		tableMMA->Columns->Add(columnMMA);
		columnMMA = gcnew DataColumn(nameSecondColumn, Int32::typeid);
		tableMMA->Columns->Add(columnMMA);
		columnMMA = gcnew DataColumn(nameTrirdColumn, Double::typeid);
		tableMMA->Columns->Add(columnMMA);
		columnMMA = gcnew DataColumn(nameFourthColumn, Double::typeid);
		tableMMA->Columns->Add(columnMMA);
		columnMIG = gcnew DataColumn(nameFirstColumn, Int32::typeid);
		tableMIG->Columns->Add(columnMIG);
		columnMIG = gcnew DataColumn(nameSecondColumn, Int32::typeid);
		tableMIG->Columns->Add(columnMIG);
		columnMIG = gcnew DataColumn(nameTrirdColumn, Double::typeid);
		tableMIG->Columns->Add(columnMIG);
		columnMIG = gcnew DataColumn(nameFourthColumn, Double::typeid);
		tableMIG->Columns->Add(columnMIG);
		columnTIG = gcnew DataColumn(nameFirstColumn, Int32::typeid);
		tableTIG->Columns->Add(columnTIG);
		columnTIG = gcnew DataColumn(nameSecondColumn, Int32::typeid);
		tableTIG->Columns->Add(columnTIG);
		columnTIG = gcnew DataColumn(nameTrirdColumn, Double::typeid);
		tableTIG->Columns->Add(columnTIG);
		columnTIG = gcnew DataColumn(nameFourthColumn, Double::typeid);
		tableTIG->Columns->Add(columnTIG);
		
		// Создание и добавление столбцов
		//
		// Таблицы формируются согласно чек-боксам
		if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == false)
		{
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			columnMMA = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			nameFifthColumn = "№ программы";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			columnMIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			columnMMA = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
			nameFifthColumn = "№ программы";
			columnMIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			columnTIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSixthColumn, Double::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameEigthColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameNinthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			columnMMA = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			columnTIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSixthColumn, Double::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameEigthColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameNinthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			nameFifthColumn = "№ программы";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			columnMIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			columnTIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSixthColumn, Double::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameEigthColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameNinthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			columnMMA = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMMA->Columns->Add(columnMMA);
			columnMMA = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMMA->Columns->Add(columnMMA);
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			nameFifthColumn = "№ программы";
			columnMIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSixthColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableMIG->Columns->Add(columnMIG);
			columnMIG = gcnew DataColumn(nameEigthColumn, Int32::typeid);
			tableMIG->Columns->Add(columnMIG);
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			columnTIG = gcnew DataColumn(nameFifthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSixthColumn, Double::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameSeventhColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameEigthColumn, String::typeid);
			tableTIG->Columns->Add(columnTIG);
			columnTIG = gcnew DataColumn(nameNinthColumn, Int32::typeid);
			tableTIG->Columns->Add(columnTIG);
		}

		// в данном этапе мы подключаемся к базе данных, что лежит в указанной папке
		db = gcnew SQLiteConnection();
		db->ConnectionString = "Data Source = test.db";
		db->Open();

		String^ sql_select = "";
		SQLiteCommand^ cmdSelect = db->CreateCommand();
		SQLiteDataReader^ dr;

		// Заполнение таблиц согласно чек-боксам
		if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == false)
		{
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, forsaj, date_izm, time_izm, defence from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			while (dr->Read())
			{
				// Заполнение строчек таблицы MMA
				rowMMA = tableMMA->NewRow();
				rowMMA[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMMA[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMMA[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMMA[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMMA[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMMA[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMMA[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMMA[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMMA->Rows->Add(rowMMA);
			}
			dr->Close();
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			nameFifthColumn = "№ программы";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Заполнение строчек таблицы MIG/MAG
				rowMIG = tableMIG->NewRow();
				rowMIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMIG[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMIG[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMIG->Rows->Add(rowMIG);
			}
			dr->Close();
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, forsaj, date_izm, time_izm, defence from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Заполнение строчек таблицы MMA
				rowMMA = tableMMA->NewRow();
				rowMMA[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMMA[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMMA[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMMA[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMMA[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMMA[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMMA[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMMA[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMMA->Rows->Add(rowMMA);
			}
			dr->Close();
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				nameFifthColumn = "№ программы";
				// Заполнение строчек таблицы MIG/MAG
				rowMIG = tableMIG->NewRow();
				rowMIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMIG[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMIG[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMIG->Rows->Add(rowMIG);
			}
			dr->Close();
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, amp_set, volt_set, date_izm, time_izm, defence from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Заполнение строчек таблицы TIG
				rowTIG = tableTIG->NewRow();
				rowTIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowTIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowTIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowTIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowTIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowTIG[nameSixthColumn] = Convert::ToDouble(dr[5]);
				rowTIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowTIG[nameEigthColumn] = Convert::ToString(dr[7]);
				rowTIG[nameNinthColumn] = Convert::ToInt32(dr[8]);
				tableTIG->Rows->Add(rowTIG);
			}
			dr->Close();
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, forsaj, date_izm, time_izm, defence from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			while (dr->Read())
			{
				// Заполнение строчек таблицы MMA
				rowMMA = tableMMA->NewRow();
				rowMMA[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMMA[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMMA[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMMA[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMMA[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMMA[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMMA[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMMA[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMMA->Rows->Add(rowMMA);
			}
			dr->Close();
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, amp_set, volt_set, date_izm, time_izm, defence from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			while (dr->Read())
			{
				// Заполнение строчек таблицы TIG
				rowTIG = tableTIG->NewRow();
				rowTIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowTIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowTIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowTIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowTIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowTIG[nameSixthColumn] = Convert::ToDouble(dr[5]);
				rowTIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowTIG[nameEigthColumn] = Convert::ToString(dr[7]);
				rowTIG[nameNinthColumn] = Convert::ToInt32(dr[8]);
				tableTIG->Rows->Add(rowTIG);
			}
			dr->Close();
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "№ программы";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			while (dr->Read())
			{
				// Заполнение строчек таблицы MIG/MAG
				rowMIG = tableMIG->NewRow();
				rowMIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMIG[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMIG[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMIG->Rows->Add(rowMIG);
			}
			dr->Close();
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, amp_set, volt_set, date_izm, time_izm, defence from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			while (dr->Read())
			{
				// Заполнение строчек таблицы TIG
				rowTIG = tableTIG->NewRow();
				rowTIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowTIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowTIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowTIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowTIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowTIG[nameSixthColumn] = Convert::ToDouble(dr[5]);
				rowTIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowTIG[nameEigthColumn] = Convert::ToString(dr[7]);
				rowTIG[nameNinthColumn] = Convert::ToInt32(dr[8]);
				tableTIG->Rows->Add(rowTIG);
			}
			dr->Close();
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, forsaj, date_izm, time_izm, defence from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "Форсаж";
			nameSixthColumn = "Дата измерений";
			nameSeventhColumn = "Время испытаний";
			nameEigthColumn = "Защита";
			while (dr->Read())
			{
				// Заполнение строчек таблицы MMA
				rowMMA = tableMMA->NewRow();
				rowMMA[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMMA[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMMA[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMMA[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMMA[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMMA[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMMA[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMMA[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMMA->Rows->Add(rowMMA);
			}
			dr->Close();
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "№ программы";
			while (dr->Read())
			{
				// Заполнение строчек таблицы MIG/MAG
				rowMIG = tableMIG->NewRow();
				rowMIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowMIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowMIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowMIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowMIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowMIG[nameSixthColumn] = Convert::ToString(dr[5]);
				rowMIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowMIG[nameEigthColumn] = Convert::ToInt32(dr[7]);
				tableMIG->Rows->Add(rowMIG);
			}
			dr->Close();
			sql_select = "select num_cycle, step_cycle, amper_izm, volt_izm, amp_set, volt_set, date_izm, time_izm, defence from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			nameFifthColumn = "I уст.";
			nameSixthColumn = "U уст.";
			nameSeventhColumn = "Дата измерений";
			nameEigthColumn = "Время испытаний";
			nameNinthColumn = "Защита";
			while (dr->Read())
			{
				// Заполнение строчек таблицы TIG
				rowTIG = tableTIG->NewRow();
				rowTIG[nameFirstColumn] = Convert::ToInt32(dr[0]);
				rowTIG[nameSecondColumn] = Convert::ToInt32(dr[1]);
				rowTIG[nameTrirdColumn] = Convert::ToDouble(dr[2]);
				rowTIG[nameFourthColumn] = Convert::ToDouble(dr[3]);
				rowTIG[nameFifthColumn] = Convert::ToInt32(dr[4]);
				rowTIG[nameSixthColumn] = Convert::ToDouble(dr[5]);
				rowTIG[nameSeventhColumn] = Convert::ToString(dr[6]);
				rowTIG[nameEigthColumn] = Convert::ToString(dr[7]);
				rowTIG[nameNinthColumn] = Convert::ToInt32(dr[8]);
				tableTIG->Rows->Add(rowTIG);
			}
			dr->Close();
		}
		
		// После того как всё подготовили, начинаем настраивать графики и передавать туда данные
		// отображение таблицы в визуалке
		dataGridView1->DataSource = tableMMA;
		dataGridView1->ReadOnly = true;
		dataGridView2->DataSource = tableMIG;
		dataGridView2->ReadOnly = true;
		dataGridView3->DataSource = tableTIG;
		dataGridView3->ReadOnly = true;
		// подчистили графики от старых картинок
		chart1->Series->Clear();
		chart2->Series->Clear();
		chart3->Series->Clear();
		// докидываем названия графикам, точнее легендам
		Series^ series1 = gcnew Series("Вольт/Ампер");
		Series^ series2 = gcnew Series("ВАХ КАКОЙ БОЛЬШОЙ МИГ!");
		Series^ series3 = gcnew Series("ВАХ ТИГР!");
		// Делаем синим цветом
		series1->Color = Color::Blue;
		series1->IsVisibleInLegend = true;
		series1->IsXValueIndexed = true;
		// Делаем оранжевого цвета
		series2->Color = Color::Orange;
		series2->IsVisibleInLegend = true;
		series2->IsXValueIndexed = true;
		// Делаем фиолетового цвета
		series3->Color = Color::Purple;
		series3->IsVisibleInLegend = true;
		series3->IsXValueIndexed = true;
		// Делаем линией
		series1->ChartType = SeriesChartType::Line;
		series2->ChartType = SeriesChartType::Line;
		series3->ChartType = SeriesChartType::Line;
		// добавляем линию
		chart1->Series->Add(series1);
		chart2->Series->Add(series2);
		chart3->Series->Add(series3);
		// Вот тут мы начинаем заполнять график данными
		if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == false)
		{
			// запрос к таблице MMA и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MMA
				series1->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			// запрос к таблице MIG/MAG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MIG/MAG
				series2->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == false)
		{
			// запрос к таблице MMA и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MMA
				series1->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();

			// запрос к таблице MIG/MAG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MIG/MAG
				series2->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			// запрос к таблице TIG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции TIG
				series3->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == true)
		{
			// запрос к таблице MMA и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MMA
				series1->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();

			// запрос к таблице TIG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции TIG
				series3->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();
		}
		else if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			// запрос к таблице MIG/MAG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MIG/MAG
				series2->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();

			// запрос к таблице TIG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции TIG
				series3->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();
		}
		else if (checkBox1->Checked == true && checkBox2->Checked == true && checkBox3->Checked == true)
		{
			// запрос к таблице MMA и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MMA, Devices where serial_number = " + sernumber + " AND MMA.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MMA
				series1->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();

			// запрос к таблице MIG/MAG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from MIGMAG, Devices where serial_number = " + sernumber + " AND MIGMAG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции MIG/MAG
				series2->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();

			// запрос к таблице TIG и приборам для вывода в график-жирафик
			sql_select = "select amper_izm, volt_izm from TIG, Devices where serial_number = " + sernumber + " AND TIG.id_device = Devices.id_device;";
			cmdSelect->CommandText = sql_select;
			dr = cmdSelect->ExecuteReader();
			while (dr->Read())
			{
				// Строим график функции TIG
				series3->Points->AddXY(Convert::ToDouble(dr[0]), Convert::ToDouble(dr[1]));
			}
			dr->Close();
		}
		db->Close();
	}
	else
	{
		dataGridView1->DataSource = nullptr;
		dataGridView2->DataSource = nullptr;
		dataGridView3->DataSource = nullptr;
		chart1->Series->Clear();
		chart2->Series->Clear();
		chart3->Series->Clear();
	}
	return System::Void();
}

//------------------------------------------------------------------------
// Чтобы часики тикали и показывало время в форме
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	label2->Text = DateTime::Now.ToString("HH:mm");
	return System::Void();
}

//------------------------------------------------------------------------
// Во время запуска программы и загрузке формы включается таймер
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	timer1->Start();
	return System::Void();
}

//------------------------------------------------------------------------
// кнопка Увеличить под графиком MMA
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button6_Click(System::Object^ sender, System::EventArgs^ e)
{
	Grafiki^ f4 = gcnew Grafiki(this);
	f4->graphicName("MMA");
	f4->Show();
	return System::Void();
}

//------------------------------------------------------------------------
// кнопка Увеличить под графиком MIG/MAG
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button7_Click(System::Object^ sender, System::EventArgs^ e)
{
	Grafiki^ f4 = gcnew Grafiki(this);
	f4->graphicName("MIG/MAG");
	f4->Show();
	return System::Void();
}

//------------------------------------------------------------------------
// кнопка Увеличить под графиком TIG
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::button8_Click(System::Object^ sender, System::EventArgs^ e)
{
	Grafiki^ f4 = gcnew Grafiki(this);
	f4->graphicName("TIG");
	f4->Show();
	return System::Void();
}

//------------------------------------------------------------------------
// Чек-бокс для MMA
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBox1->Checked) 
	{
		flag_mma = true;
	}
	else
	{
		flag_mma = false;
	}
	return System::Void();
}

//------------------------------------------------------------------------
// Чек-бокс для MIG/MAG
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBox1->Checked)
	{
		flag_mig = true;
	}
	else
	{
		flag_mig = false;
	}
	return System::Void();
}

//------------------------------------------------------------------------
// Чек-бокс для TIG
//------------------------------------------------------------------------
System::Void WorkWithSqlite::MyForm::checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBox1->Checked)
	{
		flag_tig = true;
	}
	else
	{
		flag_tig = false;
	}
	return System::Void();
}
