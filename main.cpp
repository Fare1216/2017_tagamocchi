/*-----�c:480 �~ ��:640-----*/

#include "DxLib.h"


/*-----�L�����f�[�^�@�ۑ�-----*/
typedef struct{
	char name[256];
	int number;
	int count;
	char about[256];
}c_data;

/*-----��̃J�[�h�f�[�^-----*/
struct {
	int mark;
	int number;
	bool reverse;
} cards[3][4];

typedef enum{
	TitleLeady,
	Title,
	MenuLeady,
	Menu,
	CharcterLeady,
	Charcter,
	StatusLeady,
	Status,
	RiceLeady,
	Rice,
	GameLeady,
	Game,
	T_GameLeady,
	T_Game,
	P_TitleLeady,
	P_Title,
	P_Main,
	P_Clear,
	ItemLeady,
	Item,
	SettingLeady,
	Setting,
	CreditLeady,
	Credit,
}eScene;


int Scene = TitleLeady;

int mode = 0; //�������������
int click = 0; //�N���b�N��
int Count = 0; //1�b�͂���

int mx;        //�}�E�Xx���W
int my;        //�}�E�Xy���W
int Mouse;     //�}�E�X�ʒu
int cflag = 0; //�N���b�N�̃t���O

c_data c[18];

/*-----�摜�ϐ�-----*/
int title;
int charcter[18];
int t_button[2];
int m_button[6];
int game_back;
int g_button[2];
int back;
int item_back[2];
int item[3];
int room;
int status;
int rice;
int credit;
int setting;
int evolution;

/*-----�p�Y���@�摜�p�ϐ�-----*/
int frame;
int pics[9];
int pic_all;
int panel[9];

/*-----�g�����v�@�摜�p�ϐ�*/
int graph_cards[2], graph_marks[2], graph_numbers[3];
int table;

/*-----�g�����v�p�ϐ�-----*/
int mk;
int no;
int turns = 0; //1�^�[���̍s����
int ox, oy; //1���ڂ̃J�[�h�̔ԍ�
int tx, ty; //2���ڂ̃J�[�h�̔ԍ�
int i; //����Ԃ��p�ϐ�
int bb, cc; //�f�[�^��^���邽�߂̈ꎞ�ϐ�
bool deal[3][4] = {};
int remains = 12; //�c���Ă�J�[�h����
bool mouse_flag = false;

/*-----�F�֘A-----*/
int White = GetColor( 255, 255, 255);
int Black = GetColor(   0,   0,   0);
int Red   = GetColor( 255,   0,   0);


