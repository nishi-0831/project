#include "MapEdit.h"
#include "DxLib.h"
#include "ImGui/imgui.h"
#include <algorithm>
#include "Input.h"
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
	//std::map<int, int> myMapMap;
	Point down = Point{0,0};
	Point up = Point{ 0,0 };
	bool rectSelecting = false;
	Rect rect;
	Rect gridRect;
}
#define flag 1
MapEdit::MapEdit()
	: GameObject(), mapEditConfig_(GetMapEditConfig())
{
	//mapChipArea_ = {
	/*Screen::WIDTH - MAP_CHIP_WIN_WIDTH,
		0,
		Screen::WIDTH,
		MAP_CHIP_WIN_HEIGHT*/
		//};

	//mapEditConfig_.MAP_WIDTH = mapEditConfig_.MAP_WIDTH;
		//mapEditConfig_.MAP_HEIGHT = mapEditConfig_.MAP_HEIGHT;
		//mapEditConfig_.MAP_IMAGE_SIZE = mapEditConfig_.MAP_IMAGE_SIZE;
		//mapEditConfig_.LEFT_MARGIN = mapEditConfig_.LEFT_MARGIN;
		//mapEditConfig_.TOP_MARGIN = mapEditConfig_.TOP_MARGIN;

	myMap_.resize(mapEditConfig_.MAP_WIDTH * mapEditConfig_.MAP_HEIGHT, -1);//�����l��-1��20*20�̃}�b�v
	mapEditArea_ = {
		mapEditConfig_.LEFT_MARGIN,
		mapEditConfig_.TOP_MARGIN,
		mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_WIDTH + mapEditConfig_.LEFT_MARGIN,
		mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_HEIGHT + mapEditConfig_.TOP_MARGIN
	};
}

MapEdit::~MapEdit()
{

}

void MapEdit::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_S) && Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
	{
		SaveMapData();
	}
	if (Input::IsKeyDown(KEY_INPUT_L))
	{
		LoadMapData();
	}
	if (Input::IsButtonDown(Input::Mouse::MIDDLE))
	{
		int x, y;
		GetMousePoint(&x, &y);
		down.x = x;
		down.y = y;
		rectSelecting = true;
	}
	if (Input::IsButtonKeep(Input::Mouse::MIDDLE) && rectSelecting)
	{
		int x, y;
		GetMousePoint(&x, &y);
		up.x = x;
		up.y = y;
	}
	if (Input::IsButtonUp(Input::Mouse::MIDDLE) && rectSelecting)
	{
		rectSelecting = false;
		//down��up��rectFill()!!!
		MapChip* mapChip = FindGameObject<MapChip>();
		RectFill(mapChip->GetHImage());
		//RectFill(1);
	}
}

