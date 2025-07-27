#include "InputManager.h"
#include <DxLib.h>

namespace
{
    
}
InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::Initialize()
{
    Input::InitializeInputSystem();
}

void InputManager::Update()
{
    Input::UpdateContext();
    Input::UpdateInputSystem();
}

void InputManager::SetContext(Input::InputContext context)
{
    currentContext = context;
    Input::SetInputContext(context);
}

Input::InputContext InputManager::GetContext() const
{
    return Input::InputContext();
}


Input::InputBinding InputManager::CreateKeyBinding(int keyCode, int modifierKey)
{
    Input::InputBinding binding;
    binding.keyCode = keyCode;
    if (modifierKey != -1)
    {
        binding.modifierKey = modifierKey;
        binding.requiresModifier = true;
    }
    return binding;
}

Input::InputBinding InputManager::CreateMouseBinding(int mouseButton, int modifierKey)
{
    Input::InputBinding binding;
    binding.mouseButton = mouseButton;
    if (modifierKey != -1)
    {
        binding.modifierKey = modifierKey;
        binding.requiresModifier = true;
    }
    return binding;
}
