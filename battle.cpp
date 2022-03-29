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
	//1�l��
	{"�p���`",90,20},
	{"�񂵏R��",70,40},
	{"����",50,60},
	{"���C�t��",20,150},
	//2�l��
	{"�w��������",100,10},
	{"�D�M����",70,40},
	{"�n���h�K��",30,120},
	{"�U���w��",10,200},
	//3�l��
	{"�t�@�C�A",90,20},
	{"�΂̋ʓ���",70,40},
	{"�^�b�N��",50,60},
	{"���e",30,120},
	//4�l��
	{"�L�b�N",80,30},
	{"�{�g������",70,40},
	{"�\�A�{�g�����C������",50,60},
	{"�n���h�K��",30,120},
	//5�l��
	{"�p���`",10,100},
	{"�i�C�t",80,30},
	{"�d�U��",50,60},
	{"�C��",20,150},
	//6�l��
	{"�L�b�N",100,10},
	{"�M����",70,40},
	{"�Ê퓊��",50,60},
	{"���U��",30,120},
	//7�l��
	{"�{�g������",50,60},
	{"�i�C�t����",50,60},
	{"�d������",50,60},
	{"�o�g������",50,60},
	//8�l��
	{"�L�b�N",80,30},
	{"�i�C�t����",70,40},
	{"���U��",50,60},
	{"���݂�",10,200},
	//9�l��
	{"�p���`",90,20},
	{"�Ê퓊��",70,40},
	{"���Ȃ��",50,60},
	{"�j�ł̌�",10,200},
	//10�l��
	{"�t�@�C�A",90,20},
	{"�T���_�[",70,40},
	{"�u���U�[�h",40,75},
	{"�g���l�[�h",20,150}
};

