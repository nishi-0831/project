#include "MapChip.h"
#include "DxLib.h"
#include "Source/Screen.h"
#include "ImGui/imgui.h"
#include "global.h"
#include <assert.h>
#include "Input.h"
#include "MapEdit.h"
#include <algorithm>
#include <WinBase.h>
#include <string>
#define test 0

namespace
{
	//同じ名前の変数は後でまとめましょう
	//const int mapChipConfig_.TILE_PIX_SIZE = { 32 };
	//画像のチップ数
	//const int mapChipConfig_.TILES_X = { 16 };
	//const int mapChipConfig_.TILES_Y = { 12 };
	//マップのチップ数
	
	

#if 0
	const int MAP_CHIP_NUM_X = { 8 };
	const int MAP_CHIP_NUM_Y = { 24 };
#else
	//チップ選択ウィンドウが表示するチップ数
	//画像そのもののチップ数と選択ウィンドウが表示するチップ数の変数が見分け付きづらいので要改名
	//const int mapChipConfig_.MAPCHIP_VIEW_X = { 8 };
	//const int mapChipConfig_.MAPCHIP_VIEW_Y = { mapChipConfig_.TILES_Y };
#endif
	
	//縦
	//const int mapChipConfig_.MAPCHIP_WIN_WIDTH = { mapChipConfig_.TILE_PIX_SIZE * mapChipConfig_.MAPCHIP_VIEW_X };
	//const int mapChipConfig_.MAPCHIP_WIN_HEIGHT = { mapChipConfig_.TILE_PIX_SIZE * mapChipConfig_.MAPCHIP_VIEW_Y};

#if test
	std::map<Point, int> bgHandleMap;

#else
	std::map<int, int> bgHandleMap;
	std::map<int, int> bgChipIndexMap;
#endif
	std::pair<Point, int> selectedChip;
	//std::pair<int, int> selectedChip;
	/*struct BgHandle
	{
		std::vector<int> index;
		std::vector<int> hImages;
	};*/
	//BgHandle bgHandleMap;
	Rect defaultMapChipArea_;


}
void MapChip::Input()
{
#if 0
	int dir=0;
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		tipOffset_ += 1;
		dir = 1;
	}
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		tipOffset_ -= 1;
		dir = -1;
	}
	//tipOffset_ = std::clamp(tipOffset_, -mapChipConfig_.MAPCHIP_VIEW_X,0);
	tipOffset_ = std::clamp(tipOffset_, 0, mapChipConfig_.MAPCHIP_VIEW_X);
	//mapChipArea_.x = std::clamp(mapChipArea_.x+(dir * mapChipConfig_.TILE_PIX_SIZE), Screen::WIDTH - MAP_CHIP_WIN_WIDTH, Screen::WIDTH);
