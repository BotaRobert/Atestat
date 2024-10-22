#include <fmx.h>
#pragma hdrstop
#include "Unit1.h"
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
//---------------------------------------------------------------------------
TForm1 *Form1;
char s[4]=" XO";
int a[4][4];
struct mut{
	int l,c;
};
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	GameState->TextSettings->Font->Size=30;
	GameState->TextSettings->Font->Family="Calibri";
	GameState->TextSettings->Font->Style = TFontStyles() << TFontStyle::fsBold;
	GameState->TextSettings->HorzAlign = TTextAlign::Center;
    PlayButton->TextSettings->Font->Size=30;
	PlayButton->TextSettings->Font->Family="Calibri";
	PlayButton->TextSettings->Font->Style = TFontStyles() << TFontStyle::fsBold;
	ChooseX->TextSettings->Font->Family="Comic Sans MS";
	ChooseX->TextSettings->Font->Size = 70;
	ChooseX->TextSettings->Font->Style = TFontStyles() << TFontStyle::fsBold;
	ChooseO->TextSettings->Font->Family="Comic Sans MS";
	ChooseO->TextSettings->Font->Size = 70;
	ChooseO->TextSettings->Font->Style = TFontStyles() << TFontStyle::fsBold;
    Pick->TextSettings->Font->Size=30;
	Pick->TextSettings->Font->Family="Calibri";
	Pick->TextSettings->Font->Style = TFontStyles() << TFontStyle::fsBold;
	Pick->TextSettings->HorzAlign = TTextAlign::Center;
}
//---------------------------------------------------------------------------
float TERMINAT()
{
    int i,j;
	if((a[1][1]==a[2][2] && a[2][2]==a[3][3]) || (a[1][3]==a[2][2] && a[2][2]==a[3][1]))
        return a[2][2];//castigat pe o diagonala sau exista o diagonala care are doar elemente 0, deci jocul continua
    for(i=1;i<=3;i++)
    {
		if(a[i][1]==a[i][2] && a[i][2]==a[i][3] && a[i][1]!=0)
			return a[i][1]; //castigat pe orizontala
        if(a[1][i]==a[2][i] && a[2][i]==a[3][i] && a[1][i]!=0)
			return a[1][i]; //castigat pe verticala
	}
	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
            if(a[i][j]==0)
				return 0; //continua jocul
    return 1.5;//remiza: s-a ramas fara spatii libere de jucat
}
//---------------------------------------------------------------------------
int JUCATOR()
{
    int contorX=0,contorO=0,i,j;
    for(i=1;i<=3;i++)
        for(j=1;j<=3;j++)
            if(a[i][j]==1)
                contorX++;
            else
                if(a[i][j]==2)
                    contorO++;
    if(contorX==contorO) //presupunem in contextul programului ca diferenta dintre contorX si contorO este de maxim 1
        return 1;//pentru un numar egal de X si O pe tabla, P1 este la mutare
    return 2; //altfel, P2 urmeaza la rand
}
//---------------------------------------------------------------------------
float MINIMAX(mut &mutare,int depth)
{
    int i,j;
    float val,valMut;
    float final=TERMINAT();
    if(final)
	{
        return final;
    }
    if(JUCATOR()==1)//randul jucatorului P1, care joaca cu X
    {
        val=10;
        for(i=1;i<=3;i++)
			for(j=1;j<=3;j++)
                if(a[i][j]==0)
                {
                    a[i][j]=1;//foloseste mutarea i,j
					valMut=MINIMAX(mutare,depth+1);//evalueaza cel mai bun rezultat posibil al jocului pentru P1 cu mutarea i,j
					if(valMut<val)
                    {
                        val=valMut;
                        if(depth==0)
                        {
                            mutare.l=i;
                            mutare.c=j;
                        }
                    }//determina daca mutarea i,j este mai buna pentru P1 decat mutarile evaluate anterior
                    a[i][j]=0;//retrage mutarea facuta pentru a evalua restul mutarilor posibile
                }
        return val;
    }
    else//randul jucatorului P2, care joaca cu O
    {
        val=-10;
        for(i=1;i<=3;i++)
            for(j=1;j<=3;j++)
                if(a[i][j]==0)
                {
                    a[i][j]=2;//foloseste mutarea i,j
                    valMut=MINIMAX(mutare,depth+1);//evalueaza cel mai bun rezultat posibil al jocului pentru P2 cu mutarea i,j
                    if(valMut>val)
                    {
                        val=valMut;
                        if(depth==0)
                        {
                            mutare.l=i;
                            mutare.c=j;
                        }
                    }//determina daca mutarea i,j este mai buna pentru P2 decat mutarile evaluate anterior
                    a[i][j]=0;//retrage mutarea facuta pentru a evalua restul mutarilor posibile
                }
        return val;
    }
}
//---------------------------------------------------------------------------

