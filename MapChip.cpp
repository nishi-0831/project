#include "MapChip.h"
#include "DxLib.h"
#include "Source/Screen.h"
#include <assert.h>
namespace
{
	//同じ名前の変数は後でまとめましょう
	const int IMAGE_SIZE = { 32 };
	//画像のチップ数
	const int MAP_CHIP_WIDTH = { 16 };
	const int MAP_CHIP_HEIGHT = { 12 };
	//マップのチップ数
	
	//マップチップウィンドウの並び数
	const int MAP_CHIP_NUM_X = { 8 };
	const int MAP_CHIP_NUM_Y = { 24 };

	//縦
	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y};
}
MapChip::MapChip()
	: GameObject()
{
	//bgHandle = std::vector<int>(MAP_CHIP_HEIGHT * MAP_CHIP_WIDTH, -1);
	bgHandle.resize(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT);
	int a = LoadGraph("bg.png", 0);
	LoadDivGraph("bg.png", 
		MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, 
		MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, 
		IMAGE_SIZE, IMAGE_SIZE,
		bgHandle.data());
}

MapChip::~MapChip()
{
	for (int i = 0; i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT; i++)
	{
		if (bgHandle[i] != -1)
		{
			DeleteGraph(bgHandle[i]);
			bgHandle[i] = -1;
		}
	}
}

void MapChip::Update()
{
}

void MapChip::Draw()
{
	
	int topLeft_x = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int topLeft_y = 0;
	int bottomRight_x = Screen::WIDTH;
	int bottomRight_y = MAP_CHIP_WIN_HEIGHT;
	DrawBox(topLeft_x, topLeft_y, bottomRight_x, bottomRight_y, GetColor(255, 0, 0), FALSE,3);

	for (int y = 0; y < MAP_CHIP_NUM_Y;y++)
	{
		for (int x = 0; x < MAP_CHIP_NUM_X;x++)
		{	
			////グリッド描画していく
			//
			////縦線
			//int verticalLineX = topLeft_x + x * IMAGE_SIZE;
			//DrawLine(verticalLineX, 0, verticalLineX, MAP_CHIP_WIN_HEIGHT, GetColor(255, 255, 255));
			////横線も
			//int holizontalLineY = y * IMAGE_SIZE;
			//DrawLine(topLeft_x, holizontalLineY, Screen::WIDTH, holizontalLineY, GetColor(255, 255, 255));


			int handle = bgHandle[y * MAP_CHIP_NUM_X + x];
			if (handle != -1)
			{
				DrawGraph(topLeft_x + x * IMAGE_SIZE, y * IMAGE_SIZE, handle, TRUE);
			}
		}
	}
}
