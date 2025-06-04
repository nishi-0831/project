#include "MapChip.h"
#include "DxLib.h"
#include "Source/Screen.h"
#include "ImGui/imgui.h"
#include "global.h"
#include <assert.h>
#include "Input.h"

#define test 0

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

#if test
	std::map<Point, int> bgHandleMap;

#else
	std::map<int, int> bgHandleMap;
#endif
	std::pair<Point, int> selectedChip;
	//std::pair<int, int> selectedChip;
	/*struct BgHandle
	{
		std::vector<int> index;
		std::vector<int> hImages;
	};*/
	//BgHandle bgHandleMap;
}
MapChip::MapChip()
	: GameObject()
{
	//bgHandle = std::vector<int>(MAP_CHIP_HEIGHT * MAP_CHIP_WIDTH, -1);
	bgHandle.resize(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT);
	//bgHandleMap.index.resize(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT);
	//bgHandleMap.hImages.resize(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT);

	int a = LoadGraph("bg.png", 0);
	LoadDivGraph("bg.png", 
		MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, 
		MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, 
		IMAGE_SIZE, IMAGE_SIZE,
		bgHandle.data());


	int topLeft_x = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int topLeft_y = 0;
	int bottomRight_x = Screen::WIDTH;
	int bottomRight_y = MAP_CHIP_WIN_HEIGHT;

	mapChipArea_ = {
	Screen::WIDTH - MAP_CHIP_WIN_WIDTH,
	0,
	Screen::WIDTH,
	 MAP_CHIP_WIN_HEIGHT
	};

	for (int i = 0;i < bgHandle.size();i++)
	{
		int x = i / MAP_CHIP_WIDTH;
		int y = i % MAP_CHIP_WIDTH;
#if test
		//https://learn.microsoft.com/ja-jp/cpp/error-messages/compiler-errors-2/compiler-error-c2676?view=msvc-170
		//Point型にオーバーロードした演算子を書いてない たぶん 二項演算子<
		Point point = { x,y };
		bgHandleMap.insert(std::make_pair(Point{x,y}, bgHandle[i]));
#else
		bgHandleMap.insert(std::make_pair(i, bgHandle[i]));
#endif
		
	}
	/*LoadDivGraph("bg.png",
		MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT,
		MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT,
		IMAGE_SIZE, IMAGE_SIZE,
		bgHandleMap.hImages.data());*/

	//for()
	SetDrawOrder(-1);
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
	Point mousePos;
	if (GetMousePoint(&mousePos.x , &mousePos.y) == -1)
	{
		return;
	}

	isInMapChipArea_ = (mousePos.x > Screen::WIDTH - MAP_CHIP_WIDTH && mousePos.x < Screen::WIDTH &&
		mousePos.y > 0 && mousePos.y < MAP_CHIP_WIN_HEIGHT);
	if (isInMapChipArea_)
	{

	}
	else
	{
		isInMapChipArea_ = false;
	}
	if (Input::IsButtonDown(Input::Mouse::LEFT))
	{
		Point point = { 0,0 };
		if (IsInMapChipArea(&point))
		{
			//int index = point.y * MAP_CHIP_NUM_X + point.x;
			selectedChip.first = point;
#if test
			selectedChip.second = bgHandleMap[point];
#else
			selectedChip.second = bgHandleMap[point.y * MAP_CHIP_NUM_X + point.x];
#endif
		
			
		}
	}
	
}

