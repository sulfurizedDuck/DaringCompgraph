### Basic Introduction

Karena skala proyek di _TM Bawa Pulang_ dan _Project_ tidak kecil dan tidak efisien untuk dibuat dari nol, maka sudah ada _framework_ yang telah disiapkan dan dapat dipakai untuk mengerjakan proyek tersebut. Framework tersebut dapat di download dari [sini][framework-ko-kc].


#### Konfigurasi GLUT Window
Di framework semua kodingan untuk mengkonfigurasi window, size, position, telah ada. Secara default, nama window GLUT kita adalah `2DGame`.  Namanya dapat diganti di file `GLUTMain.cpp`. Cari potongan kodingan `glutCreateWindow` dan ubahlah _title_ nya sesuai dengan yang diinginkan.
```cpp
glutCreateWindow("2DGame");
```
Sedangkan untuk ukuran window ada di file `cGame.h`. Cari potongan kodingan berikut dan ubah sesuai dengan ukuran window yang diinginkan.
```cpp
#define GAME_WIDTH	800
#define GAME_HEIGHT	600
```

#### Scene
Jika biasanya kita menaruh kodingan display kita dalam satu function, di framework ini menggunakan `scene` dimana akan ada satu class scene yang sedang aktif dan akan digunakan oleh framework untuk dijalankan pada satu waktu. Secara default, project memiliki dua scene yaitu `cMenuScene` dan `cLevel1Scene`. Dan ketika pertama kali dijalankan, scene yang ditampilkan pertama adalah `cMenuScene` yang isinya text `Press Any Key To Continue`.

![cMenuScene.png][c-menu-scene]

Dan jika ditekan `Enter` maka akan berpindah scene ke `cLevel1Scene` yang isinya ada empat alien berjajar. Untuk berpindah scene, dapat menggunakan potongan kodingan yang dapat dilihat di `cMenuScene.cpp` pada function `ReadKeyboard`.
```cpp
void cMenuScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	...
	if (key == 13) {
		cGame::getInstance().UpdateScene(new cLevel1Scene());
	}
}
```
Dan dari sini kita bisa menyimpulkan bahwa cara mengganti scene dapat dengan memanggil function `cGame::getInstance().UpdateScene()` dan memasukkan scene apa yang ingin kita masukkan nanti.

#### Render Text
Untuk me-_render_ tulisan kita dapat mengintip kodingan yang ada di balik tulisan `Press Any Key To Continue` yang ada di `cMenuScene.cpp`.
```cpp
void cMenuScene::Render()
{
	renderBitmapString(300, 300, 9, GLUT_BITMAP_HELVETICA_18, "Press Any Key To Continue", 1, 0, 0);
}
```
Untuk parameter yang diperlukan untuk render dapat dilihat dibawah:
![renderBitmapString][render-bitmap-string]
- `float x`, `float y`, dan `float z` diisi dengan dimana kita ingin me-render text kita.
- `void *font` adalah jenis font yang digunakan untuk text. Untuk pilihan font ada beberapa yaitu:
	+ GLUT_BITMAP_9_BY_15
	+ GLUT_BITMAP_8_BY_13
	+ GLUT_BITMAP_TIMES_ROMAN_10
	+ GLUT_BITMAP_TIMES_ROMAN_24
	+ GLUT_BITMAP_HELVETICA_10
	+ GLUT_BITMAP_HELVETICA_12
	+ GLUT_BITMAP_HELVETICA_18
- `char *string` berisi text/tulisan yang ingin kita render.
- `float r`, `float g`, dan `float b` berisi warna RGB pada text dengan _range_ antara 0 dan 1.

[framework-ko-kc]: https://tinyurl.com/CompgraphSharedFrameworkUpgrad
[c-menu-scene]: https://i.ibb.co/f83nQZn/menuscene.png
[render-bitmap-string]: https://i.ibb.co/j6dL1Zj/Screenshot-9.png