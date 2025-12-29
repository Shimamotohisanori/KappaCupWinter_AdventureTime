#pragma once
class Game;
class GameTitle : public IGameObject
{
public:
	GameTitle();
	~GameTitle();
	bool Start();
	void Update();
	void TitleManager();
	void Render(RenderContext& rc);

private:

	void FadeManager();

	SpriteRender p_titleSpriteRender;
	SpriteRender p_titlePressButtonSpriteRender;
	Vector3 p_titlePressButtonSpritePos = Vector3::Zero;
	
	Game* p_game;

	SoundSource* p_titleBGM;
	SoundSource* p_titleDecisionSE;

	enum EnState
	{
		enState_FadeIn,//フェードイン中
		enState_FadeOut,//フェードアウト中
	};
	EnState p_state = enState_FadeIn;//現在の状態
	
	float p_currentAlpha = 1.0f;
	float p_deltatime = 0.0f;//画面の移行に使う時間

	bool p_isNewGame = false;//ゲーム画面に移行できるかどうかのフラグ
};

