#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "MapChip.h"
#include "MapEdit.h"

class Stage :
    public GameObject
{
private:
	//std::vector<int> bgHandleVec_;//背景画像のハンドルの配列
    MapChip* mapChip_; //マップチップのポインタ
    MapEdit* mapEdit_;

    //int* bgHandle;//背景画像のハンドルの配列へのポインタ
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

