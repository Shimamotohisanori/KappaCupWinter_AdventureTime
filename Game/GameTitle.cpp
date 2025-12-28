#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"
#include "SoundManager.h"
namespace
{
	const char* TITLE_SPRITE_FILEPATH = "Assets/sprite/GameTitle1.dds";
	const char* TITLE_PRESS_BUTTON_SPRITE_FILEPATH = "Assets/sprite/TitlePressButtonSprite.dds";

	const Vector3 TITLE_PRESS_BUTTON_SPRITE_POS = { 0.0f,-400.0f,0.0f };//ボタンを押してスタートの画像の位置
}
GameTitle::GameTitle()
{
}

GameTitle::~GameTitle()
{
}

bool GameTitle::Start()
{
	p_titleSpriteRender.Init(TITLE_SPRITE_FILEPATH, 1920.0f, 1080.0f);
	
	p_titlePressButtonSpriteRender.Init(TITLE_PRESS_BUTTON_SPRITE_FILEPATH,1200.0f,200.0f);
	p_titlePressButtonSpritePos = TITLE_PRESS_BUTTON_SPRITE_POS;
	p_titlePressButtonSpriteRender.SetPosition(p_titlePressButtonSpritePos);
	//PlayingSound()を使用するため、SoundManagerのインスタンスを取得。
	SoundManager* sound = FindGO<SoundManager>("soundmanager");
	//BGMの再生
	p_titleBGM = sound->PlayingSound(enSound_GameTitleBGM,true,0.5f);
	return true;
}

void GameTitle::Update()
{
	TitleManager();
	FadeManager();
	p_titleSpriteRender.Update();
	p_titlePressButtonSpriteRender.Update();
}

void GameTitle::TitleManager()
{
	//何かのボタンが押されていたら
	if (g_pad[0]->IsPressAnyKey() && !p_isNewGame)
	{
		SoundManager* sound = FindGO<SoundManager>("soundmanager");
		p_titleDecisionSE = sound->PlayingSound(enSound_DecisionSE, false);

		p_isNewGame = true;
	}

	if (p_isNewGame)
	{
		p_deltatime += g_gameTime->GetFrameDeltaTime();
	}

	if (p_deltatime > 3.0f)
	{
		p_isNewGame = false;
		p_deltatime = 0.0f;
		p_game = NewGO<Game>(0, "game");
		DeleteGO(p_titleBGM);
		DeleteGO(p_titleDecisionSE);
		DeleteGO(this);
	}
}

void GameTitle::FadeManager()
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

void GameTitle::Render(RenderContext& rc)
{
	p_titleSpriteRender.Draw(rc);
	if (p_currentAlpha > 0.0f)
	{
		p_titlePressButtonSpriteRender.SetMulColor(
			Vector4{
				1.0f,
				1.0f,
				1.0f,
				p_currentAlpha }
		);
		p_titlePressButtonSpriteRender.Draw(rc);
	}
}