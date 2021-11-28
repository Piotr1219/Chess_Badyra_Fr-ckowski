#pragma once
#include "Source.h"
//#include "globals2.h"
#include <string>
#include <msclr\marshal_cppstd.h>


namespace chessBadyraFrackowskigui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ f0;
	private: System::Windows::Forms::PictureBox^ f61;





	private: System::Windows::Forms::PictureBox^ f34;

	private: System::Windows::Forms::PictureBox^ f20;
	private: System::Windows::Forms::PictureBox^ f36;


	private: System::Windows::Forms::PictureBox^ f4;
	private: System::Windows::Forms::PictureBox^ f32;


	private: System::Windows::Forms::PictureBox^ f18;

	private: System::Windows::Forms::PictureBox^ f16;

	private: System::Windows::Forms::PictureBox^ f2;
	private: System::Windows::Forms::PictureBox^ f29;



	private: System::Windows::Forms::PictureBox^ f9;
	private: System::Windows::Forms::PictureBox^ f63;


	private: System::Windows::Forms::PictureBox^ f54;

	private: System::Windows::Forms::PictureBox^ f50;

	private: System::Windows::Forms::PictureBox^ f22;
	private: System::Windows::Forms::PictureBox^ f48;


	private: System::Windows::Forms::PictureBox^ f6;
	private: System::Windows::Forms::PictureBox^ f52;


	private: System::Windows::Forms::PictureBox^ f38;

	private: System::Windows::Forms::PictureBox^ f27;

	private: System::Windows::Forms::PictureBox^ f11;
	private: System::Windows::Forms::PictureBox^ f25;
	private: System::Windows::Forms::PictureBox^ f45;



	private: System::Windows::Forms::PictureBox^ f41;

	private: System::Windows::Forms::PictureBox^ f13;
	private: System::Windows::Forms::PictureBox^ f43;


	private: System::Windows::Forms::PictureBox^ f15;
	private: System::Windows::Forms::PictureBox^ f57;


	private: System::Windows::Forms::PictureBox^ f31;
	private: System::Windows::Forms::PictureBox^ f59;


	private: System::Windows::Forms::PictureBox^ f47;

	private: System::Windows::Forms::PictureBox^ f40;
	private: System::Windows::Forms::PictureBox^ f60;


	private: System::Windows::Forms::PictureBox^ f24;
	private: System::Windows::Forms::PictureBox^ f58;


	private: System::Windows::Forms::PictureBox^ f8;
	private: System::Windows::Forms::PictureBox^ f44;


	private: System::Windows::Forms::PictureBox^ f14;
	private: System::Windows::Forms::PictureBox^ f42;
	private: System::Windows::Forms::PictureBox^ f46;



	private: System::Windows::Forms::PictureBox^ f26;

	private: System::Windows::Forms::PictureBox^ f12;
	private: System::Windows::Forms::PictureBox^ f28;
	private: System::Windows::Forms::PictureBox^ f39;
private: System::Windows::Forms::PictureBox^ f53;




	private: System::Windows::Forms::PictureBox^ f7;
private: System::Windows::Forms::PictureBox^ f49;


	private: System::Windows::Forms::PictureBox^ f23;
private: System::Windows::Forms::PictureBox^ f51;
private: System::Windows::Forms::PictureBox^ f55;
private: System::Windows::Forms::PictureBox^ f56;




	private: System::Windows::Forms::PictureBox^ f10;
private: System::Windows::Forms::PictureBox^ f30;


	private: System::Windows::Forms::PictureBox^ f3;
	private: System::Windows::Forms::PictureBox^ f17;
private: System::Windows::Forms::PictureBox^ f19;
private: System::Windows::Forms::PictureBox^ f33;




	private: System::Windows::Forms::PictureBox^ f5;
private: System::Windows::Forms::PictureBox^ f37;


private: System::Windows::Forms::PictureBox^ f21;
private: System::Windows::Forms::PictureBox^ f35;
private: System::Windows::Forms::PictureBox^ f62;



	private: System::Windows::Forms::PictureBox^ f1;
private: System::Windows::Forms::Button^ button2;
private: System::Windows::Forms::Button^ button3;
private: System::Windows::Forms::ComboBox^ comboBox1;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::Label^ label_info;

