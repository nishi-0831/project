#include "MapEdit.h"
#include "DxLib.h"
MapEdit::MapEdit()
	: GameObject(),myMap_(MAP_WIDTH * MAP_HEIGHT,-1)//初期値を-1で20*20のマップ
{
	
}

MapEdit::~MapEdit()
{

}

void MapEdit::Update()
{

}

void MapEdit::Draw()
{
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	int topLeftX = 0 + LEFT_MARGIN;
	int topLeftY = 0 + TOP_MARGIN;
	int bottomLightX = MAP_IMAGE_SIZE * MAP_WIDTH + LEFT_MARGIN;
	int bottomLightY = MAP_IMAGE_SIZE * MAP_HEIGHT + TOP_MARGIN;
	DrawBox(topLeftX, topLeftY, bottomLightX-1, bottomLightY-1, GetColor(122, 122, 122), FALSE,3);

	for (int i = 1;i < MAP_WIDTH;i++)
	{
		int x = i * MAP_IMAGE_SIZE + LEFT_MARGIN;

		//起点のy
		int startY = topLeftY;
		//終点のy
		int endY = bottomLightY;

		DrawLine(x, startY, x, endY, GetColor(255, 0, 0), 1);
	}
	for (int i = 1;i < MAP_HEIGHT;i++)
	{
		//起点も終点もyは同じ。横線だから
		int y = i * MAP_IMAGE_SIZE + TOP_MARGIN;

		//起点のx
		int startX = topLeftX;
		int endX = bottomLightX;

		DrawLine(startX, y, endX, y, GetColor(255, 0, 0), 1);
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
