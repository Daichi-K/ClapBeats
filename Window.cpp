#include "common.h"

// ウィンドウのタイトルを設定する
void windowTitle( ) {
	Window::SetTitle( L"ClapBeats" );
}

//フルスクリーンにする
void fullScreen( ) {
	Window::SetVirtualFullscreen( Window::GetState( ).screenSize );
}

// ウィンドウサイズを 幅 300, 高さ 400 にする
void windowSize( ) {
	Window::Resize( WINDOW_WIDTH, WINDOW_HEIGHT );
}