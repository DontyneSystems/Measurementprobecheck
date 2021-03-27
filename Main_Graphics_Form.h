//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//© Dontyne Systems Ltd 2021

#ifndef Main_Graphics_FormH
#define Main_Graphics_FormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TEquator_Helical_Graphics_Check_form : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox2;
	TLabel *Label10;
	TLabel *Label1;
	TLabel *Label5;
	TComboBox *ComboBoxFlankcut;
	TEdit *gearzposedit;
	TComboBox *ComboBoxwidthdensity;
	TEdit *gearthetaedit;
	TCheckBox *CheckBoxunits;
	TComboBox *ComboBoxtoothtomeasure;
	TRadioGroup *RadioGroupfinish;
	TGroupBox *GroupBox1;
	TLabel *Label8;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *stemdiaedit;
	TEdit *stemlengthedit;
	TEdit *balldiaedit;
	TSaveDialog *SaveDialog2;
	TMainMenu *MainMenu1;
	TPanel *Panel1;
	TLabel *Labelrotx;
	TLabel *Labelroty;
	TLabel *Labelrotz;
	TLabel *Labelzoom;
	TLabel *Label2;
	TBitBtn *resetButton;
	TPanel *Panel3Dcolor;
	TLabel *Label3;
	TTrackBar *TrackBarGreen;
	TTrackBar *TrackBarRed;
	TTrackBar *TrackBarBlue;
	TRadioButton *RadioButtonprt;
	TRadioButton *RadioButtonbk;
	TTrackBar *TrackBarX;
	TTrackBar *TrackBarY;
	TTrackBar *TrackBarZ;
	TTrackBar *TrackBarZoom;
	TMemo *Memo1;
	TButton *Button4;
	TComboBox *ComboBoxline;
	TCheckBox *CheckBoxshowstylus;
	TButton *Buttonright;
	TButton *Buttonleft;
	TButton *fontbutton2;
	TButton *fontbutton1;
	TCheckBox *CheckBoxshowtable;
	TButton *Buttonupdate;
	TCheckBox *CheckBox4teeth;
	TLabel *Labelunits;
	TLabel *Labelcopyright;
	TLabel *Label9;
	TEdit *totalspanedit;
	TButton *Button2;
	TRadioGroup *RadioGroupangulardatum;
	TCheckBox *CheckBoxnormals;
	TCheckBox *CheckBoxshowsides;
	TComboBox *ComboBoxprobe;
	TLabel *Labelteethn;
	TLabel *Label4;
	TEdit *approachdistedit;
	TCheckBox *CheckBoxbtransparent;
	TPanel *OpenGLAPPanel;

	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall OpenGLAPPanelPaint(TObject *Sender);
	void __fastcall OpenGLAPPanelClick(TObject *Sender);
	void __fastcall OpenGLAPPanelInit(TObject *Sender);
	void __fastcall OpenGLAPPanelMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall OpenGLAPPanelMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall OpenGLAPPanelMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);

	void __fastcall resetButtonClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall TrackBarBlueChange(TObject *Sender);
	void __fastcall fontbutton2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall fontbutton1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall LabelrotxMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall LabelrotyMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall LabelrotzMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall CheckBoxshowstylusMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall ButtonupdateClick(TObject *Sender);
	void __fastcall Memo1Exit(TObject *Sender);
	void __fastcall ComboBoxlineChange(TObject *Sender);
	void __fastcall ButtonrightMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ButtonleftClick(TObject *Sender);
	void __fastcall CheckBoxunitsMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall gearthetaeditChange(TObject *Sender);
	void __fastcall gearthetaeditEnter(TObject *Sender);
	void __fastcall gearthetaeditExit(TObject *Sender);
	void __fastcall gearzposeditChange(TObject *Sender);
	void __fastcall gearzposeditEnter(TObject *Sender);
	void __fastcall gearzposeditExit(TObject *Sender);
	void __fastcall stemdiaeditChange(TObject *Sender);
	void __fastcall stemdiaeditEnter(TObject *Sender);
	void __fastcall stemdiaeditExit(TObject *Sender);
	void __fastcall balldiaeditChange(TObject *Sender);
	void __fastcall balldiaeditEnter(TObject *Sender);
	void __fastcall balldiaeditExit(TObject *Sender);
	void __fastcall stemlengtheditChange(TObject *Sender);
	void __fastcall stemlengtheditEnter(TObject *Sender);
	void __fastcall stemlengtheditExit(TObject *Sender);
	void __fastcall totalspaneditChange(TObject *Sender);
	void __fastcall totalspaneditEnter(TObject *Sender);
	void __fastcall totalspaneditExit(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall LabelzoomMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ComboBoxprobeSelect(TObject *Sender);
    void __fastcall Setmaintextboxes(void);
	void __fastcall approachdisteditChange(TObject *Sender);
	void __fastcall approachdisteditEnter(TObject *Sender);
	void __fastcall approachdisteditExit(TObject *Sender);
	void __fastcall CheckBoxbtransparentMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormDestroy(TObject *Sender);



// OPenGL Directly
private:	// User declarations
    HDC hdc;
	HGLRC hrc;
	int PixelFormat;
public:		// User declarations
	void __fastcall SetPixelFormatDescriptor();
    void __fastcall SetupRC(void);



	__fastcall TEquator_Helical_Graphics_Check_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEquator_Helical_Graphics_Check_form *Equator_Helical_Graphics_Check_form;
//---------------------------------------------------------------------------
#endif
