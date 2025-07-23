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
#include <algorithm>
#define test 0

namespace
{
	//同じ名前の変数は後でまとめましょう
	//const int mapChipConfig_.TILE_PIX_SIZE = { 32 };
	//画像のチップ数
	//const int mapChipConfig_.TILES_X = { 16 };
	//const int mapChipConfig_.TILES_Y = { 12 };
	//マップのチップ数
	Point down = Point{ 0,0 };
	Point up = Point{ 0,0 };
	//bool rectSelecting = false;
	Rect rect;
	Rect gridRect;
	bool isUsedMapChip;
	
#if test
	std::map<Point, int> bgHandleMap;

#else
	std::map<int, int> bgHandleMap;
	std::map<int, int> bgChipIndexMap;
#endif
	std::pair<Point, int> selectedChip;
	std::vector<std::pair<Point, int>> selectedChipVec;
	
	Rect defaultMapChipArea_;


}
void MapChip::Input()
{
#if 1
	int dir=0;
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		tipOffsetX_ += 1;
		dir = 1;
	}
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		tipOffsetX_ -= 1;
		dir = -1;
	}
	if (Input::IsKeyDown(KEY_INPUT_W))
	{
		tipOffsetY_ -= 1;
	}
	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		tipOffsetY_ += 1;
	}
	//tipOffset_ = std::clamp(tipOffset_, -mapChipConfig_.MAPCHIP_VIEW_X,0);
	tipOffsetX_ = std::clamp(tipOffsetX_, 0, mapChipConfig_.TILES_X -mapChipConfig_.MAPCHIP_VIEW_X);
	tipOffsetY_ = std::clamp(tipOffsetY_, 0, mapChipConfig_.TILES_Y - mapChipConfig_.MAPCHIP_VIEW_Y);
	//mapChipArea_.x = std::clamp(mapChipArea_.x+(dir * mapChipConfig_.TILE_PIX_SIZE), Screen::WIDTH - MAP_CHIP_WIN_WIDTH, Screen::WIDTH);

	if (Input::IsButtonDown(Input::Mouse::MIDDLE))
	{
		if (Input::IsMouseInRect(mapChipArea_))
		{
			isUsedMapChip = true;
		}
	}
	if (Input::IsButtonUp(Input::Mouse::MIDDLE))
	{
		//MapChip内で押してから離した
		if (isUsedMapChip)
		{
			selectedChipVec.clear();
			RectSelect();
			isUsedMapChip = false;
		}
	}
#endif
}
Point MapChip::GetViewOrigin() const
{
	return {Screen::WIDTH - mapChipConfig_.MAPCHIP_WIN_WIDTH,Screen::HEIGHT - mapChipConfig_.MAPCHIP_WIN_HEIGHT};
}
int MapChip::GetCorrectIndex(int x, int y) const
{
	return (y + tipOffsetY_) * mapChipConfig_.TILES_X + (x + tipOffsetX_);
}
void MapChip::DrawMouseOverlapChip()
{
	Point point = { 0,0 };
	
	//マウスカーソルが重なっているタイルを塗る?
	if (IsInMapChipArea(&point))
	{
		DrawBox(mapChipArea_.x + point.x * mapChipConfig_.TILE_PIX_SIZE, point.y * mapChipConfig_.TILE_PIX_SIZE, mapChipArea_.x + point.x * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, point.y * mapChipConfig_.TILE_PIX_SIZE + mapChipConfig_.TILE_PIX_SIZE, GetColor(0, 255, 0), false, 5);
	}
}
void MapChip::DrawSelectedChip()
{
	const Point& mousePos = Input::GetMousePos();
	//現在選択中のタイルの画像をマウスの場所に描画
	DrawGraph(mousePos.x, mousePos.y, selectedChip.second, TRUE);

	
	//selectedChipVecを塗る
	if (selectedChipVec.empty())
	{
		return;
	}

	//先頭からの差分
	//(0,0),(1,0),(0,1),(1,1)
	//(5,5),(6,5),(5,6),(6,6)
	for (int i = 0; i < selectedChipVec.size(); i++)
	{
		//DrawGraph(mousePos.x + (i * mapChipConfig_.TILE_PIX_SIZE),mousePos.y + ())
	}
	for (auto& chip : selectedChipVec)
	{
		Point offset = selectedChipVec[0].first - chip.first;
		DrawGraph(mousePos.x + (-offset.x * mapChipConfig_.TILE_PIX_SIZE), mousePos.y + (-offset.y * mapChipConfig_.TILE_PIX_SIZE),chip.second,FALSE);
	}
}
void MapChip::DrawSelectedChipFrame()
{
	//現在選択中のタイルの枠を塗る
	int px = mapChipArea_.x + (selectedChip.first.x - tipOffsetX_) * mapChipConfig_.TILE_PIX_SIZE;
	int py = (selectedChip.first.y - tipOffsetY_) * mapChipConfig_.TILE_PIX_SIZE;
	//int py = selectedChip.first.y * mapChipConfig_.TILE_PIX_SIZE;
	if (mapChipArea_.x < px || mapChipArea_.x + mapChipArea_.w < px + mapChipConfig_.TILE_PIX_SIZE)
	{
		DrawBox(px,
			py,
			px + mapChipConfig_.TILE_PIX_SIZE,
			py + mapChipConfig_.TILE_PIX_SIZE, GetColor(0, 255, 0), false, 5);
	}
}
void MapChip::DrawMapChipWindow()
{
	for (int y = 0; y < mapChipConfig_.MAPCHIP_VIEW_Y;y++)
	{
		for (int x = 0; x < mapChipConfig_.MAPCHIP_VIEW_X;x++)
		{
			int idx = (y + tipOffsetY_) * mapChipConfig_.TILES_X + (x + tipOffsetX_);
			//int idx = y * mapChipConfig_.TILES_X + (x + tipOffsetX_);
			if (idx < bgHandle.size())
			{
				int handle = bgHandle[idx];
				if (handle != -1)
				{
					DrawGraph(mapChipArea_.x + x * mapChipConfig_.TILE_PIX_SIZE, mapChipArea_.y + y * mapChipConfig_.TILE_PIX_SIZE, handle, FALSE);
				}
			}
		}
	}
}
MapChip::MapChip()
	: GameObject() , mapChipConfig_(GetMapChipConfig())
{

	
	selectedChip.second = -1;
	bgHandle.resize(mapChipConfig_.TILES_X * mapChipConfig_.TILES_Y);

	tipOffsetX_ = 0;
	tipOffsetY_ = 0;
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
			//selectedChip.first = Point{ point.x + tipOffsetX_,point.y };
			selectedChip.first = Point{ point.x + tipOffsetX_,point.y + tipOffsetY_ };
			//selectedChip.second = bgHandleMap[(point.y + tipOffsetY_ ) * mapChipConfig_.TILES_X +( point.x + tipOffsetX_)];
			selectedChip.second = bgHandleMap[(point.y +tipOffsetY_ ) * mapChipConfig_.TILES_X +( point.x + tipOffsetX_)];
			selectedChipVec.clear();
			selectedChipVec.push_back(selectedChip);
		}
		
		
	}
	
}

