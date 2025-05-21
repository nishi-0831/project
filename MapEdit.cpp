#include "MapEdit.h"
#include "DxLib.h"
MapEdit::MapEdit()
	: GameObject(),myMap_(MAP_WIDTH * MAP_HEIGHT,-1)//�����l��-1��20*20�̃}�b�v
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

		//�N�_��y
		int startY = topLeftY;
		//�I�_��y
		int endY = bottomLightY;

		DrawLine(x, startY, x, endY, GetColor(255, 0, 0), 1);
	}
	for (int i = 1;i < MAP_HEIGHT;i++)
	{
		//�N�_���I�_��y�͓����B����������
		int y = i * MAP_IMAGE_SIZE + TOP_MARGIN;

		//�N�_��x
		int startX = topLeftX;
		int endX = bottomLightX;

		DrawLine(startX, y, endX, y, GetColor(255, 0, 0), 1);
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
