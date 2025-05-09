#pragma once
#include "Library/GameObject.h"
#include <vector>

namespace
{
    //20����20��400�A32�̃T�C�Y�̃}�X�ŃO���b�h�����
    const int MAP_WIDTH = { 20 };
    const int MAP_HEIGHT = { 20 };
    const int MAP_IMAGE_SIZE = { 32 };
    //���͎g��Ȃ�
    const int LEFT_MERGIN = { 100 };
    const int TOP_MERGIN = { 40 };

}
class MapEdit :
    public GameObject
{
    //�i�q�͗l����
    //�c�[���ŃG�f�B�b�g������������Ă���
    std::vector<int> myMap_;
public:
    MapEdit();
    ~MapEdit();
    void Update() override;
    void Draw() override;
};

