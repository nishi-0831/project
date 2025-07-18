#pragma once
#include <functional>
#include <vector>




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
		bool operator==(const Point& other)const
		{
			return (x == other.x && y == other.y);
		}
	};

	namespace std
	{
		template<>
		struct hash<Point>
		{
			size_t operator()(const Point& p) const
			{
				//例えば(18,0)と(0,18)が同じハッシュ値にならないように
				return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
			}
		};
	}

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

	static bool IsPointInRect(const Point& point,const Rect& rect)
	{
		bool ret = false;

		if(rect.x <= point.x && rect.x + rect.w >= point.x
		&& rect.y <= point.y && rect.y + rect.h >= point.y)
		{
			ret = true;
		}

		return ret;
	}

//namespace
//{
//	const int CHA_SIZE = 32;//キャラクターのサイズ
//
//	const int STAGE_WIDTH = 39;
//	const int STAGE_HEIGHT = 21;
//}