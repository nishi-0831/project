#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "global.h"
#include <map>
#include "MapChipConfig.h"

class MapChip :
    public GameObject
{
private:
	//チップを横スクロールさせたい
	int tipOffsetX_;
	int tipOffsetY_;
	void Input();

	bool isUpdate_;
	bool isInMapChipArea_;
	//Point selected_;
	Rect mapChipArea_;
	//int selectedIndex_;
	MapChipConfig mapChipConfig_;
	Point GetViewOrigin() const;
public:
	std::vector<int> bgHandle;
	MapChip();
	~MapChip();
	void Update() override;
	void Draw() override;
	void LoadIni();
	bool IsInMapChipArea(Point* point);
	//void File()
	int GetHImage();
	int GetChipIndex(int handle);
	int GetChipHandle(int index);
};

