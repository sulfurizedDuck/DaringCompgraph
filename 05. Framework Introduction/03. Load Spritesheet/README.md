### Load Spritesheet Dengan Framework

Load spritesheet pada dasarnya sama dengan load image, namun karena spritesheet biasanya berisi tentang karakter dan karakter biasanya memiliki action yang lebih kompleks daripada background yang cukup dirender doang, maka untuk load spritesheet lebih berat daripada load image biasa. Pada materi kali ini kita akan membahas tentang load spritesheet. Kita akan  menggunakan spritesheet di bawah ini.

![spritesheet.png][spritesheet]

Karena pada framework belum ada spritesheet ini, silakan download dan dipindahkan ke folder `Textures/Spritesheets/` dan beri nama `spritesheet_person.png`.

Selanjutnya mari buka file `cAssetManager.h` untuk menambahkan index texture dari spritesheet kita.
```cpp
...
//Image identifiers
#define SPRITESHEET_PLAYERS	1
#define SPRITE_COLORED_GRASS	2
#define SPRITESHEET_PERSON	3
...
```

Setelah itu, karena bentuknya spritesheet, maka kita akan memerlukan vector untuk menampung data dari spritesheetnya.
```cpp
std::vector<cSprite*> *person = new std::vector<cSprite*>;
```

Sekarang kita akan ke file `cAssetManager.cpp` untuk melakukan load spritesheet_person kita.
```cpp
bool cAssetManager::Load() {
	...
	int size_x, size_y;
	res = LoadImage(SPRITESHEET_PERSON, "Textures/Spritesheets/spritesheet_person.png", GL_RGBA);
	if (!res) return false;
	size_x = 4;
	size_y = 4;
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			double x0, x1, y0, y1;
			x0 = (double) i / size_x;
			x1 = (double) (i + 1) / size_x;
			y0 = (double) j / size_y;
			y1 = (double) (j + 1) / size_y;
			person->push_back(new cSprite(GetID(SPRITESHEET_PERSON), x0, y0, x1, y1));
		}
	}
	...
}
```

Sekarang mari kita melihat bagaimana framework merender spritesheet pada `cLevel1Scene` seperti pada di bawah.
![cLevel1Scene.png][c-level1-scene]

__cLevel1Scene.h__
```cpp
...
class cLevel1Scene:public cScene
{
public:
...
	cPlayer *player;
	cPlayer *player1;
	cPlayer *player2;
	cPlayer *player3;
	...
```
__cLevel1Scene.cpp__
```cpp
void cLevel1Scene::Init()
{
	player = new cPlayer(cAssetManager::getInstance().player, 100, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player);

	player1 = new cPlayer(cAssetManager::getInstance().player, 200, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player1);

	player2 = new cPlayer(cAssetManager::getInstance().player, 300, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player2);

	player3 = new cPlayer(cAssetManager::getInstance().player, 400, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player3);
}
```

Di sini terlihat bahwa ada satu class `cPlayer` yang digunakan untuk menampung semua tentang sprite alien. Dan jika kita membuka file `cPlayer.h` dan `cPlayer.cpp`, kita dapat menarik kesimpulan bahwa mulai dari rendering aliennya, animasi, yang mengatur gerak gerik alien dari mouse dan keyboard ada di sini.

Maka untuk merender `spritesheet_person` kita, mari menggunakan teknik yang sama dengan `cPlayer`. Kita akan membuat class sendiri yang bernama `cPerson`, dan dengan ini kita akan membuat dua file baru yaitu `cPerson.h` dan `cPerson.cpp`.

Cara membuat file baru dapat dilakukan di __Solution Explorer__  bagian __Header Files__ untuk file `*.h` dan __Source Files__ untuk file `*.cpp`.

![add new file.png][add-new-class]

Atau untuk cara mudahnya dengan menggunakan shortcut __Ctrl+Shift+A__.


![add new file2.png][add-cperson-header]

Setelah membuat file baru untuk `cPerson.h` dan `cPerson.cpp`, untuk isinya dapat langsung di copy-paste dari `cPlayer`, dimana isi dari `cPerson.h` di copas dari `cPlayer.h` dan isi dari `cPerson.cpp` di copas dari `cPlayer.cpp`.

Lalu kita tinggal mengganti saja semua nama yang awalnya `cPlayer` menjadi `cPerson` dengan menggunakan fitur _Find and Replace_ yang dapat diakses dengan shortcut __Ctrl+H__.

![find and replace.png][find-and-replace-1]

Sekarang kita kembali ke file `cLevel1Scene.h` dan tambahkan deklarasi object cPerson dengan sehingga kodingan akan menjadi seperti ini.
```cpp
...
#include "Globals.h"
#include "cScene.h"
#include "cPlayer.h"
#include "cRect.h"
#include "cPerson.h"
...
class cLevel1Scene:public cScene
{
public:
	...
	cPerson *person;
	...
```

Setelah itu kita ke file `cLevel1Scene.cpp` dan tambahkan `person` kita sebagai game object dari `cLevel1Scene`.
```cpp
...
void cLevel1Scene::Init()
{
	...
	person = new cPerson(cAssetManager::getInstance().person, 100, 100, 2 * TILE_SIZE, 2 * TILE_SIZE);
	addGameObject(person);
}
...
```

Setelah itu maka ketika kita jalankan projectnya akan muncul person kita.

![cLevel1Scene.png][c-level1-scene-done]

Untuk adanya background putih di sekeliling orangnya diabaikan saja karena dari assetnya memang ada background.

Selanjutnya jika kita mencoba menekan arrow kiri dan kanan, maka dapat dilihat person kita juga bergerak layaknya empat alien lainnya. Person kita juga memiliki animasi aneh. Ini karena kita melakukan copy paste dari class `cPlayer` nya alien, maka segala control mouse dan keyboard dari alien juga didapat oleh `cPerson` kita. Untuk menghilangkannya dapat ke file `cPerson.cpp` dan menghapus kodingan yang ada di `cPerson::Update`.

```cpp
void cPerson::Update(float tpf /*= 0.0333*/)
{
	
}
```

Setelah mengosongkan function `cPerson::Update`, maka person kita tidak lagi mengikuti gerak alien.

Untuk kodingan mana saja yang berubah dapat dilihat di folder `Modified File`. File yang tidak ada di folder tersebut berarti tidak berubah dari framework awal.

[spritesheet]: https://i.ibb.co/zXZxJ90/spritesheet.png
[c-level1-scene]: https://i.ibb.co/X7tB5dj/clevel1.png
[add-new-class]: https://i.ibb.co/FwK3ZPM/image.png
[add-cperson-header]: https://i.ibb.co/yy644C1/image.png
[find-and-replace-1]: https://i.ibb.co/S6jr8rL/image.png
[c-level1-scene-done]: https://i.ibb.co/SQ0BFmv/image.png