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
	//外枠
	int topLeftX = 0 + LEFT_MERGIN;
	int topLeftY = 0 + TOP_MERGIN;
	int bottomLightX = MAP_IMAGE_SIZE * MAP_WIDTH + LEFT_MERGIN;
	int bottomLightY = MAP_IMAGE_SIZE * MAP_HEIGHT + TOP_MERGIN;
	DrawBox(topLeftX, topLeftY, bottomLightX-1, bottomLightY-1, GetColor(122, 122, 122), FALSE,3);

	//グリッド書きたい
	//まず縦線 IMAGE_SIZEの間隔でMAP_WIDTH回だけ書く
	
	//x,yそれぞれ外枠の最初に書く側、0番目の行、列で外枠を塗りつぶしてしまっている
	//イテレータを1から始めるとか?
	for (int i = 1;i < MAP_WIDTH;i++)
	{
		//マージンも考慮しないとね
		//起点も終点もxは同じ。縦線だから
		int x = i * MAP_IMAGE_SIZE + LEFT_MERGIN;

		//起点のy
		int startY = topLeftY;
		//終点のy
		int endY = bottomLightY;

		DrawLine(x, startY, x, endY, GetColor(255, 0, 0), 1);
	}
	for (int i = 1;i < MAP_HEIGHT;i++)
	{
		//起点も終点もyは同じ。横線だから
		int y = i * MAP_IMAGE_SIZE + TOP_MERGIN;

		//起点のx
		int startX = topLeftX;
		int endX = bottomLightX;

		DrawLine(startX, y, endX, y, GetColor(255, 0, 0), 1);
	}
}
