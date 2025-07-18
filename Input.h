#pragma once
#include "global.h"

namespace Input {
	enum Mouse
	{
		LEFT = 0,
		RIGHT,
		MIDDLE,
		MAX
	};

	//キーボード取得関連
	//キーボードの状態を更新
	void KeyStateUpdate();
	//キーが離された瞬間
	bool IsKeyUp(int keyCode);
	//キーが押された瞬間(押下)
	bool IsKeyDown(int keyCode);
	//キーが押されている間
	int IsKeepKeyDown(int keyCode);

	bool IsMouseDown(); //
	bool IsMouseUp(); //マウスが離された瞬間
	bool IsMouseKeep(); //マウスが押されている間

	bool IsDown(int mouse); //
	bool IsUp(int mouse); //離している
	
	void Calculate();
	
	bool IsButtonDown(int button);
	bool IsButtonUp(int button);
	bool IsButtonKeep(int button);

	Rect GetSelectRect();
	bool IsSelectRect();
	bool IsMouseInRect(const Rect& rect);
}