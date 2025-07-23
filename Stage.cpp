#include "Stage.h"
#include "Input.h"
#include "DxLib.h"
//const int IMAGE_SIZE = { 32 };
//
////マップのチップ数
//const int MAP_WIDTH{ 32 };
//const int MAP_HEIGHT{ 32 };
//
////横には0から15
////画像のチップ数
//const int MAP_CHIP_WIDTH = 16;
//const int MAP_CHIP_HEIGHT = 12;
//
//const int myMap[MAP_HEIGHT][MAP_WIDTH] = {
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,120,121,121,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,120,121,17,17,17,17,17,17,17,17,80,80,17,17,17,17,136,137,137,17,17,17,17,120,121,17,17,17},
//{17,17,17,17,120,121,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,136,137,17,17,17},
//{17,17,17,17,136,137,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{101,101,101,101,101,101,101,101,101,101,101,101,101,101,80,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
//{101,101,101,101,101,101,101,101,101,101,101,101,101,101,80,80,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,120,121,17,17,17,120,121,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,136,137,17,17,17,136,137,17,17,17,17,17},
//{17,17,17,17,17,17,17,120,121,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,120,120,121,17,17,136,137,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,136,136,137,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
//{17,17,17,17,17,17,17,17,17,17,17,17,17,17,80,80,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17}
//};

namespace
{
	Rect rect;
}
Stage::Stage()
	: GameObject()
{

	mapChip_ = new MapChip();
	mapEdit_ = new MapEdit();
}

Stage::~Stage()
{
	//for (int i = 0;i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT;i++)
	{
		/*if (bgHandleVec_[i] != -1)
		{
			DeleteGraph(bgHandle[i]);
			bgHandleVec_[i] = -1;
		}*/
	}
	//delete[] bgHandle;
	delete mapChip_;
}

void Stage::Update()
{
#if 0
	if (Input::IsButtonDown(Input::Mouse::LEFT))
	{
		DxLib::printfDx("左が押された瞬間!\n");
	}
	if (Input::IsButtonKeep(Input::Mouse::LEFT))
	{
		//DxLib::printfDx("左が押されてる\n");
	}
	if (Input::IsButtonDown(Input::Mouse::RIGHT))
	{
		DxLib::printfDx("右が押された瞬間!\n");
	}
	if (Input::IsButtonUp(Input::Mouse::RIGHT))
	{
		DxLib::printfDx("右が離された瞬間!\n");
	}
	if (Input::IsButtonKeep(Input::Mouse::RIGHT))
	{
		//DxLib::printfDx("右が押されている!\n");
	}
#endif
	if (Input::IsButtonDown(Input::Mouse::LEFT))
	{
		if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
		{
			int hImage = mapChip_->GetHImage();
			mapEdit_->Fill(hImage);
		}
	}
	if (Input::IsButtonKeep(Input::Mouse::LEFT))
	{
		//int hImage = mapChip_->GetHImage();
		//mapEdit_->SetMap(hImage);
		mapEdit_->SetMapVec(mapChip_->GetSelectedChipVec());
	}
	if (Input::IsButtonDown(Input::Mouse::RIGHT))
	{
		
	}
	//消しゴム的な機能
	if (Input::IsButtonKeep(Input::Mouse::RIGHT))
	{
		if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
		{
			int hImage = -1;
			mapEdit_->Fill(hImage);
		}
		int hImage = -1;
		mapEdit_->SetMap(hImage);
	}
	if (Input::IsButtonUp(Input::Mouse::RIGHT))
	{
		int hImage = -1;
		mapEdit_->Fill(hImage);
	}
	
}

void Stage::Draw()
{
	if (!Input::IsSelectRect())
	{
		return;
	}
	rect = Input::GetSelectRect();
	DrawBox(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, GetColor(0, 200, 0), FALSE);
}

int Stage::GetHImage()
{
	return 0;
}
