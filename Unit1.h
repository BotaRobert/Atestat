//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *b11;
	TButton *b12;
	TButton *b13;
	TButton *b21;
	TButton *b22;
	TButton *b23;
	TButton *b32;
	TButton *b31;
	TButton *b33;
	TLabel *GameState;
	TRectangle *boardBack;
	TButton *PlayButton;
	TButton *ChooseX;
	TButton *ChooseO;
	TRectangle *PlayBack;
	TRectangle *ChooseXBack;
	TRectangle *ChooseOBack;
	TLabel *Pick;
	void __fastcall ButtonClick(TObject *Sender);
	void __fastcall PlayButtonClick(TObject *Sender);
	void __fastcall ChooseXClick(TObject *Sender);
	void __fastcall ChooseOClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
