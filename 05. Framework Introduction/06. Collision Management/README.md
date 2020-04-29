### Collision

Pada materi kali ini kita akan membahas tentang cara kerja collision/tabrakan antar objek dan bagaimana mendeteksinya di framework ini. Konsep collision ini sangat sering kita pakai dalam pembuatan game, seperti ketika kita ingin mendeteksi apakah karakter kita sedang menginjak lantai (collide dengan lantai), atau mungkin tertembak peluru (collide dengan peluru).

Pada umumnya, jika kita melihat menggunakan mata kita maka kita dapat dengan mudah mengetahui apakah dua objek mengalami collision atau tidak. Namun program tidak dapat melihat dengan cara kita, sehingga kita harus menggunakan cara lain untuk membuat program kita 'mengenali' collision. Mari kita lihat konsepnya.

![collision][collision.png]

Dua objek dikatakan bertabrakan apabila terjadi _overlap_ pada kedua axis, yaitu axis x dan axis y. Lalu bagaimana kita mendeteksi adanya _overlap_ atau tidak? Mari kita melihat dari satu axis dulu saja, seperti axis y.

![overlap][overlap.png]

Untuk mengeceknya yaitu sisi __atas kotak pertama__ harus diatas sisi __bawah kotak kedua__ dan sisi __bawah kotak pertama__ harus diatas sisi __atas kotak kedua__, maka ini dapat disebut _overlap_ pada _axis y_.

Secara kodingan maka kita akan menulis seperti ini.
```cpp
if (obj1->y0 < obj2->y1 && obj1->y1 > obj2->y0) {
	// overlap y terjadi!
}
```

Hal yang sama juga berlaku pada _axis x_, yaitu jika sisi __kiri kotak pertama__ harus dikiri sisi __kanan kotak kedua__ dan sisi __kanan kotak pertama__ harus dikanan sisi __kiri kotak kedua__ maka dinyatakan terjadi _overlap_ pada _axis x_.

Secara kodingan maka kita akan menulis seperti ini.
```cpp
if (obj1->x0 < obj2->x1 && obj1->x1 > obj2->x0) {
	// overlap x terjadi!
}
```

Karena untuk dinyatakan terjadi collision harus terjadi _overlap_ untuk kedua axis, maka kita gabung saja keduanya.
```cpp
if (obj1->y0 < obj2->y1 && obj1->y1 > obj2->y0
	&& obj1->x0 < obj2->x1 && obj1->x1 > obj2->x0) {
	// collision terjadi!
}
```

Mari kita implementasikan pada kodingan. Kali ini kita akan mencoba membuat `cPerson` kita tabrakan dengan `cPlayer` yang telah ada di `cLevel1Scene`. Agar tidak terjadi hal yang tidak diinginkan, dari empat `cPlayer` yang ada mari kita buang tiga lainnya dulu.

__cLevel1Scene.cpp__
```cpp
...
void cLevel1Scene::Init()
{
	player = new cPlayer(cAssetManager::getInstance().player, 100, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player);

	person = new cPerson(cAssetManager::getInstance().person, 100, 100, 2 * TILE_SIZE, 2 * TILE_SIZE);
	addGameObject(person);
}
...
```

Dan karena pada materi `Scene Management` yang lalu ada berpindah scene secara otomatis ke `cEndScene`, mari kita matikan yang itu dahulu.

__cLevel1Scene.cpp__
```cpp
...
void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);
	
	countDown -= tpf;
	if (countDown <= 0) {
		// cGame::getInstance().UpdateScene(new cEndScene());
	}
}
...
```

Maka sekarang scene kita akan tampak seperti ini.

![scene][scene.png]

Tanpa kita lakukan apa-apa kita sudah tahu bahwa `cPlayer` dan `cPerson` telah mengalami collision. Mari kita buat satu function yang berfungsi mendeteksinya dahulu untuk membuktikan konsep yang kita bahas di atas tadi benar dapat berjalan atau tidak.

__cLevel1Scene.h__
```cpp
...
class cLevel1Scene:public cScene
{
public:
	...
	bool IsCollide(cGameObject *obj1, cGameObject *obj2);
	...
};

```

__cLevel1Scene.cpp__
```cpp
...
bool cLevel1Scene::IsCollide(cPerson *obj1, cPlayer *obj2)
{

	float obj1x0 = obj1->X();
	float obj1x1 = obj1->X() + obj1->Width();
	float obj1y0 = obj1->Y();
	float obj1y1 = obj1->Y() + obj1->Height();

	float obj2x0 = obj2->X();
	float obj2x1 = obj2->X() + obj2->Width();
	float obj2y0 = obj2->Y();
	float obj2y1 = obj2->Y() + obj2->Height();

	if (obj1y0 < obj2y1 && obj1y1 > obj2y0
		&& obj1x0 < obj2x1 && obj1x1 > obj2x0) 
	{
		return true;
	}
	return false;
}
```

Di sini, karena pada `cPlayer` dan `cPerson` hanya menyimpan `x0` dan `y0`, maka untuk `x1` dan `y1` harus dikalkulasikan manual dengan bantuan `width` dan `height` mereka.

Setelah `IsCollide` kita jadi, mari kita mencobanya.

__cLevel1Scene.cpp__
```cpp
...
void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	...
	if (IsCollide(person, player)) {
		printf("Collide when countdown: %.2f\n", countDown);
	}
}
...
```

Maka sekarang otomatis akan muncul hasil `printf` kita secara terus menerus. Ini menunjukkan bahwa telah terdeteksi dengan benar bahwa terjadi collision. Dan jika kita menggerakkan `cPlayer` dengan arrow atas/kiri/bawah/kanan dan mereka telah tidak terjadi collision, maka hasil `printf` juga tidak akan berjalan lagi.

Sekarang mari kita memindahkan `cPerson` kita ke koordinat (500, 100) agar tidak langsung terjadi collision pada saat masuk ke scene.

__cLevel1Scene.cpp__
```cpp
...
void cLevel1Scene::Init()
{
	player = new cPlayer(cAssetManager::getInstance().player, 100, 200, 2 * TILE_SIZE, 4 * TILE_SIZE);
	addGameObject(player);

	person = new cPerson(cAssetManager::getInstance().person, 500, 100, 2 * TILE_SIZE, 2 * TILE_SIZE);
	addGameObject(person);
}
...
```

Berikutnya kita mencoba sesuatu selain `printf`, yaitu jika terjadi collision, maka kita akan membuang `cPerson` kita dari scene. Caranya sebagai berikut.

__cLevel1Scene.cpp__
```cpp
...
void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	...
	if (IsCollide(person, player)) {
		// printf("Collide when countdown: %.2f\n", countDown);
		removeGameObject(person);
	}
}
...
```

Sekarang apabila kita menabrakkan `cPlayer` kita ke `cPerson`, maka `cPerson` akan hilang dari scene.

![collision][collision.gif]

Seperti biasa, untuk kodingan mana saja yang berubah dapat dilihat di folder Modified File. File yang tidak ada di folder tersebut berarti tidak berubah dari framework awal.

[collision.png]: https://learnopengl.com/img/in-practice/breakout/collisions_overlap.png
[overlap.png]: https://i.ibb.co/rFj40Kf/image.png
[scene.png]: https://i.ibb.co/xh8C6Yn/image.png
[collision.gif]: https://i.ibb.co/SR4CqrW/collision.gif