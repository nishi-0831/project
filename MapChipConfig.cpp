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
	cfg. TILE_PIX_SIZE= GetPrivateProfileInt("MapChip","TILE_PIX_SIZE",255,iniPath.c_str());//1タイルのピクセルサイズ
	cfg. TILES_X=	 GetPrivateProfileInt("MapChip","TILES_X",255,iniPath.c_str());//マップチップ画像の横タイル数
	cfg. TILES_Y=	 GetPrivateProfileInt("MapChip","TILES_Y",255,iniPath.c_str());//マップチップ画像の縦タイル数
	cfg. MAPCHIP_VIEW_X=  GetPrivateProfileInt("MapChip","MAPCHIP_VIEW_X",255,iniPath.c_str());//マップチップをウィンドウに表示する数,X
	cfg.MAPCHIP_VIEW_Y = GetPrivateProfileInt("MapChip", "MAPCHIP_VIEW_Y", 255, iniPath.c_str());//マップチップをウィンドウに表示する数,X
	cfg.MAPCHIP_WIN_WIDTH = cfg.TILE_PIX_SIZE * cfg.MAPCHIP_VIEW_X;//マップチップウィンドウの幅
	cfg.MAPCHIP_WIN_HEIGHT = cfg.TILE_PIX_SIZE * cfg.MAPCHIP_VIEW_Y; //マップチップウィンドウの高さ
	return cfg;
}
