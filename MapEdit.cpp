#include "MapEdit.h"
#include "DxLib.h"
#include "ImGui/imgui.h"
MapEdit::MapEdit()
	: GameObject(),myMap_(MAP_WIDTH * MAP_HEIGHT,-1)//初期値を-1で20*20のマップ
{
	//mapChipArea_ = {
	/*Screen::WIDTH - MAP_CHIP_WIN_WIDTH,
		0,
		Screen::WIDTH,
		MAP_CHIP_WIN_HEIGHT*/
		//};
	mapEditArea_ = {
		LEFT_MARGIN,
		TOP_MARGIN,
		MAP_IMAGE_SIZE * MAP_WIDTH + LEFT_MARGIN,
		MAP_IMAGE_SIZE * MAP_HEIGHT+TOP_MARGIN
	};
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
	Point p = { 0,1 };
	//if (IsInMapEdit(p))
	{
		//DrawBox(mapEditArea_.x, mapEditArea_.y, mapEditArea_.w, mapEditArea_.h, GetColor(255, 0, 0), TRUE);
	}
	ImGui::Begin("MapEdit");
	for (int y = 0; y < MAP_HEIGHT;y++)
	{
		const int IMAGE_SIZE = { 32 };
		for (int x = 0; x < MAP_WIDTH;x++)
		{
			int handle = myMap_[y * MAP_WIDTH + x];
			ImGui::Text("myMap(%d,%d):%d", x, y, handle);
			if (handle != -1)
			{
				
				DrawGraph(mapEditArea_.x + x * IMAGE_SIZE, mapEditArea_.y + y * IMAGE_SIZE, handle, FALSE);
			}
		}
	}

	ImGui::End();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MapEdit::SetMap(int value)
{
	Point p = { 0,1 };
	if (IsInMapEdit(&p))
	{
		int idx = p.x + MAP_WIDTH * p.y;
		myMap_[idx] = value;
	}
}

void MapEdit::GetMap(Point p) const
{
}

bool MapEdit::IsInMapEdit(Point* p)
{
	const int IMAGE_SIZE = { 32 };
	
		bool ret = false;

		int mx = -1, my = -1;
		GetMousePoint(&mx, &my);
		for (int y = 0; y < MAP_HEIGHT;y++)
		{
			for (int x = 0; x < MAP_WIDTH;x++)
			{
				
				int touchX= (mx - mapEditArea_.x) / MAP_IMAGE_SIZE;
				int touchY= (my - mapEditArea_.y) / MAP_IMAGE_SIZE;
					if ((touchX == x) && (touchY == y ))
					{
						p->x = x;
						p->y = y;
						ret = true;
					}
				
			}
		}
		return ret;
	
}
