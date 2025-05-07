#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "MapChip.h"

class Stage :
    public GameObject
{
private:
	std::vector<int> bgHandleVec_;//背景画像のハンドルの配列
    MapChip* mapChip_; //マップチップのポインタ

    int* bgHandle;//背景画像のハンドルの配列へのポインタ
    int tipNum;
    int hImage;
public:

    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
};

//playsceneでstageクラスのインスタンスを作って、
//playSceneに、bg.pngが表示される

