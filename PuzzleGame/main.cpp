#include<SFML/Graphics.hpp>

using namespace sf;

int main(void) {
	RenderWindow app(VideoMode(256, 256), "PuzzleGame");//화면 생성
	app.setFramerateLimit(60);

	Texture t;//전체 그림
	t.loadFromFile("images/15.png");
	
	int w = 64; //퍼즐 하나의 폭 ( 전체 이미지는 256x256 )
	
	int grid[6][6] = { 0, }; //4*4로 하게되면 1, 2, 3, 4, 5, 8등 끝에부분의 위 아래 등이 비게된다.
	
	Sprite sprite[17];

	int number = 1;
	//초기 이미지 및 타일설정
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sprite[number].setTexture(t);
			sprite[number].setTextureRect((IntRect(i * w, j * w, w, w)));
			grid[i + 1][j + 1] = number;
			number++;
		}
	}

}