//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "progressform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProgress_form *Progress_form;
//---------------------------------------------------------------------------
__fastcall TProgress_form::TProgress_form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
