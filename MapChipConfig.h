#pragma once
#include <string>
struct MapChipConfig
{
	int TILE_PIX_SIZE;//1�^�C���̃s�N�Z���T�C�Y
	int TILES_X;	//�}�b�v�`�b�v�摜�̉��^�C����
	int TILES_Y;	//�}�b�v�`�b�v�摜�̏c�^�C����

	int MAPCHIP_VIEW_X; //�}�b�v�`�b�v���E�B���h�E�ɕ\�����鐔,X
	int MAPCHIP_VIEW_Y; //�}�b�v�`�b�v���E�B���h�E�ɕ\�����鐔,X
	int MAPCHIP_WIN_WIDTH; //�}�b�v�`�b�v�E�B���h�E�̕�
	int MAPCHIP_WIN_HEIGHT; //�}�b�v�`�b�v�E�B���h�E�̍���
};

//const�œn���ĊԈ���ď������������Ȃ�
//�Q�Ƃ�����R�s�[�̃I�[�o�[�w�b�h�͂Ȃ�
const MapChipConfig& GetMapChipConfig();
MapChipConfig LoadMapChipConfig(const std::string& iniPath);
