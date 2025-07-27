#pragma once
#include "global.h"
#include <string>
namespace Input {
	enum Mouse
	{
		LEFT = 0,
		RIGHT,
		MIDDLE,
		MAX
	};

	enum class InputActionType
	{
		PRESSED,
		RELEASED,
		HELD
	};
	

	//入力の文脈
	enum class InputContext
	{
		GENERAL,//どちらでも
		MAP_EDIT,//MapEdit
		MAP_CHIP,//MapChip
	};
	struct ContextArea
	{
		Rect area;
		Input::InputContext context;
	};
	
	struct InputAction
	{
		std::string name;//名前
		InputActionType type;//入力の種類
		InputContext context;//入力の文脈
		std::function<void()> callback;//アクション(関数)
	};

	//何のキー、またはマウスのボタンなのか
	struct InputBinding
	{
		int keyCode = -1;
		int mouseButton = -1;
		int modifierKey = -1;//keyCodeともう一つキーコード
		bool requiresModifier = false;//二つ押していなければいけないのか
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

	void SetInputContextArea(const Rect& rect, InputContext context);

	const Point& GetMousePos();

	void InitializeInputSystem();
	void UpdateInputSystem();
	void SetInputContext(InputContext context);
	InputContext GetCurrentInputContext();
	void RegisterAction(const std::string& actionName, const InputBinding& binding,
		InputActionType type, InputContext context, std::function<void()> callback);

	void EraseAction(const std::string& actionName);

	bool IsInputTriggered(const InputBinding& binding, InputActionType type);
	void UpdateInputActions();
	void UpdateContext();
}