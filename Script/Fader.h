/* ------------------
　フェード演出データ
 -------------------- */

class Fader
{

public:

	// フェードが進む速さ
	static constexpr float SPEED_ALPHA = 5.0f;

	// 状態
	enum class STATE
	{
		NONE,
		FADE_OUT,	// 徐々に暗転
		FADE_IN		// 徐々に明転
	};

	// コンストラクタ
	Fader(void);

	// デストラクタ
	~Fader(void);

	void Init(void);
	void Update(void);
	void Draw(void);

	// 状態の取得
	STATE GetState(void);

	// 指定フェードを開始する
	void SetFade(STATE state, unsigned int color);

	// フェード演出終了判定 取得
	bool GetIsFeedEnd(void);


private:

	// 状態
	STATE state_;

	// 透明度(負の値が無効)
	float alpha_;

	// 状態(STATE)を保ったまま終了判定を行うため、
	// Update->Draw->Updateの1フレーム判定用
	bool isPreEnd_;

	// フェード処理の終了判定
	bool isFadeEnd_;

	// フェード演出色(負の値が無効)
	unsigned int color_;
};
