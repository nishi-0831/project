#include "MapEdit.h"
#include "DxLib.h"
#include "ImGui/imgui.h"
#include <algorithm>
#include "Input.h"
#include "InputManager.h"
#include <fstream>
#include <map>
#include "MapChip.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <WinBase.h>

namespace
{
	Point down = Point{0,0};
	Point up = Point{ 0,0 };
	bool isUsedMapEdit = false;
	Rect rect;
	Rect gridRect;
}

using namespace Input;

#define flag 1
MapEdit::MapEdit()
	: GameObject(), mapEditConfig_(GetMapEditConfig())
{
	myMap_.resize(mapEditConfig_.MAP_WIDTH * mapEditConfig_.MAP_HEIGHT, -1);//初期値を-1で20*20のマップ
	mapEditArea_ = {
		mapEditConfig_.LEFT_MARGIN,
		mapEditConfig_.TOP_MARGIN,
		mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_WIDTH + mapEditConfig_.LEFT_MARGIN,
		mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_HEIGHT + mapEditConfig_.TOP_MARGIN
	};
	RegisterInputActions();
	SetInputContextArea(mapEditArea_, InputContext::MAP_EDIT);
	SetDrawOrder(1);

}

MapEdit::~MapEdit()
{

}
void MapEdit::RegisterInputActions()
{
	InputManager& inputManager = InputManager::GetInstance();

	InputBinding saveBinding = inputManager.CreateKeyBinding(KEY_INPUT_S, KEY_INPUT_LSHIFT);
	RegisterAction("mapedit_save", saveBinding, InputActionType::PRESSED, InputContext::GENERAL,
		[this]() {SaveMapData(); });
	InputBinding loadBinding = inputManager.CreateKeyBinding(KEY_INPUT_L);
	RegisterAction("mapedit_load", loadBinding, InputActionType::PRESSED, InputContext::GENERAL,
		[this]() {LoadMapData(); });

	InputBinding middleDownBinding;
	middleDownBinding.mouseButton = Mouse::MIDDLE;
	RegisterAction("mapedit_rect_start", middleDownBinding,InputActionType::PRESSED,InputContext::MAP_EDIT,
		[this]() {OnMiddleButtonDown(); });

	RegisterAction("mapedit_rect_end", middleDownBinding, InputActionType::RELEASED,
		InputContext::MAP_EDIT, [this]() { OnMiddleButtonUp(); });
}

void MapEdit::OnMiddleButtonDown()
{
	if (IsButtonDown(Mouse::MIDDLE))
	{
		if (IsMouseInRect(mapEditArea_))
		{
			isUsedMapEdit = true;
		}
	}
}
void MapEdit::OnMiddleButtonUp()
{
	if (IsButtonUp(Mouse::MIDDLE))
	{
		if (isUsedMapEdit)
		{
			if (IsKeepKeyDown(KEY_INPUT_LSHIFT))
			{
				RectFill(-1);
			}
			else
			{
				MapChip* mapChip = FindGameObject<MapChip>();
				RectFill(mapChip->GetHImage());
			}
			isUsedMapEdit = false;
		}
	}
}
void MapEdit::Update()
{
	
}

