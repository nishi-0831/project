#include "Input.h"
#include "DxLib.h"
#include "bitset"
#include "string"


namespace Input {
	//キーボード取得関連
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//キーバッファ (現フレーム)
	char keyBuffOld[KEY_MAX];	//1つ前のキーバッファ(前フレーム) 
	char key_down[KEY_MAX];		//押された瞬間 
	char key_up[KEY_MAX];		//離された瞬間 
	char Key_Keep[KEY_MAX];		//押しっぱなし

	int mousePrev;//前のフレームのマウスの状態
	int mouseNow;//現フレームのマウスの状態

	std::bitset<(int)Mouse::MAX> mousePrevBitset;
	std::bitset<(int)Mouse::MAX> mouseNowBitset;
}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX);

	GetHitKeyStateAll(keyBuff);//全てのキーの状態を取得 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) Key_Keep[i]++;
		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//前フレームと現フレームのxor
		if (key_xor) Key_Keep[i] = 0;
		key_down[i] = key_xor & keyBuff[i];		//押された瞬間 = (現フレームとkey_xorのAND) 
		key_up[i] = key_xor & keyBuffOld[i];	//離された瞬間 = (前フレームとkey_xorのAND) 
	}
	mousePrev = mouseNow;//前のフレームのマウスの状態を保存
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
	
	
	

	//キーの状態を取得する関数
	if (Input::IsMouseDown())
	{
		//DxLib::printfDx("マウスが押された瞬間!\n");
		
	}
	else if (Input::IsMouseUp())
	{
		//DxLib::printfDx("マウスが離された瞬間!\n");
	}
	else if (Input::IsMouseKeep())
	{
		//DxLib::printfDx("マウスが押されている!\n");
	}



	
	
}
//mouseNow,mousePrev == 0 押されていない、 != 0 は押されている



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
	//押された瞬間
	//マウスの状態を取得
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
	//話された瞬間か
	// 0だったら押されていない
	//前回押されていて、今回は押してない
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
	//前回も今回も
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


