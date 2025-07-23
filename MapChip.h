#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "global.h"
#include <map>

class MapChip :
    public GameObject
{
	
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
	int GetHImage();
};

