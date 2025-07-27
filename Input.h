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
	

	//���͂̕���
	enum class InputContext
	{
		GENERAL,//�ǂ���ł�
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
		std::string name;//���O
		InputActionType type;//���͂̎��
		InputContext context;//���͂̕���
		std::function<void()> callback;//�A�N�V����(�֐�)
	};

	//���̃L�[�A�܂��̓}�E�X�̃{�^���Ȃ̂�
	struct InputBinding
	{
		int keyCode = -1;
		int mouseButton = -1;
		int modifierKey = -1;//keyCode�Ƃ�����L�[�R�[�h
		bool requiresModifier = false;//������Ă��Ȃ���΂����Ȃ��̂�
	};

	
	//�L�[�{�[�h�擾�֘A
	//�L�[�{�[�h�̏�Ԃ��X�V
	void KeyStateUpdate();
	//�L�[�������ꂽ�u��
	bool IsKeyUp(int keyCode);
	//�L�[�������ꂽ�u��(����)
	bool IsKeyDown(int keyCode);
	//�L�[��������Ă����
	int IsKeepKeyDown(int keyCode);

	bool IsMouseDown(); //
	bool IsMouseUp(); //�}�E�X�������ꂽ�u��
	bool IsMouseKeep(); //�}�E�X��������Ă����

	bool IsDown(int mouse); //
	bool IsUp(int mouse); //�����Ă���
	
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