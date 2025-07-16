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

	efg.MAP_WIDTH = GetPrivateProfileInt("MapEdit", "MAP_WIDTH", 255, iniPath.c_str());//1タイルのピクセルサイズ
	efg.MAP_HEIGHT = GetPrivateProfileInt("MapEdit", "MAP_HEIGHT", 255, iniPath.c_str());//マップチップ画像の横タイル数
	efg.MAP_IMAGE_SIZE = GetPrivateProfileInt("MapEdit", "MAP_IMAGE_SIZE", 255, iniPath.c_str());//マップチップ画像の縦タイル数
	efg.LEFT_MARGIN = GetPrivateProfileInt("MapEdit", "LEFT_MARGIN", 255, iniPath.c_str());//マップチップをウィンドウに表示する数,X
	efg.TOP_MARGIN = GetPrivateProfileInt("MapEdit", "TOP_MARGIN", 255, iniPath.c_str());//マップチップをウィンドウに表示する数,X

	return efg;
}
