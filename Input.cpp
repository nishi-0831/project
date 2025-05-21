#include "Input.h"
#include "DxLib.h"
#include "bitset"
#include "string"


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


