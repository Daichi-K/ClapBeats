#include "common.h"

// �E�B���h�E�̃^�C�g����ݒ肷��
void windowTitle( ) {
	Window::SetTitle( L"ClapBeats" );
}

//�t���X�N���[���ɂ���
void fullScreen( ) {
	Window::SetVirtualFullscreen( Window::GetState( ).screenSize );
}

// �E�B���h�E�T�C�Y�� �� 300, ���� 400 �ɂ���
void windowSize( ) {
	Window::Resize( WINDOW_WIDTH, WINDOW_HEIGHT );
}