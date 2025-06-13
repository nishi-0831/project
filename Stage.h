#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "MapChip.h"
#include "MapEdit.h"

class Stage :
    public GameObject
{
private:
	//std::vector<int> bgHandleVec_;//�w�i�摜�̃n���h���̔z��
    MapChip* mapChip_; //�}�b�v�`�b�v�̃|�C���^
    MapEdit* mapEdit_;

    //int* bgHandle;//�w�i�摜�̃n���h���̔z��ւ̃|�C���^
    int tipNum;
    int hImage;
public:

    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
    int GetHImage();
};

//playscene��stage�N���X�̃C���X�^���X������āA
//playScene�ɁAbg.png���\�������

