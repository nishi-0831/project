#pragma once
#include "Input.h"
class InputManager
{
public:
	static InputManager& GetInstance();

	void Initialize();
	void Update();

	void SetContext(Input::InputContext context);

	Input::InputContext GetContext() const;

	/// <summary>
	/// 渡したキーに応じた入力の取り方を返してくれる
	/// </summary>
	/// <param name="keyCode">キー</param>
	/// <param name="modifierKey">keyCodeに加えて押していなければいけないキー。デフォルトで-1(無効)</param>
	/// <returns></returns>
	Input::InputBinding CreateKeyBinding(int keyCode,int modifierKey = -1);
	Input::InputBinding CreateMouseBinding(int mouseButton,int modifierKey = -1);
private:
	InputManager() = default;
	Input::InputContext currentContext = Input::InputContext::GENERAL;

};