void Graph();
void SetChar();
void MenuIcon(int aflag);
/*-----�g�����v�p�@�֐�-----*/
void Reset();
void Shuffle();
/*-----�p�Y���p�@�֐�-----*/
void Change(int x, int y);


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	Graph();
	SetChar();

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)){

		/*-----�}�E�X���W�@�擾-----*/
		Mouse = GetMouseInput();
		GetMousePoint(&mx, &my);


		switch (Scene){

		case TitleLeady:{
			mode = 0;
			click = 0;

			Scene = Title;
			break;
		}

		case Title:{
			DrawGraph(   0,   0,       title, FALSE);
			DrawGraph(  80, 380, t_button[0], FALSE);
			DrawGraph( 400, 380, t_button[1], FALSE);

			/*-----Start�@�I��-----*/
			if (80 <= mx && mx < 240 && 380 <= my && my < 440){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = MenuLeady;
					cflag = 1;
				}
			}
			/*-----Credit�@�I��-----*/
			if (400 <= mx && mx < 560 && 380 <= my && my < 440){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = CreditLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case MenuLeady:{
			if (click == c[mode].count){
				Scene = CharcterLeady;

				break;
			}

			Scene = Menu;
			break;
		}

		case Menu:{
			DrawGraph( 120,  40, room, FALSE);
			DrawGraph( 120,  40, charcter[mode], TRUE);

			MenuIcon(0);
			
			/*-----�L�����N���b�N-----*/
			if (mode == 0){
				if (120 <= mx && mx < 520 && 40 <= my && my < 440){
					if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						click++;
						if (click == c[mode].count){
							Scene = CharcterLeady;
						}
						cflag = 1;
					}
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}


			break;
		}

		case CharcterLeady:{
			DrawGraph(   0,   0, evolution, FALSE);
			Count++;

			if (Count == 60){
				Scene = Charcter;
				Count = 0;
			}

			break;
		}

		case Charcter:{
			/*-----���܂��@�i����@�ݒ�-----*/
			if ( (mode == 0) && (click == c[0].count) ){
				mode = GetRand(1) + 1;
				click = 0;
			}

			/*-----���������j�@�i����@�ݒ�-----*/
			if ( (mode == 1) && (click == c[1].count) ){
				mode = 3;
				click = 0;
			}

			/*-----��������񏗁@�i����@�ݒ�-----*/
			if ( (mode == 2) && (click == c[2].count) ){
				mode = 4;
				click = 0;
			}

			/*-----�c�����j�@�i����@�ݒ�-----*/
			if ( (mode == 3) && (click == c[3].count) ){
				mode = GetRand(1) + 5;
				click = 0;
			}

			/*-----�c�������@�i����@�ݒ�-----*/
			if ( (mode == 4) && (click == c[4].count) ){
				mode = GetRand(1) + 7;
				click = 0;
			}

			/*-----�f���E���O���j�@�i����@�ݒ�-----*/
			if ( ((mode == 5) && (click == c[5].count)) || ((mode == 6) && (click == c[6].count)) ){
				mode = GetRand(2) + 9;
				click = 0;
			}

			/*-----�f���E���O�����@�i����@�ݒ�-----*/
			if ( ((mode == 7) && (click == c[7].count)) || ((mode == 8) && (click == c[8].count)) ){
				mode = GetRand(2) + 12;
				click = 0;
			}

			/*-----�N���j�@�i����@�ݒ�-----*/
			if ( ((mode == 9) && (click == c[9].count)) || ((mode == 10) && (click == c[10].count)) || ((mode == 11) && (click == c[11].count)) ){
				mode = 15;
				click = 0;
			}

			/*-----�N�����@�i����@�ݒ�-----*/
			if ( ((mode == 12) && (click == c[12].count)) || ((mode == 13) && (click == c[13].count)) || ((mode == 14) && (click == c[14].count)) ){
				mode = 16;
				click = 0;
			}

			/*-----�V�l�@�i����@�ݒ�-----*/
			if ( ((mode == 15) && (click == c[15].count)) || ((mode == 16) && (click == c[16].count)) ){
				mode = 17;
				click = 0;
			}

			Scene = MenuLeady;
			break;
		}

		case StatusLeady:{
			if (click == c[mode].count){
				Scene = CharcterLeady;
				break;
			}

			Scene = Status;
			break;
		}

		case Status:{
			DrawGraph( 120,  40, status, FALSE);
			MenuIcon(0);

			SetFontSize(32);
			DrawFormatString( 270,  80, Black, "%s", c[mode].name);
			SetFontSize(16);
			DrawFormatString( 165, 305, Black, "%s", c[mode].about);

			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case RiceLeady:{
			if ( (mode == 0) || (mode == 17) ){
				Scene = MenuLeady;
				break;
			}
			if (click == c[mode].count){
				Scene = CharcterLeady;

				break;
			}

			click++;

			Scene = Rice;
			break;
		}

		case Rice:{
			DrawGraph( 120, 40, rice, FALSE);
			MenuIcon(1);

			Count++;

			if (Count == 60){
				Scene = MenuLeady;
				Count = 0;
			}

			break;
		}

		case GameLeady:{
			if ( (mode == 0) || (mode == 17) ){
				Scene = MenuLeady;
				break;
			}
			if (click == c[mode].count){
				Scene = CharcterLeady;

				break;
			}

			Scene = Game;
			break;
		}

		case Game:{
			MenuIcon(0);

			DrawGraph( 120,  40, game_back, FALSE);
			DrawGraph( 170,  76, g_button[0], FALSE);
			DrawGraph( 170, 256, g_button[1], FALSE);

			/*-----�_�o����@�I��-----*/
			if (170 <= mx && mx < 470 && 76 <= my && my < 226){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){

					Scene = T_GameLeady;
					cflag = 1;
				}
			}
			/*-----�X���C�h�p�Y���@�I��-----*/
			if (170 <= mx && mx < 470 && 256 <= my && my < 406){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){

					Scene = P_TitleLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}


			break;
		}

		case T_GameLeady:{
			remains = 12;
			Reset();
			Shuffle();

			click++;

			Scene = T_Game;
			break;
		}

		case T_Game:{
			MenuIcon(1);
			DrawGraph( 120, 40, table, TRUE);

			// �J�[�h�߂��菈��
			if (240 <= mx && mx < 400 && 150 <= my && my < 330){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){

						if (turns == 2) {
							cards[oy][ox].reverse = true;
							cards[ty][tx].reverse = true;
							turns = 0;
						}
						else {
							//GetMousePoint(&tx, &ty);

							tx = (mx - 240) / 40;
							ty = (my - 150) / 60;

							if (tx >= 0 && tx <= 3 && ty >= 0 && ty <= 2 && cards[ty][tx].reverse) {
								cards[ty][tx].reverse = false;

								if (turns == 0) {
									ox = tx; oy = ty;
									turns = 1;
								}
								else {
									if (cards[ty][tx].number == cards[oy][ox].number) {
										remains -= 2;
										turns = 0;
									}
									else {
										turns = 2;
									}
								}
							}
						}
					}
				cflag = 1;
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			// ��̃J�[�h�\��
			for (int cc = 0; cc < 3; cc++) {
				for (int bb = 0; bb < 4; bb++) {
					int bb2 = bb * 40 + 240;
					int cc2 = cc * 60 + 150;

					DrawGraph(bb2, cc2, graph_cards[cards[cc][bb].reverse], FALSE);

					if (!cards[cc][bb].reverse) {
						DrawGraph(bb2 + 6, cc2 + 5, graph_marks[cards[cc][bb].mark], FALSE);
						DrawGraph(bb2 + 6, cc2 + 32, graph_numbers[cards[cc][bb].number], FALSE);
					}
				}
			}

			// ���b�Z�[�W�\��
			if (remains <= 0) {
				DrawGraph(120, 40, table, TRUE);

				{SetFontSize(32);
				DrawFormatString(256, 224, White, "�N���A�I");}
				Count++;

				if (Count == 120){
					Scene = MenuLeady;
					Count = 0;
					break;
				}
			}
			break;
		}

		case P_TitleLeady:{
			click++;

			Scene = P_Title;
			break;
		}

		case P_Title: {
			MenuIcon(1);
			DrawGraph(120, 40, frame, FALSE);
			DrawGraph(160, 80, pic_all, FALSE);
			SetFontSize(16);
			DrawFormatString(262, 222, Red, "CLICK TO START");

			if (160 <= mx && mx < 520 && 80 <= my && my < 400){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					// �����p�l���̃V���b�t��
					for (int i = 0; i < 9; i++) {
						panel[i] = i;
					}
					for (int i = 0; i < 1000; i++) {
						Change(GetRand(2), GetRand(2));
					}

					Scene = P_Main;
					cflag = 1;
				}
			}

			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case P_Main: {
			MenuIcon(1);
			DrawGraph(120, 40, frame, FALSE);

			if (GetMouseInput() & MOUSE_INPUT_LEFT) {

				GetMousePoint(&mx, &my);
				Change((mx - 160) / 106.666666667, (my - 80) / 106.666666667);

				// �p�l�����S��������������
				bool clear = true;
				for (int i = 0; i < 9; i++) {
					if (panel[i] != i) {
						clear = false;
					}
				}
				if (clear) {
					Scene = P_Clear;
				}
			}

			// �p�l���̕`��
			for (int i = 0; i < 9; i++) {
				if (panel[i] < 8) {
					DrawGraph(((i % 3) * 106.666666667) + 160, ((i / 3) * 106.666666667) + 80, pics[panel[i]], FALSE);
				}
			}

			break;
		}

		case P_Clear: {
			MenuIcon(1);
			DrawGraph(120, 40, frame, FALSE);
			DrawGraph(160, 80, pic_all, FALSE);
			DrawFormatString(275, 222, Red, "GAME CLEAR!");

			if (160 <= mx && mx < 520 && 80 <= my && my < 400){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = MenuLeady;
					cflag = 1;
				}
			}

			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case ItemLeady:{
			if ( (mode == 0) || (mode == 17) ){
				Scene = MenuLeady;
				break;
			}
			if (click == c[mode].count){
				Scene = CharcterLeady;
				break;
			}

			Scene = Item;
			break;
		}

		case Item:{
			if ((mode == 9) || (mode == 10) || (mode == 11) || (mode == 12) || (mode == 13) || (mode == 14)){
				DrawGraph(120, 40, item_back[0], FALSE);
				DrawGraph(180, 100, item[0], TRUE);
				DrawGraph(180, 220, item[1], TRUE);
				DrawGraph(180, 340, item[2], TRUE);

				SetFontSize(32);
				DrawFormatString( 260, 110, Black, "������{");
				DrawFormatString( 260, 230, Black, "��΂�������");
				DrawFormatString( 260, 350, Black, "Twi��ter");

				MenuIcon(0);

				/*-----�{�@�I��-----*/
				if (120 <= mx && mx < 520 && 60 <= my && my < 178){
					if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						if ((mode == 10) || (mode == 11)){
							mode = 9;
						}
						if ((mode == 13) || (mode == 14)){
							mode = 12;
						}

						click++;
						Scene = MenuLeady;
						cflag = 1;
					}
				}
				/*-----�����ǁ@�I��-----*/
				if (120 <= mx && mx < 520 && 201 <= my && my < 319){
					if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						if ((mode == 9) || (mode == 11)){
							mode = 10;
						}
						if ((mode == 12) || (mode == 14)){
							mode = 13;
						}

						click++;
						Scene = MenuLeady;
						cflag = 1;
					}
				}
				/*-----Twitter �I��-----*/
				if (120 <= mx && mx < 520 && 322 <= my && my < 440){
					if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						if ((mode == 9) || (mode == 10)){
							mode = 11;
						}
						if ((mode == 12) || (mode == 13)){
							mode = 14;
						}

						click++;
						Scene = MenuLeady;
						cflag = 1;
					}
				}
			}
			else{
				DrawGraph(120, 40, item_back[1], FALSE);
				MenuIcon(1);

				Count++;

				if (Count == 60){
					Scene = MenuLeady;
					Count = 0;
				}

				break;
			}

			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case SettingLeady:{
			if (click == c[mode].count){
				Scene = CharcterLeady;
				break;
			}

			Scene = Setting;
			break;
		}

		case Setting:{
			DrawGraph( 120,  40, setting, FALSE);
			MenuIcon(0);

			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		case CreditLeady:{

			Scene = Credit;
			break;
		}

		case Credit:{
			DrawGraph(   0,   0, credit, FALSE);

			/*-----Click-----*/
			if (0 <= mx && mx < 640 && 0 <= my && my < 480){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = TitleLeady;
					cflag = 1;
				}
			}
			if (Mouse & MOUSE_INPUT_LEFT){
				cflag = 1;
			}
			else if ((Mouse & MOUSE_INPUT_LEFT) == 0){
				cflag = 0;
			}

			break;
		}

		}

	}

	DxLib_End();
	return 0;
}



