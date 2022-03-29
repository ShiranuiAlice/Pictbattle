#include "DxLib.h"

int function_status = 0, ch = 0, skillch = 0, eskillch = 0, White, i, charactar[10], skill[40], under, right, enemy, turn = 0, hp = 0, enemyhp = 0, Hit = 0;
char KeyBuf[256];
int Key[256];

typedef struct {
	char skill[30];
	int  skillHit;
	int  skillDam;
} skill_t;

typedef struct {
	int health;
}status_t;

status_t st[10] = {
		{200},
		{180},
		{240},
		{220},
		{200},
		{190},
		{170},
		{210},
		{250},
		{220}
};
skill_t sk[40] = {
	//1人目
	{"パンチ",90,20},
	{"回し蹴り",70,40},
	{"投石",50,60},
	{"ライフル",20,150},
	//2人目
	{"背負い投げ",100,10},
	{"灰皿投げ",70,40},
	{"ハンドガン",30,120},
	{"攻撃ヘリ",10,200},
	//3人目
	{"ファイア",90,20},
	{"火の玉投げ",70,40},
	{"タックル",50,60},
	{"爆弾",30,120},
	//4人目
	{"キック",80,30},
	{"ボトル投げ",70,40},
	{"十連ボトルワイン投げ",50,60},
	{"ハンドガン",30,120},
	//5人目
	{"パンチ",10,100},
	{"ナイフ",80,30},
	{"錨攻撃",50,60},
	{"砲撃",20,150},
	//6人目
	{"キック",100,10},
	{"皿投げ",70,40},
	{"暗器投擲",50,60},
	{"総攻撃",30,120},
	//7人目
	{"ボトル投げ",50,60},
	{"ナイフ投げ",50,60},
	{"硬球投げ",50,60},
	{"バトン投げ",50,60},
	//8人目
	{"キック",80,30},
	{"ナイフ投げ",70,40},
	{"鎖攻撃",50,60},
	{"噛みつき",10,200},
	//9人目
	{"パンチ",90,20},
	{"暗器投擲",70,40},
	{"聖なる光",50,60},
	{"破滅の光",10,200},
	//10人目
	{"ファイア",90,20},
	{"サンダー",70,40},
	{"ブリザード",40,75},
	{"トルネード",20,150}
};

