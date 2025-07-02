#include "Stage.h"
#include "Input.h"
#include "DxLib.h"
//const int IMAGE_SIZE = { 32 };
//
////�}�b�v�̃`�b�v��
//const int MAP_WIDTH{ 32 };
//const int MAP_HEIGHT{ 32 };
//
////���ɂ�0����15
////�摜�̃`�b�v��
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

Stage::Stage()
	: GameObject()
{
	
	//bgHandleVec_.resize(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT,-1);
	//bgHandleVec_ = std::vector<int>(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, -1);
	////vector�̒��̐l�A�f�[�^�ɃA�N�Z�X����
	//LoadDivGraph("bg.png",MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, IMAGE_SIZE, IMAGE_SIZE,
	//	bgHandleVec_.data());
	//hImage = LoadGraph("bg.png", 0);

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
		DxLib::printfDx("���������ꂽ�u��!\n");
	}
	if (Input::IsButtonKeep(Input::Mouse::LEFT))
	{
		//DxLib::printfDx("����������Ă�\n");
	}
	if (Input::IsButtonDown(Input::Mouse::RIGHT))
	{
		DxLib::printfDx("�E�������ꂽ�u��!\n");
	}
	if (Input::IsButtonUp(Input::Mouse::RIGHT))
	{
		DxLib::printfDx("�E�������ꂽ�u��!\n");
	}
	if (Input::IsButtonKeep(Input::Mouse::RIGHT))
	{
		//DxLib::printfDx("�E��������Ă���!\n");
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
		
		int hImage = mapChip_->GetHImage();
		mapEdit_->SetMap(hImage);
	}
	if (Input::IsButtonDown(Input::Mouse::RIGHT))
	{
		if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
		{
			int hImage = -1;
			mapEdit_->Fill(hImage);
		}
	}
	//�����S���I�ȋ@�\
	if (Input::IsButtonKeep(Input::Mouse::RIGHT))
	{
		int hImage = -1;
		mapEdit_->SetMap(hImage);
	}
	
	
}

void Stage::Draw()
{
	//for (int i = 0;i < MAP_HEIGHT;i++)
	//{
	//	for (int j = 0;j < MAP_WIDTH;j++)
	//	{
	//		//�O���b�h�`�悵�Ă���

	//		//�c��
	//		int verticalLineX = topLeft_x + x * IMAGE_SIZE;
	//		DrawLine(verticalLineX, 0, verticalLineX, MAP_CHIP_WIN_HEIGHT, GetColor(255, 255, 255));
	//		//������
	//		int holizontalLineY = y * IMAGE_SIZE;
	//		DrawLine(topLeft_x, holizontalLineY, Screen::WIDTH, holizontalLineY, GetColor(255, 255, 255));

	//		int chi = myMap[i][j];

	//		/*if (bgHandleVec_[chi] == -1)
	//		{
	//			continue;
	//		}
	//		DrawGraph(j * IMAGE_SIZE, i * IMAGE_SIZE, bgHandleVec_[chi], TRUE);*/
	//	}
	//}
}

int Stage::GetHImage()
{
	return 0;
}