void Graph(){
	/*-----�^�C�g���摜�@�ǂݍ���-----*/
	title = LoadGraph("Graphics/Title.png");

	/*-----�L�����摜�@�ǂݍ���-----*/
	charcter[0]  = LoadGraph("Graphics/egg.png");         //���܂�
	charcter[1]  = LoadGraph("Graphics/baby_m.png");      //���������j
	charcter[2]  = LoadGraph("Graphics/baby_f.png");      //���������
	charcter[3]  = LoadGraph("Graphics/childhood_m.png"); //�c�����j
	charcter[4]  = LoadGraph("Graphics/childhood_f.png"); //�c������
	charcter[5]  = LoadGraph("Graphics/honest_m.png");    //�f���j
	charcter[6]  = LoadGraph("Graphics/bad_m.png");       //�͂񂮂�j
	charcter[7]  = LoadGraph("Graphics/honest_f.png");    //�f����
	charcter[8]  = LoadGraph("Graphics/bad_f.png");        //�͂񂮂ꏗ
	charcter[9]  = LoadGraph("Graphics/language_m.png");  //���n�j
	charcter[10] = LoadGraph("Graphics/science_m.png");   //���n�j
	charcter[11] = LoadGraph("Graphics/nube_m.png");      //�L�`�K�C�j
	charcter[12] = LoadGraph("Graphics/language_f.png");  //���n��
	charcter[13] = LoadGraph("Graphics/science_f.png");   //���n��
	charcter[14] = LoadGraph("Graphics/nube_f.png");      //�L�`�K�C��
	charcter[15] = LoadGraph("Graphics/grandpa.png");     //�V�l�j
	charcter[16] = LoadGraph("Graphics/grandma.png");     //�V�l��
	charcter[17] = LoadGraph("Graphics/tomb.png");        //��

	/*-----�^�C�g���{�^���摜�@�ǂݍ���-----*/
	t_button[0] = LoadGraph("Graphics/T_Button.png");
	t_button[1] = LoadGraph("Graphics/C_Button.png");

	/*-----���j���[�{�^���摜�@�ǂݍ���-----*/
	m_button[0] = LoadGraph("Graphics/Status_B.png");
	m_button[1] = LoadGraph("Graphics/Rice_B.png");
	m_button[2] = LoadGraph("Graphics/Game_B.png");
	m_button[3] = LoadGraph("Graphics/Item_B.png");
	m_button[4] = LoadGraph("Graphics/Setting_B.png");
	m_button[5] = LoadGraph("Graphics/Back_B.png");

	/*-----�Q�[���I���@�ǂݍ���-----*/
	game_back = LoadGraph("Graphics/Game_Back.png");
	g_button[0] = LoadGraph("Graphics/tranp_B.png");
	g_button[1] = LoadGraph("Graphics/puzzle_B.png");

	/*-----�w�i�摜�@�ǂݍ���-----*/
	room = LoadGraph("Graphics/Room.png");

	/*-----�X�e�[�^�X�摜�@�ǂݍ���-----*/
	status = LoadGraph("Graphics/Status.png");

	/*-----���ĉ摜�@�ǂݍ���-----*/
	rice = LoadGraph("Graphics/syu-zo.png");
	
	/*-----�A�C�e���摜�@�ǂݍ���-----*/
	item_back[0] = LoadGraph("Graphics/Item_Back.png");
	item_back[1] = LoadGraph("Graphics/Item_Back2.png");
	item[0] = LoadGraph("Graphics/Item1.png");
	item[1] = LoadGraph("Graphics/Item2.png");
	item[2] = LoadGraph("Graphics/Item3.png");

	/*-----�������������i���������I�I�@�ǂݍ���-----*/
	evolution = LoadGraph("Graphics/evolution.png");

	/*-----�ݒ�摜�@�ǂݍ���-----*/
	setting = LoadGraph("Graphics/Setting.png");

	/*-----�N���W�b�g�摜�@�ǂݍ���-----*/
	credit = LoadGraph("Graphics/Credit.png");

	/*-----�g�����v�p�摜�@�ǂݍ���-----*/
	LoadDivGraph("Graphics/card.png", 2, 2, 1, 40, 60, graph_cards); //�J�[�h�摜�@�ǂݍ���
	LoadDivGraph("Graphics/mark.png", 2, 2, 1, 28, 28, graph_marks); //�}�[�N�摜�@�ǂݍ���
	LoadDivGraph("Graphics/number.png", 3, 3, 1, 28, 28, graph_numbers); //�����摜�@�ǂݍ���
	table = LoadGraph("Graphics/table.png");

	/*-----�p�Y���p�摜�@�ǂݍ���-----*/
	frame = LoadGraph("Graphics/frame.png");
	LoadDivGraph("Graphics/pic.png", 9, 3, 3, 106.666666667, 106.666666667, pics);
	pic_all = LoadGraph("Graphics/pic.png");

}

