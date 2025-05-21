#pragma once


namespace Input {
	enum Mouse
	{
		LEFT = 0,
		RIGHT,
		MIDDLE,
		MAX
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
}