#ifndef RENDERER_H
#define RENDERER_H

typedef int PIXEL;

struct TEXT {
        AnsiString text;
        TColor textColor;
        PIXEL textSize;
        PIXEL centerX;
        PIXEL centerY;
};
struct FILLED_RECTANGLE {
        TColor filledColor;
        PIXEL beginX;
        PIXEL beginY;
        PIXEL endX;
        PIXEL endY;
};
struct LINE {
        TColor filledColor;
        PIXEL lineWidth;
        PIXEL beginX;
        PIXEL beginY;
        PIXEL endX;
        PIXEL endY;
};

class Renderer {
public:
        Renderer(PIXEL width,PIXEL height) {
                bitmap = new Graphics::TBitmap();
                bitmap->Width = width;
                bitmap->Height = height;
                context = bitmap->Canvas;
                
                /*
		//Some examples are as follow.
                RenderText(NewText("H",0x000099ff,50,25,25));
                RenderFilledRectangle(NewFilledRectangle(0x000099ff,0,25,25,50));
                RenderLine(NewLine(0x00225566,1,0,0,60,60));
                */
        }
        ~Renderer() {
                delete bitmap;
        }
protected:
        Graphics::TBitmap *bitmap;
        Graphics::TCanvas *context;

        void RenderText(TEXT text) {
                PIXEL textWidth = 0;
                PIXEL textHeight = 0;
                context->Brush->Style = bsClear;
                context->Font->Color = text.textColor;
                context->Font->Size = text.textSize;
                context->Font->Name = "ËÎÌו";
                context->Font->Style = TFontStyles() << fsBold;
                
                textWidth = context->TextWidth(text.text);
                textHeight = context->TextHeight(text.text);
                context->TextOut(text.centerX-textWidth/2,text.centerY-textHeight/2,text.text);
        }
        void RenderFilledRectangle(FILLED_RECTANGLE filledRectangle) {
                context->Brush->Color = filledRectangle.filledColor;
                context->Pen->Color = filledRectangle.filledColor;
                context->Pen->Width = 1;
                context->Rectangle(filledRectangle.beginX,filledRectangle.beginY,
                filledRectangle.endX,filledRectangle.endY);
        }
        void RenderLine(LINE line) {
                context->Pen->Color = line.filledColor;
                context->Pen->Width = line.lineWidth;
                context->MoveTo(line.beginX,line.beginY);
                context->LineTo(line.endX,line.endY);
        }
        //
        Graphics::TCanvas *GetContext() {
                return context;
        }
        TRect GetRect() {
                return  Rect(0,0,bitmap->Width,bitmap->Height);
        }

        //
        TEXT NewText(AnsiString t,TColor tc,PIXEL ts,PIXEL cx,PIXEL cy) {
                TEXT *tmp = new TEXT;
                tmp->text = t;
                tmp->textColor = tc;
                tmp->textSize = ts;
                tmp->centerX = cx;
                tmp->centerY = cy;
                return *tmp;
        }
        FILLED_RECTANGLE NewFilledRectangle(TColor fc,PIXEL bx,PIXEL by,PIXEL ex,PIXEL ey) {
                FILLED_RECTANGLE *tmp = new FILLED_RECTANGLE;
                tmp->filledColor = fc;
                tmp->beginX = bx;
                tmp->beginY = by;
                tmp->endX = ex;
                tmp->endY = ey;
                return *tmp;
        }
        LINE NewLine(TColor fc,PIXEL lw,PIXEL bx,PIXEL by,PIXEL ex,PIXEL ey) {
                LINE *tmp = new LINE;
                tmp->filledColor = fc;
                tmp->lineWidth = lw;
                tmp->beginX = bx;
                tmp->beginY = by;
                tmp->endX = ex;
                tmp->endY = ey;
                return *tmp;
        }
};

#endif