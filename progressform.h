//---------------------------------------------------------------------------

#ifndef progressformH
#define progressformH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TProgress_form : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *ProgressBar1;
private:	// User declarations
public:		// User declarations
	__fastcall TProgress_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProgress_form *Progress_form;
//---------------------------------------------------------------------------
#endif
