#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "global.h"
#include <map>

class MapChip :
    public GameObject
{
private:
	//チップを横スクロールさせたい
	int tipOffset_;
	void Input();

	bool isUpdate_;
	bool isInMapChipArea_;
	Point selected_;
	Rect mapChipArea_;
	int selectedIndex_;
public:
	std::vector<int> bgHandle;
	MapChip();
	~MapChip();
	void Update() override;
	void Draw() override;
	
	bool IsInMapChipArea(Point* point);
	//void File()
	int GetHImage();
	int GetChipIndex(int handle);
	int GetChipHandle(int index);
};

