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
	//�O�g
	int topLeftX = 0 + LEFT_MERGIN;
	int topLeftY = 0 + TOP_MERGIN;
	int bottomLightX = MAP_IMAGE_SIZE * MAP_WIDTH + LEFT_MERGIN;
	int bottomLightY = MAP_IMAGE_SIZE * MAP_HEIGHT + TOP_MERGIN;
	DrawBox(topLeftX, topLeftY, bottomLightX-1, bottomLightY-1, GetColor(122, 122, 122), FALSE,3);

	//�O���b�h��������
	//�܂��c�� IMAGE_SIZE�̊Ԋu��MAP_WIDTH�񂾂�����
	
	//x,y���ꂼ��O�g�̍ŏ��ɏ������A0�Ԗڂ̍s�A��ŊO�g��h��Ԃ��Ă��܂��Ă���
	//�C�e���[�^��1����n�߂�Ƃ�?
	for (int i = 1;i < MAP_WIDTH;i++)
	{
		//�}�[�W�����l�����Ȃ��Ƃ�
		//�N�_���I�_��x�͓����B�c��������
		int x = i * MAP_IMAGE_SIZE + LEFT_MERGIN;

		//�N�_��y
		int startY = topLeftY;
		//�I�_��y
		int endY = bottomLightY;

		DrawLine(x, startY, x, endY, GetColor(255, 0, 0), 1);
	}
	for (int i = 1;i < MAP_HEIGHT;i++)
	{
		//�N�_���I�_��y�͓����B����������
		int y = i * MAP_IMAGE_SIZE + TOP_MERGIN;

		//�N�_��x
		int startX = topLeftX;
		int endX = bottomLightX;

		DrawLine(startX, y, endX, y, GetColor(255, 0, 0), 1);
	}
}
