#include "Input.h"
#include "DxLib.h"
#include "bitset"
#include "string"
#include <unordered_map>
#include <vector>
namespace Input {
	//�L�[�{�[�h�擾�֘A
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//�L�[�o�b�t�@ (���t���[��)
	char keyBuffOld[KEY_MAX];	//1�O�̃L�[�o�b�t�@(�O�t���[��) 
	char key_down[KEY_MAX];		//�����ꂽ�u�� 
	char key_up[KEY_MAX];		//�����ꂽ�u�� 
	char Key_Keep[KEY_MAX];		//�������ςȂ�

	int mousePrev;//�O�̃t���[���̃}�E�X�̏��
	int mouseNow;//���t���[���̃}�E�X�̏��

	std::bitset<(int)Mouse::MAX> mousePrevBitset;
	std::bitset<(int)Mouse::MAX> mouseNowBitset;

	
	Point down;//�������񂾎��̍��W
	Point up;//��������ł��痣�������̍��W
	static bool rectSelecting;
	static Rect rect;
	static Point mousePos;

	static InputContext currentContext = InputContext::GENERAL;
	static std::unordered_map<std::string, InputAction> registeredActions;
	static std::unordered_map<std::string, InputBinding> actionBindings;
	static std::vector<ContextArea> contextAreas;
}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX);

	GetHitKeyStateAll(keyBuff);//�S�ẴL�[�̏�Ԃ��擾 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) Key_Keep[i]++;
		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//�O�t���[���ƌ��t���[����xor
		if (key_xor) Key_Keep[i] = 0;
		key_down[i] = key_xor & keyBuff[i];		//�����ꂽ�u�� = (���t���[����key_xor��AND) 
		key_up[i] = key_xor & keyBuffOld[i];	//�����ꂽ�u�� = (�O�t���[����key_xor��AND) 
	}
	mousePrev = mouseNow;//�O�̃t���[���̃}�E�X�̏�Ԃ�ۑ�
	mouseNow = GetMouseInput();

	int mouseInput = mouseNow;

	mousePrevBitset = mouseNowBitset;

	for (int i = 0;i < 8;i++)
	{
		int bit = mouseInput % 2;
		for (int j = 0;j < (int)Mouse::MAX;j++)
		{
			mouseNowBitset.reset(j);
		}
		if (bit == 1)
		{
			mouseNowBitset[i] = true;
		}
		
		if ((mouseInput /= 2) == 0)
		{
			break;
		}
		
	}
	
	int x, y;
	GetMousePoint(&x, &y);
	mousePos.x = x;
	mousePos.y = y;

	if (IsButtonDown(Mouse::MIDDLE))
	{
		/*int x, y;
		GetMousePoint(&x, &y);
		down.x = x;
		down.y = y;*/
		down = mousePos;
		rectSelecting = true;
	}

	if (IsButtonKeep(Mouse::MIDDLE) && rectSelecting)
	{
		/*int x, y;
		GetMousePoint(&x, &y);
		up.x = x;
		up.y = y;*/
		up = mousePos;
	}

	if (IsButtonUp(Mouse::MIDDLE) && rectSelecting)
	{
		rectSelecting = false;
	}
	

	//�L�[�̏�Ԃ��擾����֐�
	if (Input::IsMouseDown())
	{
		//DxLib::printfDx("�}�E�X�������ꂽ�u��!\n");
		
	}
	else if (Input::IsMouseUp())
	{
		//DxLib::printfDx("�}�E�X�������ꂽ�u��!\n");
	}
	else if (Input::IsMouseKeep())
	{
		//DxLib::printfDx("�}�E�X��������Ă���!\n");
	}
}
//mouseNow,mousePrev == 0 ������Ă��Ȃ��A != 0 �͉�����Ă���

Rect Input::GetSelectRect()
{
	if (down.x < up.x)
	{
		rect.x = down.x;
		rect.w = up.x - down.x;
	}
	//��������
	else
	{
		rect.x = up.x;
		rect.w = down.x - up.x;
	}

	///y
	if (down.y < up.y)
	{
		rect.y = down.y;
		rect.h = up.y - down.y;
	}
	//��������
	else
	{
		rect.y = up.y;
		rect.h = down.y - up.y;
	}
	return rect;
}

bool Input::IsSelectRect()
{
	return rectSelecting;
}

bool Input::IsMouseInRect(const Rect& rect)
{
	return IsPointInRect(mousePos,rect);
}

const Point& Input::GetMousePos()
{
	return mousePos;
}

void Input::InitializeInputSystem()
{
	registeredActions.clear();
	actionBindings.clear();
	currentContext = InputContext::GENERAL;
}

void Input::UpdateInputSystem()
{
	KeyStateUpdate();
	UpdateInputActions();
}

