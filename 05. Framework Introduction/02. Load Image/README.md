### Load Image Dengan Framework

Kita sudah membahas tentang cara load image di tahap sebelumnya. Namun di _shared framework_ akan menggunakan cara yang sedikit berbeda. Karena semua bagian berkaitan dengan load image akan ada di `cAssetManager` dan untuk rendering akan dibuat class baru dan terpisah. Oleh karena itu mari kita memulai dengan mengerti `cAssetManager` sebelum melanjutkan

Secara default, sudah ada contoh load spritesheet yang ada di framework. Load image nya masih menggunakan konsep identifier dan index seperti pada sebelumnya, namun dengan cara yang lebih berbeda. `identifiers` kita sudah dibungkus dengan class `cTexture` dan kita menentukan identifier kita di sini. Buka file `cAssetManager.h` dan kita akan dapat melihat potongan kodingan seperti di bawah.
```cpp
...
//Image array size
#define NUM_TEX		 1
//Image identifiers
#define SPRITESHEET_PLAYERS	1
...
	cTexture textures[NUM_TEX];
...
```

Di sini, `identifiers` kita telah digantikan dengan `textures[NUM_TEX]`. Secara default, nilai dari `NUM_TEX` adalah 1 karena di project hanya menggunakan satu texture. Kita dapat mengubah nilai dari `NUM_TEX` sesuai dengan jumlah texture yang akan kita load nantinya. Jika ingin dilebihkan indexnya juga tidak masalah.
Lalu, untuk `#define SPRITESHEET_PLAYERS	1` menunjukkan bahwa index dari spritesheet player adalah 1. Ini membantu kita sehingga kita tidak perlu lagi mengingat-ingat terus index-index dari setiap texture kita karena sudah di-define. Untuk kedepannya,  kita akan menambahkan 1 setiap melakukan load texture baru.
Di file ini juga terdapat satu vector yang menampung data koordinat serta identifier dari sprite player.
```cpp
std::vector<cSprite*> *player = new std::vector<cSprite*>;
```

Sekarang mari kita melihat file `cAssetManager.cpp` di function `cAssetManager::Load()`. Di sini akan berisi kodingan untuk load setiap texture yang akan kita gunakan.
```cpp
bool cAssetManager::Load()
{
	int res;

	res = LoadImage(SPRITESHEET_PLAYERS, "Textures/Spritesheets/spritesheet_players.png", GL_RGBA);
	if (!res) return false;
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 8; i++) {
			float x0, y0, x1, y1;
			int tex_w, tex_h;
			GetSize(GetID(SPRITESHEET_PLAYERS), &tex_w, &tex_h);
			float sprite_width = 128.0f / tex_w;
			float sprite_height = 256.0f / tex_h;
			x0 = sprite_width*j;
			x1 = sprite_width*(j + 1);
			y0 = sprite_height*i;
			y1 = sprite_height*(i + 1);
			player->push_back(new cSprite(GetID(SPRITESHEET_PLAYERS), x0, y0, x1, y1));
		}
	}

	return true;
}
```

Mari kita mencoba untuk load background image di framework ini. Gambar yang akan kita load akan ada di path `Textures/PNG/Backgrounds/colored_grass.png`.
![background.png][background.png]

Kembali lagi ke file `cAssetManager.h`, mari kita menambahkan identifier untuk sprite kita.
```cpp
...
//Image array size
#define NUM_TEX		 10
//Image identifiers
#define SPRITESHEET_PLAYERS	1
#define SPRITE_COLORED_GRASS 2
...
```
Setelah itu, tambahkan juga satu object `cSprite` yang akan menampung data dari background setelah kita me-load texturenya di bawah vector player.
```cpp
...
std::vector<cSprite*> *player = new std::vector<cSprite*>;
cSprite *background;
...
```
Lalu kita ke file `cAssetManager.cpp` dan menambahkan kodingan di function Load.
```cpp
bool cAssetManager::Load()
{
	...
	res = LoadImage(SPRITE_COLORED_GRASS, "Textures/PNG/Backgrounds/colored_grass.png", GL_RGBA);
	if (!res) return false;
	background = new cSprite(GetID(SPRITE_COLORED_GRASS), 0, 0, 1, 1);
	...
}
```
Kita tidak perlu menambahkan loopingan `for` seperti di `SPRITESHEET_PLAYERS` karena background kita hanya satu gambar saja.

Sekarang mari kita ke file `cMenuScene.cpp` untuk mencoba render `colored_grass` kita. Ubah kodingan `cMenuScene::Render()` menjadi seperti di bawah.
```cpp
void cMenuScene::Render()
{
	renderBitmapString(300, 300, 9, GLUT_BITMAP_HELVETICA_18, "Press Any Key To Continue", 1, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().background->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);	glVertex3i(0, 0, 49);
	glTexCoord2f(1, 1);	glVertex3i(GAME_WIDTH, 0, 49);
	glTexCoord2f(1, 0);	glVertex3i(GAME_WIDTH, GAME_HEIGHT, 49);
	glTexCoord2f(0, 0);	glVertex3i(0, GAME_HEIGHT, 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
```
Dan coba jalankan project, maka di scene awal sudah akan muncul background kita.
![result][result.png]

Untuk kodingan mana saja yang berubah dapat dilihat di folder `Modified File`. File yang tidak ada di folder tersebut berarti tidak berubah dari framework awal.
[background.png]: https://i.ibb.co/2FWf15j/background.png
[result.png]: https://i.ibb.co/74vTpbv/background.png