void SetChar(){
	c[0]  = {       "������",  1, 5, "���������܂ꂻ���ȕ��͋C�̂��܂�"};
	c[1]  = {   "����������",  2, 2, "���܂ꂽ�΂���̒j�̎q�@�c��"};
	c[2]  = {   "�����߂���",  3, 2, "���܂ꂽ�΂���̏��̎q�@�c��"};
	c[3]  = { "���܂񂶂イ",  4, 3, "�����������@�����܂��Ⴍ������"};
	c[4]  = {       "�|�Z��",  5, 3, "�����������@���������D���[�[�["};
	c[5]  = {       "�Ђ낵",  6, 4, "�������đ����L���킯�ł͂Ȃ�"};
	c[6]  = {   "���[�[���g",  7, 4, "�X�L���w�b�h�I�I�I�I�I"};
	c[7]  = {         "�Ȃ�",  8, 4, "�c���f�������������炢����"};
	c[8]  = {     "�X�P�o��",  9, 4, "�ǂ����̃h���}�ɏo�Ă�������"};
	c[9]  = {         "�C��", 10, 5, "���O�͋������������܂͎ア"};
	c[10] = {         "����", 11, 5, "����Łu�����ށv���ēǂ߂Ȃ�"};
	c[11] = {       "������", 12, 5, "������������������������������������������������"};
	c[12] = {         "����", 13, 5, "�G�t�̂��C�ɓ���̂�"};
	c[13] = {         "����", 14, 5, "���[�����剻�����i���J����"};
	c[14] = {         "Mary", 15, 5, "Mary is very yammy."};
	c[15] = {       "������", 16, 5, "�����܂̃o�[�R�[�h��������"};
	c[16] = {       "���΂�", 17, 5, "�G�r�����Ȃ����Ă�w��"};
	c[17] = {   "���E�́E��", 18, 1, "�����������������ޯ������������"};
}

