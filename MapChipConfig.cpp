#include "MapChipConfig.h"

#include <windows.h>

const MapChipConfig& GetMapChipConfig()
{
	static MapChipConfig config = LoadMapChipConfig(".\\mySetup.ini");
	return config;
}

MapChipConfig LoadMapChipConfig(const std::string& iniPath)
{
	MapChipConfig cfg;
	cfg. TILE_PIX_SIZE= GetPrivateProfileInt("MapChip","TILE_PIX_SIZE",255,iniPath.c_str());//1�^�C���̃s�N�Z���T�C�Y
	cfg. TILES_X=	 GetPrivateProfileInt("MapChip","TILES_X",255,iniPath.c_str());//�}�b�v�`�b�v�摜�̉��^�C����
	cfg. TILES_Y=	 GetPrivateProfileInt("MapChip","TILES_Y",255,iniPath.c_str());//�}�b�v�`�b�v�摜�̏c�^�C����
	cfg. MAPCHIP_VIEW_X=  GetPrivateProfileInt("MapChip","MAPCHIP_VIEW_X",255,iniPath.c_str());//�}�b�v�`�b�v���E�B���h�E�ɕ\�����鐔,X
	cfg.MAPCHIP_VIEW_Y = GetPrivateProfileInt("MapChip", "MAPCHIP_VIEW_Y", 255, iniPath.c_str());//�}�b�v�`�b�v���E�B���h�E�ɕ\�����鐔,X
	cfg.MAPCHIP_WIN_WIDTH = cfg.TILE_PIX_SIZE * cfg.MAPCHIP_VIEW_X;//�}�b�v�`�b�v�E�B���h�E�̕�
	cfg.MAPCHIP_WIN_HEIGHT = cfg.TILE_PIX_SIZE * cfg.MAPCHIP_VIEW_Y; //�}�b�v�`�b�v�E�B���h�E�̍���
	return cfg;
}
