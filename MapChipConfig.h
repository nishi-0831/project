#pragma once
#include <string>
struct MapChipConfig
{
	int TILE_PIX_SIZE;//1タイルのピクセルサイズ
	int TILES_X;	//マップチップ画像の横タイル数
	int TILES_Y;	//マップチップ画像の縦タイル数

	int MAPCHIP_VIEW_X; //マップチップをウィンドウに表示する数,X
	int MAPCHIP_VIEW_Y; //マップチップをウィンドウに表示する数,X
	int MAPCHIP_WIN_WIDTH; //マップチップウィンドウの幅
	int MAPCHIP_WIN_HEIGHT; //マップチップウィンドウの高さ
};

//constで渡して間違って書き換えさせない
//参照だからコピーのオーバーヘッドはない
const MapChipConfig& GetMapChipConfig();
MapChipConfig LoadMapChipConfig(const std::string& iniPath);
