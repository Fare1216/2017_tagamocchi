/*-----縦:480 × 横:640-----*/

#include "DxLib.h"


/*-----キャラデータ　保存-----*/
typedef struct{
	char name[256];
	int number;
	int count;
	char about[256];
}c_data;

/*-----場のカードデータ-----*/
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

int mode = 0; //たがもっち状態
int click = 0; //クリック回数
int Count = 0; //1秒はかる

int mx;        //マウスx座標
int my;        //マウスy座標
int Mouse;     //マウス位置
int cflag = 0; //クリックのフラグ

c_data c[18];

/*-----画像変数-----*/
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

/*-----パズル　画像用変数-----*/
int frame;
int pics[9];
int pic_all;
int panel[9];

/*-----トランプ　画像用変数*/
int graph_cards[2], graph_marks[2], graph_numbers[3];
int table;

/*-----トランプ用変数-----*/
int mk;
int no;
int turns = 0; //1ターンの行動回数
int ox, oy; //1枚目のカードの番号
int tx, ty; //2枚目のカードの番号
int i; //くり返し用変数
int bb, cc; //データを与えるための一時変数
bool deal[3][4] = {};
int remains = 12; //残ってるカード枚数
bool mouse_flag = false;

/*-----色関連-----*/
int White = GetColor( 255, 255, 255);
int Black = GetColor(   0,   0,   0);
int Red   = GetColor( 255,   0,   0);