void Input::SetInputContext(InputContext context)
{
	currentContext = context;
}

Input::InputContext Input::GetCurrentInputContext()
{
	return currentContext;
}
void Input::RegisterAction(const std::string& actionName, const InputBinding& binding, InputActionType type, InputContext context, std::function<void()> callback)
{
	InputAction action;
	action.name = actionName;
	action.type = type;
	action.context = context;
	action.callback = callback;

	registeredActions[actionName] = action;
	actionBindings[actionName] = binding;
}

void Input::EraseAction(const std::string& actionName)
{
	registeredActions.erase(actionName);
	actionBindings.erase(actionName);
}

bool Input::IsInputTriggered(const InputBinding& binding, InputActionType type)
{
	bool triggered = false;

	//�L�[�̓��͂𒲂ׂ�
	if (binding.keyCode != -1)
	{
		//�ǉ��ŉ����Ă��Ȃ���΂����Ȃ��L�[�����邩��
		if (binding.requiresModifier && binding.modifierKey != -1)
		{
			if (!IsKeepKeyDown(binding.modifierKey))
			{
				return false;
			}
		}

		switch (type)
		{
		case InputActionType::PRESSED:
			triggered = IsKeyDown(binding.keyCode);
			break;
		case InputActionType::RELEASED:
			triggered = IsKeyUp(binding.keyCode);
			break;
		case InputActionType::HELD:
			triggered = IsKeepKeyDown(binding.keyCode);
			break;
		}
	}

	//�}�E�X�̓��͂𒲂ׂ�
	if (binding.mouseButton != -1)
	{
		//�ǉ��ŉ����Ă��Ȃ���΂����Ȃ��L�[�����邩��
		if (binding.requiresModifier && binding.modifierKey != -1)
		{
			if (!IsKeepKeyDown(binding.modifierKey))
			{
				return false;
			}
		}
		switch (type)
		{
		case InputActionType::PRESSED:
			triggered = IsButtonDown(binding.mouseButton);
			break;
		case InputActionType::RELEASED:
			triggered = IsButtonUp(binding.mouseButton);
			break;
		case InputActionType::HELD:
			triggered = IsButtonKeep(binding.mouseButton);
			break;
		}
	}

	return triggered;
}
void Input::UpdateInputActions()
{
	for (const auto& pair : registeredActions)
	{
		const InputAction& action = pair.second;

		//���݂̕����ƈ�ʓI�ȕ����̃A�N�V����������������
		if (action.context != currentContext && action.context != InputContext::GENERAL)
		{
			continue;
		}

		//�������O���L�[�ɂȂ��Ă�InputBinding��T��
		const InputBinding& binding = actionBindings[pair.first];

		if (IsInputTriggered(binding, action.type))
		{
			action.callback();
		}
	}
}
void Input::UpdateContext()
{
	for (auto& contextArea : contextAreas)
	{
		if (IsMouseInRect(contextArea.area))
		{
			SetInputContext(contextArea.context);
			break;
		}
	}
}
void Input::SetInputContextArea(const Rect& rect, InputContext context)
{
	contextAreas.push_back(ContextArea{ rect, context });
}
bool Input::IsKeyUp(int keyCode)
{
	return(key_up[keyCode]);
}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

int Input::IsKeepKeyDown(int keyCode)
{
	return(Key_Keep[keyCode]);
}

bool Input::IsMouseDown()
{
	//�����ꂽ�u��
	//�}�E�X�̏�Ԃ��擾
	//return (mouseNow && !mousePrev)
	if (IsUp(mousePrev) && IsDown(mouseNow))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Input::IsMouseUp()
{
	//�b���ꂽ�u�Ԃ�
	// 0�������牟����Ă��Ȃ�
	//�O�񉟂���Ă��āA����͉����ĂȂ�
	//return (mouseNow && mousePrev)
	if (IsDown(mousePrev) && IsUp(mouseNow))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input::IsMouseKeep()
{
	//�O��������
	if (IsDown(mousePrev) && IsDown(mouseNow))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input::IsDown(int mouse)
{
	if ((mouse & MOUSE_INPUT_LEFT) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input::IsUp(int mouse)
{
	if ((mouse & MOUSE_INPUT_LEFT) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Input::Calculate()
{

}	

bool Input::IsButtonDown(int button)
{
	return (mouseNowBitset.test(button)) && !(mousePrevBitset.test(button));
}

bool Input::IsButtonUp(int button)
{
	return !(mouseNowBitset.test(button)) && (mousePrevBitset.test(button));
}

bool Input::IsButtonKeep(int button)
{
	return (mouseNowBitset.test(button)) && (mousePrevBitset.test(button));
}




