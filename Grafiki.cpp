#include "Grafiki.h"
#include "MyForm.h"

using namespace WorkWithSqlite;
void GetName();

System::Void WorkWithSqlite::Grafiki::Grafiki_Load(System::Object^ sender, System::EventArgs^ e)
{
	parentForm->db = gcnew SQLiteConnection();
	parentForm->db->ConnectionString = "Data Source = test.db";
	parentForm->db->Open();
	SQLiteCommand^ cmdselector = parentForm->db->CreateCommand();
	SQLiteDataReader^ dr;
	"select amper_izm, volt_izm from " + 1 + ", Devices where serial_number = " + serial_number + " AND MMA.id_device = Devices.id_device;";

	chart1->ChartAreas[0]->AxisX->Title = "Ток";
	chart1->ChartAreas[0]->AxisY->Title = "Напряжение";
	return System::Void();
}

void GetName() {
	;
}