void MenuIcon(int aflag){

	DrawGraph(  10,  40, m_button[0], FALSE);
	DrawGraph(  10, 190, m_button[1], FALSE);
	DrawGraph(  10, 340, m_button[2], FALSE);
	DrawGraph( 530,  40, m_button[3], FALSE);
	DrawGraph( 530, 190, m_button[4], FALSE);
	DrawGraph( 530, 340, m_button[5], FALSE);

	if (aflag == 0){
		/*-----Status�@�I��-----*/
		if (10 <= mx && mx < 110 && 40 <= my && my < 140){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = StatusLeady;
				cflag = 1;
			}
		}
		/*-----Rice�@�I��-----*/
		if (10 <= mx && mx < 110 && 190 <= my && my < 290){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = RiceLeady;
				cflag = 1;
			}
		}
		/*-----Game�@�I��-----*/
		if (10 <= mx && mx < 110 && 340 <= my && my < 440){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = GameLeady;
				cflag = 1;
			}
		}
		/*-----Item�@�I��-----*/
		if (530 <= mx && mx < 630 && 40 <= my && my < 140){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = ItemLeady;
				cflag = 1;
			}
		}
		/*-----Setting�@�I��-----*/
		if (530 <= mx && mx < 630 && 190 <= my && my < 290){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = SettingLeady;
				cflag = 1;
			}
		}
		/*-----Back�@�I��-----*/
		if (530 <= mx && mx < 630 && 340 <= my && my < 440){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				if (Scene == Menu){
					Scene = TitleLeady;
				}
				else{
					Scene = MenuLeady;
				}
				cflag = 1;
			}
		}
	}

}