void MapChip::Draw()
{
	ImGui::Text("selectedChip[%d,%d] : %d", selectedChip.first.x, selectedChip.first.y, selectedChip.second);
	//ImGui::Separator();
	ImGui::BeginChild("bgHandle Map Viwer", ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar);
	
	for (const auto bg : bgHandleMap)
	{
#if test
		ImGui::Text("bgHandleMap[%d,%d] = %d", bg.first.x, bg.first.y, bg.second);
#else
		ImGui::Text("bgHandleMap[%d] = %d", bg.first, bg.second);
#endif
	}
	ImGui::EndChild();

	Point point = { 0,0 };
	
	for (int y = 0; y < MAP_CHIP_NUM_Y;y++)
	{
		for (int x = 0; x < MAP_CHIP_NUM_X;x++)
		{
			int handle = bgHandle[y * MAP_CHIP_NUM_X + x];
			if (handle != -1)
			{
				DrawGraph(mapChipArea_.x + x * IMAGE_SIZE, y * IMAGE_SIZE, handle, FALSE);
			}
		}
	}
	if (IsInMapChipArea(&point))
	{
		DrawBox(mapChipArea_.x + point.x * IMAGE_SIZE, point.y * IMAGE_SIZE, mapChipArea_.x + point.x * IMAGE_SIZE + IMAGE_SIZE, point.y * IMAGE_SIZE + IMAGE_SIZE, GetColor(0, 255, 0), false, 5);
	}
	DrawBox(mapChipArea_.x + selectedChip.first.x * IMAGE_SIZE, selectedChip.first.y * IMAGE_SIZE, mapChipArea_.x + selectedChip.first.x * IMAGE_SIZE + IMAGE_SIZE, selectedChip.first.y * IMAGE_SIZE + IMAGE_SIZE, GetColor(0, 255, 0), false, 5);
#if 0
	int topLeft_x = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int topLeft_y = 0;
	int bottomRight_x = Screen::WIDTH;
	int bottomRight_y = MAP_CHIP_WIN_HEIGHT;
	DrawBox(topLeft_x, topLeft_y, bottomRight_x, bottomRight_y, GetColor(255, 0, 0), true,3);
	int mx = -1, my = -1;
	GetMousePoint(&mx, &my);
	for (int y = 0; y < MAP_CHIP_NUM_Y;y++)
	{
		for (int x = 0; x < MAP_CHIP_NUM_X;x++)
		{	
			int handle = bgHandle[y * MAP_CHIP_NUM_X + x];
			if (handle != -1)
			{
				DrawGraph(topLeft_x + x * IMAGE_SIZE, y * IMAGE_SIZE, handle, FALSE);
				if (((mx - topLeft_x ) / IMAGE_SIZE  ) == x && (my / IMAGE_SIZE) == y)
				{
					DrawBox(topLeft_x + x * IMAGE_SIZE, y * IMAGE_SIZE, topLeft_x + x * IMAGE_SIZE + IMAGE_SIZE, y * IMAGE_SIZE + IMAGE_SIZE, GetColor(0, 255, 0), false, 5);
				}
			}
		}
	}
#endif
}

bool MapChip::IsInMapChipArea(Point* point)
{
	bool ret = false;

#if 0
	int topLeft_x = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int topLeft_y = 0;
	int bottomRight_x = Screen::WIDTH;
	int bottomRight_y = MAP_CHIP_WIN_HEIGHT;
#endif
#if 0
	int mx = -1, my = -1;
	GetMousePoint(&mx, &my);
	for (int y = 0; y < MAP_CHIP_NUM_Y;y++)
	{
		for (int x = 0; x < MAP_CHIP_NUM_X;x++)
		{
			int handle = bgHandle[y * MAP_CHIP_NUM_X + x];
			if (handle != -1)
			{
				//DrawGraph(topLeft_x + x * IMAGE_SIZE, y * IMAGE_SIZE, handle, FALSE);
				if (((mx - topLeft_x) / IMAGE_SIZE) == x && (my / IMAGE_SIZE) == y)
				{
					//DrawBox(topLeft_x + x * IMAGE_SIZE, y * IMAGE_SIZE, topLeft_x + x * IMAGE_SIZE + IMAGE_SIZE, y * IMAGE_SIZE + IMAGE_SIZE, GetColor(0, 255, 0), false, 5);
					point->x = x;
					point->y = y;
					ret = true;
				}
			}
		}
	}
#endif
	int mx = -1, my = -1;
	GetMousePoint(&mx, &my);
	for (int y = 0; y < MAP_CHIP_NUM_Y;y++)
	{
		for (int x = 0; x < MAP_CHIP_NUM_X;x++)
		{
			int handle = bgHandle[y * MAP_CHIP_NUM_X + x];
			if (handle != -1)
			{
				if (((mx - mapChipArea_.x) / IMAGE_SIZE) == x && (my / IMAGE_SIZE) == y)
				{		
					point->x = x;
					point->y = y;
					ret = true;
				}
			}
		}
	}
	return ret;
}

