#pragma once
#include <functional>
#include <vector>




	//�񎟌��x�N�g��(����)
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
				//�Ⴆ��(18,0)��(0,18)�������n�b�V���l�ɂȂ�Ȃ��悤��
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

	//�񎟌��x�N�g��(���������_��)
	struct Pointf
	{
		float x;
		float y;
	};

	//��`(������)��\����
	struct Rect
	{
		int x;//����x
		int y;//����y
		int w;//��
		int h;//����
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
//	const int CHA_SIZE = 32;//�L�����N�^�[�̃T�C�Y
//
//	const int STAGE_WIDTH = 39;
//	const int STAGE_HEIGHT = 21;
//}