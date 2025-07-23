#pragma once
#include "Library/GameObject.h"
#include <vector>
#include <algorithm>
#include "global.h"
#include "MapEditConfig.h"
namespace
{
    //20����20��400�A32�̃T�C�Y�̃}�X�ŃO���b�h�����
    int MAP_WIDTH;
    int MAP_HEIGHT;
    int MAP_IMAGE_SIZE;
    int LEFT_MARGIN;
    int TOP_MARGIN;

    /*
    const int MAP_WIDTH = { 20 };
    const int MAP_HEIGHT = { 20 };
    const int MAP_IMAGE_SIZE = { 32 };
    //���͎g��Ȃ�
    const int LEFT_MARGIN = { 100 };
    const int TOP_MARGIN = { 40 };
    */
}
class MapEdit :
    public GameObject
{
    //�i�q�͗l����
    //�c�[���ŃG�f�B�b�g������������Ă���
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

