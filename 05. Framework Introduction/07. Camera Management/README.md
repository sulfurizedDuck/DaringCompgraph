### Camera Management

Pada materi kali ini kita akan membahas tentang camera dan cara memanipulasinya. Selama ini camera kita statis dan menjangkau seluruh window game kita. Di sini, kita akan membuat camera kita tidak lagi melihat seluruh window game, namun fokus ke satu patokan dan dapat mengikuti target yang kita buat.

Di sini, object yang dapat bergerak adalah `cPlayer`, sehingga kita akan membuat camera mengikuti `cPlayer`. Pertama mari kita melihat dulu cara camera bekerja. Mari kita buka file `cGame.cpp` dan melihat ke function `Init`.

__cGame.cpp__
```cpp
...
bool cGame::Init()
{
	...
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.left = 0;
	visible_area.right = GAME_WIDTH;
	visible_area.bottom = 0;
	visible_area.top = GAME_HEIGHT;

	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
	...
}
...
```

Inilah potongan kodingan yang diperlukan untuk melakukan set camera, tepatnya pada function `glOrtho`. Namun, `glOrtho` berefek pada _matrix projection_, sedangkan secara normal kita selalu ada di _matrix model-view_ sehingga sebelum memanggil function `glOrtho` kita harus mengubah mode matrix kita menjadi _matrix projection_ dengan function `glMatrixMode`. Pada function `glOrtho` sendiri menerima parameter `left`, `right`, `bottom`, `top`, `near`, dan `far`, yang masing-masing merepresentasikan titik koordinat kamera untuk masing-masing sisi. Di contoh di atas menggunakan satu object pendukung yaitu `visible_area` yang merupakan object dari class `cRect`. Untuk pendefinisiannya dapat dilihat di file `cGame.h`.

__cGame.h__
```cpp
class cGame
{
public:
	...
private:
	/**
	Default camera viewport to use on the ortographic camera
	*/
	cRect visible_area;
	...
};
```

Sedangkan untuk `near` dan `far` adalah koordinat untuk kedalaman yang dapat dilihat oleh kamera. Untuk nilainya kita biarkan saja.

Mari kita mencoba membuat kamera kita menjadi mengikuti `cPlayer` kemanapun `cPlayer` kita bergerak. Maka mari kita _copas_ potongan kodingan untuk mengatur kamera ke file `cLevel1Scene.cpp` function `Render`.

__cLevel1Scene.cpp__
```cpp
...
void cLevel1Scene::Render()
{
	...
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.left = 0;
	visible_area.right = GAME_WIDTH;
	visible_area.bottom = 0;
	visible_area.top = GAME_HEIGHT;

	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
}
...
```

Karena di `cLevel1Scene` belum ada definisi untuk `visible_area`, mari kita membuatnya dahulu di file `cLevel1Scene.h`.

__cLevel1Scene.h__
```cpp
class cLevel1Scene:public cScene
{
public:
	...
private:
	...
	cRect visible_area;
};
```

Maka sekarang setiap kali scene kita melakukan render ulang scene, _projection matrix_ kita juga ikutan berubah. Namun karena posisi kamera tidak kita ubah sama sekali, maka ketika dijalankan tidak akan terlihat perubahan sama sekali.

Mari kita mengganti `left`, `right`, `bottom`, dan `top` dari `visible_area` menjadi relative terhadap posisi `cPlayer`.

__cLevel1Scene.cpp__
```cpp
void cLevel1Scene::Render()
{
	...
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.left = player->X();
	visible_area.right = player->X() + player->Width();
	visible_area.bottom = player->Y();
	visible_area.top = player->Y() + player->Height();

	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
}
```

Sekarang jika kita jalankan lagi maka sekarang `cPlayer` kita menjadi cukup besar untuk menutupi seluruh kamera dan setiap kita membuat `cPlayer` berjalan maka kamera akan mengikuti `cPlayer`. 

![plain-scene.gif][plain-scene.gif]

Namun kita jadi tidak dapat memastikan apakah `cPlayer` beneran bergerak atau hanya diam di tempat, sehingga mari menambahkan background.

__cLevel1Scene.cpp__
```cpp
void cLevel1Scene::Render()
{
	...
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().background->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);	glVertex3i(0, 0, 49);
	glTexCoord2f(1, 1);	glVertex3i(GAME_WIDTH, 0, 49);
	glTexCoord2f(1, 0);	glVertex3i(GAME_WIDTH, GAME_HEIGHT, 49);
	glTexCoord2f(0, 0);	glVertex3i(0, GAME_HEIGHT, 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.left = player->X();
	visible_area.right = player->X() + player->Width();
	visible_area.bottom = player->Y();
	visible_area.top = player->Y() + player->Height();

	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
}
```

Mari kita mencoba jalankan lagi.

![bg-added-scene.gif][bg-added-scene.gif]

Sekarang kelihatan bahwa player kita beneran bergerak dan background di belakang statis. Namun perspektif camera masih sangat jelek, sehingga mari kita membuat cameranya dapat melihat lebih jauh dari player.

__cLevel1Scene.cpp__
```cpp
void cLevel1Scene::Render()
{
	...
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.left = player->X() - 100;
	visible_area.right = player->X() + player->Width() + 100;
	visible_area.bottom = player->Y() - 100;
	visible_area.top = player->Y() + player->Height() + 100;

	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
}
```

Sekarang sudah terlihat lebih baik. 

![adjusted-scene.gif][adjusted-scene.gif]

Namun perbandingan panjang dan lebar `cPlayer` kita menjadi tidak terlalu sesuai dengan sebelumnya. Ini karena aspek rasio antara panjang camera dan lebar camera tidak sama lagi setelah kita melakukan resize. Maka untuk memastikan aspek rasio yang tetap dan tidak berubah, kita mengubahnya menjadi seperti di bawah ini.

```cpp
void cLevel1Scene::Render()
{
	...
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.left = player->X() - 100;
	visible_area.right = player->X() + player->Width() + 100;

	double ratio = (double) GAME_HEIGHT / GAME_WIDTH;
	double camera_width = visible_area.right - visible_area.left;

	visible_area.bottom = player->Y() - 50;
	visible_area.top = visible_area.bottom + (ratio * camera_width);

	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
}
```

Maka karena kita sudah menggunakan rasio dalam pengukuran ukuran kamera, maka rasio panjang dan lebar dari yang diproyeksikan camera kita sudah bagus.

![ratio-scene.gif][ratio-scene.gif]

Seperti biasa, untuk kodingan mana saja yang berubah dapat dilihat di folder Modified File. File yang tidak ada di folder tersebut berarti tidak berubah dari framework awal.

[plain-scene.gif]: https://i.ibb.co/3zntYcS/plain-scene.gif
[bg-added-scene.gif]: https://i.ibb.co/v1cF1gG/bg-added-scene.gif
[adjusted-scene.gif]: https://i.ibb.co/JHPkNMG/adjusted-scene.gif
[ratio-scene.gif]: https://i.ibb.co/P92wRfx/ratio-scene.gif