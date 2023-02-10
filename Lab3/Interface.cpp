#include "Interface.h"
#include "AVL_tree.h"


using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    ADLab31::MyForm form;
    Application::Run(% form);
    form.Close();
}