void MapChip::Draw()
{
#pragma region
	ImGui::Text("selectedChip[%d,%d] : %d", selectedChip.first.x, selectedChip.first.y, selectedChip.second);

	ImGui::BeginChild("selectedChipVec Viwer", ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar);

	for (const auto handle : selectedChipVec)
	{
		ImGui::Text("selectedChip[%d,%d] : %d", handle.first.x, handle.first.y, handle.second);
	}
	ImGui::EndChild();

	//ImGui::Separator();
	ImGui::BeginChild("bgHandle Map Viwer", ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar);
	
	for (const auto bg : bgHandleMap)
	{
		ImGui::Text("bgHandleMap[%d] = %d", bg.first, bg.second);
	}
	ImGui::EndChild();
#pragma endregion
	
	
	DrawMapChipWindow();
	DrawMouseOverlapChip();
	DrawSelectedChipFrame();
	DrawSelectedChip();
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

	int mx = -1, my = -1;
	GetMousePoint(&mx, &my);
	for (int y = 0; y < mapChipConfig_.MAPCHIP_VIEW_Y;y++)
	{
		for (int x = 0; x < mapChipConfig_.MAPCHIP_VIEW_X;x++)
		{
			//int idx = (y) * mapChipConfig_.TILES_X + (x + tipOffsetX_);
			//int idx = (y + tipOffsetY_) * mapChipConfig_.TILES_X + (x + tipOffsetX_);
			int idx = GetCorrectIndex(x, y);
			if (idx < bgHandle.size())
			{
				int handle = bgHandle[idx];
				//int handle = bgHandle[y * mapChipConfig_.TILES_X + (x + tipOffsetX_)];
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

void MapChip::RectSelect()
{
	rect = Input::GetSelectRect();
	int offsetX = rect.x - defaultMapChipArea_.x;
	int offsetY = rect.y - defaultMapChipArea_.y;
	gridRect =
	{
		std::clamp(offsetX / mapChipConfig_.TILE_PIX_SIZE,0,mapChipConfig_.MAPCHIP_VIEW_X - 1),
		std::clamp((offsetY) / mapChipConfig_.TILE_PIX_SIZE,0,mapChipConfig_.MAPCHIP_VIEW_Y - 1),
		std::clamp((offsetX + rect.w ) / mapChipConfig_.TILE_PIX_SIZE,0,mapChipConfig_.MAPCHIP_VIEW_X - 1),
		std::clamp((offsetY + rect.h) / mapChipConfig_.TILE_PIX_SIZE,0,mapChipConfig_.MAPCHIP_VIEW_Y - 1)
	};

	for (int i = gridRect.x;i <= gridRect.w;i++)
	{
		for (int j = gridRect.y; j <= gridRect.h; j++)
		{
			int idx = GetCorrectIndex(i, j);
			if (idx >= 0 && idx < mapChipConfig_.MAPCHIP_VIEW_X * mapChipConfig_.MAPCHIP_VIEW_Y)
			{
				Point p = { i,j };
				int handle = bgHandle[idx];
				auto pair = std::make_pair(p, handle);
				selectedChipVec.push_back(pair);
			}
		}
	}

}

const std::vector<std::pair<Point, int>>& MapChip::GetSelectedChipVec()
{
	return selectedChipVec;
}

int MapChip::GetHImage()
{
	if (selectedChipVec.empty())
	{
		return -1;
	}
	return selectedChipVec.at(0).second;
	//return selectedChip.second;
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

