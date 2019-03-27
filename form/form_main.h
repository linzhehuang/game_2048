//---------------------------------------------------------------------------

#ifndef form_mainH
#include "../view/view.hpp"
#include "../data/file.hpp"
#include <Classes.hpp>
#include <Menus.hpp>
#include <Controls.hpp>
#include <MPlayer.hpp>
#include <ExtCtrls.hpp>
#define form_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N2;
        TMenuItem *N5;
        TMenuItem *N6;
        TMediaPlayer *music;
        TTimer *Timer1;
        TMenuItem *N3;
        TMenuItem *N4;
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
        View *view;
        Grid *grid;
        File *file;
        //
        void Redraw();
        void NewGame();
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
