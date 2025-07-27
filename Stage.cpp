#include "Stage.h"
#include "Input.h"
#include "DxLib.h"
#include "InputManager.h"

namespace
{
	Rect rect;
}

using namespace Input;

void Stage::RegisterInputActions()
{
	InputManager& inputManager = InputManager::GetInstance();
	InputContext context = InputContext::GENERAL;

	InputBinding leftClickBinding;
	leftClickBinding.mouseButton = Mouse::LEFT;
	RegisterAction("stage_paint", leftClickBinding, InputActionType::HELD,
		context, [this]() { OnPaint(); });

	InputBinding leftClickAndLShiftBinding = inputManager.CreateMouseBinding(Mouse::LEFT,KEY_INPUT_LSHIFT);
	RegisterAction("stage_fill", leftClickAndLShiftBinding, InputActionType::PRESSED,
		context, [this]() { OnFill(); });

	InputBinding rightClickBinding;
	rightClickBinding.mouseButton = Mouse::RIGHT;
	RegisterAction("stage_erase", rightClickBinding, InputActionType::HELD,
		context, [this]() { OnErase(); });

	RegisterAction("stage_erase_fill", inputManager.CreateMouseBinding(Mouse::RIGHT, KEY_INPUT_LSHIFT), InputActionType::PRESSED,
		context, [this]() { OnEraseFill(); });
}
void Stage::OnPaint()
{
	mapEdit_->SetMapVec(mapChip_->GetSelectedChipVec());
}
void Stage::OnFill()
{
	int hImage = mapChip_->GetHImage();
	mapEdit_->Fill(hImage);
}
void Stage::OnErase()
{	
	int hImage = -1;
	mapEdit_->SetMap(hImage);
}
void Stage::OnEraseFill()
{
	int hImage = -1;
	mapEdit_->Fill(hImage);
}
Stage::Stage()
	: GameObject()
{
	InputManager::GetInstance().Initialize();
	mapChip_ = new MapChip();
	mapEdit_ = new MapEdit();
	RegisterInputActions();
	SetDrawOrder(-1);
}

Stage::~Stage()
{
}

void Stage::Update()
{
	InputManager::GetInstance().Update();	
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (!IsSelectRect())
	{
		return;
	}
	rect = GetSelectRect();
	DrawBoxAA(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, GetColor(0, 200, 0), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int Stage::GetHImage()
{
	return 0;
}
