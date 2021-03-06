#include "WgBackground.h"
#include "../CPicturesStorage.h"
#include "../CFontStorage.h"
//#include "../lib/Picture.h"
//#include "../lib/TFont/TFont.h"

//#include "iostream"
//using namespace std;


WgBackground::WgBackground(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode)
{
	// -- parameters
	scrWidth = AscrWidth;
	scrHeight = AscrHeight;
	posX = AposX; // horizontal position in the grid
	posY = AposY; // vertical position in the grid
	mode = Amode;
	color = 1+rand()%10;
	
	isShadows = true; // shadows on
	
	// -- create one grid step
	gridStep.horizontal = scrWidth/GRID_HORIZONTAL;
	gridStep.vertical = scrHeight/GRID_VERTICAL;
	
	// -- convert position in the grid to coordinates
	// -- -- it is top-left corner
	x = gridStep.horizontal * posX;
	y = gridStep.vertical * posY;
	
	// -- select widget size from mode
	switch (mode){
		case md1x1: {sizeX = 1; sizeY = 1; break;}
		case md1x2: {sizeX = 1; sizeY = 2; break;}
		case md1x3: {sizeX = 1; sizeY = 3; break;}
		case md2x8: {break;}
	}
}

WgBackground::~WgBackground()
{
	
}

void WgBackground::setTextColor(wgColor c){
	if (c==clBlue) FontStorage->getFont((char*)"arialBold")->SetColour(0,121,194);
	else if (c==clCyan) FontStorage->getFont((char*)"arialBold")->SetColour(37,196,166);
	else if (c==clGreen) FontStorage->getFont((char*)"arialBold")->SetColour(139,209,93);
	else if (c==clHighBlue) FontStorage->getFont((char*)"arialBold")->SetColour(0,185,241);
	else if (c==clHighPurple) FontStorage->getFont((char*)"arialBold")->SetColour(139,91,164);
	else if (c==clLazyYellow) FontStorage->getFont((char*)"arialBold")->SetColour(201,208,34);
	else if (c==clOrange) FontStorage->getFont((char*)"arialBold")->SetColour(240,115,30);
	else if (c==clPurple) FontStorage->getFont((char*)"arialBold")->SetColour(183,46,145);
	else if (c==clYellow) FontStorage->getFont((char*)"arialBold")->SetColour(255,200,50);
	else if (c==clHaki) FontStorage->getFont((char*)"arialBold")->SetColour(0, 85, 81);
}

void WgBackground::setFillColor(wgColor c)
{
	if (c==clWhite) Fill(255,255,255,1);
	else if (c==clBlue) Fill(0,121,194,1);
	else if (c==clCyan) Fill(37,196,166,1);
	else if (c==clGreen) Fill(139,209,93,1);
	else if (c==clHighBlue) Fill(0,185,241,1);
	else if (c==clHighPurple) Fill(139,91,164,1);
	else if (c==clLazyYellow) Fill(201,208,34,1);
	else if (c==clOrange) Fill(240,115,30,1);
	else if (c==clPurple) Fill(183,46,145,1);
	else if (c==clYellow) Fill(255,200,50,1);	
}


void WgBackground::render()
{
	// -- render widget background blocks
	for (int i=0; i<sizeX; i++){
		for (int j=0; j<sizeY; j++){
			if (j==0) setFillColor(color);
			else setFillColor(clWhite);
			Rect(x+gridStep.horizontal*i,
				 y-gridStep.vertical*j,
				 gridStep.horizontal, gridStep.vertical);
		}
	}
	if (isShadows)
	{
		// -- render widget shadows
		int w = gridStep.horizontal * sizeX; //get width in px of widget block
		int h = gridStep.vertical *sizeY; //get height in px of widget block
		int Y = y - gridStep.vertical*(sizeY-1); //get Y coordinates of bottom-left corner (y,x - top-left corner)
		
		// -- -- render corners
		PicStorage->WgShadows->lt->render(x-9, Y+h);
		PicStorage->WgShadows->rt->render(x+w, Y+h);
		PicStorage->WgShadows->lb->render(x-9, Y-9);
		PicStorage->WgShadows->rb->render(x+w, Y-9);
		
		// -- -- render top and bot
		for (int i=0; i<w; i++){
			PicStorage->WgShadows->t->render(x+i, Y+h);
			PicStorage->WgShadows->b->render(x+i, Y-9);
		}
		
		// -- -- render left and right
		for (int i=0; i<h; i++){
			PicStorage->WgShadows->l->render(x-9, Y+i);
			PicStorage->WgShadows->r->render(x+w, Y+i);
		}
	}
}