void Graph();
void SetChar();
void MenuIcon(int aflag);
/*-----トランプ用　関数-----*/
void Reset();
void Shuffle();
/*-----パズル用　関数-----*/
void Change(int x, int y);


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	Graph();
	SetChar();

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)){

		/*-----マウス座標　取得-----*/
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

			/*-----Start　選択-----*/
			if (80 <= mx && mx < 240 && 380 <= my && my < 440){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
					Scene = MenuLeady;
					cflag = 1;
				}
			}
			/*-----Credit　選択-----*/
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
			
			/*-----キャラクリック-----*/
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
			/*-----たまご　進化先　設定-----*/
			if ( (mode == 0) && (click == c[0].count) ){
				mode = GetRand(1) + 1;
				click = 0;
			}

			/*-----あかちゃん男　進化先　設定-----*/
			if ( (mode == 1) && (click == c[1].count) ){
				mode = 3;
				click = 0;
			}

			/*-----あかちゃん女　進化先　設定-----*/
			if ( (mode == 2) && (click == c[2].count) ){
				mode = 4;
				click = 0;
			}

			/*-----幼少期男　進化先　設定-----*/
			if ( (mode == 3) && (click == c[3].count) ){
				mode = GetRand(1) + 5;
				click = 0;
			}

			/*-----幼少期女　進化先　設定-----*/
			if ( (mode == 4) && (click == c[4].count) ){
				mode = GetRand(1) + 7;
				click = 0;
			}

			/*-----素直・半グレ男　進化先　設定-----*/
			if ( ((mode == 5) && (click == c[5].count)) || ((mode == 6) && (click == c[6].count)) ){
				mode = GetRand(2) + 9;
				click = 0;
			}

			/*-----素直・半グレ女　進化先　設定-----*/
			if ( ((mode == 7) && (click == c[7].count)) || ((mode == 8) && (click == c[8].count)) ){
				mode = GetRand(2) + 12;
				click = 0;
			}

			/*-----青年期男　進化先　設定-----*/
			if ( ((mode == 9) && (click == c[9].count)) || ((mode == 10) && (click == c[10].count)) || ((mode == 11) && (click == c[11].count)) ){
				mode = 15;
				click = 0;
			}

			/*-----青年期女　進化先　設定-----*/
			if ( ((mode == 12) && (click == c[12].count)) || ((mode == 13) && (click == c[13].count)) || ((mode == 14) && (click == c[14].count)) ){
				mode = 16;
				click = 0;
			}

			/*-----老人　進化先　設定-----*/
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

			/*-----神経衰弱　選択-----*/
			if (170 <= mx && mx < 470 && 76 <= my && my < 226){
				if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){

					Scene = T_GameLeady;
					cflag = 1;
				}
			}
			/*-----スライドパズル　選択-----*/
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

			// カードめくり処理
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

			// 場のカード表示
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

			// メッセージ表示
			if (remains <= 0) {
				DrawGraph(120, 40, table, TRUE);

				{SetFontSize(32);
				DrawFormatString(256, 224, White, "クリア！");}
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
					// 初期パネルのシャッフル
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

				// パネルが全部揃ったか判定
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

			// パネルの描画
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
				DrawFormatString( 260, 110, Black, "小難しい本");
				DrawFormatString( 260, 230, Black, "やばい試験管");
				DrawFormatString( 260, 350, Black, "Twi○ter");

				MenuIcon(0);

				/*-----本　選択-----*/
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
				/*-----試験管　選択-----*/
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
				/*-----Twitter 選択-----*/
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
	/*-----タイトル画像　読み込み-----*/
	title = LoadGraph("Graphics/Title.png");

	/*-----キャラ画像　読み込み-----*/
	charcter[0]  = LoadGraph("Graphics/egg.png");         //たまご
	charcter[1]  = LoadGraph("Graphics/baby_m.png");      //あかちゃん男
	charcter[2]  = LoadGraph("Graphics/baby_f.png");      //あかちゃん女
	charcter[3]  = LoadGraph("Graphics/childhood_m.png"); //幼少期男
	charcter[4]  = LoadGraph("Graphics/childhood_f.png"); //幼少期女
	charcter[5]  = LoadGraph("Graphics/honest_m.png");    //素直男
	charcter[6]  = LoadGraph("Graphics/bad_m.png");       //はんぐれ男
	charcter[7]  = LoadGraph("Graphics/honest_f.png");    //素直女
	charcter[8]  = LoadGraph("Graphics/bad_f.png");        //はんぐれ女
	charcter[9]  = LoadGraph("Graphics/language_m.png");  //文系男
	charcter[10] = LoadGraph("Graphics/science_m.png");   //理系男
	charcter[11] = LoadGraph("Graphics/nube_m.png");      //キチガイ男
	charcter[12] = LoadGraph("Graphics/language_f.png");  //文系女
	charcter[13] = LoadGraph("Graphics/science_f.png");   //理系女
	charcter[14] = LoadGraph("Graphics/nube_f.png");      //キチガイ女
	charcter[15] = LoadGraph("Graphics/grandpa.png");     //老人男
	charcter[16] = LoadGraph("Graphics/grandma.png");     //老人女
	charcter[17] = LoadGraph("Graphics/tomb.png");        //墓

	/*-----タイトルボタン画像　読み込み-----*/
	t_button[0] = LoadGraph("Graphics/T_Button.png");
	t_button[1] = LoadGraph("Graphics/C_Button.png");

	/*-----メニューボタン画像　読み込み-----*/
	m_button[0] = LoadGraph("Graphics/Status_B.png");
	m_button[1] = LoadGraph("Graphics/Rice_B.png");
	m_button[2] = LoadGraph("Graphics/Game_B.png");
	m_button[3] = LoadGraph("Graphics/Item_B.png");
	m_button[4] = LoadGraph("Graphics/Setting_B.png");
	m_button[5] = LoadGraph("Graphics/Back_B.png");

	/*-----ゲーム選択　読み込み-----*/
	game_back = LoadGraph("Graphics/Game_Back.png");
	g_button[0] = LoadGraph("Graphics/tranp_B.png");
	g_button[1] = LoadGraph("Graphics/puzzle_B.png");

	/*-----背景画像　読み込み-----*/
	room = LoadGraph("Graphics/Room.png");

	/*-----ステータス画像　読み込み-----*/
	status = LoadGraph("Graphics/Status.png");

	/*-----お米画像　読み込み-----*/
	rice = LoadGraph("Graphics/syu-zo.png");
	
	/*-----アイテム画像　読み込み-----*/
	item_back[0] = LoadGraph("Graphics/Item_Back.png");
	item_back[1] = LoadGraph("Graphics/Item_Back2.png");
	item[0] = LoadGraph("Graphics/Item1.png");
	item[1] = LoadGraph("Graphics/Item2.png");
	item[2] = LoadGraph("Graphics/Item3.png");

	/*-----たがもっちが進化したぞ！！　読み込み-----*/
	evolution = LoadGraph("Graphics/evolution.png");

	/*-----設定画像　読み込み-----*/
	setting = LoadGraph("Graphics/Setting.png");

	/*-----クレジット画像　読み込み-----*/
	credit = LoadGraph("Graphics/Credit.png");

	/*-----トランプ用画像　読み込み-----*/
	LoadDivGraph("Graphics/card.png", 2, 2, 1, 40, 60, graph_cards); //カード画像　読み込み
	LoadDivGraph("Graphics/mark.png", 2, 2, 1, 28, 28, graph_marks); //マーク画像　読み込み
	LoadDivGraph("Graphics/number.png", 3, 3, 1, 28, 28, graph_numbers); //数字画像　読み込み
	table = LoadGraph("Graphics/table.png");

	/*-----パズル用画像　読み込み-----*/
	frame = LoadGraph("Graphics/frame.png");
	LoadDivGraph("Graphics/pic.png", 9, 3, 3, 106.666666667, 106.666666667, pics);
	pic_all = LoadGraph("Graphics/pic.png");

}