void Opning() {
	SetFontSize(30);
	DrawString(200, 100, "�s�N�g�o�g��", White);
	SetFontSize(14);
	DrawString(200, 400, "SPACE�������ăX�^�[�g", White);
	ScreenFlip();
	if (KeyBuf[KEY_INPUT_SPACE] == 1)
	{
		function_status = 1;
	}
}
void Howto() {
	SetFontSize(16);
	DrawString(100, 140, "��������ix���v�b�V���j", White);
	DrawString(100, 180, "�����̃L������I��ŋZ�œG��|���Q�[���ł�\n�G�̓L�����I�����Z�I�������S�����_���ł�\n�I��肽���Ƃ���Escape�L�[�������Ă�������", White);
	ScreenFlip();
	if (KeyBuf[KEY_INPUT_X] == 1)
	{
		function_status = 2;
	}
}
void choose()
{
	SetFontSize(30);
	DrawString(100, 30, "�L������I�����Ă�������", White);
	//��i�\��
	for (i = 0; i <= 4; i++)
	{
		DrawRotaGraph((i + 1) * 100, 150, 0.2, 0, charactar[i], TRUE);
	}

	//���i�\��
	for (i = 5; i <= 9; i++)
	{
		DrawRotaGraph((i - 4) * 100, 300, 0.2, 0, charactar[i], TRUE);
	}

	//���\��
	if (ch <= 4)
	{
		DrawRotaGraph((ch + 1) * 100, 90, 0.1, 0, under, TRUE);
	}
	else
	{
		DrawRotaGraph((ch - 4) * 100, 240, 0.1, 0, under, TRUE);
	}

	//���ړ�
	if (Key[KEY_INPUT_RIGHT] == 1)
	{
		ch++;
	}
	if (Key[KEY_INPUT_LEFT] == 1)
	{
		ch--;
	}

	//�[�܂ōs�������̏���
	if (ch < 0)
	{
		ch = 9;
	}
	if (ch == 10)
	{
		ch = 0;
	}

	SetFontSize(14);
	DrawFormatString(100, 200, White, "���̃L�����ŗǂ����Enter�L�[�������Ă��������B");
	enemy = GetRand(9);
	ScreenFlip();
	if (KeyBuf[KEY_INPUT_RETURN] == 1)
	{
		function_status = 3;
	}
}
void Game() {

	//�I���L�����\��
	DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
	DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);

	//�̗͕\��
	DrawFormatString(500, 200, White, "�̗́F%d/%d", hp, st[ch].health);
	DrawFormatString(100, 100, White, "�̗́F%d/%d", enemyhp, st[enemy].health);

	for (i = 0; i <= 3; i++)
	{
		DrawFormatString(350, 400 + i * 20, White, "%s  �����F%d�@�_���[�W�F%d", sk[ch * 4 + i].skill, sk[ch * 4 + i].skillHit, sk[ch * 4 + i].skillDam);
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
			DrawFormatString(10, 360, White, "���Ȃ���%s�U���I�����%d�̃_���[�W�I", sk[ch * 4 + skillch].skill, sk[ch * 4 + skillch].skillDam);
			ScreenFlip();
			enemyhp = enemyhp - sk[ch * 4 + skillch].skillDam;
			WaitKey();
			turn = 1;
			if (enemyhp <= 0)
			{
				//����
				ClearDrawScreen();
				//�ĕ\��
				DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
				DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);
				DrawFormatString(500, 200, White, "�̗́F%d/%d", hp, st[ch].health);
				DrawFormatString(100, 100, White, "�̗́F%d/%d", enemyhp, st[enemy].health);

				DrawString(200, 300, "YOU WIN!\nR�L�[:�L�����I�����\nEscape�L�[:�Q�[���I��", White);
				ScreenFlip();
				turn = 2;
			}
		}
		else
		{
			DrawFormatString(10, 360, White, "���Ȃ���%s�U���I�������A�O��Ă��܂����I", sk[ch * 4 + skillch].skill);
			ScreenFlip();
			WaitKey();
			turn = 1;
		}
	}
}
void Enemy() {
	//�I���L�����\��
	DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
	DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);

	//�̗͕\��
	DrawFormatString(500, 200, White, "�̗́F%d/%d", hp, st[ch].health);
	DrawFormatString(100, 100, White, "�̗́F%d/%d", enemyhp, st[enemy].health);

	DrawString(100, 180, "�G�̃^�[��", White);


	ScreenFlip();
	if (KeyBuf[KEY_INPUT_RETURN] == 1)
	{
		Hit = GetRand(100);
		eskillch = GetRand(3);
		if (Hit <= sk[enemy * 4 + eskillch].skillHit)
		{
			DrawFormatString(10, 360, White, "�����%s�U���I���Ȃ���%d�̃_���[�W�I", sk[enemy * 4 + eskillch].skill, sk[enemy * 4 + eskillch].skillDam);
			ScreenFlip();
			hp = hp - sk[enemy * 4 + eskillch].skillDam;
			WaitKey();
			turn = 0;
			if (hp <= 0)
			{
				//����
				ClearDrawScreen();
				//�ĕ\��
				DrawRotaGraph(500, 300, 0.4, 0, charactar[ch], true);
				DrawRotaGraph(100, 200, 0.4, 0, charactar[enemy], true);
				DrawFormatString(500, 200, White, "�̗́F%d/%d", hp, st[ch].health);
				DrawFormatString(100, 100, White, "�̗́F%d/%d", enemyhp, st[enemy].health);
				DrawString(200, 300, "YOU LOSE!\nR�L�[:�L�����I�����\nEscape�L�[:�Q�[���I��", White);
				ScreenFlip();
				turn = 2;
			}
		}
		else
		{
			DrawFormatString(10, 360, White, "�����%s�U���I�������A�O��Ă��܂����I", sk[enemy * 4 + eskillch].skill);
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
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h��
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
		switch (function_status) {//function_status�̒l�ŏ�ʓ]��
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
	// �c�w���C�u�����g�p�̏I��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}