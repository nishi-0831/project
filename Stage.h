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

    void RegisterInputActions();
    void OnPaint();
    void OnFill();
    void OnErase();
    void OnEraseFill();
public:

    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
    int GetHImage();

    
};