/*-----�J�[�h�f�[�^�����Z�b�g-----*/
void Reset(){
	for (cc = 0; cc < 3; cc++){
		for (bb = 0; bb < 4; bb++){
			cards[cc][bb].mark = 0;
			cards[cc][bb].number = 0;
			cards[cc][bb].reverse = true;

			deal[cc][bb] = false;
		}
	}
}

void Shuffle(){
	// �V���b�t��
	for (mk = 0; mk < 2; mk++){ //�}�[�N��0��1��
		for (no = 0; no < 3; no++){ //������1��2��3��
			for (i = 0; i < 2; i++){
				do {
					bb = GetRand(3);
					cc = GetRand(2);
				} while (deal[cc][bb]);

				cards[cc][bb].mark = mk;
				cards[cc][bb].number = no;
				cards[cc][bb].reverse = true;

				deal[cc][bb] = true; //�����ꏊ�Ƀf�[�^��^���Ȃ��悤�ɂ���
			}
		}
	}
}

/*-----�I�������p�l���Ƌ󔒂����ւ���-----*/
void Change(int x, int y) {
	int p1 = y * 3 + x;
	int p2 = -1;

	if (x > 0 && panel[p1 - 1] == 8) {
		p2 = p1 - 1;
	}
	if (x < 2 && panel[p1 + 1] == 8) {
		p2 = p1 + 1;
	}
	if (y > 0 && panel[p1 - 3] == 8) {
		p2 = p1 - 3;
	}
	if (y < 2 && panel[p1 + 3] == 8) {
		p2 = p1 + 3;
	}
	if (p2 != -1) {
		panel[p2] = panel[p1];
		panel[p1] = 8;
	}
}