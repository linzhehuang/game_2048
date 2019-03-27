#ifndef VIEW_HPP
#define VIEW_HPP

#include "renderer.hpp"
#include "../data/grid.hpp"

class View:public Renderer {
public:
        View(PIXEL width,PIXEL height,Graphics::TCanvas *pCanvas):
        Renderer(width,height) {
                canvas = pCanvas;
                InitalLayout();
                InitalColor();
        }
	void Clear() {
                RenderFilledRectangle(
                NewFilledRectangle(0x00ffffff,0,0,bitmap->Width,bitmap->Height)
                );
        }
        void Refresh() {
                canvas->CopyRect(GetRect(),context,GetRect());
        }
	//
        void RenderBackground() {
                RenderFilledRectangle(
                NewFilledRectangle(
                BGCOLOR,
                0,0,
                bitmap->Width,bitmap->Height)
                );
        }
        void RenderScore(int score) {
                RenderText(
                NewText(
                AnsiString(score),SCORE_COLOR,12,
                bitmap->Width/2,30)
                );
        }
        void RenderGrid() {
                RenderFilledRectangle(
                NewFilledRectangle(
                GRID_BGCOLOR,
                GRID_LEFT,GRID_TOP,
                GRID_LEFT+GRID_SIZE,GRID_TOP+GRID_SIZE)
                );
        }
        void RenderTile(Grid &grid) {
                TColor tileColor = 0x00ffffff;
                int tileLeft = 0,tileTop = 0;
                int num = 0;

                for(int i = 0;i < 4;i++) {
                        tileTop = GRID_TOP +
                        (TILE_SPACE+TILE_SIZE)*i + TILE_SPACE;
                        for(int j = 0;j < 4;j++) {
                                tileLeft = GRID_LEFT +
                                (TILE_SPACE+TILE_SIZE)*j + TILE_SPACE;
                                num = grid.GetData(i,j);

                                RenderFilledRectangle(
                                NewFilledRectangle(
                                TILE_BGCOLORS[NumToColorIndex(num)],
                                tileLeft,tileTop,
                                tileLeft+TILE_SIZE,tileTop+TILE_SIZE)
                                );

                                if(num > 0 && num <= 4)
                                        tileColor = 0x00333333;
                                else
                                        tileColor = 0x00ffffff;

                                if(num > 0) {
                                        RenderText(
                                        NewText(AnsiString(num),tileColor,10,
                                        tileLeft + (TILE_SIZE/2),
                                        tileTop + (TILE_SIZE/2))
                                        );
                                }
                        }
                }
        }
        void RenderGameOver(int score) {
                RenderBackground();
                RenderText(
                NewText(
                "Game Over",0xa5b0be,18,
                bitmap->Width/2,bitmap->Height/2-20)
                );
                RenderText(
                NewText(
                AnsiString(score),SCORE_COLOR,12,
                bitmap->Width/2,bitmap->Height/2+20)
                );
        }
private:
        Graphics::TCanvas *canvas;
        //Layout
        PIXEL GRID_LEFT;
        PIXEL GRID_TOP;
        PIXEL GRID_SIZE;

        PIXEL TILE_SIZE;
        PIXEL TILE_SPACE;
        //Color
        TColor BGCOLOR;
        TColor SCORE_COLOR;
        TColor GRID_BGCOLOR;
        TColor TILE_BGCOLORS[13];
        //
        void InitalLayout() {
                GRID_LEFT = 20;
                GRID_TOP = 60;

                TILE_SIZE = 60;
                TILE_SPACE = 10;

                GRID_SIZE = (TILE_SIZE + TILE_SPACE)*4 + TILE_SPACE;
        }
        void InitalColor() {
                BGCOLOR = 0xeff8fa;
                SCORE_COLOR = 0x00333333;
                GRID_BGCOLOR = 0x00a5b0be;

                TILE_BGCOLORS[0] = 0x00b6c3d1;  //0
                TILE_BGCOLORS[1] = 0x00dee7f4;  //2
                TILE_BGCOLORS[2] = 0x00cae3f3;  //4
                TILE_BGCOLORS[3] = 0x0075b4f8;  //8

                TILE_BGCOLORS[4] = 0x005a92ff;  //16
                TILE_BGCOLORS[5] = 0x002791f6;  //32
                TILE_BGCOLORS[6] = 0x002c63f4;  //64
                TILE_BGCOLORS[7] = 0x006ed2f4;  //128

                TILE_BGCOLORS[8] = 0x0067ceef;  //256
                TILE_BGCOLORS[9] = 0x0032a3ff;  //512
                TILE_BGCOLORS[10] = 0x0034caf3; //1024
                TILE_BGCOLORS[11] = 0x001ac6f6; //2048

                TILE_BGCOLORS[12] = 0x00446655; //4096
        }
        //
        int NumToColorIndex(int num) {
                int index = 0;
                if(num == 0) return index;

                while(num != 0) {
                        index++;
                        num = num >> 1;
                }

                return (index-1);
        }
};

#endif