private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label5;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->f0 = (gcnew System::Windows::Forms::PictureBox());
			this->f61 = (gcnew System::Windows::Forms::PictureBox());
			this->f34 = (gcnew System::Windows::Forms::PictureBox());
			this->f20 = (gcnew System::Windows::Forms::PictureBox());
			this->f36 = (gcnew System::Windows::Forms::PictureBox());
			this->f4 = (gcnew System::Windows::Forms::PictureBox());
			this->f32 = (gcnew System::Windows::Forms::PictureBox());
			this->f18 = (gcnew System::Windows::Forms::PictureBox());
			this->f16 = (gcnew System::Windows::Forms::PictureBox());
			this->f2 = (gcnew System::Windows::Forms::PictureBox());
			this->f29 = (gcnew System::Windows::Forms::PictureBox());
			this->f9 = (gcnew System::Windows::Forms::PictureBox());
			this->f63 = (gcnew System::Windows::Forms::PictureBox());
			this->f54 = (gcnew System::Windows::Forms::PictureBox());
			this->f50 = (gcnew System::Windows::Forms::PictureBox());
			this->f22 = (gcnew System::Windows::Forms::PictureBox());
			this->f48 = (gcnew System::Windows::Forms::PictureBox());
			this->f6 = (gcnew System::Windows::Forms::PictureBox());
			this->f52 = (gcnew System::Windows::Forms::PictureBox());
			this->f38 = (gcnew System::Windows::Forms::PictureBox());
			this->f27 = (gcnew System::Windows::Forms::PictureBox());
			this->f11 = (gcnew System::Windows::Forms::PictureBox());
			this->f25 = (gcnew System::Windows::Forms::PictureBox());
			this->f45 = (gcnew System::Windows::Forms::PictureBox());
			this->f41 = (gcnew System::Windows::Forms::PictureBox());
			this->f13 = (gcnew System::Windows::Forms::PictureBox());
			this->f43 = (gcnew System::Windows::Forms::PictureBox());
			this->f15 = (gcnew System::Windows::Forms::PictureBox());
			this->f57 = (gcnew System::Windows::Forms::PictureBox());
			this->f31 = (gcnew System::Windows::Forms::PictureBox());
			this->f59 = (gcnew System::Windows::Forms::PictureBox());
			this->f47 = (gcnew System::Windows::Forms::PictureBox());
			this->f40 = (gcnew System::Windows::Forms::PictureBox());
			this->f60 = (gcnew System::Windows::Forms::PictureBox());
			this->f24 = (gcnew System::Windows::Forms::PictureBox());
			this->f58 = (gcnew System::Windows::Forms::PictureBox());
			this->f8 = (gcnew System::Windows::Forms::PictureBox());
			this->f44 = (gcnew System::Windows::Forms::PictureBox());
			this->f14 = (gcnew System::Windows::Forms::PictureBox());
			this->f42 = (gcnew System::Windows::Forms::PictureBox());
			this->f46 = (gcnew System::Windows::Forms::PictureBox());
			this->f26 = (gcnew System::Windows::Forms::PictureBox());
			this->f12 = (gcnew System::Windows::Forms::PictureBox());
			this->f28 = (gcnew System::Windows::Forms::PictureBox());
			this->f39 = (gcnew System::Windows::Forms::PictureBox());
			this->f53 = (gcnew System::Windows::Forms::PictureBox());
			this->f7 = (gcnew System::Windows::Forms::PictureBox());
			this->f49 = (gcnew System::Windows::Forms::PictureBox());
			this->f23 = (gcnew System::Windows::Forms::PictureBox());
			this->f51 = (gcnew System::Windows::Forms::PictureBox());
			this->f55 = (gcnew System::Windows::Forms::PictureBox());
			this->f56 = (gcnew System::Windows::Forms::PictureBox());
			this->f10 = (gcnew System::Windows::Forms::PictureBox());
			this->f30 = (gcnew System::Windows::Forms::PictureBox());
			this->f3 = (gcnew System::Windows::Forms::PictureBox());
			this->f17 = (gcnew System::Windows::Forms::PictureBox());
			this->f19 = (gcnew System::Windows::Forms::PictureBox());
			this->f33 = (gcnew System::Windows::Forms::PictureBox());
			this->f5 = (gcnew System::Windows::Forms::PictureBox());
			this->f37 = (gcnew System::Windows::Forms::PictureBox());
			this->f21 = (gcnew System::Windows::Forms::PictureBox());
			this->f35 = (gcnew System::Windows::Forms::PictureBox());
			this->f62 = (gcnew System::Windows::Forms::PictureBox());
			this->f1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label_info = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f0))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f61))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f34))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f36))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f32))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f63))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f54))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f50))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f48))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f52))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f38))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f45))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f41))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f43))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f57))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f31))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f59))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f47))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f40))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f60))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f58))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f44))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f42))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f46))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f28))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f39))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f53))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f49))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f51))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f55))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f56))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f37))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f35))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f62))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox1->Location = System::Drawing::Point(612, 163);
			this->textBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(65, 35);
			this->textBox1->TabIndex = 0;
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox1_KeyPress);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->Location = System::Drawing::Point(682, 147);
			this->button1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(110, 67);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Make move";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(8, 8);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(464, 483);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// f0
			// 
			this->f0->BackColor = System::Drawing::Color::White;
			this->f0->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f0.Image")));
			this->f0->Location = System::Drawing::Point(8, 8);
			this->f0->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f0->Name = L"f0";
			this->f0->Size = System::Drawing::Size(58, 60);
			this->f0->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f0->TabIndex = 5;
			this->f0->TabStop = false;
			// 
			// f61
			// 
			this->f61->BackColor = System::Drawing::Color::White;
			this->f61->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f61.Image")));
			this->f61->Location = System::Drawing::Point(298, 430);
			this->f61->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f61->Name = L"f61";
			this->f61->Size = System::Drawing::Size(58, 60);
			this->f61->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f61->TabIndex = 8;
			this->f61->TabStop = false;
			// 
			// f34
			// 
			this->f34->BackColor = System::Drawing::Color::White;
			this->f34->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f34.Image")));
			this->f34->Location = System::Drawing::Point(124, 249);
			this->f34->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f34->Name = L"f34";
			this->f34->Size = System::Drawing::Size(58, 60);
			this->f34->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f34->TabIndex = 9;
			this->f34->TabStop = false;
			// 
			// f20
			// 
			this->f20->BackColor = System::Drawing::Color::White;
			this->f20->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f20.Image")));
			this->f20->Location = System::Drawing::Point(240, 128);
			this->f20->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f20->Name = L"f20";
			this->f20->Size = System::Drawing::Size(58, 60);
			this->f20->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f20->TabIndex = 10;
			this->f20->TabStop = false;
			// 
			// f36
			// 
			this->f36->BackColor = System::Drawing::Color::White;
			this->f36->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f36.Image")));
			this->f36->Location = System::Drawing::Point(240, 249);
			this->f36->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f36->Name = L"f36";
			this->f36->Size = System::Drawing::Size(58, 60);
			this->f36->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f36->TabIndex = 11;
			this->f36->TabStop = false;
			// 
			// f4
			// 
			this->f4->BackColor = System::Drawing::Color::White;
			this->f4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f4.Image")));
			this->f4->Location = System::Drawing::Point(240, 8);
			this->f4->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f4->Name = L"f4";
			this->f4->Size = System::Drawing::Size(58, 60);
			this->f4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f4->TabIndex = 12;
			this->f4->TabStop = false;
			// 
			// f32
			// 
			this->f32->BackColor = System::Drawing::Color::White;
			this->f32->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f32.Image")));
			this->f32->Location = System::Drawing::Point(8, 249);
			this->f32->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f32->Name = L"f32";
			this->f32->Size = System::Drawing::Size(58, 60);
			this->f32->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f32->TabIndex = 13;
			this->f32->TabStop = false;
			// 
			// f18
			// 
			this->f18->BackColor = System::Drawing::Color::White;
			this->f18->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f18.Image")));
			this->f18->Location = System::Drawing::Point(124, 128);
			this->f18->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f18->Name = L"f18";
			this->f18->Size = System::Drawing::Size(58, 60);
			this->f18->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f18->TabIndex = 14;
			this->f18->TabStop = false;
			// 
			// f16
			// 
			this->f16->BackColor = System::Drawing::Color::White;
			this->f16->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f16.Image")));
			this->f16->Location = System::Drawing::Point(8, 128);
			this->f16->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f16->Name = L"f16";
			this->f16->Size = System::Drawing::Size(58, 60);
			this->f16->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f16->TabIndex = 15;
			this->f16->TabStop = false;
			// 
			// f2
			// 
			this->f2->BackColor = System::Drawing::Color::White;
			this->f2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f2.Image")));
			this->f2->Location = System::Drawing::Point(124, 8);
			this->f2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f2->Name = L"f2";
			this->f2->Size = System::Drawing::Size(58, 60);
			this->f2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f2->TabIndex = 16;
			this->f2->TabStop = false;
			// 
			// f29
			// 
			this->f29->BackColor = System::Drawing::Color::White;
			this->f29->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f29.Image")));
			this->f29->Location = System::Drawing::Point(298, 189);
			this->f29->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f29->Name = L"f29";
			this->f29->Size = System::Drawing::Size(58, 60);
			this->f29->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f29->TabIndex = 17;
			this->f29->TabStop = false;
			// 
			// f9
			// 
			this->f9->BackColor = System::Drawing::Color::White;
			this->f9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f9.Image")));
			this->f9->Location = System::Drawing::Point(66, 68);
			this->f9->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f9->Name = L"f9";
			this->f9->Size = System::Drawing::Size(58, 60);
			this->f9->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f9->TabIndex = 18;
			this->f9->TabStop = false;
			// 
			// f63
			// 
			this->f63->BackColor = System::Drawing::Color::White;
			this->f63->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f63.Image")));
			this->f63->Location = System::Drawing::Point(414, 430);
			this->f63->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f63->Name = L"f63";
			this->f63->Size = System::Drawing::Size(58, 60);
			this->f63->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f63->TabIndex = 19;
			this->f63->TabStop = false;
			// 
			// f54
			// 
			this->f54->BackColor = System::Drawing::Color::White;
			this->f54->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f54.Image")));
			this->f54->Location = System::Drawing::Point(356, 370);
			this->f54->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f54->Name = L"f54";
			this->f54->Size = System::Drawing::Size(58, 60);
			this->f54->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f54->TabIndex = 20;
			this->f54->TabStop = false;
			// 
			// f50
			// 
			this->f50->BackColor = System::Drawing::Color::White;
			this->f50->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f50.Image")));
			this->f50->Location = System::Drawing::Point(124, 370);
			this->f50->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f50->Name = L"f50";
			this->f50->Size = System::Drawing::Size(58, 60);
			this->f50->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f50->TabIndex = 21;
			this->f50->TabStop = false;
			// 
			// f22
			// 
			this->f22->BackColor = System::Drawing::Color::White;
			this->f22->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f22.Image")));
			this->f22->Location = System::Drawing::Point(356, 128);
			this->f22->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f22->Name = L"f22";
			this->f22->Size = System::Drawing::Size(58, 60);
			this->f22->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f22->TabIndex = 22;
			this->f22->TabStop = false;
			// 
			// f48
			// 
			this->f48->BackColor = System::Drawing::Color::White;
			this->f48->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f48.Image")));
			this->f48->Location = System::Drawing::Point(8, 370);
			this->f48->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f48->Name = L"f48";
			this->f48->Size = System::Drawing::Size(58, 60);
			this->f48->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f48->TabIndex = 23;
			this->f48->TabStop = false;
			// 
			// f6
			// 
			this->f6->BackColor = System::Drawing::Color::White;
			this->f6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f6.Image")));
			this->f6->Location = System::Drawing::Point(356, 8);
			this->f6->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f6->Name = L"f6";
			this->f6->Size = System::Drawing::Size(58, 60);
			this->f6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f6->TabIndex = 24;
			this->f6->TabStop = false;
			// 
			// f52
			// 
			this->f52->BackColor = System::Drawing::Color::White;
			this->f52->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f52.Image")));
			this->f52->Location = System::Drawing::Point(240, 370);
			this->f52->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f52->Name = L"f52";
			this->f52->Size = System::Drawing::Size(58, 60);
			this->f52->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f52->TabIndex = 25;
			this->f52->TabStop = false;
			// 
			// f38
			// 
			this->f38->BackColor = System::Drawing::Color::White;
			this->f38->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f38.Image")));
			this->f38->Location = System::Drawing::Point(356, 249);
			this->f38->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f38->Name = L"f38";
			this->f38->Size = System::Drawing::Size(58, 60);
			this->f38->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f38->TabIndex = 26;
			this->f38->TabStop = false;
			// 
			// f27
			// 
			this->f27->BackColor = System::Drawing::Color::White;
			this->f27->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f27.Image")));
			this->f27->Location = System::Drawing::Point(182, 189);
			this->f27->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f27->Name = L"f27";
			this->f27->Size = System::Drawing::Size(58, 60);
			this->f27->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f27->TabIndex = 27;
			this->f27->TabStop = false;
			// 
			// f11
			// 
			this->f11->BackColor = System::Drawing::Color::White;
			this->f11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f11.Image")));
			this->f11->Location = System::Drawing::Point(182, 68);
			this->f11->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f11->Name = L"f11";
			this->f11->Size = System::Drawing::Size(58, 60);
			this->f11->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f11->TabIndex = 28;
			this->f11->TabStop = false;
			// 
			// f25
			// 
			this->f25->BackColor = System::Drawing::Color::White;
			this->f25->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f25.Image")));
			this->f25->Location = System::Drawing::Point(66, 189);
			this->f25->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f25->Name = L"f25";
			this->f25->Size = System::Drawing::Size(58, 60);
			this->f25->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f25->TabIndex = 29;
			this->f25->TabStop = false;
			// 
			// f45
			// 
			this->f45->BackColor = System::Drawing::Color::White;
			this->f45->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f45.Image")));
			this->f45->Location = System::Drawing::Point(298, 309);
			this->f45->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f45->Name = L"f45";
			this->f45->Size = System::Drawing::Size(58, 60);
			this->f45->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f45->TabIndex = 30;
			this->f45->TabStop = false;
			// 
			// f41
			// 
			this->f41->BackColor = System::Drawing::Color::White;
			this->f41->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f41.Image")));
			this->f41->Location = System::Drawing::Point(66, 309);
			this->f41->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f41->Name = L"f41";
			this->f41->Size = System::Drawing::Size(58, 60);
			this->f41->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f41->TabIndex = 31;
			this->f41->TabStop = false;
			// 
			// f13
			// 
			this->f13->BackColor = System::Drawing::Color::White;
			this->f13->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f13.Image")));
			this->f13->Location = System::Drawing::Point(298, 68);
			this->f13->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f13->Name = L"f13";
			this->f13->Size = System::Drawing::Size(58, 60);
			this->f13->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f13->TabIndex = 32;
			this->f13->TabStop = false;
			// 
			// f43
			// 
			this->f43->BackColor = System::Drawing::Color::White;
			this->f43->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f43.Image")));
			this->f43->Location = System::Drawing::Point(182, 309);
			this->f43->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f43->Name = L"f43";
			this->f43->Size = System::Drawing::Size(58, 60);
			this->f43->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f43->TabIndex = 33;
			this->f43->TabStop = false;
			// 
			// f15
			// 
			this->f15->BackColor = System::Drawing::Color::White;
			this->f15->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f15.Image")));
			this->f15->Location = System::Drawing::Point(414, 68);
			this->f15->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f15->Name = L"f15";
			this->f15->Size = System::Drawing::Size(58, 60);
			this->f15->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f15->TabIndex = 34;
			this->f15->TabStop = false;
			// 
			// f57
			// 
			this->f57->BackColor = System::Drawing::Color::White;
			this->f57->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f57.Image")));
			this->f57->Location = System::Drawing::Point(66, 430);
			this->f57->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f57->Name = L"f57";
			this->f57->Size = System::Drawing::Size(58, 60);
			this->f57->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f57->TabIndex = 35;
			this->f57->TabStop = false;
			// 
			// f31
			// 
			this->f31->BackColor = System::Drawing::Color::White;
			this->f31->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f31.Image")));
			this->f31->Location = System::Drawing::Point(414, 189);
			this->f31->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f31->Name = L"f31";
			this->f31->Size = System::Drawing::Size(58, 60);
			this->f31->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f31->TabIndex = 36;
			this->f31->TabStop = false;
			// 
			// f59
			// 
			this->f59->BackColor = System::Drawing::Color::White;
			this->f59->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f59.Image")));
			this->f59->Location = System::Drawing::Point(182, 430);
			this->f59->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f59->Name = L"f59";
			this->f59->Size = System::Drawing::Size(58, 60);
			this->f59->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f59->TabIndex = 37;
			this->f59->TabStop = false;
			// 
			// f47
			// 
			this->f47->BackColor = System::Drawing::Color::White;
			this->f47->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f47.Image")));
			this->f47->Location = System::Drawing::Point(414, 309);
			this->f47->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f47->Name = L"f47";
			this->f47->Size = System::Drawing::Size(58, 60);
			this->f47->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f47->TabIndex = 38;
			this->f47->TabStop = false;
			// 
			// f40
			// 
			this->f40->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f40->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f40.Image")));
			this->f40->Location = System::Drawing::Point(8, 309);
			this->f40->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f40->Name = L"f40";
			this->f40->Size = System::Drawing::Size(58, 60);
			this->f40->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f40->TabIndex = 71;
			this->f40->TabStop = false;
			// 
			// f60
			// 
			this->f60->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f60->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f60.Image")));
			this->f60->Location = System::Drawing::Point(240, 430);
			this->f60->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f60->Name = L"f60";
			this->f60->Size = System::Drawing::Size(58, 60);
			this->f60->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f60->TabIndex = 70;
			this->f60->TabStop = false;
			// 
			// f24
			// 
			this->f24->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f24->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f24.Image")));
			this->f24->Location = System::Drawing::Point(8, 189);
			this->f24->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f24->Name = L"f24";
			this->f24->Size = System::Drawing::Size(58, 60);
			this->f24->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f24->TabIndex = 69;
			this->f24->TabStop = false;
			// 
			// f58
			// 
			this->f58->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f58->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f58.Image")));
			this->f58->Location = System::Drawing::Point(124, 430);
			this->f58->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f58->Name = L"f58";
			this->f58->Size = System::Drawing::Size(58, 60);
			this->f58->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f58->TabIndex = 68;
			this->f58->TabStop = false;
			// 
			// f8
			// 
			this->f8->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f8.Image")));
			this->f8->Location = System::Drawing::Point(8, 68);
			this->f8->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f8->Name = L"f8";
			this->f8->Size = System::Drawing::Size(58, 60);
			this->f8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f8->TabIndex = 67;
			this->f8->TabStop = false;
			// 
			// f44
			// 
			this->f44->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f44->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f44.Image")));
			this->f44->Location = System::Drawing::Point(240, 309);
			this->f44->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f44->Name = L"f44";
			this->f44->Size = System::Drawing::Size(58, 60);
			this->f44->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f44->TabIndex = 66;
			this->f44->TabStop = false;
			// 
			// f14
			// 
			this->f14->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f14->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f14.Image")));
			this->f14->Location = System::Drawing::Point(356, 68);
			this->f14->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f14->Name = L"f14";
			this->f14->Size = System::Drawing::Size(58, 60);
			this->f14->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f14->TabIndex = 65;
			this->f14->TabStop = false;
			// 
			// f42
			// 
			this->f42->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f42->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f42.Image")));
			this->f42->Location = System::Drawing::Point(124, 309);
			this->f42->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f42->Name = L"f42";
			this->f42->Size = System::Drawing::Size(58, 60);
			this->f42->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f42->TabIndex = 64;
			this->f42->TabStop = false;
			// 
			// f46
			// 
			this->f46->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f46->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f46.Image")));
			this->f46->Location = System::Drawing::Point(356, 309);
			this->f46->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f46->Name = L"f46";
			this->f46->Size = System::Drawing::Size(58, 60);
			this->f46->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f46->TabIndex = 63;
			this->f46->TabStop = false;
			// 
			// f26
			// 
			this->f26->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f26->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f26.Image")));
			this->f26->Location = System::Drawing::Point(124, 189);
			this->f26->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f26->Name = L"f26";
			this->f26->Size = System::Drawing::Size(58, 60);
			this->f26->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f26->TabIndex = 62;
			this->f26->TabStop = false;
			// 
			// f12
			// 
			this->f12->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f12.Image")));
			this->f12->Location = System::Drawing::Point(240, 68);
			this->f12->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f12->Name = L"f12";
			this->f12->Size = System::Drawing::Size(58, 60);
			this->f12->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f12->TabIndex = 61;
			this->f12->TabStop = false;
			// 
			// f28
			// 
			this->f28->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f28->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f28.Image")));
			this->f28->Location = System::Drawing::Point(240, 189);
			this->f28->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f28->Name = L"f28";
			this->f28->Size = System::Drawing::Size(58, 60);
			this->f28->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f28->TabIndex = 60;
			this->f28->TabStop = false;
			// 
			// f39
			// 
			this->f39->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f39->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f39.Image")));
			this->f39->Location = System::Drawing::Point(414, 249);
			this->f39->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f39->Name = L"f39";
			this->f39->Size = System::Drawing::Size(58, 60);
			this->f39->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f39->TabIndex = 59;
			this->f39->TabStop = false;
			// 
			// f53
			// 
			this->f53->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f53->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f53.Image")));
			this->f53->Location = System::Drawing::Point(298, 370);
			this->f53->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f53->Name = L"f53";
			this->f53->Size = System::Drawing::Size(58, 60);
			this->f53->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f53->TabIndex = 58;
			this->f53->TabStop = false;
			// 
			// f7
			// 
			this->f7->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f7.Image")));
			this->f7->Location = System::Drawing::Point(414, 8);
			this->f7->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f7->Name = L"f7";
			this->f7->Size = System::Drawing::Size(58, 60);
			this->f7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f7->TabIndex = 57;
			this->f7->TabStop = false;
			// 
			// f49
			// 
			this->f49->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f49->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f49.Image")));
			this->f49->Location = System::Drawing::Point(66, 370);
			this->f49->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f49->Name = L"f49";
			this->f49->Size = System::Drawing::Size(58, 60);
			this->f49->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f49->TabIndex = 56;
			this->f49->TabStop = false;
			// 
			// f23
			// 
			this->f23->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f23->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f23.Image")));
			this->f23->Location = System::Drawing::Point(414, 128);
			this->f23->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f23->Name = L"f23";
			this->f23->Size = System::Drawing::Size(58, 60);
			this->f23->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f23->TabIndex = 55;
			this->f23->TabStop = false;
			// 
			// f51
			// 
			this->f51->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f51->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f51.Image")));
			this->f51->Location = System::Drawing::Point(182, 370);
			this->f51->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f51->Name = L"f51";
			this->f51->Size = System::Drawing::Size(58, 60);
			this->f51->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f51->TabIndex = 54;
			this->f51->TabStop = false;
			// 
			// f55
			// 
			this->f55->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f55->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f55.Image")));
			this->f55->Location = System::Drawing::Point(414, 370);
			this->f55->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f55->Name = L"f55";
			this->f55->Size = System::Drawing::Size(58, 60);
			this->f55->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f55->TabIndex = 53;
			this->f55->TabStop = false;
			// 
			// f56
			// 
			this->f56->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f56->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f56.Image")));
			this->f56->Location = System::Drawing::Point(8, 430);
			this->f56->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f56->Name = L"f56";
			this->f56->Size = System::Drawing::Size(58, 60);
			this->f56->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f56->TabIndex = 52;
			this->f56->TabStop = false;
			// 
			// f10
			// 
			this->f10->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f10.Image")));
			this->f10->Location = System::Drawing::Point(124, 68);
			this->f10->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f10->Name = L"f10";
			this->f10->Size = System::Drawing::Size(58, 60);
			this->f10->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f10->TabIndex = 51;
			this->f10->TabStop = false;
			// 
			// f30
			// 
			this->f30->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f30->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f30.Image")));
			this->f30->Location = System::Drawing::Point(356, 189);
			this->f30->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f30->Name = L"f30";
			this->f30->Size = System::Drawing::Size(58, 60);
			this->f30->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f30->TabIndex = 50;
			this->f30->TabStop = false;
			// 
			// f3
			// 
			this->f3->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f3.Image")));
			this->f3->Location = System::Drawing::Point(182, 8);
			this->f3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f3->Name = L"f3";
			this->f3->Size = System::Drawing::Size(58, 60);
			this->f3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f3->TabIndex = 49;
			this->f3->TabStop = false;
			// 
			// f17
			// 
			this->f17->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f17->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f17.Image")));
			this->f17->Location = System::Drawing::Point(66, 128);
			this->f17->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f17->Name = L"f17";
			this->f17->Size = System::Drawing::Size(58, 60);
			this->f17->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f17->TabIndex = 48;
			this->f17->TabStop = false;
			// 
			// f19
			// 
			this->f19->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f19->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f19.Image")));
			this->f19->Location = System::Drawing::Point(182, 128);
			this->f19->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f19->Name = L"f19";
			this->f19->Size = System::Drawing::Size(58, 60);
			this->f19->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f19->TabIndex = 47;
			this->f19->TabStop = false;
			// 
			// f33
			// 
			this->f33->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f33->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f33.Image")));
			this->f33->Location = System::Drawing::Point(66, 249);
			this->f33->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f33->Name = L"f33";
			this->f33->Size = System::Drawing::Size(58, 60);
			this->f33->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f33->TabIndex = 46;
			this->f33->TabStop = false;
			// 
			// f5
			// 
			this->f5->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f5.Image")));
			this->f5->Location = System::Drawing::Point(298, 8);
			this->f5->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f5->Name = L"f5";
			this->f5->Size = System::Drawing::Size(58, 60);
			this->f5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f5->TabIndex = 45;
			this->f5->TabStop = false;
			// 
			// f37
			// 
			this->f37->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f37->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f37.Image")));
			this->f37->Location = System::Drawing::Point(298, 249);
			this->f37->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f37->Name = L"f37";
			this->f37->Size = System::Drawing::Size(58, 60);
			this->f37->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f37->TabIndex = 44;
			this->f37->TabStop = false;
			// 
			// f21
			// 
			this->f21->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f21->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f21.Image")));
			this->f21->Location = System::Drawing::Point(298, 128);
			this->f21->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f21->Name = L"f21";
			this->f21->Size = System::Drawing::Size(58, 60);
			this->f21->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f21->TabIndex = 43;
			this->f21->TabStop = false;
			// 
			// f35
			// 
			this->f35->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f35->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f35.Image")));
			this->f35->Location = System::Drawing::Point(182, 249);
			this->f35->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f35->Name = L"f35";
			this->f35->Size = System::Drawing::Size(58, 60);
			this->f35->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f35->TabIndex = 42;
			this->f35->TabStop = false;
			// 
			// f62
			// 
			this->f62->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f62->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f62.Image")));
			this->f62->Location = System::Drawing::Point(356, 430);
			this->f62->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f62->Name = L"f62";
			this->f62->Size = System::Drawing::Size(58, 60);
			this->f62->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f62->TabIndex = 41;
			this->f62->TabStop = false;
			// 
			// f1
			// 
			this->f1->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->f1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"f1.Image")));
			this->f1->Location = System::Drawing::Point(66, 8);
			this->f1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->f1->Name = L"f1";
			this->f1->Size = System::Drawing::Size(58, 60);
			this->f1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->f1->TabIndex = 40;
			this->f1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button2->Location = System::Drawing::Point(537, 309);
			this->button2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(91, 92);
			this->button2->TabIndex = 72;
			this->button2->Text = L"Undo";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button3->Location = System::Drawing::Point(682, 309);
			this->button3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(98, 92);
			this->button3->TabIndex = 73;
			this->button3->Text = L"New game";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Easy", L"Medium", L"Hard" });
			this->comboBox1->Location = System::Drawing::Point(612, 241);
			this->comboBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(164, 37);
			this->comboBox1->TabIndex = 74;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->ForeColor = System::Drawing::Color::Gainsboro;
			this->label1->Location = System::Drawing::Point(532, 166);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(72, 29);
			this->label1->TabIndex = 75;
			this->label1->Text = L"Move";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18.4F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->ForeColor = System::Drawing::Color::Gainsboro;
			this->label2->Location = System::Drawing::Point(474, 24);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 435);
			this->label2->TabIndex = 76;
			this->label2->Text = L"8\r\n\r\n7\r\n\r\n6\r\n\r\n5\r\n\r\n4\r\n\r\n3\r\n\r\n2\r\n\r\n1";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label3->ForeColor = System::Drawing::Color::Gainsboro;
			this->label3->Location = System::Drawing::Point(524, 9);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(263, 46);
			this->label3->TabIndex = 77;
			this->label3->Text = L"Chess engine";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label4->ForeColor = System::Drawing::Color::Gainsboro;
			this->label4->Location = System::Drawing::Point(532, 242);
			this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(71, 29);
			this->label4->TabIndex = 78;
			this->label4->Text = L"Level";
			// 
			// label_info
			// 
			this->label_info->AutoSize = true;
			this->label_info->BackColor = System::Drawing::Color::Transparent;
			this->label_info->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
			this->label_info->Location = System::Drawing::Point(532, 79);
			this->label_info->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label_info->Name = L"label_info";
			this->label_info->Size = System::Drawing::Size(146, 30);
			this->label_info->TabIndex = 79;
			this->label_info->Text = L"Make move";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label6->ForeColor = System::Drawing::Color::Gainsboro;
			this->label6->Location = System::Drawing::Point(522, 486);
			this->label6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(278, 18);
			this->label6->TabIndex = 80;
			this->label6->Text = L"Authors: Wasyl Badyra, Piotr Fr¹ckowski";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label5->ForeColor = System::Drawing::Color::Gainsboro;
			this->label5->Location = System::Drawing::Point(24, 513);
			this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(444, 30);
			this->label5->TabIndex = 81;
			this->label5->Text = L"A      B      C      D     E      F     G      H ";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(840, 561);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label_info);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->f40);
			this->Controls->Add(this->f60);
			this->Controls->Add(this->f24);
			this->Controls->Add(this->f58);
			this->Controls->Add(this->f8);
			this->Controls->Add(this->f44);
			this->Controls->Add(this->f14);
			this->Controls->Add(this->f42);
			this->Controls->Add(this->f46);
			this->Controls->Add(this->f26);
			this->Controls->Add(this->f12);
			this->Controls->Add(this->f28);
			this->Controls->Add(this->f39);
			this->Controls->Add(this->f53);
			this->Controls->Add(this->f7);
			this->Controls->Add(this->f49);
			this->Controls->Add(this->f23);
			this->Controls->Add(this->f51);
			this->Controls->Add(this->f55);
			this->Controls->Add(this->f56);
			this->Controls->Add(this->f10);
			this->Controls->Add(this->f30);
			this->Controls->Add(this->f3);
			this->Controls->Add(this->f17);
			this->Controls->Add(this->f19);
			this->Controls->Add(this->f33);
			this->Controls->Add(this->f5);
			this->Controls->Add(this->f37);
			this->Controls->Add(this->f21);
			this->Controls->Add(this->f35);
			this->Controls->Add(this->f62);
			this->Controls->Add(this->f1);
			this->Controls->Add(this->f47);
			this->Controls->Add(this->f59);
			this->Controls->Add(this->f31);
			this->Controls->Add(this->f57);
			this->Controls->Add(this->f15);
			this->Controls->Add(this->f43);
			this->Controls->Add(this->f13);
			this->Controls->Add(this->f41);
			this->Controls->Add(this->f45);
			this->Controls->Add(this->f25);
			this->Controls->Add(this->f11);
			this->Controls->Add(this->f27);
			this->Controls->Add(this->f38);
			this->Controls->Add(this->f52);
			this->Controls->Add(this->f6);
			this->Controls->Add(this->f48);
			this->Controls->Add(this->f22);
			this->Controls->Add(this->f50);
			this->Controls->Add(this->f54);
			this->Controls->Add(this->f63);
			this->Controls->Add(this->f9);
			this->Controls->Add(this->f29);
			this->Controls->Add(this->f2);
			this->Controls->Add(this->f16);
			this->Controls->Add(this->f18);
			this->Controls->Add(this->f32);
			this->Controls->Add(this->f4);
			this->Controls->Add(this->f36);
			this->Controls->Add(this->f20);
			this->Controls->Add(this->f34);
			this->Controls->Add(this->f61);
			this->Controls->Add(this->f0);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f0))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f61))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f34))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f36))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f32))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f63))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f54))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f50))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f48))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f52))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f38))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f45))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f41))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f43))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f57))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f31))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f59))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f47))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f40))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f60))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f58))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f44))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f42))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f46))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f28))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f39))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f53))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f49))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f51))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f55))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f56))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f37))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f35))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f62))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

			this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
			this->label_info->Text = "Make move";
			this->comboBox1->SelectedIndex = 0;
			string fen = Source::get_board();
			draw_from_fen(fen);

		}
		//this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
		//this->label_info->Text = "Make move";
		//this->comboBox1->SelectedItem = 0;
		//string fen = Source::get_board();
		//draw_from_fen(fen);
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		make_move();
	}
	private: System::Void make_move() {
		string text;
		text = msclr::interop::marshal_as<std::string>(this->textBox1->Text);
		string fen_n = Source::move_human(text);
		this->textBox1->Text = "";
		System::Int16 n = interpret_message(fen_n);
		MyForm::Refresh();
		if (n == 0) {
			this->label_info->ForeColor = System::Drawing::Color::Yellow;
			this->label_info->Text = "Wait for engine's move ...";
			MyForm::Refresh();
			fen_n = Source::move_engine();
			interpret_message(fen_n);
		}
	}
	private: System::Int16 interpret_message(string f) {
		if (f == "") {
			this->label_info->ForeColor = System::Drawing::Color::Red;
			this->label_info->Text = "Invalid move, try again";
			return 1;
		}
		else if (f == "1/2-1/2 {Draw by insufficient material}")
		{
			this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
			this->label_info->Text = "Draw";
			string fen = Source::get_board();
			draw_from_fen(fen);
			return 1;
		}
		else if (f == "1/2-1/2 {Draw by repetition}")
		{
			this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
			this->label_info->Text = "Draw";
			string fen = Source::get_board();
			draw_from_fen(fen);
			return 1;
		}
		else if (f == "1/2-1/2 {Draw by fifty move rule}")
		{
			this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
			this->label_info->Text = "Draw";
			string fen = Source::get_board();
			draw_from_fen(fen);
			return 1;
		}
		else if (f == "1/2-1/2 {Stalemate}")
		{
			this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
			this->label_info->Text = "Stalemate";
			string fen = Source::get_board();
			draw_from_fen(fen);
			return 1;
		}
		else if (f == "0-1 {Black mates}")
		{
			this->label_info->ForeColor = System::Drawing::Color::Red;
			this->label_info->Text = "Black mates";
			string fen = Source::get_board();
			draw_from_fen(fen);
			return 1;
		}
		else if (f == "1-0 {White mates}")
		{
			this->label_info->ForeColor = System::Drawing::Color::Green;
			this->label_info->Text = "White mates";
			string fen = Source::get_board();
			draw_from_fen(fen);
			return 1;
		}
		else {
			this->label_info->ForeColor = System::Drawing::Color::DeepSkyBlue;
			this->label_info->Text = "Make move";
			draw_from_fen(f);
			return 0;
		}
	}
	private: System::Void draw_from_fen(string fen) {
		char index = 0;
		char spc = 0;
		int Squares[64];
		for (int i = 0; i < 64; i++) {
			Squares[i] = 0;
		}
		for (auto& c : fen)
		{
			if (index < 64 && spc == 0)
			{
				if (c == '1' && index < 63)
				{
					for (int i = 0; i < 1; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 1);
				}
				else if (c == '2' && index < 62)
				{
					for (int i = 0; i < 2; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 2);
				}
				else if (c == '3' && index < 61)
				{
					for (int i = 0; i < 3; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 3);
				}
				else if (c == '4' && index < 60)
				{
					for (int i = 0; i < 4; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 4);
				}
				else if (c == '5' && index < 59)
				{
					for (int i = 0; i < 5; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 5);
				}
				else if (c == '6' && index < 58)
				{
					for (int i = 0; i < 6; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 6);
				}
				else if (c == '7' && index < 57)
				{
					for (int i = 0; i < 7; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 7);
				}
				else if (c == '8' && index < 56)
				{
					for (int i = 0; i < 8; i++) {
						Squares[index + i] = 0;
					}
					index = (index + 8);
				}
				else if (c == 'P')
				{
					Squares[index] = 1;
					index = (index + 1);
				}
				else if (c == 'N')
				{
					Squares[index] = 3;
					index = (index + 1);
				}
				else if (c == 'B')
				{
					Squares[index] = 4;
					index = (index + 1);
				}
				else if (c == 'R')
				{
					Squares[index] = 2;
					index = (index + 1);
				}
				else if (c == 'Q')
				{
					Squares[index] = 5;
					index = (index + 1);
				}
				else if (c == 'K')
				{
					Squares[index] = 6;
					index = (index + 1);
				}
				else if (c == 'p')
				{
					Squares[index] = 7;
					index = (index + 1);
				}
				else if (c == 'n')
				{
					Squares[index] = 9;
					index = (index + 1);
				}
				else if (c == 'b')
				{
					Squares[index] = 10;
					index = (index + 1);
				}
				else if (c == 'r')
				{
					Squares[index] = 8;
					index = (index + 1);
				}
				else if (c == 'q')
				{
					Squares[index] = 11;
					index = (index + 1);
				}
				else if (c == 'k')
				{
					Squares[index] = 12;
					index = (index + 1);
				}
				else if (c == '/')
				{
					continue;
				}
				else if (c == ' ')
				{
					spc = (spc + 1);
				}
			}
		}
		draw_board(Squares);
	}
	private: System::Void draw_board(int B[]) {
		delete f0->Image;
		delete f1->Image;
		delete f2->Image;
		delete f3->Image;
		delete f4->Image;
		delete f5->Image;
		delete f6->Image;
		delete f7->Image;
		delete f8->Image;
		delete f9->Image;
		delete f10->Image;
		delete f11->Image;
		delete f12->Image;
		delete f13->Image;
		delete f14->Image;
		delete f15->Image;
		delete f16->Image;
		delete f17->Image;
		delete f18->Image;
		delete f19->Image;
		delete f20->Image;
		delete f21->Image;
		delete f22->Image;
		delete f23->Image;
		delete f24->Image;
		delete f25->Image;
		delete f26->Image;
		delete f27->Image;
		delete f28->Image;
		delete f29->Image;
		delete f30->Image;
		delete f31->Image;
		delete f32->Image;
		delete f33->Image;
		delete f34->Image;
		delete f35->Image;
		delete f36->Image;
		delete f37->Image;
		delete f38->Image;
		delete f39->Image;
		delete f40->Image;
		delete f41->Image;
		delete f42->Image;
		delete f43->Image;
		delete f44->Image;
		delete f45->Image;
		delete f46->Image;
		delete f47->Image;
		delete f48->Image;
		delete f49->Image;
		delete f50->Image;
		delete f51->Image;
		delete f52->Image;
		delete f53->Image;
		delete f54->Image;
		delete f55->Image;
		delete f56->Image;
		delete f57->Image;
		delete f58->Image;
		delete f59->Image;
		delete f60->Image;
		delete f61->Image;
		delete f62->Image;
		delete f63->Image;

		f0->Image = get_im(B[0]);
		f1->Image = get_im(B[1]);
		f2->Image = get_im(B[2]);
		f3->Image = get_im(B[3]);
		f4->Image = get_im(B[4]);
		f5->Image = get_im(B[5]);
		f6->Image = get_im(B[6]);
		f7->Image = get_im(B[7]);
		f8->Image = get_im(B[8]);
		f9->Image = get_im(B[9]);
		f10->Image = get_im(B[10]);
		f11->Image = get_im(B[11]);
		f12->Image = get_im(B[12]);
		f13->Image = get_im(B[13]);
		f14->Image = get_im(B[14]);
		f15->Image = get_im(B[15]);
		f16->Image = get_im(B[16]);
		f17->Image = get_im(B[17]);
		f18->Image = get_im(B[18]);
		f19->Image = get_im(B[19]);
		f20->Image = get_im(B[20]);
		f21->Image = get_im(B[21]);
		f22->Image = get_im(B[22]);
		f23->Image = get_im(B[23]);
		f24->Image = get_im(B[24]);
		f25->Image = get_im(B[25]);
		f26->Image = get_im(B[26]);
		f27->Image = get_im(B[27]);
		f28->Image = get_im(B[28]);
		f29->Image = get_im(B[29]);
		f30->Image = get_im(B[30]);
		f31->Image = get_im(B[31]);
		f32->Image = get_im(B[32]);
		f33->Image = get_im(B[33]);
		f34->Image = get_im(B[34]);
		f35->Image = get_im(B[35]);
		f36->Image = get_im(B[36]);
		f37->Image = get_im(B[37]);
		f38->Image = get_im(B[38]);
		f39->Image = get_im(B[39]);
		f40->Image = get_im(B[40]);
		f41->Image = get_im(B[41]);
		f42->Image = get_im(B[42]);
		f43->Image = get_im(B[43]);
		f44->Image = get_im(B[44]);
		f45->Image = get_im(B[45]);
		f46->Image = get_im(B[46]);
		f47->Image = get_im(B[47]);
		f48->Image = get_im(B[48]);
		f49->Image = get_im(B[49]);
		f50->Image = get_im(B[50]);
		f51->Image = get_im(B[51]);
		f52->Image = get_im(B[52]);
		f53->Image = get_im(B[53]);
		f54->Image = get_im(B[54]);
		f55->Image = get_im(B[55]);
		f56->Image = get_im(B[56]);
		f57->Image = get_im(B[57]);
		f58->Image = get_im(B[58]);
		f59->Image = get_im(B[59]);
		f60->Image = get_im(B[60]);
		f61->Image = get_im(B[61]);
		f62->Image = get_im(B[62]);
		f63->Image = get_im(B[63]);

	}
	private: System::Drawing::Image^ get_im(int n) {
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew
			System::ComponentModel::ComponentResourceManager(MyForm::typeid));
		if (n == 1) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_plt60")));
		}
		else if (n == 2) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_rlt60")));
		}
		else if (n == 3) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_nlt60")));
		}
		else if (n == 4) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_blt60")));
		}
		else if (n == 5) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_qlt60")));
		}
		else if (n == 6) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_klt60")));
		}
		else if (n == 7) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_pdt60")));
		}
		else if (n == 8) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_rdt60")));
		}
		else if (n == 9) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_ndt60")));
		}
		else if (n == 10) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_bdt60")));
		}
		else if (n == 11) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_qdt60")));
		}
		else if (n == 12) {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chess_kdt60")));
		}
		else {
			return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"empty")));
		}
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	string fen_n = Source::undo();
	interpret_message(fen_n);
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	string fen_n = Source::new_game();
	interpret_message(fen_n);
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	int level = this->comboBox1->SelectedIndex;
	int changes_level = Source::set_level(level);
}
private: System::Void textBox1_TextChanged_1(System::Object^ sender, System::EventArgs^ e) {
	this->label_info->Text = "Moved";
}
private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == 13)
	{
		make_move();
	}
}
};
}
