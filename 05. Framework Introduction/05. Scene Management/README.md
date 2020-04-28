### Scene Management

 Seperti yang kita ketahui, pada framework yang telah disediakan, sudah ada dua scene yang tersedia, yaitu `cMenuScene` dan `cLevel1Scene`. Kita juga sudah tahu bahwa cara berpindah scene lumayan mudah, yaitu dengan menggunakan function `UpdateScene` pada `cGame`.

```cpp
cGame::getInstance().UpdateScene(new cLevel1Scene());
```

Namun masih ada satu lagi, yaitu bagaimana kita membuat scene baru? Maka pada materi kali ini, kita akan membahas lebih lanjut tentang cara membuat dan berpindah ke scene baru.

#### Buat scene baru
Untuk mempraktekkannya, mari kita membuat satu scene baru yang berisi ending dari `cLevel1Scene`. Mari kita menamakannya dengan `cEndScene`. Tahap awalnya adalah dengan membuat 2 file baru, yaitu file header dan file cpp dengan cara __Add New Item__ seperti ketika kita membuat `cPerson.h` dan `cPerson.cpp`.

![new-file][new-file.png]

Lalu berikutnya kita akan mengisi code nya. Isi awalnya kita copy-paste dulu dari `cMenuScene.h` dan `cMenuScene.cpp`. Setelah itu, kita mengganti saja semua nama yang awalnya `cMenuScene` menjadi `cEndScene` dengan menggunakan fitur _Find and Replace_ yang dapat diakses dengan shortcut __Ctrl+H__. Lakukan ini untuk kedua file `cEndScene.h` dan `cEndScene.cpp`.

![find-and-replace][find-and-replace.png]

Maka sekarang kita sudah punya satu scene `cEndScene` yang isinya sama persis dengan `cMenuScene`. Sekarang kita akan membuat jika waktu telah berlalu 5 detik berlalu di `cLevel1Scene`, maka akan otomatis berpindah ke `cEndScene`.

Kita sudah tahu bahwa di `cLevel1Scene`, ada satu alien yang menghilang setelah 5 detik. Potongan kodingannya dapat dicari di `cLevel1Scene.cpp`.

```cpp
...
float countDown = 5;

void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);
	
	countDown -= tpf;
	if (countDown <= 0) {
		removeGameObject(player);
	}
}
...
```

Mari kita mengganti `removeGameObject(player)` dengan kodingan `UpdateScene`. Jangan lupa untuk include `cEndScene` kita agar dapat membuat object `cEndScene` baru.

```cpp
...
#include "cEndScene.h"
...
float countDown = 5;

void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);
	
	countDown -= tpf;
	if (countDown <= 0) {
		cGame::getInstance().UpdateScene(new cEndScene());
	}
}
...
```

Maka jika dijalankan, kita sudah bisa berpindah ke `cEndScene` setelah 5 detik berada di `cLevel1Scene`. Namun masalahnya adalah scene ini kontennya sama persis dengan `cMenuScene` sehingga membingungkan. Agar menghilangkan kebingungan ini mari kita mengubah tampilannya sedikit menjadi tanpa background image dan tulisan `Press Any Key To Continue` diganti menjadi `End Scene`.

```cpp
...
void cEndScene::Render()
{
	renderBitmapString(300, 300, 9, GLUT_BITMAP_HELVETICA_18, "End Scene", 1, 0, 0);

	// glEnable(GL_TEXTURE_2D);
	// glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().background->Texture());
	// glBegin(GL_QUADS);

	// glTexCoord2f(0, 1);	glVertex3i(0, 0, 49);
	// glTexCoord2f(1, 1);	glVertex3i(GAME_WIDTH, 0, 49);
	// glTexCoord2f(1, 0);	glVertex3i(GAME_WIDTH, GAME_HEIGHT, 49);
	// glTexCoord2f(0, 0);	glVertex3i(0, GAME_HEIGHT, 49);
	// glEnd();
	// glDisable(GL_TEXTURE_2D);
}
...
```

Maka sekarang sudah terlihat bedanya dengan jelas.

Seperti biasa, untuk kodingan mana saja yang berubah dapat dilihat di folder Modified File. File yang tidak ada di folder tersebut berarti tidak berubah dari framework awal.

[new-file.png]: https://i.ibb.co/TYD8Nbv/image.png
[find-and-replace.png]: https://i.ibb.co/m62Z21T/image.png
