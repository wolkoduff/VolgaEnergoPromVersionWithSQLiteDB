#include "Tests.h"
#include "MyForm.h"
#include "Include/Lusbapi.h"
#include "Include/LusbapiTypes.h"

#define CHANNELS_QUANTITY (0x3)

using namespace System::IO;
using namespace System::Data::SQLite;

namespace WorkWithSqlite
{
	// ����� ������ ��� �� ��������� :)
	int count;
	double toker, volteraj, tok, napruga, peresvet, zasvet;

	// ������ ����������
	DWORD DllVersion;

	// ��������� �� ��������� ������
	ILE140* pModule;

	// ���������� ����������
	HANDLE ModuleHandle;

	// ����������� ��������� ���-�� ������������ 
	// ����������� ������ (��� ������ ������)
	const WORD MaxVirtualSoltsQuantity = 127;

	// ��������� �������� �����
	WORD TtlIn;
	WORD TtlINEr = 0xFFFE;
	WORD TtlOut = 0x200;
	// ��������� �������� ��� ������ ���������
	WORD i, result;
	// ����� �������� � ������ ������ ������ � ����������
	// ������� �������� ��������� MMA
	int mma = 0;
	// ������� �������� ��������� MIG/MAG
	int migmag = 0;
	// ������� �������� ��������� TIG
	int tig = 0;
	// ������� ��������� �������� �������
	void Commutator();

	// �������� ������ ���� USB
	BYTE UsbSpeed;

	// ��������� � ������ ����������� � ������
	MODULE_DESCRIPTION_E140 ModuleDescription;

	// ��������� ���������� ������ ��� ������
	ADC_PARS_E140 ap;

	// ���������������� ������������
	double A, B;

	// ������ �������� ��������� ����������
	const WORD InputRangeIndex = ADC_INPUT_RANGE_10000mV_E140;

	// ������� ���
	SHORT AdcSample1, AdcSample2, AdcSample3;

	// ������ ������� ������ ������ ������ ��������� ���������, �.�. �� 0 �� 63
	BOOL pusk = FALSE;
	// ������ ������� ������ MMA
	BOOL mma_flag = FALSE;
	// ������ ������� ������ MIG/MAG
	BOOL migmag_flag = FALSE;
	// ������ ������� ������ TIG
	BOOL tig_flag = FALSE;
	// ������ ��������
	BOOL full = FALSE;
	// ������ ������������ ������
	int fucker = 0;
	// ������ ������ ��� �������
	BOOL avtomat = FALSE;
	// ������ ����������� ������� � �����
	BOOL flagstat = FALSE;
	// �������� ���������� ���������
	BOOL flagcomplete = FALSE;

