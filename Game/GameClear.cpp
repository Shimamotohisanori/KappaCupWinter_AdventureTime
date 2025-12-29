#include "stdafx.h"
#include "GameClear.h"
#include "GameTitle.h"
#include "SoundManager.h"
namespace
{
	const char* PRESS_BUTTON_TO_TITLE_SPRITE_FILEPATH = "Assets/sprite/ClearPressButtonSprite.dds";

	const Vector3 PRESS_BUTTON_TO_TITLE_SPRITE_POS = { 60.0f,-400.0f,0.0f };//ボタンを押してタイトルに戻るの画像の位置
}
GameClear::GameClear()
{
}

GameClear::~GameClear()
{
}

bool GameClear::Start()
{
	m_GameClearRender.Init("Assets/sprite/GameClear1.dds", 1920.0f, 1080.0f);

	p_pressAnyButtonToTitleSpriteRender.Init(PRESS_BUTTON_TO_TITLE_SPRITE_FILEPATH, 1200.0f, 400.0f);
	p_pressAnyButtonToTitleSpriteRender.SetPosition(PRESS_BUTTON_TO_TITLE_SPRITE_POS);

	SoundManager* sound = FindGO<SoundManager>("soundmanager");
	p_gameClearBGM = sound->PlayingSound(enSound_GameClearBGM);

	return true;
}

void GameClear::Update()
{
	GameClearManager();
	FadeManager();
	p_pressAnyButtonToTitleSpriteRender.Update();
}

void GameClear::FadeManager()
{
	switch (p_state)
	{
	case enState_FadeIn:
		p_currentAlpha -= 0.5f * g_gameTime->GetFrameDeltaTime();
		if (p_currentAlpha <= 0.0f)
		{
			p_currentAlpha = 0.0f;
			p_state = enState_FadeOut;
		}
		break;

	case enState_FadeOut:
		p_currentAlpha += 0.5 * g_gameTime->GetFrameDeltaTime();
		if (p_currentAlpha >= 1.0f)
		{
			p_currentAlpha = 1.0f;
			p_state = enState_FadeIn;
		}
		break;
	default:
		break;
	}
}


void GameClear::GameClearManager()
{
	//何かのボタンが押されていたら
	if (g_pad[0]->IsPressAnyKey() && !p_isNewTitle)
	{
		SoundManager* sound = FindGO<SoundManager>("soundmanager");
		p_gameClearDecisionSE = sound->PlayingSound(enSound_DecisionSE, false);

		p_isNewTitle = true;
	}

	if (p_isNewTitle)
	{
		p_deltatime += g_gameTime->GetFrameDeltaTime();
	}

	if (p_deltatime > 3.0f)
	{
		p_isNewTitle = false;
		p_deltatime = 0.0f;
		m_gameTitle = NewGO<GameTitle>(0, "gametitle");
		DeleteGO(p_gameClearBGM);
		DeleteGO(p_gameClearDecisionSE);
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_GameClearRender.Draw(rc);
	if (p_currentAlpha > 0.0f)
	{
		p_pressAnyButtonToTitleSpriteRender.SetMulColor(
			Vector4{
				1.0f,
				1.0f,
				1.0f,
				p_currentAlpha }
				);
		p_pressAnyButtonToTitleSpriteRender.Draw(rc);
	}
}