void SetChar(){
	c[0]  = {       "たがも",  1, 5, "何かが生まれそうな雰囲気のたまご"};
	c[1]  = {   "がもおっち",  2, 2, "生まれたばかりの男の子　幼い"};
	c[2]  = {   "がもめっち",  3, 2, "生まれたばかりの女の子　幼い"};
	c[3]  = { "おまんじゅう",  4, 3, "足が生えた　おたまじゃくしかよ"};
	c[4]  = {       "ポ〇ョ",  5, 3, "足が生えた　そうすけ好きーーー"};
	c[5]  = {       "ひろし",  6, 4, "けっして足が臭いわけではない"};
	c[6]  = {   "リーゼント",  7, 4, "スキンヘッド！！！！！"};
	c[7]  = {         "なお",  8, 4, "ツンデレ属性あったらいいね"};
	c[8]  = {     "スケバン",  9, 4, "どこぞのドラマに出てきそうね"};
	c[9]  = {         "辰文", 10, 5, "名前は強そうだが喧嘩は弱い"};
	c[10] = {         "理虫", 11, 5, "これで「おさむ」って読めない"};
	c[11] = {       "たけし", 12, 5, "ｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀｶﾞﾀ"};
	c[12] = {         "文緒", 13, 5, "絵師のお気に入りのこ"};
	c[13] = {         "理嘉", 14, 5, "乳房が巨大化する薬品を開発中"};
	c[14] = {         "Mary", 15, 5, "Mary is very yammy."};
	c[15] = {       "おじい", 16, 5, "あたまのバーコードが美しい"};
	c[16] = {       "おばあ", 17, 5, "エビよりも曲がってる背中"};
	c[17] = {   "お・は・か", 18, 1, "ｷｪｪｪｪｪｪｪｪｪｪｪｪｪｼｬﾍﾞｯﾀｧｧｧｧｧｧｧｧｧｧｧ"};
}

void MenuIcon(int aflag){

	DrawGraph(  10,  40, m_button[0], FALSE);
	DrawGraph(  10, 190, m_button[1], FALSE);
	DrawGraph(  10, 340, m_button[2], FALSE);
	DrawGraph( 530,  40, m_button[3], FALSE);
	DrawGraph( 530, 190, m_button[4], FALSE);
	DrawGraph( 530, 340, m_button[5], FALSE);

	if (aflag == 0){
		/*-----Status　選択-----*/
		if (10 <= mx && mx < 110 && 40 <= my && my < 140){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = StatusLeady;
				cflag = 1;
			}
		}
		/*-----Rice　選択-----*/
		if (10 <= mx && mx < 110 && 190 <= my && my < 290){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = RiceLeady;
				cflag = 1;
			}
		}
		/*-----Game　選択-----*/
		if (10 <= mx && mx < 110 && 340 <= my && my < 440){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = GameLeady;
				cflag = 1;
			}
		}
		/*-----Item　選択-----*/
		if (530 <= mx && mx < 630 && 40 <= my && my < 140){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = ItemLeady;
				cflag = 1;
			}
		}
		/*-----Setting　選択-----*/
		if (530 <= mx && mx < 630 && 190 <= my && my < 290){
			if (Mouse & MOUSE_INPUT_LEFT && cflag == 0){
				Scene = SettingLeady;
				cflag = 1;
			}
		}
		/*-----Back　選択-----*/
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

/*-----カードデータをリセット-----*/
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
	// シャッフル
	for (mk = 0; mk < 2; mk++){ //マークが0か1か
		for (no = 0; no < 3; no++){ //数字が1か2か3か
			for (i = 0; i < 2; i++){
				do {
					bb = GetRand(3);
					cc = GetRand(2);
				} while (deal[cc][bb]);

				cards[cc][bb].mark = mk;
				cards[cc][bb].number = no;
				cards[cc][bb].reverse = true;

				deal[cc][bb] = true; //同じ場所にデータを与えないようにする
			}
		}
	}
}

/*-----選択したパネルと空白を入れ替える-----*/
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