	//------------------------------------------------------------------------
	// ����� ����������� ������ ������ � ����
	//------------------------------------------------------------------------
	System::Void Tests::backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
	{
		String^ filer;
		if (mma_flag == TRUE && migmag_flag == FALSE && tig_flag == FALSE)
		{
			filer = "\\mma\\mma"+ mma +".csv";
		}
		else if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
		{
			filer = "\\migmag\\migmag" + migmag + ".csv";
		}
		else if (mma_flag == FALSE && migmag_flag == FALSE && tig_flag == TRUE)
		{
			filer = "\\tig\\tig" + tig + ".csv";
		}
		FileStream^ fs = gcnew FileStream(parentForm->path + filer, FileMode::CreateNew);
		fs->Close();
		StreamWriter^ sw = gcnew StreamWriter(parentForm->path + filer, FALSE, Encoding::Default);
		sw->Flush();
		parentForm->db = gcnew SQLiteConnection();
		parentForm->db->ConnectionString = "Data Source = test.db";
		parentForm->db->Open();
		SQLiteCommand^ cmdInsertValue = parentForm->db->CreateCommand();
		SQLiteCommand^ cmdSelect = parentForm->db->CreateCommand();
		SQLiteDataReader^ dr;
		if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
		{
			while (TRUE)
			{
				//pModule->ADC_SAMPLE(&AdcSample3, (WORD)(0x22));
				//double jdun = (A + (int)AdcSample3) * B;
				double jdun = 300;
				if (jdun >= 200)
				{
					break;
				}
			}
		}
		else if (mma_flag == FALSE && migmag_flag == FALSE && tig_flag == TRUE) {
			if (full == true) {
				// pModule->TTL_OUT(0x27f);
				Sleep(500);
				i++;
				// pModule->TTL_OUT(i);
			}
		}
		if (textBox2->Text == "") {
			MessageBox::Show("������� ���������/�������� ����� �������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Information);
			e->Cancel = TRUE;
		}
		else
		{
			cmdSelect->CommandText = "Select id_device from Devices where serial_number = " + Convert::ToInt32(textBox2->Text) + ";";
			dr = cmdSelect->ExecuteReader();
			int id_device = 0;
			while (dr->Read())
			{
				id_device = Convert::ToInt32(dr[0]);
			}
			dr->Close();
			String^ sqlInsert = "";
			for (i; i <= result; i++)
			{
				if (TtlIn != TtlINEr)
				{
					// pModule->TTL_IN(&TtlIn);
					// ��������� ������ �� ����
					if (TtlIn == TtlINEr) {
						fucker = 1;
						// pModule->TTL_OUT(0x0);
						sw->WriteLine("*��������� ������ �� ����*");
						e->Cancel = FALSE;
						backgroundWorker1->CancelAsync();
					}
					// ���������, ���� �� ������ ������ ���������� ���������� ���������
					if (backgroundWorker1->CancellationPending)
					{
						// pModule->TTL_OUT(0x0);
						sw->Close();
						e->Cancel = TRUE;
						break;
					}
					else
					{
						// pModule->ADC_SAMPLE(&AdcSample1, (WORD)(0x20));
						// pModule->ADC_SAMPLE(&AdcSample2, (WORD)(0x21));
						// toker = (AdcSample1 + A) * B;
						// volteraj = (AdcSample2 + A) * B;
						// napruga = volteraj / 40;
						// tok = toker / 8;
						tok = 200;
						napruga = 300;
						if (mma_flag == TRUE && migmag_flag == FALSE && tig_flag == FALSE)
						{
							if (full == TRUE)
							{
								sw->WriteLine((i - 0x200) + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "INSERT INTO MMA(num_cycle, step_cycle, amper_izm, volt_izm, forsaj, date_izm, time_izm, defence, id_device) VALUES (" + mma + "," + (i - 0x200) + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
							else
							{
								sw->WriteLine(i + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "INSERT INTO MMA(num_cycle, step_cycle, amper_izm, volt_izm, forsaj, date_izm, time_izm, defence, id_device) VALUES (" + mma + "," + i + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
						}
						else if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
						{
							if (full == FALSE && avtomat == FALSE)
							{
								sw->WriteLine(i + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "insert into migmag(num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence, id_device) values (" + migmag + "," + i + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
							else if (full == TRUE && avtomat == FALSE)
							{
								sw->WriteLine((i - 0x200) + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "insert into migmag(num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence, id_device) values (" + migmag + "," + (i - 0x200) + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
							else if (full == FALSE && avtomat == TRUE)
							{
								sw->WriteLine((i - 0x40) + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "insert into migmag(num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence, id_device) values (" + migmag + "," + (i - 0x40) + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
							else if (full == TRUE && avtomat == TRUE)
							{
								sw->WriteLine((i - 0x240) + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "insert into migmag(num_cycle, step_cycle, amper_izm, volt_izm, num_prog, date_izm, time_izm, defence, id_device) values (" + migmag + "," + (i - 0x240) + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
						}
						else if (mma_flag == FALSE && migmag_flag == FALSE && tig_flag == TRUE)
						{
							if (full == TRUE)
							{
								sw->WriteLine(tig + ";" + (i - 0x240) + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "insert into tig(num_cycle, step_cycle, amper_izm, volt_izm, amp_set, volt_set, date_izm, time_izm, defence, id_device) values (" + tig + "," + (i - 0x240) + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + "," + (Convert::ToUInt32(textBox1->Text) * 0.04 + 15) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
							else
							{
								sw->WriteLine(tig + ";" + (i - 0x40) + ";" + Math::Round(tok, 1, MidpointRounding::AwayFromZero).ToString() + ";" + Math::Round(napruga, 1, MidpointRounding::AwayFromZero).ToString());
								sqlInsert = "insert into tig(num_cycle, step_cycle, amper_izm, volt_izm, amp_set, volt_set, date_izm, time_izm, defence, id_device) values (" + tig + "," + i + "," + tok + "," + napruga + "," + Convert::ToInt32(textBox1->Text) + "," + (Convert::ToUInt32(textBox1->Text) * 0.04 + 15) + ",'" + DateTime::Now.ToString("yyyy-MM-dd") + "','" + DateTime::Now.ToString("HH:mm") + "'," + fucker + "," + id_device + ");";
							}
						}
						cmdInsertValue->CommandText = sqlInsert;
						cmdInsertValue->ExecuteNonQuery();
						backgroundWorker1->ReportProgress(i);
						System::Threading::Thread::Sleep(300);
					}
				}
				if (backgroundWorker1->CancellationPending)
				{
					// pModule->TTL_OUT(0x0);
					sw->Close();
					parentForm->db->Close();
					e->Cancel = TRUE;
					break;
				}
			}
			if (progressBar1->Value == progressBar1->Maximum)
			{
				parentForm->db->Close();
				sw->Close();
				flagcomplete = TRUE;
				System::Threading::Thread::Sleep(300);
			}
			if (flagcomplete == TRUE)
			{
				for (i = result; i >= result - 63; i--)
				{
					if (backgroundWorker1->CancellationPending)
					{
						e->Cancel = TRUE;
						break;
					}
					else if (progressBar1->Value == progressBar1->Minimum)
					{
						break;
					}
					else
					{
						backgroundWorker1->ReportProgress(i);
						System::Threading::Thread::Sleep(100);
					}
				}
			}
			else
			{
				parentForm->db->Close();
				backgroundWorker1->CancelAsync();
			}
		}
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ��������� ���������� ��������
	//------------------------------------------------------------------------
	System::Void Tests::backgroundWorker1_ProgressChanged(System::Object^ sender, System::ComponentModel::ProgressChangedEventArgs^ e)
	{
		// pModule->TTL_OUT(e->ProgressPercentage + i);
		progressBar1->Value = e->ProgressPercentage;
		label4->Text = Math::Round(napruga, MidpointRounding::AwayFromZero).ToString();
		label5->Text = Math::Round(tok, MidpointRounding::AwayFromZero).ToString();
		if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
		{
			if (avtomat == TRUE) {
				label6->Visible = FALSE;
				pictureBox2->Visible = FALSE;
			}
			else
			{
				label6->Visible = TRUE;
				pictureBox2->Visible = TRUE;
				label6->Text = Convert::ToString("����������� ������ �������\n������� �� ��������� ���������");
			}
		}
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ���������� ������� ����������� ������. �� ��� ���� ����� � ������� ���� �� 
	// ������ ���#� ��������� � �������
	//------------------------------------------------------------------------
	System::Void Tests::backgroundWorker1_RunWorkerComplete(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
	{
		MessageBox::Show("����� �������", "�������");
		if (fucker == 1 || flagcomplete == FALSE) // ��������� ������ ��� �������� ���������?
		{
			if (e->Cancelled == FALSE && fucker == 1) // ���� ��������� ������
			{
				MessageBox::Show("��������� ������ �� ����. ��� ����� 550 �����!", "������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				flagcomplete = FALSE;
				button1->Enabled = TRUE;
				button2->Enabled = TRUE;
				button3->Enabled = TRUE;
				button4->Enabled = TRUE;
				button5->Enabled = TRUE;
				button6->Enabled = FALSE;
				checkBox2->Enabled = TRUE;
				textBox1->Enabled = TRUE;
				textBox2->Enabled = TRUE;
				if (checkBox2->Checked)
				{
					i = 0x200;
					result = 0x23f;
				}
				else
				{
					i = 0x0;
					result = 0x3f;
				}
				if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
				{
					checkBox1->Enabled = TRUE;
				}
				pictureBox2->Visible = FALSE;
				progressBar1->Minimum = i;
				progressBar1->Value = progressBar1->Minimum;
				progressBar1->Maximum = result;
			}
			else // ���� ������ ������ ���������
			{
				MessageBox::Show("������ ��������� ������� ����", "�������");
				flagcomplete = FALSE;
				button1->Enabled = TRUE;
				button2->Enabled = TRUE;
				button3->Enabled = TRUE;
				button4->Enabled = TRUE;
				button5->Enabled = TRUE;
				button6->Enabled = FALSE;
				textBox1->Enabled = TRUE;
				textBox2->Enabled = TRUE;
				if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
				{
					checkBox1->Enabled = TRUE;
				}
				checkBox2->Enabled = TRUE;
				if (checkBox2->Checked) // ���� ���������� ������ ��������
				{
					i = 0x200;
					result = 0x23f;
				}
				else // �������� ��������
				{
					i = 0x0;
					result = 0x3f;
				}
				pictureBox2->Visible = FALSE;
				progressBar1->Minimum = i;
				progressBar1->Value = progressBar1->Minimum;
				progressBar1->Maximum = result;
			}
			if (e->Error != nullptr) // ���� ������ �����������, ��� ��������� �����-�� ������, ������ ����� ����������
			{
				MessageBox::Show("������: " + e->Error->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
				flagcomplete = FALSE;
				button1->Enabled = TRUE;
				button2->Enabled = TRUE;
				button3->Enabled = TRUE;
				button4->Enabled = TRUE;
				button5->Enabled = TRUE;
				textBox1->Enabled = TRUE;
				textBox2->Enabled = TRUE;
				button6->Enabled = FALSE;
				checkBox2->Enabled = TRUE;
				pictureBox2->Visible = FALSE;
				if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE) 
				{
					checkBox1->Enabled = TRUE;
				}
			}
		}
		else if (flagcomplete == TRUE)		// ����� ���� ������ ������� ��� ����� ���������, �� ���� �������� �� ����� � ����� � ���������
		{
			if (checkBox2->Checked)			// ���� ���������� ������ ��������
			{
				i = 0x200;
				result = 0x23f;
			}
			else							// �������� ��������
			{
				i = 0x0;
				result = 0x3f;
			}
			progressBar1->Minimum = i;
			progressBar1->Value = progressBar1->Minimum;
			progressBar1->Maximum = result;
			flagcomplete = FALSE;
			button1->Enabled = TRUE;
			button2->Enabled = TRUE;
			button3->Enabled = TRUE;
			button4->Enabled = TRUE;
			button5->Enabled = TRUE;
			textBox1->Enabled = TRUE;
			textBox2->Enabled = TRUE;
			button6->Enabled = FALSE;
			checkBox2->Enabled = TRUE;
			pictureBox2->Visible = FALSE;
			if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
			{
				checkBox1->Enabled = TRUE;
			}
		}
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ������ ����������� ��������� ���
	//------------------------------------------------------------------------
	System::Void Tests::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		button1->Visible = TRUE;
		button2->Visible = TRUE;
		button3->Visible = TRUE;
		button4->Visible = TRUE;
		button5->Visible = TRUE;
		button6->Visible = TRUE;
		button6->Enabled = FALSE;
		checkBox1->Visible = FALSE;
		checkBox2->Visible = TRUE;
		checkBox2->Checked = FALSE;
		textBox1->Visible = TRUE;
		textBox2->Visible = TRUE;
		progressBar1->Visible = TRUE;
		label1->Visible = TRUE;
		label2->Visible = TRUE;
		label3->Visible = TRUE;
		label4->Visible = TRUE;
		label5->Visible = TRUE;
		label6->Visible = FALSE;
		label7->Visible = TRUE;
		pictureBox2->Visible = FALSE;
		label1->Text = "������";
		mma_flag = TRUE;
		migmag_flag = FALSE;
		tig_flag = FALSE;
		avtomat = FALSE;
		full = FALSE;
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ������ ����������� ��������� �IG/MAG
	//------------------------------------------------------------------------
	System::Void Tests::button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		button1->Visible = TRUE;
		button2->Visible = TRUE;
		button3->Visible = TRUE;
		button4->Visible = TRUE;
		button5->Visible = TRUE;
		button6->Visible = TRUE;
		button6->Enabled = FALSE;
		checkBox1->Visible = TRUE;
		checkBox2->Visible = TRUE;
		checkBox1->Checked = FALSE;
		checkBox2->Checked = FALSE;
		pictureBox2->Visible = FALSE;
		progressBar1->Visible = TRUE;
		textBox1->Visible = TRUE;
		textBox2->Visible = TRUE;
		label1->Visible = TRUE;
		label2->Visible = TRUE;
		label3->Visible = TRUE;
		label4->Visible = TRUE;
		label5->Visible = TRUE;
		label6->Visible = FALSE;
		label7->Visible = TRUE;
		label1->Text = "� ���������";
		mma_flag = FALSE;
		migmag_flag = TRUE;
		tig_flag = FALSE;
		avtomat = FALSE;
		full = FALSE;
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ������ ����������� ��������� TIG
	//------------------------------------------------------------------------
	System::Void Tests::button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		button1->Visible = TRUE;
		button2->Visible = TRUE;
		button3->Visible = TRUE;
		button4->Visible = TRUE;
		button5->Visible = TRUE;
		button6->Visible = TRUE;
		button6->Enabled = FALSE;
		checkBox1->Visible = FALSE;
		checkBox2->Visible = TRUE;
		checkBox2->Checked = FALSE;
		pictureBox2->Visible = FALSE;
		textBox1->Visible = TRUE;
		textBox2->Visible = TRUE;
		progressBar1->Visible = TRUE;
		label1->Visible = TRUE;
		label2->Visible = TRUE;
		label3->Visible = TRUE;
		label4->Visible = TRUE;
		label5->Visible = TRUE;
		label6->Visible = FALSE;
		label7->Visible = TRUE;
		label1->Text = "�������� ����";
		mma_flag = FALSE;
		migmag_flag = FALSE;
		tig_flag = TRUE;
		avtomat = TRUE;
		full = FALSE;
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ������ ���������� ������ � ������
	//------------------------------------------------------------------------
	System::Void Tests::button4_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (flagstat == TRUE)
		{
			backgroundWorker1->CancelAsync();
			// pModule->TTL_OUT(0x0);
			// pModule->ReleaseLInstance();
			// ������� ��������� �� ��������� ������
			// pModule = NULL;
		}
		Close();
		parentForm->Show();
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ������ ������� ���������
	//------------------------------------------------------------------------
	System::Void Tests::button5_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// ��������� ��� �������� ���������� ����� ������ ����������
		button1->Enabled = FALSE;
		button2->Enabled = FALSE;
		button3->Enabled = FALSE;
		button4->Enabled = FALSE;
		button5->Enabled = FALSE;
		button6->Enabled = TRUE;
		textBox1->Enabled = FALSE;
		textBox2->Enabled = FALSE;
		Commutator(); // ������������� ������
		flagcomplete = FALSE; // ���������� ������ ��������� ������� ���������
		MessageBox::Show("�������� i: " + i + "\n�������� result: " + result);
		if (mma_flag == TRUE && migmag_flag == FALSE && tig_flag == FALSE)
		{
			mma++;
		}
		else if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
		{
			migmag++;
			checkBox1->Enabled = FALSE;
		}
		else if (mma_flag == FALSE && migmag_flag == FALSE && tig_flag == TRUE) 
		{
			if (MessageBox::Show("������� �������� �� ���������! �� ����� ��������?", "��������������", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No) {
				return System::Void();
			}
			else
			{
				tig++;
			}
		}
		checkBox2->Enabled = FALSE;
		// pModule->TTL_IN(&TtlIn);
		if (TtlIn != TtlINEr) // ���� ������ ��� �� ���������
		{
			while (TRUE)
			{
				// ������ ����������������. �� ���� ������ ��������� � ����
				if (backgroundWorker1->IsBusy != TRUE)
				{
					backgroundWorker1->RunWorkerAsync();
					fucker = 0; // ������������ ������
					break;
				}
			}
		}
		else // ���� ���������
		{
			button1->Enabled = TRUE;
			button2->Enabled = TRUE;
			button3->Enabled = TRUE;
			button4->Enabled = TRUE;
			button5->Enabled = TRUE;
			button6->Enabled = FALSE;
			textBox1->Enabled = TRUE;
			textBox2->Enabled = TRUE;
			checkBox2->Enabled = TRUE;
			if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
			{
				checkBox1->Enabled = TRUE;
			}
			MessageBox::Show("��������� ������ �� ����", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ������ ��������� ��������
	//------------------------------------------------------------------------
	System::Void Tests::button6_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// ������ ����������� ��������
		if (backgroundWorker1->WorkerSupportsCancellation == TRUE)
		{
			backgroundWorker1->CancelAsync();
		}
		button1->Enabled = TRUE;
		button2->Enabled = TRUE;
		button3->Enabled = TRUE;
		button4->Enabled = TRUE;
		button5->Enabled = TRUE;
		button6->Enabled = FALSE;
		textBox1->Enabled = TRUE;
		textBox2->Enabled = TRUE;
		checkBox2->Enabled = TRUE;
		if (mma_flag == FALSE && migmag_flag == TRUE && tig_flag == FALSE)
		{
			checkBox1->Enabled = TRUE;
		}
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ���������� � ����� ������
	//------------------------------------------------------------------------
	System::Void Tests::Tests_Load(System::Object^ sender, System::EventArgs^ e)
	{
		button1->Visible = TRUE;
		button2->Visible = TRUE;
		button3->Visible = TRUE;
		button4->Visible = TRUE;
		button5->Visible = FALSE;
		button6->Visible = FALSE;
		checkBox1->Visible = FALSE;
		checkBox2->Visible = FALSE;
		pictureBox2->Visible = FALSE;
		textBox1->Visible = FALSE;
		textBox2->Visible = FALSE;
		progressBar1->Visible = FALSE;
		label1->Visible = FALSE;
		label2->Visible = FALSE;
		label3->Visible = FALSE;
		label4->Visible = FALSE;
		label5->Visible = FALSE;
		label6->Visible = FALSE;
		label7->Visible = FALSE;
		mma_flag = FALSE;
		migmag_flag = FALSE;
		tig_flag = FALSE;
		return System::Void();
	}
	
	//------------------------------------------------------------------------
	// ������ ��� �������������� ����� ����� ������. �.�. ���� ������� ������ ��� ��� ���.
	//------------------------------------------------------------------------
	System::Void Tests::checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (checkBox1->Checked)
		{
			checkBox1->Text = "�������������� ����� ������";
			avtomat = TRUE;
			Commutator();
			label1->Text = "� ���������";
			progressBar1->Minimum = i;
			progressBar1->Value = progressBar1->Minimum;
			progressBar1->Maximum = result;
		}
		else
		{
			checkBox1->Text = "������ ����� ������";
			avtomat = FALSE;
			Commutator();
			label1->Text = "� ���������";
			progressBar1->Minimum = i;
			progressBar1->Value = progressBar1->Minimum;
			progressBar1->Maximum = result;
		}
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ������ ����� �������� ��� ������ �������� ��������
	//------------------------------------------------------------------------
	System::Void Tests::checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (checkBox2->Checked)
		{
			full = TRUE;
			checkBox2->Text = "������ ��������";
			Commutator();
			progressBar1->Minimum = i;
			progressBar1->Value = progressBar1->Minimum;
			progressBar1->Maximum = result;
		}
		else
		{
			full = FALSE;
			checkBox2->Text = "�������� ��������";
			Commutator();
			progressBar1->Minimum = i;
			progressBar1->Value = progressBar1->Minimum;
			progressBar1->Maximum = result;
		}
		return System::Void();
	}

	//------------------------------------------------------------------------
	// ���������� ���� ���-������, ������ ���� ������
	//------------------------------------------------------------------------
	void Commutator() {
		if (full == FALSE && avtomat == FALSE)
		{
			i = 0x0;
			result = 0x3f;
		}
		else if (full == TRUE && avtomat == FALSE)
		{
			i = 0x200;
			result = 0x23f;
		}
		else if (full == FALSE && avtomat == TRUE)
		{
			i = 0x40;
			result = 0x7f;
		}
		else if (full == TRUE && avtomat == TRUE)
		{
			i = 0x240;
			result = 0x27f;
		}
	}
}