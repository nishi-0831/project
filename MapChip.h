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
	int tipOffsetX_;
	int tipOffsetY_;
	void Input();

	bool isUpdate_;
	bool isInMapChipArea_;
	Rect mapChipArea_;
	MapChipConfig mapChipConfig_;
	Point GetViewOrigin() const;
	int GetCorrectIndex(int x, int y) const;

	void DrawMouseOverlapChip();
	void DrawSelectedChip();
	void DrawSelectedChipFrame();
	void DrawMapChipWindow();

	void RegisterInputActions();
	void OnMovement(int x,int y);
	void OnSelection();
	void OnRectSelection();
	void OnMiddleButtonDown();
	void OnMiddleButtonUp();
	void OnRightButtonDown();
public:
	std::vector<int> bgHandle;
	MapChip();
	~MapChip();
	void Update() override;
	void Draw() override;
	void LoadIni();
	bool IsInMapChipArea(Point* point);
	void RectSelect();
	const std::vector<std::pair<Point,int>>& GetSelectedChipVec();
	int GetHImage();
	int GetChipIndex(int handle);
	int GetChipHandle(int index);

};