void MapEdit::Draw()
{
	ImGui::Begin("Rect");
	SetSelectRect();
	ImGui::Text("down(%i,%i)", down.x, down.y);
	ImGui::Text("up(%i,%i)", up.x, up.y);
	ImGui::Text("rect(%i,%i,%i,%i)", rect.x, rect.y, rect.w, rect.h);
	ImGui::Text("gridRect(%i,%i,%i,%i)", gridRect.x, gridRect.y, gridRect.w, gridRect.h);

	ImGui::End();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	if (rectSelecting)
	{
		DrawSelectRect();

	}



	int topLeftX = 0 + mapEditConfig_.LEFT_MARGIN;
	int topLeftY = 0 + mapEditConfig_.TOP_MARGIN;
	int bottomLightX = mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_WIDTH + mapEditConfig_.LEFT_MARGIN;
	int bottomLightY = mapEditConfig_.MAP_IMAGE_SIZE * mapEditConfig_.MAP_HEIGHT + mapEditConfig_.TOP_MARGIN;
	DrawBox(topLeftX, topLeftY, bottomLightX - 1, bottomLightY - 1, GetColor(122, 122, 122), FALSE, 3);

	for (int i = 1;i < mapEditConfig_.MAP_WIDTH;i++)
	{
		int x = i * mapEditConfig_.MAP_IMAGE_SIZE + mapEditConfig_.LEFT_MARGIN;

		//�N�_��y
		int startY = topLeftY;
		//�I�_��y
		int endY = bottomLightY;

		DrawLine(x, startY, x, endY, GetColor(255, 0, 0), 1);
	}
	for (int i = 1;i < mapEditConfig_.MAP_HEIGHT;i++)
	{
		//�N�_���I�_��y�͓����B����������
		int y = i * mapEditConfig_.MAP_IMAGE_SIZE + mapEditConfig_.TOP_MARGIN;

		//�N�_��x
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
	
	DrawBox(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, GetColor(0, 200, 0), FALSE);
}

void MapEdit::SetSelectRect()
{
	//�������񂾎��̍��W�ƁA���������̍��W�ŋ�`�����

	//�������l����/��Ƃ���


	//�������񂾎���x����
	if (down.x < up.x)
	{
		rect.x = down.x;
		rect.w = up.x - down.x;
	}
	//��������
	else
	{
		rect.x = up.x;
		rect.w = down.x - up.x;
	}

	///y
	if (down.y < up.y)
	{
		rect.y = down.y;
		rect.h = up.y - down.y;
	}
	//��������
	else
	{
		rect.y = up.y;
		rect.h = down.y - up.y;
	}
}
void MapEdit::RectFill(int value)
{
	SetSelectRect();
	gridRect =
	{
		std::clamp((rect.x - mapEditConfig_.LEFT_MARGIN) / mapEditConfig_.MAP_IMAGE_SIZE,0,mapEditConfig_.MAP_WIDTH-1),
		std::clamp((rect.y - mapEditConfig_.TOP_MARGIN) / mapEditConfig_.MAP_IMAGE_SIZE,0,mapEditConfig_.MAP_HEIGHT-1),
		std::clamp((rect.x + rect.w - mapEditConfig_.LEFT_MARGIN) / mapEditConfig_.MAP_IMAGE_SIZE,0,mapEditConfig_.MAP_WIDTH-1),
		std::clamp((rect.y + rect.h - mapEditConfig_.TOP_MARGIN) / mapEditConfig_.MAP_IMAGE_SIZE,0,mapEditConfig_.MAP_HEIGHT-1)
	};
	

	//x��-���Ƃ��������]������Ȃ��Ȃ�
	/*int i = gridRect.x;
	while ((i <= gridRect.w && i < mapEditConfig_.MAP_WIDTH ) && i >= 0)
	{
		int j = gridRect.y;
		while ((j <= gridRect.h && j < mapEditConfig_.MAP_HEIGHT ) && j >= 0)
		{
			int idx = i + (j * mapEditConfig_.MAP_WIDTH);
			myMap_[idx] = value;
			j++;
		}
		i++;
	}*/

	//�̈��͈͊O�ɑ���ƍ������łč��̂ق���
	// x��mapEditConfig_.MAP_WIDTH������Ƃ��̕����̍s��
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

void MapEdit::GetMap(Point p) const
{
}

void MapEdit::Fill(int value)
{
#if flag
	//������tile��value
	Point p = { 0,1 };
	int idx;
	//�ߖT�ɂ���checkHImage�ɊY������̂�����
	int checkHImage;
	if (IsInMapEdit(&p))
	{
		idx = p.x + mapEditConfig_.MAP_WIDTH * p.y;
		//�������ӏ���HIage
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
	//�N���b�N�����ӏ���hImage�ƁA�I�𒆂�hImage���ꏏ�Ȃ�return
	if (myMap_[idx] == fillHImage)
	{
		return;
	}
	//���̉ӏ���hImage�����ݓh��Ԃ��ΏۂƈقȂ�Ȃ�return
	if (myMap_[idx] != checkHImage)
	{
		return;
	}
	myMap_[idx] = fillHImage;

	////��
	FillRecursive(fillHImage, checkHImage, ToSafeNeighbor(p, Point{ -1,0 }));
	////�E
	FillRecursive(fillHImage, checkHImage, ToSafeNeighbor(p, Point{ 1,0 }));
	////��
	FillRecursive(fillHImage, checkHImage, ToSafeNeighbor(p, Point{ 0,-1 }));
	////��
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
	//�撣���ăt�@�C���I���_�C�A���O���o��
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//�E�B���h�E�̃I�[�i�[=�e�E�B���h�E�̃n���h��

	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	//�����t�@�C���I���_�C�A���O���\������邾���ŁA�ۑ��{�^���Ƃ������Ă��Ȃ���N���Ȃ���


	//�t�@�C������lpstrFile�ɓn����filename�ɓ����Ă�
	if (GetSaveFileName(&ofn))
	{
		printfDx("�t�@�C�����I�����ꂽ\n");
		//�t�@�C�����J���āA�Z�[�u
		//std::filesystem �t�@�C�����������o��
		//���ꂩ��ofstream���J��
		std::ofstream openfile(filename);



		printfDx("File Saved!!!\n");

		std::ofstream file("data.dat");

		openfile << "#TinyMapData\n";
		//�o�͌��ʂ̃t�@�C��
		//std::ofstream	file("data.dat");



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
		//�t�@�C���̑I�����L�����Z��
		printfDx("�Z�[�u���L�����Z��\n");
	}

}

void MapEdit::LoadMapData()
{
	//�撣���ăt�@�C���I���_�C�A���O���o��
	TCHAR filename[255] = "";
	OPENFILENAME ifn = { 0 };

	ifn.lStructSize = sizeof(ifn);
	//�E�B���h�E�̃I�[�i�[=�e�E�B���h�E�̃n���h��

	ifn.hwndOwner = GetMainWindowHandle();
	ifn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ifn.lpstrFile = filename;
	ifn.nMaxFile = 255;
	//ifn.Flags = OFN_OVERWRITEPROMPT;

	//�����t�@�C���I���_�C�A���O���\������邾���ŁA�ۑ��{�^���Ƃ������Ă��Ȃ���N���Ȃ���

	
	//�t�@�C������lpstrFile�ɓn����filename�ɓ����Ă�
	if (GetOpenFileName(&ifn))
	{
		printfDx("�t�@�C�����I�����ꂽ\n", filename);
		//�t�@�C�����J���āA�Z�[�u
		//std::filesystem �t�@�C�����������o��
		//ifstream���J�� input file stream
		std::ifstream inputfile(filename);
		if (!inputfile)
		{
			std::cerr << "�t�@�C�����J���܂���ł����B" << std::endl;
		}
		//inputfile�̒��ɓǂݍ��񂾕����񂠂��
		std::string str_buf;

		if (inputfile.is_open())
		{
			MapChip* mc = FindGameObject<MapChip>();
			if (getline(inputfile, str_buf))
			{
				
				if (str_buf != "#TinyMapData")
				{
					printfDx("�����ȃt�@�C�����Ǝv���܂�");
					return;
				}
			}
			//std::cerr << "error: failed to open file " << std::endl;
			//��s����
			myMap_.clear();
			while (getline(inputfile, str_buf))
			{
				
#if 1
				//�R���}��؂�œǂݍ��݂Ă���
				std::string data;
				//std::istringstream stream(str_buf);

				std::stringstream sstream(str_buf);

				while (getline(sstream, data, ','))
				{
					int num;
					num = std::stoi(data);
					//printfDx("%i",num);
					//printfDx(" ");
					myMap_.push_back(mc->GetChipHandle(num));
				}
#else
				if (str_buf.empty()) continue;
				if (str_buf[0] != '#')
				{
					std::istringstream iss(str_buf);
					int tmp;
					while (iss >> tmp)
					{

						myMap_.push_back(mc->GetChipHandle(tmp));
					}
				}
#endif
				printfDx("\n");
			}
			//printfDx("File Saved!!!\n");
			//�o�͌��ʂ̃t�@�C��
			//std::ofstream	file("data.dat");
		}
#if 0
		inputfile << "#header" << std::endl;
		inputfile << "WIDTH " << mapEditConfig_.MAP_WIDTH << std::endl;
		inputfile << "HEIGHT " << mapEditConfig_.MAP_HEIGHT << std::endl;
		inputfile << std::endl;
		inputfile << "#data" << std::endl;

		MapChip* mc = FindGameObject<MapChip>();

		for (int y = 0; y < mapEditConfig_.mapEditConfig_.MAP_HEIGHT;y++)
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
				inputfile << index << ",";
			}
			inputfile << std::endl;
		}
		inputfile.close();
	}
	else
	{
		//�t�@�C���̑I�����L�����Z��
		printfDx("�Z�[�u���L�����Z��\n");
	}
#endif
	}
}