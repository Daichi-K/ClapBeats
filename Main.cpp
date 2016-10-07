#include "common.h"


//グローバル変数宣言
double circleRadius[ MAX_MUSIC_DATA ];
int notesCount = 0;
int comboNum = 0;
int gageNum = 0;
bool isCircleDisplay[MAX_MUSIC_DATA] = { false };
int SCREEN_WIDTH =  0;
int SCREEN_HEIGHT = 0;



//プロトタイプ宣言
void getSound( );
void setSound( );
void drawCircle( Texture circle );

void Main( ) {	
	
	// テクスチャを画像ファイルからロード
	const Size targetSize(1024, 768);
	const Texture backGroundTexture(L"Assets//BackGround.jpg");
	const Texture cockpit(L"Assets//cockpit.png");
	const Texture title(L"Assets//title.jpg");
	const Image icon(L"Assets//icon.png");
	const Texture enemy(L"Assets//enemy.png");
	const Texture circle(L"Assets//circle.png");
	const Texture enemyEffect(L"Assets//enemyEffect.png");
	const Texture enemyHit(L"Assets//enemyHit.png");
	const Texture beatsEffect(L"Assets//beatsEffect.png");
	const Texture frame(L"Assets//frame.png");
	const Texture frame2(L"Assets//frame2.png");
	const Texture kitou2(L"Assets//kito2.png");
	const Texture kitou1(L"Assets//kito1.png");
	const Texture garasu(L"Assets//garasu.png");
	const Texture comboTxt(L"Assets//character//combo//combo.png"); 
	const Texture radar(L"Assets//radar.png");
	const Texture ball(L"Assets//ball.png");
	const Texture tca(L"Assets//tca.png");
	const Texture break0(L"Assets//break.png");
	const Texture last(L"Assets//last.jpg");

	const Texture num0( L"Assets//character//number//0.png" );
	const Texture num1( L"Assets//character//number//1.png" );
	const Texture num2( L"Assets//character//number//2.png" );
	const Texture num3( L"Assets//character//number//3.png" );
	const Texture num4( L"Assets//character//number//4.png" );
	const Texture num5( L"Assets//character//number//5.png" );
	const Texture num6( L"Assets//character//number//6.png" );
	const Texture num7( L"Assets//character//number//7.png" );
	const Texture num8( L"Assets//character//number//8.png" );
	const Texture num9( L"Assets//character//number//9.png" );

	const Texture gageBase(L"Assets//character//gage//gage.png");
	const Texture gage01( L"Assets//character//gage//01.png" );
	const Texture gage02( L"Assets//character//gage//02.png" );
	const Texture gage03( L"Assets//character//gage//03.png" );
	const Texture gage04( L"Assets//character//gage//04.png" );
	const Texture gage05( L"Assets//character//gage//05.png" );
	const Texture gage06( L"Assets//character//gage//06.png" );
	const Texture gage07( L"Assets//character//gage//07.png" );
	const Texture gage08( L"Assets//character//gage//08.png" );
	const Texture gage09( L"Assets//character//gage//09.png" );
	const Texture gage10( L"Assets//character//gage//10.png" );
	const Texture gage11( L"Assets//character//gage//11.png" );
	const Texture gage12( L"Assets//character//gage//12.png" );
	const Texture gage13( L"Assets//character//gage//13.png" );
	const Texture gage14( L"Assets//character//gage//14.png" );
	const Texture gage15( L"Assets//character//gage//15.png" );
	const Texture gage16( L"Assets//character//gage//16.png" );
	const Texture gage17( L"Assets//character//gage//17.png" );
	const Texture gage18( L"Assets//character//gage//18.png" );
	const Texture gage19( L"Assets//character//gage//19.png" );
	const Texture gage20( L"Assets//character//gage//20.png" );
	const Texture gage21( L"Assets//character//gage//21.png" );
	const Texture gage22( L"Assets//character//gage//22.png" );
	const Texture gage23( L"Assets//character//gage//23.png" );
	const Texture gage24( L"Assets//character//gage//24.png" );
	const Texture gage25( L"Assets//character//gage//25.png" );
	const Texture gage26( L"Assets//character//gage//26.png" );

	// サウンドファイルをロード
	const Sound soundEffect( L"Assets//sound//soundE.wav" );
	const Sound music( L"Assets//sound//music.mp3" );
	const Sound breakSe( L"Assets//sound//breakSe.wav" );


	//ウィンドウの設定
	Window::SetIcon( icon );
	windowTitle( );
	//windowSize( );			//ウィンドウ
	Window::SetVirtualFullscreen( targetSize );//フルスクリーン
	//Window::SetFullscreen(true, targetSize);
	//Window::SetStyle(WindowStyle::Sizeable);

	//時間経過測定
	double gameTime = 0;
	
	//定数宣言
	const Font font( 10 );

	//変数宣言
	int notesCountHit = 0;
	int soundCount = 0;
	int enemyAlpha = 0;
	int hitEffect = 0;
	int beatsEffectAlpha = 0;
	int beatsEffectCount = 0;
	double radarRad = 0;
	bool clapping = false;
	bool hitting = false;
	bool titleSwitch = true;
	double max = 0;
	double circlePosX[ MAX_MUSIC_DATA ];
	double circlePosY[ MAX_MUSIC_DATA ];
	double breakRadius = 0;

	for( int i = 0; i < MAX_MUSIC_DATA  ; i++ ) {
		circleRadius[ i ] = 1300;
		circlePosX[ i ] = 0;
		circlePosY[ i ] = 0;
	}

	//録音機器
	setSound( );	
	//録音機器設定 

	// 10 秒間, サンプリングレート 44100Hz で録音を開始する
	if ( !Recorder::Start( ) ) {
		return;
	}

	//メインループ
	while ( System::Update ( ) ) {

		SCREEN_WIDTH = Window::Width( );
		SCREEN_HEIGHT = Window::Height( );
		/*------------------------------------------------
			背景の描画
		--------------------------------------------------*/
		backGroundTexture. resize( SCREEN_WIDTH, SCREEN_HEIGHT ). draw( );

		/*------------------------------------------------
			あたり判定
		--------------------------------------------------*/
			enemyHit.resize( SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.66666 ).draw( SCREEN_WIDTH * 0.25, 0, Alpha( hitEffect ) );

			if (clapping && circleRadius[ notesCountHit ] <= SCREEN_HEIGHT * 0.56666 && circleRadius[ notesCountHit ] >= SCREEN_HEIGHT * 0.383333 ) {		//当たり判定
				hitting = true;
				isCircleDisplay[ notesCountHit ] = false;
				circleRadius[notesCountHit] = 0;
				notesCountHit++;
			} else {
				hitting = false;
			}

			if(  circleRadius[ notesCountHit ] <= SCREEN_HEIGHT * 0.25  ) {
				notesCountHit++;
			}

			if( hitting == true ) {
				comboNum++;
				gageNum++;
				hitEffect = 200;
			} else {
				hitEffect-= 10;
			}
			if( hitEffect <= 0 ) {
				hitEffect = 0;
			}

		/*------------------------------------------------
		 ノーツの更新
		--------------------------------------------------*/
		//ノーツが時間になったら
			int dataTime = (musicTimeData[notesCount] + 2.9) * 60;
			if (gameTime == dataTime) {
			isCircleDisplay[ notesCount ] = true;
			circleRadius[ notesCount ] = SCREEN_WIDTH * 1.625;
				
			notesCount++;
		}


		/*------------------------------------------------
			ターゲットの描画														
		--------------------------------------------------*/
		enemy. resize( SCREEN_WIDTH * 0.275, SCREEN_WIDTH * 0.275 ).draw( SCREEN_WIDTH * 0.3625, SCREEN_HEIGHT * 0.15 );
		enemyEffect. resize( SCREEN_WIDTH * 0.275, SCREEN_WIDTH * 0.275 ).draw( SCREEN_WIDTH * 0.3625, SCREEN_HEIGHT * 0.15, Alpha( enemyAlpha ) );

		circle.resize( SCREEN_HEIGHT * 0.5, SCREEN_HEIGHT * 0.5 ).drawAt(SCREEN_WIDTH * 0.3625 + SCREEN_WIDTH * 0.275 / 2, SCREEN_HEIGHT * 0.15 + SCREEN_WIDTH * 0.275 / 2, Alpha( 150 ) );

		if( clapping == true ) {
			soundEffect.playMulti( );
			enemyAlpha = 255;
		} else{
			enemyAlpha-= 20;
		}

		if( enemyAlpha <= 0 ) {
			enemyAlpha = 0;
		}

		/*------------------------------------------------
			ノーツの描画
		--------------------------------------------------*/
		//ノーツ通常時
		drawCircle( circle );	

		/*------------------------------------------------
			コクピットの描画
		--------------------------------------------------*/
		beatsEffectCount++;

		if( beatsEffectCount == 21 ) {
			beatsEffectAlpha = 255;
			beatsEffectCount = 0;
		} else {
			beatsEffectAlpha-= 30;
		}

		if( beatsEffectAlpha <= 0 ) {
			beatsEffectAlpha = 0;
		}

		cockpit. resize( SCREEN_WIDTH, SCREEN_HEIGHT ). draw( );

		//グラフ

		tca. resize( SCREEN_WIDTH * 0.1, SCREEN_HEIGHT * 0.1083 ). draw( SCREEN_WIDTH * 0.2975, SCREEN_HEIGHT * 0.7666 );		

		//レーダー

		radarRad-= 3;

		radar.resize( SCREEN_WIDTH * 0.0912, SCREEN_WIDTH * 0.0912 ).rotate(Radians( radarRad ) ).draw( SCREEN_WIDTH * 0.615, SCREEN_HEIGHT * 0.76666 );
		ball.resize( SCREEN_WIDTH * 0.0912  , SCREEN_WIDTH * 0.0912                             ).draw( SCREEN_WIDTH * 0.615, SCREEN_HEIGHT * 0.76666 );
		
		frame2.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		
		//コンボ描画
		comboTxt. resize( SCREEN_WIDTH * 0.05, SCREEN_HEIGHT *  0.03333). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.01875, SCREEN_HEIGHT * 0.8  );

		//10の位
		if( comboNum / 10 == 1 ) {
			num1. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 2 ) {
			num2. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 3 ) {
			num3. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 4 ) {
			num4. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 5 ) {
			num5. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 6 ) {
			num6. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 7 ) {
			num7. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 8 ) {
			num8. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		} else if( comboNum / 10 == 9 ) {
			num9. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2 - SCREEN_WIDTH * 0.04 , SCREEN_HEIGHT * 0.70833  );
		}

		//1の位
		if( comboNum % 10 == 0 ) {
			num0. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 1 ) {
			num1. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 2 ) {
			num2. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 3 ) {
			num3. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 4 ) {
			num4. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 5 ) {
			num5. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 6 ) {
			num6. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 7 ) {
			num7. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 8 ) {
			num8. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		} else if( comboNum % 10 == 9 ) {
			num9. resize( SCREEN_WIDTH * 0.0375, SCREEN_HEIGHT * 0.08333 ). draw( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.70833 );
		}


		frame. resize( SCREEN_WIDTH, SCREEN_HEIGHT ). draw( );

		//ゲージ
		gageBase.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();

		if (gageNum == 1) {
			gage01.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 2) {
			gage02.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 3) {
			gage03.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 4) {
			gage04.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 5) {
			gage05.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 6) {
			gage06.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 7) {
			gage07.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 8) {
			gage08.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 9) {
			gage09.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 10) {
			gage10.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 11) {
			gage11.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 12) {
			gage12.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 13) {
			gage13.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 14) {
			gage14.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 15) {
			gage15.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 16) {
			gage16.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 17) {
			gage17.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 18) {
			gage18.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 19) {
			gage19.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 20) {
			gage20.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 21) {
			gage21.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 22) {
			gage22.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 23) {
			gage23.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 24) {
			gage24.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum == 25) {
			gage25.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}
		if (gageNum >= 26) {
			gage26.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw();
		}

		beatsEffect.resize(SCREEN_WIDTH, SCREEN_HEIGHT).draw(Alpha(beatsEffectAlpha));

		/*------------------------------------------------
			ラストエフェクト
		--------------------------------------------------*/

		if( gameTime / 60 >= 170 ) {
			breakRadius+= SCREEN_HEIGHT * 0.02;
			break0.resize( breakRadius, breakRadius).drawAt(SCREEN_WIDTH * 0.3625 + SCREEN_WIDTH * 0.275 / 2, SCREEN_HEIGHT * 0.15 + SCREEN_WIDTH * 0.275 / 2, Alpha( 200 ) );
		}
		if( gameTime / 60 == 172 ) {
			breakSe.playMulti( );
		}
		if(  gameTime / 60 >= 175 ) {
			last. resize( SCREEN_WIDTH, SCREEN_HEIGHT ). draw( );
		}

		/*------------------------------------------------
			音声の入力 ｽﾍﾟｰｽも
		--------------------------------------------------*/
		max = Recorder::GetMaxAmplitude( );

		//音入力の確認
		if( max >= SOUND_AMPLI ) {
			soundCount++;
		} else {
			soundCount = 0;
		}

		//音が確認されたら
		if ( soundCount == 1 || Input::KeySpace.clicked ) {
			clapping = true;
		} else {
			clapping = false;
		}

		 // 録音が終了
		if (Recorder::IsEnded( ) )
		{
			// 最初の位置から録音し直し
			Recorder::Restart( );
		}

		/*------------------------------------------------
			待機画面
		--------------------------------------------------*/
		if( titleSwitch == true ) {
			if ( Input::KeyEnter.clicked ) {
				titleSwitch = false;
				music.play( );
			}

			//title. resize( SCREEN_WIDTH, SCREEN_HEIGHT ). draw( );
		}
		if ( titleSwitch == false ) {
			gameTime++;
		}
	}
	
}

//録音機器取得
void getSound( ){
	for ( const auto& recorder : Recorder::Enumerate( ) ) {
		Println( recorder.deviceID, L": ", recorder.name );
	}
}

//録音機器設定
void setSound( ) {
	 Recorder::SetDevice( 0 );
}

//サークルの描画
void drawCircle( Texture circle ) {
	for (int i = 0; i < MAX_MUSIC_DATA; i++) {
		if (!isCircleDisplay[ i ]) {
			continue;
		}
		
		circleRadius[ i ] -= SCREEN_HEIGHT * 0.02;
		if (circleRadius[ i ] <= 0) {
			isCircleDisplay[ i ] = false;
			comboNum = 0;
			gageNum -= 2;
			if (gageNum <= 0) {
				gageNum = 0;
			}
		}
		circle.resize(circleRadius[ i ], circleRadius[ i ]).drawAt(SCREEN_WIDTH * 0.3625 + SCREEN_WIDTH * 0.275 / 2, SCREEN_HEIGHT * 0.15 + SCREEN_WIDTH * 0.275 / 2, Alpha( 200 ) );
	}
}