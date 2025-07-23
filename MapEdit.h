#pragma once
#include "Library/GameObject.h"
#include <vector>
#include <algorithm>
#include "global.h"
#include "MapEditConfig.h"
namespace
{
    //20かけ20で400、32のサイズのマスでグリッドを作る
    int MAP_WIDTH;
    int MAP_HEIGHT;
    int MAP_IMAGE_SIZE;
    int LEFT_MARGIN;
    int TOP_MARGIN;

    /*
    const int MAP_WIDTH = { 20 };
    const int MAP_HEIGHT = { 20 };
    const int MAP_IMAGE_SIZE = { 32 };
    //今は使わない
    const int LEFT_MARGIN = { 100 };
    const int TOP_MARGIN = { 40 };
    */
}
class MapEdit :
    public GameObject
{
    //格子模様書く
    //ツールでエディットしたやつを持ってくる
    std::vector<int> myMap_;
	Rect mapEditArea_;
    MapEditConfig mapEditConfig_;
public:
    MapEdit();
    ~MapEdit();
    void Update() override;
    void Draw() override;
    void DrawSelectRect();
    void SetSelectRect();
    void SetMap(int value);
    void SetMapVec(const std::vector<std::pair<Point, int>>& vec);
    void GetMap(Point p) const;
    //valueで満たす
    void Fill(int value);
    void FillRecursive(int fillHImage, int checkHImage, Point p);
    //マウスで作った矩形の範囲を満たす
    void RectFill(int value);
    Point ToSafeNeighbor(Point start, Point movement);
    bool IsInMapEdit(Point* p);
    void SaveMapData();
    
    void LoadMapData();
};

