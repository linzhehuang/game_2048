//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        grid = new Grid();
        view = new View(330,410,Form1->Canvas);
        file = new File();
        music->FileName = file->GetCurrentPath() + "bg_music.wav";
        music->Open();
        NewGame();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
        Redraw();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        Grid oldGrid = *grid;
        //Bind the event
        switch(Key) {
                case 37:
                grid->MoveByDirection(Grid::DIRECT_LEFT);
                break;
                case 38:
                grid->MoveByDirection(Grid::DIRECT_UP);
                break;
                case 39:
                grid->MoveByDirection(Grid::DIRECT_RIGHT);
                break;
                case 40:
                grid->MoveByDirection(Grid::DIRECT_DOWN);
                break;
        }
        //
        if(oldGrid != *grid) {
                grid->GenerateNewValue();
        }
        //
        Redraw();
}
//---------------------------------------------------------------------------

void TForm1::Redraw()
{
        if(grid->IsEnd()) {
                view->Clear();
                view->RenderGameOver(grid->GetScore());
                view->Refresh();
        }
        else
        {
                view->Clear();
                view->RenderBackground();
                view->RenderScore(grid->GetScore());
                view->RenderGrid();
                view->RenderTile(*grid);
        }

        view->Refresh();
}
//---------------------------------------------------------------------------
void TForm1::NewGame()
{
        grid->ClearGridData();
        grid->ClearScore();
        grid->GenerateNewValue();
        grid->GenerateNewValue();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
        if(grid->IsEnd()) {
                ShowMessage("游戏已结束，无法存档！");
                return;
        }
        file->SaveDataFile(*grid);
        ShowMessage("存档成功！");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        file->ReadDataFile(*grid);
        Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
        NewGame();
        Redraw();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
        if(music->Mode == mpPaused) {
                music->Play();
        }
        else {
                music->Pause();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        if(music->Mode == mpStopped) {
                music->Play();
        }
}
//---------------------------------------------------------------------------

