#include "MapEditConfig.h"

#include <Windows.h>
const MapEditConfig& GetMapEditConfig()
{
	static MapEditConfig config = LoadMapEditConfig(".\\mySetup.ini");
	return config;
}

MapEditConfig LoadMapEditConfig(const std::string& iniPath)
{
	MapEditConfig efg;

	efg.MAP_WIDTH = GetPrivateProfileInt("MapEdit", "MAP_WIDTH", 255, iniPath.c_str());//1�^�C���̃s�N�Z���T�C�Y
	efg.MAP_HEIGHT = GetPrivateProfileInt("MapEdit", "MAP_HEIGHT", 255, iniPath.c_str());//�}�b�v�`�b�v�摜�̉��^�C����
	efg.MAP_IMAGE_SIZE = GetPrivateProfileInt("MapEdit", "MAP_IMAGE_SIZE", 255, iniPath.c_str());//�}�b�v�`�b�v�摜�̏c�^�C����
	efg.LEFT_MARGIN = GetPrivateProfileInt("MapEdit", "LEFT_MARGIN", 255, iniPath.c_str());//�}�b�v�`�b�v���E�B���h�E�ɕ\�����鐔,X
	efg.TOP_MARGIN = GetPrivateProfileInt("MapEdit", "TOP_MARGIN", 255, iniPath.c_str());//�}�b�v�`�b�v���E�B���h�E�ɕ\�����鐔,X

	return efg;
}
