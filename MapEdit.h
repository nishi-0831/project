#pragma once
#include "Library/GameObject.h"
#include <vector>

namespace
{
    //20かけ20で400、32のサイズのマスでグリッドを作る
    const int MAP_WIDTH = { 20 };
    const int MAP_HEIGHT = { 20 };
    const int MAP_IMAGE_SIZE = { 32 };
    //今は使わない
    const int LEFT_MERGIN = { 100 };
    const int TOP_MERGIN = { 40 };

}
class MapEdit :
    public GameObject
{
    //格子模様書く
    //ツールでエディットしたやつを持ってくる
    std::vector<int> myMap_;
public:
    MapEdit();
    ~MapEdit();
    void Update() override;
    void Draw() override;
};

