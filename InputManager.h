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
	/// �n�����L�[�ɉ��������͂̎�����Ԃ��Ă����
	/// </summary>
	/// <param name="keyCode">�L�[</param>
	/// <param name="modifierKey">keyCode�ɉ����ĉ����Ă��Ȃ���΂����Ȃ��L�[�B�f�t�H���g��-1(����)</param>
	/// <returns></returns>
	Input::InputBinding CreateKeyBinding(int keyCode,int modifierKey = -1);
	Input::InputBinding CreateMouseBinding(int mouseButton,int modifierKey = -1);
private:
	InputManager() = default;
	Input::InputContext currentContext = Input::InputContext::GENERAL;

};

