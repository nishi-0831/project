#pragma once
#include "Library/GameObject.h"
#include <vector>
#include <algorithm>
#include "global.h"
#include "MapEditConfig.h"
namespace
{
    int MAP_WIDTH;
    int MAP_HEIGHT;
    int MAP_IMAGE_SIZE;
    int LEFT_MARGIN;
    int TOP_MARGIN;
}
class MapEdit :
    public GameObject
{
    std::vector<int> myMap_;
	Rect mapEditArea_;
    MapEditConfig mapEditConfig_;

    void RegisterInputActions();
    void OnMiddleButtonDown();
    void OnMiddleButtonUp();
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
    //value�Ŗ�����
    void Fill(int value);
    void FillRecursive(int fillHImage, int checkHImage, Point p);
    //�}�E�X�ō������`�͈̔͂𖞂���
    void RectFill(int value);
    Point ToSafeNeighbor(Point start, Point movement);
    bool IsInMapEdit(Point* p);
    void SaveMapData();
    
    void LoadMapData();
};