#endif
}
Point MapChip::GetViewOrigin() const
{
	return {Screen::WIDTH - mapChipConfig_.MAPCHIP_WIN_WIDTH,Screen::HEIGHT - mapChipConfig_.MAPCHIP_WIN_HEIGHT};
}
MapChip::MapChip()
	: GameObject() , mapChipConfig_(GetMapChipConfig())
{

	
	selectedChip.second = -1;
	bgHandle.resize(mapChipConfig_.TILES_X * mapChipConfig_.TILES_Y);

	tipOffset_ = 0;
	const char* FileName = "bg.png";
	int AllNum = mapChipConfig_.TILES_X * mapChipConfig_.TILES_Y;
	int XNum = mapChipConfig_.TILES_X; 
	int YNum = mapChipConfig_.TILES_Y;
	int XSize = mapChipConfig_.TILE_PIX_SIZE;
	int YSize = mapChipConfig_.TILE_PIX_SIZE;
	//int HandleBuf*

	int a = LoadGraph("bg.png", 0);
	LoadDivGraph("bg.png", 
		mapChipConfig_.TILES_X * mapChipConfig_.TILES_Y, 
		mapChipConfig_.TILES_X, mapChipConfig_.TILES_Y, 
		mapChipConfig_.TILE_PIX_SIZE, mapChipConfig_.TILE_PIX_SIZE,
		bgHandle.data());


	int topLeft_x = Screen::WIDTH - mapChipConfig_.MAPCHIP_WIN_WIDTH;
	int topLeft_y = 0;
	int bottomRight_x = Screen::WIDTH;
	int bottomRight_y = mapChipConfig_.MAPCHIP_WIN_HEIGHT;

	
	defaultMapChipArea_ = {
	Screen::WIDTH - mapChipConfig_.MAPCHIP_WIN_WIDTH,
	0,
	mapChipConfig_.MAPCHIP_WIN_WIDTH,
	 mapChipConfig_.MAPCHIP_WIN_HEIGHT
	};
	
	mapChipArea_ = defaultMapChipArea_;

	for (int i = 0;i < bgHandle.size();i++)
	{
		int x = i / mapChipConfig_.TILES_X;
		int y = i % mapChipConfig_.TILES_X;
#if test
		//https://learn.microsoft.com/ja-jp/cpp/error-messages/compiler-errors-2/compiler-error-c2676?view=msvc-170
		//Point型にオーバーロードした演算子を書いてない たぶん 二項演算子<
		Point point = { x,y };
		bgHandleMap.insert(std::make_pair(Point{x,y}, bgHandle[i]));
#else
		bgHandleMap.insert(std::make_pair(i, bgHandle[i]));
		bgChipIndexMap.insert(std::make_pair(bgHandle[i], i));
#endif
		
	}
	/*LoadDivGraph("bg.png",
		mapChipConfig_.TILES_X * mapChipConfig_.TILES_Y,
		mapChipConfig_.TILES_X, mapChipConfig_.TILES_Y,
		mapChipConfig_.TILE_PIX_SIZE, mapChipConfig_.TILE_PIX_SIZE,
		bgHandleMap.hImages.data());*/

	//for()
	SetDrawOrder(-1);
}

MapChip::~MapChip()
{
	for (int i = 0; i < mapChipConfig_.TILES_X * mapChipConfig_.TILES_Y; i++)
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
	Input();
	
	Point mousePos;
	if (GetMousePoint(&mousePos.x , &mousePos.y) == -1)
	{
		return;
	}

	isInMapChipArea_ = (mousePos.x > GetViewOrigin().x && mousePos.x < Screen::WIDTH &&
		mousePos.y > GetViewOrigin().y && mousePos.y < mapChipConfig_.MAPCHIP_WIN_HEIGHT);
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
			selectedChip.first = Point{ point.x + tipOffset_,point.y };
			selectedChip.second = bgHandleMap[point.y * mapChipConfig_.TILES_X +( point.x + tipOffset_)];

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
		ImGui::Text("bgHandleMap[%d] = %d", bg.first, bg.second);
	}
	ImGui::EndChild();

	Point point = { 0,0 };
	
#if 0
	for (int y = 0; y < MAP_CHIP_NUM_Y;y++)
	{
		for (int x = 0; x < MAP_CHIP_NUM_X;x++)
		{
			//tipOffset_を加えた
			int handle = bgHandle[y * mapChipConfig_.TILES_X + (x)];

			//bgHandleの範囲外にアクセスしてしまう
			//int handle = bgHandle[y * MAP_CHIP_NUM_X + (x + tipOffset_)];
			if (handle != -1)
			{
				DrawGraph(mapChipArea_.x + (x+tipOffset_) * mapChipConfig_.TILE_PIX_SIZE, y * mapChipConfig_.TILE_PIX_SIZE, handle, FALSE);
			}
		}
	}
#else
	for (int y = 0; y < mapChipConfig_.MAPCHIP_VIEW_Y;y++)
	{
		for (int x = 0; x < mapChipConfig_.MAPCHIP_VIEW_X;x++)
		{
			int idx = y * mapChipConfig_.TILES_X + (x + tipOffset_);
			if (idx < bgHandle.size())
			{
				int handle = bgHandle[idx];
				if (handle != -1)
				{
					DrawGraph(mapChipArea_.x + x * mapChipConfig_.TILE_PIX_SIZE,mapChipArea_.y + y * mapChipConfig_.TILE_PIX_SIZE, handle, FALSE);
				}
			}
			else
			{
				int a = 0;
			}
		}
	}
