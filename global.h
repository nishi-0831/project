#pragma once

namespace
{


	//二次元ベクトル(整数)
	struct Point
	{
		int x;
		int y;
		//type operator operator-symbol ( parameter-list )
		bool operator<(const Point& rhs)
		{
			return (x + x * y < rhs.x + rhs.x * rhs.y);
		}
	};

	inline Point Add(Point a, Point b)
	{
		a.x += b.x;
		a.y += b.y;
		return a;
	}

	//二次元ベクトル(浮動小数点数)
	struct Pointf
	{
		float x;
		float y;
	};

	//矩形(くけい)を表すよ
	struct Rect
	{
		int x;//左上x
		int y;//左上y
		int w;//幅
		int h;//高さ
	};

	enum DIR
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		MAX_DIR
	};

	static const Point moveDirArray[(int)DIR::MAX_DIR] = {
			{0,-1},
			{0,1},
			{-1,0},
			{1,0},
			{0,0}
	};



	const int CHA_SIZE = 32;//キャラクターのサイズ

	const int STAGE_WIDTH = 39;
	const int STAGE_HEIGHT = 21;
}