#pragma once
#include <msclr/marshal_cppstd.h>
#include "AVL_tree.h"

namespace ADLab31 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			dataBase = new AVL_tree("DB.bin");
		}
	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Windows::Forms::Button^ doButton;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::TextBox^ idBox;
		System::Windows::Forms::TextBox^ nameBox;
		System::Windows::Forms::TextBox^ surnameBox;
		System::Windows::Forms::Panel^ panel1;
		System::Windows::Forms::RadioButton^ insertButton;
		System::Windows::Forms::RadioButton^ deleteButton;
		System::Windows::Forms::RadioButton^ selectButton;
		System::Windows::Forms::RadioButton^ updateButton;
		AVL_tree* dataBase;
		System::Windows::Forms::RadioButton^ generateButton;
		System::Windows::Forms::TextBox^ genAmountBox;
		System::Windows::Forms::Label^ label4;
		System::Windows::Forms::Button^ dropButton;
		System::ComponentModel::BackgroundWorker^ backgroundWorker1;
		System::Windows::Forms::DataGridView^ dataGridView1;
		System::Windows::Forms::DataGridViewTextBoxColumn^ idColumn;
		System::Windows::Forms::DataGridViewTextBoxColumn^ surnameColumn;
		System::Windows::Forms::DataGridViewTextBoxColumn^ nameColumn;
		   /// <summary>
		   /// ќб€зательна€ переменна€ конструктора.
		   /// </summary>
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		   /// содержимое этого метода с помощью редактора кода.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->doButton = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->idBox = (gcnew System::Windows::Forms::TextBox());
			   this->nameBox = (gcnew System::Windows::Forms::TextBox());
			   this->surnameBox = (gcnew System::Windows::Forms::TextBox());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->generateButton = (gcnew System::Windows::Forms::RadioButton());
			   this->insertButton = (gcnew System::Windows::Forms::RadioButton());
			   this->deleteButton = (gcnew System::Windows::Forms::RadioButton());
			   this->selectButton = (gcnew System::Windows::Forms::RadioButton());
			   this->updateButton = (gcnew System::Windows::Forms::RadioButton());
			   this->genAmountBox = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->dropButton = (gcnew System::Windows::Forms::Button());
			   this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->idColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->surnameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->nameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->panel1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // doButton
			   // 
			   this->doButton->Location = System::Drawing::Point(403, 345);
			   this->doButton->Name = L"doButton";
			   this->doButton->Size = System::Drawing::Size(200, 51);
			   this->doButton->TabIndex = 4;
			   this->doButton->Text = L"DO";
			   this->doButton->UseVisualStyleBackColor = true;
			   this->doButton->Click += gcnew System::EventHandler(this, &MyForm::doButton_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(324, 25);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(21, 17);
			   this->label1->TabIndex = 8;
			   this->label1->Text = L"ID";
			   this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(300, 62);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(45, 17);
			   this->label2->TabIndex = 9;
			   this->label2->Text = L"Name";
			   this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(280, 99);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(65, 17);
			   this->label3->TabIndex = 10;
			   this->label3->Text = L"Surname";
			   // 
			   // idBox
			   // 
			   this->idBox->Location = System::Drawing::Point(351, 22);
			   this->idBox->Name = L"idBox";
			   this->idBox->Size = System::Drawing::Size(308, 22);
			   this->idBox->TabIndex = 11;
			   // 
			   // nameBox
			   // 
			   this->nameBox->Location = System::Drawing::Point(351, 59);
			   this->nameBox->Name = L"nameBox";
			   this->nameBox->ReadOnly = true;
			   this->nameBox->Size = System::Drawing::Size(308, 22);
			   this->nameBox->TabIndex = 12;
			   this->nameBox->Text = L" ";
			   // 
			   // surnameBox
			   // 
			   this->surnameBox->Location = System::Drawing::Point(351, 99);
			   this->surnameBox->Name = L"surnameBox";
			   this->surnameBox->ReadOnly = true;
			   this->surnameBox->Size = System::Drawing::Size(308, 22);
			   this->surnameBox->TabIndex = 13;
			   this->surnameBox->Text = L" ";
			   // 
			   // panel1
			   // 
			   this->panel1->Controls->Add(this->generateButton);
			   this->panel1->Controls->Add(this->insertButton);
			   this->panel1->Controls->Add(this->deleteButton);
			   this->panel1->Controls->Add(this->selectButton);
			   this->panel1->Controls->Add(this->updateButton);
			   this->panel1->Location = System::Drawing::Point(13, 12);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(118, 216);
			   this->panel1->TabIndex = 19;
			   // 
			   // generateButton
			   // 
			   this->generateButton->AutoSize = true;
			   this->generateButton->Location = System::Drawing::Point(7, 156);
			   this->generateButton->Name = L"generateButton";
			   this->generateButton->Size = System::Drawing::Size(105, 38);
			   this->generateButton->TabIndex = 4;
			   this->generateButton->TabStop = true;
			   this->generateButton->Text = L"GENERATE\r\nTEST DB";
			   this->generateButton->UseVisualStyleBackColor = true;
			   this->generateButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::generateButton_CheckedChanged);
			   // 
			   // insertButton
			   // 
			   this->insertButton->AutoSize = true;
			   this->insertButton->Location = System::Drawing::Point(7, 119);
			   this->insertButton->Name = L"insertButton";
			   this->insertButton->Size = System::Drawing::Size(79, 21);
			   this->insertButton->TabIndex = 3;
			   this->insertButton->TabStop = true;
			   this->insertButton->Text = L"INSERT";
			   this->insertButton->UseVisualStyleBackColor = true;
			   // 
			   // deleteButton
			   // 
			   this->deleteButton->AutoSize = true;
			   this->deleteButton->Location = System::Drawing::Point(7, 83);
			   this->deleteButton->Name = L"deleteButton";
			   this->deleteButton->Size = System::Drawing::Size(83, 21);
			   this->deleteButton->TabIndex = 2;
			   this->deleteButton->TabStop = true;
			   this->deleteButton->Text = L"DELETE";
			   this->deleteButton->UseVisualStyleBackColor = true;
			   this->deleteButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::deleteButton_CheckedChanged);
			   // 
			   // selectButton
			   // 
			   this->selectButton->AutoSize = true;
			   this->selectButton->Checked = true;
			   this->selectButton->Location = System::Drawing::Point(7, 13);
			   this->selectButton->Name = L"selectButton";
			   this->selectButton->Size = System::Drawing::Size(82, 21);
			   this->selectButton->TabIndex = 1;
			   this->selectButton->TabStop = true;
			   this->selectButton->Text = L"SELECT";
			   this->selectButton->UseVisualStyleBackColor = true;
			   this->selectButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::selectButton_CheckedChanged);
			   // 
			   // updateButton
			   // 
			   this->updateButton->AutoSize = true;
			   this->updateButton->Location = System::Drawing::Point(7, 48);
			   this->updateButton->Name = L"updateButton";
			   this->updateButton->Size = System::Drawing::Size(85, 21);
			   this->updateButton->TabIndex = 0;
			   this->updateButton->TabStop = true;
			   this->updateButton->Text = L"UPDATE";
			   this->updateButton->UseVisualStyleBackColor = true;
			   // 
			   // genAmountBox
			   // 
			   this->genAmountBox->Location = System::Drawing::Point(25, 268);
			   this->genAmountBox->Name = L"genAmountBox";
			   this->genAmountBox->Size = System::Drawing::Size(100, 22);
			   this->genAmountBox->TabIndex = 20;
			   this->genAmountBox->Text = L"0";
			   this->genAmountBox->Visible = false;
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(22, 248);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(105, 17);
			   this->label4->TabIndex = 21;
			   this->label4->Text = L"Amount of rows";
			   this->label4->Visible = false;
			   // 
			   // dropButton
			   // 
			   this->dropButton->Location = System::Drawing::Point(20, 323);
			   this->dropButton->Name = L"dropButton";
			   this->dropButton->Size = System::Drawing::Size(115, 38);
			   this->dropButton->TabIndex = 22;
			   this->dropButton->Text = L"Drop DB";
			   this->dropButton->UseVisualStyleBackColor = true;
			   this->dropButton->Click += gcnew System::EventHandler(this, &MyForm::dropButton_Click);
			   // 
			   // dataGridView1
			   // 
			   this->dataGridView1->AllowUserToAddRows = false;
			   this->dataGridView1->AllowUserToDeleteRows = false;
			   this->dataGridView1->AllowUserToResizeColumns = false;
			   this->dataGridView1->AllowUserToResizeRows = false;
			   this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Info;
			   this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				   this->idColumn,
					   this->surnameColumn, this->nameColumn
			   });
			   this->dataGridView1->Location = System::Drawing::Point(176, 141);
			   this->dataGridView1->Name = L"dataGridView1";
			   this->dataGridView1->ReadOnly = true;
			   this->dataGridView1->RowHeadersVisible = false;
			   this->dataGridView1->RowHeadersWidth = 51;
			   this->dataGridView1->RowTemplate->Height = 24;
			   this->dataGridView1->Size = System::Drawing::Size(690, 185);
			   this->dataGridView1->TabIndex = 23;
			   // 
			   // idColumn
			   // 
			   this->idColumn->HeaderText = L"ID";
			   this->idColumn->MinimumWidth = 127;
			   this->idColumn->Name = L"idColumn";
			   this->idColumn->ReadOnly = true;
			   this->idColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   this->idColumn->Width = 127;
			   // 
			   // surnameColumn
			   // 
			   this->surnameColumn->HeaderText = L"Surname";
			   this->surnameColumn->MinimumWidth = 280;
			   this->surnameColumn->Name = L"surnameColumn";
			   this->surnameColumn->ReadOnly = true;
			   this->surnameColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   this->surnameColumn->Width = 280;
			   // 
			   // nameColumn
			   // 
			   this->nameColumn->HeaderText = L"Name";
			   this->nameColumn->MinimumWidth = 280;
			   this->nameColumn->Name = L"nameColumn";
			   this->nameColumn->ReadOnly = true;
			   this->nameColumn->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   this->nameColumn->Width = 280;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoScroll = true;
			   this->ClientSize = System::Drawing::Size(918, 417);
			   this->Controls->Add(this->dataGridView1);
			   this->Controls->Add(this->dropButton);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->genAmountBox);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->surnameBox);
			   this->Controls->Add(this->nameBox);
			   this->Controls->Add(this->idBox);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->doButton);
			   this->MaximumSize = System::Drawing::Size(936, 464);
			   this->Name = L"MyForm";
			   this->Text = L"Control panel";
			   this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm::MyForm_FormClosed);
			   this->panel1->ResumeLayout(false);
			   this->panel1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion
	private:
		System::Void doButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			dataGridView1->Rows->Clear();
			if (selectButton->Checked)
			{
				if (idBox->Text == "*")
				{
					if (dataBase->isNotEmpty())
					{
						std::vector<std::pair<int, Info>> result = dataBase->getAllNodes();
						for (auto row : result)
						{
							array <String^>^ temp =
							{
								Convert::ToString(row.first),
								gcnew String(row.second.surname.data()),
								gcnew String(row.second.name.data())
							};
							dataGridView1->Rows->Add(temp);
						}
					}
				}
				else if (inputCheck())
				{
					int compares = 0;
					Info selectInfo = dataBase->select(int::Parse(idBox->Text), compares);
					if (!(selectInfo == Info()))
					{
						array <String^>^ selectResult =
						{
							idBox->Text,
							gcnew String(selectInfo.surname.data()),
							gcnew String(selectInfo.name.data())
						};
						dataGridView1->Rows->Add(selectResult);
						MessageBox::Show("Found a row. Amount of compares: "
							+ Convert::ToString(compares), "Success");
					}
					else
					{
						MessageBox::Show("Didn`t find row with such primary key\r\nAmount of compares: "
							+ Convert::ToString(compares), "Error");
					}
				}
				else
				{
					MessageBox::Show("Incorrect input", "Error");
				}
			}
			else if (insertButton->Checked)
			{
				if (inputCheck())
				{
					bool result = dataBase->insert(int::Parse(idBox->Text),
						Info(msclr::interop::marshal_as<std::string>(nameBox->Text),
							msclr::interop::marshal_as<std::string>(surnameBox->Text)));
					if (result)
						MessageBox::Show("Inserted the row", "Done");
					else
						MessageBox::Show("Row with an equal primary key has been already created", "Error");
				}
				else
				{
					MessageBox::Show("Incorrect input", "Error");
				}
			}
			else if (updateButton->Checked)
			{
				if (inputCheck())
				{
					bool result = dataBase->update(int::Parse(idBox->Text),
						Info(msclr::interop::marshal_as<std::string>(nameBox->Text),
							msclr::interop::marshal_as<std::string>(surnameBox->Text)));
					if (result)
					{
						MessageBox::Show("Chosen row updated", "Success");
					}
					else
					{
						MessageBox::Show("Didn`t find row with such primary key. Didn`t update", "Error");
					}
				}
				else
				{
					MessageBox::Show("Incorrect input", "Error");
				}
			}
			else if (deleteButton->Checked)
			{
				if (inputCheck())
				{
					bool result = dataBase->erase(int::Parse(idBox->Text));
					if (result)
						MessageBox::Show("Deleted a row with ID " + idBox->Text, "Success");
					else
						MessageBox::Show("Didn`t find row with such primary key. Didn`t delete", "Error");
				}
				else
					MessageBox::Show("Incorrect input", "Error");
			}
			else if (generateButton->Checked)
			{
				if (dataBase->isNotEmpty())
					MessageBox::Show("There are already created rows. Delete them before generate test rows", "Error");
				else
				{
					std::string checkGenAmount = msclr::interop::marshal_as<std::string>(genAmountBox->Text);
					bool validate = !(checkGenAmount.find_first_not_of("0123456789") != std::string::npos ||
						stoi(checkGenAmount) == 0);
					if (validate)
					{
						int rowsAmount = int::Parse(genAmountBox->Text);
						for (int i = 0; i < rowsAmount; i++)
						{
							dataBase->insert(i, Info("Name" + std::to_string(i), "Surname" + std::to_string(i)));
						}
						MessageBox::Show("Created rows with test data (NameN, SurnameN)", "Done");
					}
					else
					{
						MessageBox::Show("Incorrect input", "Error");
					}
				}
			}
		}

		System::Void selectButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			changeAccessibility(selectButton);
		}

		System::Void deleteButton_CheckedChanged(Object^ sender, EventArgs^ e) {
			changeAccessibility(deleteButton);
		}

		System::Void generateButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			genAmountBox->Text = "0";
			genAmountBox->Visible = !genAmountBox->Visible;
			label4->Visible = !label4->Visible;
			changeAccessibility(generateButton);
		}

		System::Void changeAccessibility(RadioButton^ button)
		{
			if (button->Checked)
			{
				nameBox->Text = " ";
				nameBox->ReadOnly = true;
				surnameBox->Text = " ";
				surnameBox->ReadOnly = true;
				if (button->Name == "generateButton")
				{
					idBox->Text = "";
					idBox->ReadOnly = true;
				}
			}
			else
			{
				nameBox->ReadOnly = false;
				surnameBox->ReadOnly = false;
				nameBox->Text = "";
				surnameBox->Text = "";
				if (button->Name == "generateButton")
				{
					idBox->Text = "";
					idBox->ReadOnly = false;
				}
			}
		}

		System::Boolean inputCheck() {
			std::string checkId = msclr::interop::marshal_as<std::string>(idBox->Text);
			if (System::String::IsNullOrEmpty(idBox->Text) ||
				System::String::IsNullOrEmpty(nameBox->Text) ||
				System::String::IsNullOrEmpty(surnameBox->Text))
				return false;
			if (checkId.find_first_not_of("0123456789") != std::string::npos)
				return false;
			return true;
		}

		System::Void dropButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			dataGridView1->Rows->Clear();
			if (dataBase->isNotEmpty())
			{
				auto choice = MessageBox::Show("Are you sure?", "Drop DB", MessageBoxButtons::YesNo);
				if (choice == System::Windows::Forms::DialogResult::Yes)
				{
					dataBase->~AVL_tree();
					MessageBox::Show("Dropped database", "Done");
				}
			}
			else
			{
				MessageBox::Show("Database is empty", "Error");
			}
		}

		System::Void MyForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
		{
			dataBase->serialize("DB.bin");
			dataBase->~AVL_tree();
		}
	};
}