void MapEdit::Draw()
{
	ImGui::Begin("Rect");
	
	ImGui::Text("down(%i,%i)", down.x, down.y);
	ImGui::Text("up(%i,%i)", up.x, up.y);
	ImGui::Text("rect(%i,%i,%i,%i)", rect.x, rect.y, rect.w, rect.h);
	ImGui::Text("gridRect(%i,%i,%i,%i)", gridRect.x, gridRect.y, gridRect.w, gridRect.h);
	bool select = IsSelectRect();
	ImGui::Checkbox("rectselecting", &select);
	ImGui::Checkbox("isUsedMapEdit", &isUsedMapEdit);
	ImGui::End();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	

	int topLeftX = 0 + mapEditConfig_.LEFT_MARGIN;
	int topLeftY = 0 + mapEditConfig_.TOP_MARGIN;
	int bottomLightX = mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_WIDTH + mapEditConfig_.LEFT_MARGIN;
	int bottomLightY = mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_HEIGHT + mapEditConfig_.TOP_MARGIN;
	DrawBoxAA(topLeftX, topLeftY, bottomLightX - 1, bottomLightY - 1, GetColor(122, 122, 122), FALSE, 3);

	for (int i = 1;i < mapEditConfig_.MAP_WIDTH;i++)
	{
		int x = i * mapEditConfig_.MAP_IMAGE_SIZE + mapEditConfig_.LEFT_MARGIN;

		int startY = topLeftY;
		int endY = bottomLightY;

		DrawLine(x, startY, x, endY, GetColor(255, 0, 0), 1);
	}
	for (int i = 1;i < mapEditConfig_.MAP_HEIGHT;i++)
	{
		int y = i * mapEditConfig_.MAP_IMAGE_SIZE + mapEditConfig_.TOP_MARGIN;

		int startX = topLeftX;
		int endX = bottomLightX;

		DrawLine(startX, y, endX, y, GetColor(255, 0, 0), 1);
	}
	Point p = { 0,1 };
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	ImGui::Begin("MapEdit");
	for (int y = 0; y < mapEditConfig_.MAP_HEIGHT;y++)
	{
		const int IMAGE_SIZE = { 32 };
		for (int x = 0; x < mapEditConfig_.MAP_WIDTH;x++)
		{
			int handle = myMap_[y * mapEditConfig_.MAP_WIDTH + x];
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

void MapEdit::DrawSelectRect()
{
	rect = GetSelectRect();
}

void MapEdit::RectFill(int value)
{
	rect = GetSelectRect();
	int imageSize = mapEditConfig_.MAP_IMAGE_SIZE;
	gridRect =
	{
		std::clamp((rect.x - mapEditConfig_.LEFT_MARGIN) / imageSize,0,mapEditConfig_.MAP_WIDTH - 1),
		std::clamp((rect.y - mapEditConfig_.TOP_MARGIN) / imageSize,0,mapEditConfig_.MAP_HEIGHT - 1),
		std::clamp((rect.x + rect.w - mapEditConfig_.LEFT_MARGIN) / imageSize,0,mapEditConfig_.MAP_WIDTH - 1),
		std::clamp((rect.y + rect.h - mapEditConfig_.TOP_MARGIN) / imageSize,0,mapEditConfig_.MAP_HEIGHT - 1)
	};


	for (int i = gridRect.x;i <= gridRect.w;i++)
	{
		for (int j = gridRect.y; j <= gridRect.h; j++)
		{
			int idx = i + (j * mapEditConfig_.MAP_WIDTH);
			if (idx >= 0 && idx < mapEditConfig_.MAP_WIDTH * mapEditConfig_.MAP_HEIGHT)
			{
				myMap_[idx] = value;
			}
		}
	}
	
}

void MapEdit::SetMap(int value)
{
	Point p = { 0,1 };
	if (IsInMapEdit(&p))
	{
		int idx = p.x + mapEditConfig_.MAP_WIDTH * p.y;
		myMap_[idx] = value;
	}
}

void MapEdit::SetMapVec(const std::vector<std::pair<Point, int>>& vec)
{
	Point p = { 0,1 };
	if (IsInMapEdit(&p))
	{
		//int idx = p.x + mapEditConfig_.MAP_WIDTH * p.y;
		for (auto& chip : vec)
		{
			Point offset = vec[0].first;
			offset = chip.first - offset;
			
			Point point = offset + p;
			point.x = std::clamp(point.x, 0, mapEditConfig_.MAP_WIDTH - 1);
			point.y = std::clamp(point.y, 0, mapEditConfig_.MAP_HEIGHT - 1);

			//int offsetIndex = idx + (offset.x + mapEditConfig_.MAP_WIDTH * offset.y);
			int offsetIndex = (point.x + mapEditConfig_.MAP_WIDTH * point.y);

			if (offsetIndex >= 0 && offsetIndex < myMap_.size())
			{
				myMap_[offsetIndex] = chip.second;
			}
		}
	}
}

void MapEdit::GetMap(Point p) const
{
}

void MapEdit::Fill(int value)
{
#if flag
	//満たすtileがvalue
	Point p = { 0,1 };
	int idx;
	//近傍にあるcheckHImageに該当するのを消す
	int checkHImage;
	if (IsInMapEdit(&p))
	{
		idx = p.x + mapEditConfig_.MAP_WIDTH * p.y;
		//押した箇所のHIage
		checkHImage = myMap_[idx];
	}
	else
	{
		return;
	}
	FillRecursive(value, checkHImage, p);
#endif
}

void MapEdit::FillRecursive(int fillHImage, int checkHImage, Point p)
{
#if flag
	int idx;
	idx = p.x + (mapEditConfig_.MAP_WIDTH * p.y);
	//クリックした箇所のhImageと、選択中のhImageが一緒ならreturn
	if (myMap_[idx] == fillHImage)
	{
		return;
	}
	//その箇所のhImageが現在塗りつぶし対象と異なるならreturn
	if (myMap_[idx] != checkHImage)
	{
		return;
	}
	myMap_[idx] = fillHImage;

	////左
	FillRecursive(fillHImage, checkHImage, ToSafeNeighbor(p, Point{ -1,0 }));
	////右
	FillRecursive(fillHImage, checkHImage, ToSafeNeighbor(p, Point{ 1,0 }));
	////上
	FillRecursive(fillHImage, checkHImage, ToSafeNeighbor(p, Point{ 0,-1 }));
	////下
	FillRecursive(fillHImage, checkHImage, ToSafeNeighbor(p, Point{ 0,1 }));
#endif
}



Point MapEdit::ToSafeNeighbor(Point start, Point movement)
{
	start.x = std::clamp(start.x += movement.x, 0, mapEditConfig_.MAP_WIDTH - 1);
	start.y = std::clamp(start.y += movement.y, 0, mapEditConfig_.MAP_HEIGHT - 1);

	return start;
}

bool MapEdit::IsInMapEdit(Point* p)
{
	const int IMAGE_SIZE = { 32 };

	bool ret = false;

	int mx = -1, my = -1;
	GetMousePoint(&mx, &my);
	for (int y = 0; y < mapEditConfig_.MAP_HEIGHT;y++)
	{
		for (int x = 0; x < mapEditConfig_.MAP_WIDTH;x++)
		{

			int touchX = (mx - mapEditArea_.x) / mapEditConfig_.MAP_IMAGE_SIZE;
			int touchY = (my - mapEditArea_.y) / mapEditConfig_.MAP_IMAGE_SIZE;
			if ((touchX == x) && (touchY == y))
			{
				p->x = x;
				p->y = y;
				ret = true;
			}

		}
	}
	return ret;

}

void MapEdit::SaveMapData()
{
	//頑張ってファイル選択ダイアログを出す
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//ウィンドウのオーナー=親ウィンドウのハンドル

	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	//ただファイル選択ダイアログが表示されるだけで、保存ボタンとか押してもなんも起きないよ


	//ファイル名はlpstrFileに渡したfilenameに入ってる
	if (GetSaveFileName(&ofn))
	{
		printfDx("ファイルが選択された\n");
		//ファイルを開いて、セーブ
		//std::filesystem ファイル名だけ取り出す
		//それからofstreamを開く
		std::ofstream openfile(filename);

		printfDx("File Saved!!!\n");

		std::ofstream file("data.dat");

		openfile << "#TinyMapData\n";
		//出力結果のファイル

		MapChip* mc = FindGameObject<MapChip>();

		for (int y = 0; y < mapEditConfig_.MAP_HEIGHT;y++)
		{

			for (int x = 0; x < mapEditConfig_.MAP_WIDTH;x++)
			{
				int index = -1;
				int handle = myMap_[y * mapEditConfig_.MAP_WIDTH + x];
				if (handle != -1)
				{
					index = mc->GetChipIndex(handle);
				}
				//ImGui::Text("myMap(%d,%d):%d", x, y, handle);
				
				openfile << index;
				//openfile << index << ",";
				if (x != mapEditConfig_.MAP_WIDTH - 1)
				{
					openfile << ",";
				}
			}
			openfile << std::endl;
		}
		openfile.close();
	}
	else
	{
		//ファイルの選択がキャンセル
		printfDx("セーブがキャンセル\n");
	}

}

void MapEdit::LoadMapData()
{
	//頑張ってファイル選択ダイアログを出す
	TCHAR filename[255] = "";
	OPENFILENAME ifn = { 0 };

	ifn.lStructSize = sizeof(ifn);
	//ウィンドウのオーナー=親ウィンドウのハンドル

	ifn.hwndOwner = GetMainWindowHandle();
	ifn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ifn.lpstrFile = filename;
	ifn.nMaxFile = 255;

	//ファイル名はlpstrFileに渡したfilenameに入ってる
	if (GetOpenFileName(&ifn))
	{
		printfDx("ファイルが選択された\n", filename);
		
		std::ifstream inputfile(filename);
		if (!inputfile)
		{
			std::cerr << "ファイルを開けませんでした。" << std::endl;
		}
		//inputfileの中に読み込んだ文字列あるよ
		std::string str_buf;

		if (inputfile.is_open())
		{
			MapChip* mc = FindGameObject<MapChip>();
			if (getline(inputfile, str_buf))
			{
				
				if (str_buf != "#TinyMapData")
				{
					printfDx("無効なファイルだと思います");
					return;
				}
			}
			
			myMap_.clear();
			while (getline(inputfile, str_buf))
			{
				
#if 1
				//コンマ区切りで読み込みてえな
				std::string data;

				std::stringstream sstream(str_buf);

				while (getline(sstream, data, ','))
				{
					int num;
					num = std::stoi(data);
					
					myMap_.push_back(mc->GetChipHandle(num));
				}
#else
				
#endif
				printfDx("\n");
			}
			
		}

	}
}