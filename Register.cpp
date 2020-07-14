#include "Register.h"
#include "MyForm.h"

System::Void WorkWithSqlite::Register::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	parentForm->db = gcnew SQLiteConnection();
	parentForm->db->ConnectionString = "Data Source = test.db";
	parentForm->db->Open();
	SQLiteCommand^ cmdInsertValue = parentForm->db->CreateCommand();
	String^ sql_insert = "insert into Devices(name_dev, maker, vladelets, serial_number, invent_number) values('" + 
		Convert::ToString(textBox1->Text) + "', '" +
		Convert::ToString(textBox2->Text) + "', '" +
		Convert::ToString(textBox3->Text) + "','" +
		Convert::ToString(textBox4->Text) + "', '" +
		Convert::ToString(textBox5->Text) + "');";
	cmdInsertValue->CommandText = sql_insert;
	cmdInsertValue->ExecuteNonQuery();
	parentForm->db->Close();
	Close();
	return System::Void();
}
