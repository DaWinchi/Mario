#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int ground = 336;

float offsetX=0, offsetY=0;

const int W = 150;
const int H = 17;

String TileMap[H] = {
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
	"0                                                                                                                                                    0",
	"0  www                                                                               w                                                               0",
	"0                   w                                  w                   w                                                                         0",
	"0                                      w                                       kk     kkkkkk    k       k   kkkkkkk k    k kkkkk                     0",
	"0                                                                             k  k    k    k    kk     kk  k      k k    k k                         0",
	"0       w              c       w                w            w               k    k   k    k    k k   k k   k     k k    k k                         0",
	"0                                                                       r   kkkkkkkk  kkkkkk    k  k k  k    kkkkkk kkkkkk kkk                       0",
	"0                                                                      rr  k        k k         k   k   k   k     k k    k k                         0",
	"0                                                                     rrr  k        k k         k       k  k      k k    k kkkkk                     0",
	"0               c                                                    rrrr                                                                            0",
	"0                                                                   rrrrr                                                                            0",
	"0G                                                     t0          rrrrrr            G                                                               0",
	"0           d    g       d                             00         rrrrrrr                                                                            0",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};



class PLAYER {

public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		sprite.setTextureRect(IntRect(98, 144, -16, 16));
		rect = FloatRect(65, 100, 16, 16);

		dx = dy = 0.1;
		currentFrame = 0;
	}

	void update(float time)
	{
		rect.left += dx*time;

		Collision(0);

		if (!onGround) dy = dy + 0.0005*time;

		rect.top += dy;
		onGround = false;

		Collision(1);

		if (rect.top > ground) { rect.top = ground; dy = 0; onGround = true; }


		currentFrame += 0.005*time;
		if (currentFrame > 3) currentFrame -= 3;
		if (dx>0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
		if (dx<0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));


		sprite.setPosition(rect.left-offsetX, rect.top-offsetY);

		dx = 0;
	}



	void Collision(int dir)
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
			if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't') || (TileMap[i][j] == 'c'))
			{
				if (dy>0 && dir == 1)
				{
					rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
				}
				if (dy<0 && dir == 1)
				{
					rect.top = i * 16 + 16;   dy = 0; 
					
				}
				if (dx>0 && dir == 0)
				{
					rect.left = j * 16 - rect.width; 
					
				}
				if (dx<0 && dir == 0)
				{
					rect.left = j * 16 + 16;
				}
			}

			if (TileMap[i][j] == 'c') {
				// TileMap[i][j]=' '; 
			}
			}
	}
};


class ENEMY{

public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	bool life;

	void set(Texture &image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 16, 16);
		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time)
	{
		rect.left += dx*time;
		Collision(0);

		currentFrame += 0.005*time;
		if (currentFrame > 2) currentFrame -= 2;
		sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 16, 16));

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}

	void Collision(int dir)
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
			if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't') || (TileMap[i][j] == 'c'))
			{
				
				if (dx > 0 && dir == 0)
				{
					rect.left = j * 16 - rect.width;
					dx = -dx;
				}
				else  if (dx < 0 && dir == 0)
				{
					rect.left = j * 16 + 16;
					dx = -dx;
				}
			}

			if (TileMap[i][j] == 'c') {
				// TileMap[i][j]=' '; 
			}
			}
	}
};

int main()
{
	RenderWindow window(sf::VideoMode(700, 250), "Test!");
	CircleShape MyCircle(100.f);
	MyCircle.setFillColor(Color::Green);

	Texture t;
	t.loadFromFile("Mario_Tileset.png");
	Sprite tile(t);

	PLAYER player(t);
	ENEMY enemy;
	enemy.set(t, 48 * 16, 13 * 16);

	SoundBuffer buf_jump;
	buf_jump.loadFromFile("Jump.ogg");
	Sound jump(buf_jump);


	Music music;
	music.openFromFile("theme.ogg");

	Clock clock;
	music.setVolume(30);
	music.play();

	RectangleShape rectangle;
	rectangle.setSize(Vector2f(32, 32));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.dx = -0.1;

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			
			if (player.onGround) { player.dy = -0.57; player.onGround = false; jump.play(); };
		}


		player.update(time);
		enemy.update(time);

		if (player.rect.intersects(enemy.rect))
		{
			if (enemy.life){
				if (player.dy > 0) { enemy.life = false; enemy.dx = 0; player.dy = -0.2; }
				else player.sprite.setColor(Color::Red);
			}
		}


		if ((player.rect.left>200)&&(player.rect.left<(W*16-700/2)))offsetX = player.rect.left-400/2;
		//if(player.rect.top<200) offsetY = player.rect.top-250/2;

		window.clear(Color(50, 50, 50));

		for (int i = 0; i<H; i++)
			for (int j = 0; j<W; j++)
			{
			if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

			if (TileMap[i][j] == 'k')  tile.setTextureRect(IntRect(143, 112, 16, 16));

			if (TileMap[i][j] == 'c')  tile.setTextureRect(IntRect(143 - 16, 112, 16, 16));

			if (TileMap[i][j] == 't')  tile.setTextureRect(IntRect(0, 47, 32, 95 - 47));

			if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

			if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

			if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(0, 106, 74, 127 - 106));

			if (TileMap[i][j] == 'w')  tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

			if (TileMap[i][j] == 'r')  tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

			if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

			tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
			window.draw(tile);
			}


		window.draw(player.sprite);
		window.draw(enemy.sprite);
		window.display();
	}

	return 0;
}