#include <SFML/Graphics.hpp>

using namespace sf;

int main(void)
{
	RenderWindow app(VideoMode(256, 256), "PuzzleGame");//화면 생성
	app.setFramerateLimit(60);

	Texture t;//전체 그림
	t.loadFromFile("images/15.png");

	int w = 64;	// 퍼즐 하나의 폭 (전체 이미지는 256X256)

	int grid[6][6] = { 0, };	//4*4로 하게되면 1, 2, 3, 4, 5, 8등 끝에부분의 위 아래 등이 비게된다. 0은 벽을, 16은 비어있는 공간을 의미

	Sprite sprite[17];

	int number = 1;

	// 초기 이미지 및 타일설정
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprite[number].setTexture(t);
			sprite[number].setTextureRect((IntRect(j * w, i * w, w, w)));
			grid[i + 1][j + 1] = number;
			number++;
		}
	}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					Vector2i pos = Mouse::getPosition(app);
					int x, y; //grid에 대한 x행, y열
					x = pos.x / 64 + 1;
					y = pos.y / 64 + 1;

					int dx = 0, dy = 0;

					if (grid[y + 1][x] == 16) { dy = 1; dx = 0; } //밑으로 움직임
					else if (grid[y - 1][x] == 16) { dy = -1; dx = 0; } //아래로
					else if (grid[y][x + 1] == 16) { dy = 0; dx = 1; } //오른쪽으로 
					else if (grid[y][x - 1] == 16) { dy = 0; dx = -1; } //왼쪽으로


					//마우스로 누른 타일과 빈 칸의 위치바꿈
					int temp = grid[y][x];
					grid[y][x] = 16;
					grid[y + dy][x + dx] = temp;

					//애니메이션
					sprite[16].move(-dx * (float)w, -dy * (float)w);
					float speed = 3.f;

					for (int i = 0; i < w; i += (int)speed) {
						sprite[temp].move(speed * dx, speed * dy);
						app.draw(sprite[16]);
						app.draw(sprite[temp]);
						app.display();
					}
				}
			}
		}

		app.clear(Color::White);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				// 해당 행렬에 있는 숫자 가지고 오기z
				int n = grid[i + 1][j + 1];

				sprite[n].setPosition((float)(j * w), (float)(i * w));
				app.draw(sprite[n]);
			}
		}
		app.display();
	}
}