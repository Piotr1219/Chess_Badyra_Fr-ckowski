#include "MyForm.h"
#include <string>

using namespace std;         // <=== Uh-oh

using namespace System;

using namespace System::Windows::Forms;

[STAThread]

void main(cli::array<System::String^>^ args)

{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    chessBadyraFrackowskigui::MyForm form;

    Application::Run(% form);

}