void mutaP1(TButton* clickedButton)
{
	clickedButton->Text=s[JUCATOR()];
	clickedButton->TextSettings->Font->Size = 70;
	clickedButton->TextSettings->Font->Style = TFontStyles() << TFontStyle::fsBold;
	clickedButton->TextSettings->FontColor=TAlphaColorRec::Blue;
	clickedButton->TextSettings->Font->Family="Comic Sans MS";
	clickedButton->Enabled=false;
	mut mutareP1;
	mutareP1.l=clickedButton->Name[2]-'0';
	mutareP1.c=clickedButton->Name[3]-'0';
	a[mutareP1.l][mutareP1.c]=JUCATOR();
}
//---------------------------------------------------------------------------

void mutaP2()
{
    mut mutareP2;
	MINIMAX(mutareP2,0);
	a[mutareP2.l][mutareP2.c]=JUCATOR();
	for(int i = 0; i < Form1->ComponentCount; i++)
	{
		TButton *button = dynamic_cast<TButton*>(Form1->Components[i]);
		if(button && button->Name[2]-'0'==mutareP2.l && button->Name[3]-'0'==mutareP2.c)
		{
			button->Text=s[a[mutareP2.l][mutareP2.c]];
			button->TextSettings->Font->Size = 70;
			button->TextSettings->Font->Style = TFontStyles() << TFontStyle::fsBold;
			button->TextSettings->FontColor=TAlphaColorRec::Orange;
			button->TextSettings->Font->Family="Comic Sans MS";
			button->Enabled=false;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonClick(TObject *Sender)
{
	TButton *clickedButton = dynamic_cast<TButton*>(Sender);
	mutaP1(clickedButton);
	if(!TERMINAT())
		mutaP2();
	float terminat=TERMINAT();
	if(terminat)
	{
		for(int i = 0; i < Form1->ComponentCount; i++)
		{
			TButton *button = dynamic_cast<TButton*>(Form1->Components[i]);
			if(button && button->Tag == 1)
				button->Enabled = false;
		}
		PlayButton->Visible=true;
		PlayButton->Text="Play Again";
        ChooseX->Visible=true;
		ChooseO->Visible=true;
        ChooseOBack->Visible=true;
		ChooseXBack->Visible=true;
		PlayBack->Visible=true;
		if(terminat==1.5)
		{
			GameState->Text="DRAW";
			GameState->TextSettings->FontColor=TAlphaColorRec::Purple;
            return;
		}
		if((terminat==1 && ChooseX->Enabled==false) || (terminat==2 && ChooseO->Enabled==false))
		{
			GameState->Text="YOU WON!";
			GameState->TextSettings->FontColor=TAlphaColorRec::Green;
		}
		else
		{
			GameState->Text="YOU LOST...";
			GameState->TextSettings->FontColor=TAlphaColorRec::Red;
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ChooseXClick(TObject *Sender)
{
	ChooseX->Enabled=false;
	ChooseO->Enabled=true;
	PlayButton->Enabled=true;
	Pick->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChooseOClick(TObject *Sender)
{
	ChooseX->Enabled=true;
	ChooseO->Enabled=false;
	PlayButton->Enabled=true;
	Pick->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PlayButtonClick(TObject *Sender)
{
	int i,j;
	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			a[i][j]=0;
	for(int i = 0; i < this->ComponentCount; i++)
	{
		TButton *button = dynamic_cast<TButton*>(Form1->Components[i]);
		if(button && button->Tag == 1)
		{
			button->Enabled = true;
			button->Visible = true;
			button->Text="";
        }
	}
	GameState->TextSettings->FontColor=TAlphaColorRec::Black;
	GameState->Text="Choose Your Move!";
	GameState->Visible=true;
	PlayButton->Visible=false;
	ChooseX->Visible=false;
	ChooseO->Visible=false;
	ChooseOBack->Visible=false;
	ChooseXBack->Visible=false;
	PlayBack->Visible=false;
	if(ChooseO->Enabled==false)
        mutaP2();
}
//---------------------------------------------------------------------------




