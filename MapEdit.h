#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "global.h"
namespace
{
    //20かけ20で400、32のサイズのマスでグリッドを作る
    const int MAP_WIDTH = { 20 };
    const int MAP_HEIGHT = { 20 };
    const int MAP_IMAGE_SIZE = { 32 };
    //今は使わない
    const int LEFT_MARGIN = { 100 };
    const int TOP_MARGIN = { 40 };

}
class MapEdit :
    public GameObject
{
    //格子模様書く
    //ツールでエディットしたやつを持ってくる
    std::vector<int> myMap_;
	Rect mapEditArea_;
public:
    MapEdit();
    ~MapEdit();
    void Update() override;
    void Draw() override;
    void SetMap(int value);
    void GetMap(Point p) const;
    void Fill(int value);
    void FillRecursive(int fillHImage, int checkHImage, Point p);
    Point ToSafeNeighbor(Point start, Point movement);
    bool IsInMapEdit(Point* p);
};

