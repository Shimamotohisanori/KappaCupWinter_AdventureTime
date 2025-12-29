#pragma once
class GameTitle;
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void GameClearManager();
	void Render(RenderContext& rc);

	SpriteRender m_GameClearRender;
	GameTitle* m_gameTitle;


private:

	void FadeManager();

	SoundSource* p_gameClearBGM;
	SoundSource* p_gameClearDecisionSE;

	//ボタンを押してねのスプライト
	SpriteRender p_pressAnyButtonToTitleSpriteRender;
	Vector3 p_pressAnyButtonToTitleSpritePos = Vector3::Zero;

	enum EnState
	{
		enState_FadeIn,//フェードイン中
		enState_FadeOut,//フェードアウト中
	};
	EnState p_state = enState_FadeIn;//現在の状態

	float p_currentAlpha = 1.0f;

	float p_deltatime = 0.0f;//画面の移行に使う時間

	bool p_isNewTitle = false;//ゲーム画面に移行できるかどうかのフラグ
};