#endif
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}
	DrawGraph(mousePos.x , mousePos.y, selectedChip.second,TRUE);
	if (IsInMapChipArea(&point))
	{
		DrawBox(mapChipArea_.x + point.x * mapChipConfig_.TILE_PIX_SIZE, point.y * mapChipConfig_.TILE_PIX_SIZE, mapChipArea_.x + point.x * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, point.y * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, GetColor(0, 255, 0), false, 5);
	}
	DrawBox(mapChipArea_.x + selectedChip.first.x * mapChipConfig_.TILE_PIX_SIZE, selectedChip.first.y * mapChipConfig_.TILE_PIX_SIZE, mapChipArea_.x + selectedChip.first.x * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, selectedChip.first.y * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, GetColor(0, 255, 0), false, 5);
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
				DrawGraph(topLeft_x + x * mapChipConfig_.TILE_PIX_SIZE, y * mapChipConfig_.TILE_PIX_SIZE, handle, FALSE);
				if (((mx - topLeft_x ) / mapChipConfig_.TILE_PIX_SIZE  ) == x && (my / mapChipConfig_.TILE_PIX_SIZE) == y)
				{
					DrawBox(topLeft_x + x * mapChipConfig_.TILE_PIX_SIZE, y * mapChipConfig_.TILE_PIX_SIZE, topLeft_x + x * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, y * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, GetColor(0, 255, 0), false, 5);
				}
			}
		}
	}
#endif
}

void MapChip::LoadIni()
{
	char buff[128];

	GetPrivateProfileStringA(
		"MapChip",
		"Title", 
		"NONE", //デフォルト値
		buff,   //取得した値を入れるバッファのアドレス 名前だけでいい
		sizeof(buff), 
		"./mySetup.ini");

	//printfDx(buff);
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
				//DrawGraph(topLeft_x + x * mapChipConfig_.TILE_PIX_SIZE, y * mapChipConfig_.TILE_PIX_SIZE, handle, FALSE);
				if (((mx - topLeft_x) / mapChipConfig_.TILE_PIX_SIZE) == x && (my / mapChipConfig_.TILE_PIX_SIZE) == y)
				{
					//DrawBox(topLeft_x + x * mapChipConfig_.TILE_PIX_SIZE, y * mapChipConfig_.TILE_PIX_SIZE, topLeft_x + x * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, y * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, GetColor(0, 255, 0), false, 5);
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
	for (int y = 0; y < mapChipConfig_.TILES_Y;y++)
	{
		for (int x = 0; x < mapChipConfig_.TILES_X;x++)
		{
			int idx = y * mapChipConfig_.TILES_X + (x + tipOffset_);
			if (idx < bgHandle.size())
			{

				int handle = bgHandle[y * mapChipConfig_.TILES_X + (x + tipOffset_)];
				if (handle != -1)
				{
					if (((mx - mapChipArea_.x) / mapChipConfig_.TILE_PIX_SIZE) == x && (my / mapChipConfig_.TILE_PIX_SIZE) == y)
					//if (((mx - mapChipArea_.x) / mapChipConfig_.TILE_PIX_SIZE) == x + tipOffset_ && (my / mapChipConfig_.TILE_PIX_SIZE) == y)
					{		
						point->x = x;
						point->y = y;
						ret = true;
					}
				}
			}
			else
			{
				int a = 0;
			}
		}
	}
	return ret;
}

int MapChip::GetHImage()
{
	return selectedChip.second;
}

int MapChip::GetChipIndex(int handle)
{
#if 1
	
	return bgChipIndexMap[handle];
#else
	auto itr = bgChipIndexMap.find(handle);
	if (itr != bgChipIndexMap.end())
	{
		return bgChipIndexMap[handle];
	}
	else
	{
		return -1;
	}
#endif
	
}

int MapChip::GetChipHandle(int index)
{
	//存在しないキーを渡されるとそれに対応する値は値初期化されたものになる。
	//これはintなので0になるっぽい。
	return bgHandleMap[index];
}