void Opning() {
	SetFontSize(30);
	DrawString(200, 100, "ピクトバトル", White);
	SetFontSize(14);
	DrawString(200, 400, "SPACEを押してスタート", White);
	ScreenFlip();
	if (KeyBuf[KEY_INPUT_SPACE] == 1)
	{
		function_status = 1;
	}
}
void Howto() {
	SetFontSize(16);
	DrawString(100, 140, "操作説明（xをプッシュ）", White);
	DrawString(100, 180, "自分のキャラを選んで技で敵を倒すゲームです\n敵はキャラ選択も技選択も完全ランダムです\n終わりたいときはEscapeキーを押してください", White);
	ScreenFlip();
	if (KeyBuf[KEY_INPUT_X] == 1)
	{
		function_status = 2;
	}
}
void choose()
{
	SetFontSize(30);
	DrawString(100, 30, "キャラを選択してください", White);
	//上段表示
	for (i = 0; i <= 4; i++)
	{
		DrawRotaGraph((i + 1) * 100, 150, 0.2, 0, charactar[i], TRUE);
	}

	//下段表示
	for (i = 5; i <= 9; i++)
	{
		DrawRotaGraph((i - 4) * 100, 300, 0.2, 0, charactar[i], TRUE);
	}

	//矢印表示
	if (ch <= 4)
	{
		DrawRotaGraph((ch + 1) * 100, 90, 0.1, 0, under, TRUE);
	}
	else
	{
		DrawRotaGraph((ch - 4) * 100, 240, 0.1, 0, under, TRUE);
	}

	//矢印移動
	if (Key[KEY_INPUT_RIGHT] == 1)
	{
		ch++;
	}
	if (Key[KEY_INPUT_LEFT] == 1)
	{
		ch--;
	}

	//端まで行った時の処理
	if (ch < 0)
	{
		ch = 9;
	}
	if (ch == 10)
	{
		ch = 0;
	}

	SetFontSize(14);
	DrawFormatString(100, 200, White, "このキャラで良ければEnterキーを押してください。");
	enemy = GetRand(9);
	ScreenFlip();
	if (KeyBuf[KEY_INPUT_RETURN] == 1)
	{
		function_status = 3;
	}
}
void Game() {

	//選択キャラ表示
	DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
	DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);

	//体力表示
	DrawFormatString(500, 200, White, "体力：%d/%d", hp, st[ch].health);
	DrawFormatString(100, 100, White, "体力：%d/%d", enemyhp, st[enemy].health);

	for (i = 0; i <= 3; i++)
	{
		DrawFormatString(350, 400 + i * 20, White, "%s  命中：%d　ダメージ：%d", sk[ch * 4 + i].skill, sk[ch * 4 + i].skillHit, sk[ch * 4 + i].skillDam);
	}

	DrawRotaGraph(300, 405 + skillch * 20, 0.1, 0, right, TRUE);

	if (Key[KEY_INPUT_DOWN] == 1)
	{
		skillch++;
	}
	if (Key[KEY_INPUT_UP] == 1)
	{
		skillch--;
	}

	if (skillch < 0)
	{
		skillch = 3;
	}
	if (skillch > 3)
	{
		skillch = 0;
	}

	ScreenFlip();

	if (Key[KEY_INPUT_RETURN] == 1)
	{
		Hit = GetRand(100);
		if (Hit <= sk[ch * 4 + skillch].skillHit)
		{
			DrawFormatString(10, 360, White, "あなたの%s攻撃！相手に%dのダメージ！", sk[ch * 4 + skillch].skill, sk[ch * 4 + skillch].skillDam);
			ScreenFlip();
			enemyhp = enemyhp - sk[ch * 4 + skillch].skillDam;
			WaitKey();
			turn = 1;
			if (enemyhp <= 0)
			{
				//消去
				ClearDrawScreen();
				//再表示
				DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
				DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);
				DrawFormatString(500, 200, White, "体力：%d/%d", hp, st[ch].health);
				DrawFormatString(100, 100, White, "体力：%d/%d", enemyhp, st[enemy].health);

				DrawString(200, 300, "YOU WIN!\nRキー:キャラ選択画面\nEscapeキー:ゲーム終了", White);
				ScreenFlip();
				turn = 2;
			}
		}
		else
		{
			DrawFormatString(10, 360, White, "あなたの%s攻撃！しかし、外れてしまった！", sk[ch * 4 + skillch].skill);
			ScreenFlip();
			WaitKey();
			turn = 1;
		}
	}
}
void Enemy() {
	//選択キャラ表示
	DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
	DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);

	//体力表示
	DrawFormatString(500, 200, White, "体力：%d/%d", hp, st[ch].health);
	DrawFormatString(100, 100, White, "体力：%d/%d", enemyhp, st[enemy].health);

	DrawString(100, 180, "敵のターン", White);


	ScreenFlip();
	if (KeyBuf[KEY_INPUT_RETURN] == 1)
	{
		Hit = GetRand(100);
		eskillch = GetRand(3);
		if (Hit <= sk[enemy * 4 + eskillch].skillHit)
		{
			DrawFormatString(10, 360, White, "相手の%s攻撃！あなたに%dのダメージ！", sk[enemy * 4 + eskillch].skill, sk[enemy * 4 + eskillch].skillDam);
			ScreenFlip();
			hp = hp - sk[enemy * 4 + eskillch].skillDam;
			WaitKey();
			turn = 0;
			if (hp <= 0)
			{
				//消去
				ClearDrawScreen();
				//再表示
				DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
				DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);
				DrawFormatString(500, 200, White, "体力：%d/%d", hp, st[ch].health);
				DrawFormatString(100, 100, White, "体力：%d/%d", enemyhp, st[enemy].health);
				DrawString(200, 300, "YOU LOSE!\nRキー:キャラ選択画面\nEscapeキー:ゲーム終了", White);
				ScreenFlip();
				turn = 2;
			}
		}
		else
		{
			DrawFormatString(10, 360, White, "相手の%s攻撃！しかし、外れてしまった！", sk[enemy * 4 + eskillch].skill);
			ScreenFlip();
			WaitKey();
			turn = 0;
		}
	}
	ScreenFlip();
}

int gpUpdateKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0)
		{
			Key[i]++;
		}
		else
		{
			Key[i] = 0;
		}
	}
	return 0;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)return -1;
	ChangeWindowMode(TRUE);//ウィンドウモード化
	White = GetColor(255, 255, 255);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	charactar[0] = LoadGraph("./img/akazukin.png");
	charactar[1] = LoadGraph("./img/boss.png");
	charactar[2] = LoadGraph("./img/fireman.png");
	charactar[3] = LoadGraph("./img/waiter.png");
	charactar[4] = LoadGraph("./img/kaizoku.png");
	charactar[5] = LoadGraph("./img/meid.png");
	charactar[6] = LoadGraph("./img/piero.png");
	charactar[7] = LoadGraph("./img/vampire.png");
	charactar[8] = LoadGraph("./img/sister.png");
	charactar[9] = LoadGraph("./img/witch.png");
	under = LoadGraph("./img/under.png");
	right = LoadGraph("./img/right.png");

	while (1) {
		ClearDrawScreen();
		GetHitKeyStateAll(KeyBuf);
		gpUpdateKey() == 0;
		switch (function_status) {//function_statusの値で場面転換
		case 0:
			Opning();
			break;
		case 1:
			Howto();
			break;
		case 2:
			choose();
			hp = st[ch].health;
			enemyhp = st[enemy].health;
			break;
		case 3:

			if (turn == 0) { Game(); }
			else if (turn == 1) { Enemy(); }
			else { break; }
		}
		if (KeyBuf[KEY_INPUT_R] == 1)
		{
			function_status = 2;
			turn = 0;
			ch = 0;
		}
		if (ProcessMessage() == -1 || KeyBuf[KEY_INPUT_ESCAPE] == 1) {
			break;

		}


	}
	// ＤＸライブラリ使用の終了
	DxLib_End();

	// ソフトの終了
	return 0;
}