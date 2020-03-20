### GLUT Image

Untuk me-_render_ gambar dalam GLUT akan ada beberapa _step_ yang akan dibahas di bawah.

1. __Load Gambar__
	Pertama-tama kita harus melakukan _load_ gambar dari file menjadi object _image_ yang dapat dipakai langsung oleh GLUT. Proses load akan menggunakan library baru yang namanya _corona_ sehingga di header akan ditambahkan include baru.
	```cpp
	#include <corona.h>
	```
	
	Selain itu karena akan terjadi error karena _unresolved external symbol_ kita harus menambahkan `pragma comment` sebelum `include` sehingga headernya akan terlihat seperti ini.
	```cpp
	#pragma comment(lib, "corona")

	#include <stdio.h>
	#include <GL\glut.h>
	#include <corona.h>
	```
	
	Dalam load gambar, GLUT juga membutuhkan sebuah variable penampung untuk menandakan dimana gambar yang diload direferensikan. Karena dalam proses load gambar biasanya kita tidak hanya meload satu gambar saja namun lebih dari satu. Oleh karena itu kita akan membuat array yang berisi variable penampungnya.
	```cpp
	GLuint identifiers[10];
	```
	
	Setelah itu mari membuat function yang akan berfungsi untuk melakukan proses load gambar ini.
	```cpp
	bool LoadTexture(int index, char *fileName) {
		corona::Image *img = corona::OpenImage(fileName);
		if (!img) return false;

		img = ConvertImage(img, corona::PF_R8G8B8A8);

		glGenTextures(1, &identifiers[index]);

		glBindTexture(GL_TEXTURE_2D, identifiers[index]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img->getPixels());

		return true;
	}
	```
	
	Fungsi di atas akan me-_load_ gambar dengan path `fileName` dan akan direferensikan di `indentifiers[index]`. Jika image ada dan dapat di-_load_ maka functionnya akan mengembalikan nilai _true_ dan jika gagal akan mengembalikan _false_.
	
	Mari kita mencoba _load image_ dengan `background.png` yang ada di _repository_ ini. 
	![background.png](https://i.ibb.co/2FWf15j/background.png)
	Download gambarnya dan letakkan sejajar dengan kodingan `Main.cpp` yang akan mencoba load gambar ini. Lalu tambahkan kodingan seperti di bawah ini.
	```cpp
	int main(int argc, char **argv) {
		...
		LoadTexture(0, "background.png");
		...
	}
	```
	Ini akan membuat program kita untuk mencoba load image `background.png` dan menampungnya di variable `identifiers[0]` karena kita memberi index 0 ketika memanggil `LoadTexture`. Namun kita belum tahu apakah sukses diload atau gagal. Maka kita tambahkan sedikit validasi.
	```cpp
	int main(int argc, char **argv) {
		...
		if (!LoadTexture(0, "background.png")) printf("Some images may be missing\n");
		...
	}
	```
	Sehingga jika ternyata gambar `background.png` tidak ditemukan atau tidak dapat diload maka kita akan tahu.
	
	Karena nantinya kita akan mencoba load lebih dari satu gambar maka ada baiknya kita pindahkan pemanggilan `LoadTexture` ke dalam function sendiri agar lebih rapi.
	```cpp
	bool LoadAllImage() {
		if (!LoadTexture(0, "background.png")) return false;
		return true;
	}
	
	int main(int argc, char **argv) {
		...
		if (!LoadAllImage()) printf("Some images may be missing\n");
		...
	}
	```
2. __Render Gambar__
	Sebelum kita dapat render gambarnya ke dalam window, ada beberapa hal yang harus dilakukan terlebih dahulu yaitu reset projection matrix dan modelview matrix.
	```cpp
	int main(int argc, char **argv) {
		...
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 800, 0, 600, 3, -101);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		...
	}
	```
	Selain reset matrix, kita juga perlu function `glOrtho` yang berfungsi memproyeksikan kamera ke dalam dimensi pixel yang telah kita tentukan. glOrtho memerlukan 6 parameter yaitu `left`, `right`, `bottom`, `top`, `zNear`, `zFar` yang berisi batasan untuk setiap titk yang ada. Kita memberi `right` 800 dan `top` 600 karena dalam contoh ukuran window GLUT kita adalah 800x600. Ini dapat disesuaikan dengan ukuran window GLUT yang dibuat.
	
	Setelah ini maka kita dapat me-_render_ `background.png`	 kita. Ini dapat dilakukan dengan menambahkan kodingan seperti berikut ke `FunctionDisplay`.
	```cpp
	void FunctionDisplay() {
		...
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, identifiers[0]);

		glBegin(GL_QUADS);

		glTexCoord2f(0, 1); glVertex3i(0, 0, 100);
		glTexCoord2f(1, 1); glVertex3i(800, 0, 100);
		glTexCoord2f(1, 0); glVertex3i(800, 600, 100);
		glTexCoord2f(0, 0); glVertex3i(0, 600, 100);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		...
	}
	```
	Setiap kali menggambar dengan texture, kita harus memanggil `glEnable(GL_TEXTURE_2D)` untuk menandakan kita akan menggambar dari texture. Serta memanggil `glDisable(GL_TEXTURE_2D)` setelah selesai menggambar. Sedangkan `glBindTexture` akan melakukan `binding` dari texture yang akan kita gambar sehingga ketika kita menggambar, texture yang kita inginkanlah yang akan digambar. Dalam hal ini kita memberi `identifiers[0]` karena tadi kita melakukan `LoadTexture` ke dalam index ke-0.
	Untuk `glTexCoord2f` akan kita isi mulai dari mana kita mau menggambar texture kita. 
	![glTexCoord2f.png](https://i.ibb.co/ZMNPs4C/Screenshot-8.png)
	Sedangkan `glVertex3i` berisi di posisi mana di window GLUT kita akan digambar texturenya.
	![glVertex3i.png](https://i.ibb.co/PYW19kD/Screenshot-7.png)
	Untuk `glVertex3i`, parameter ketiga (100) adalah kedalaman dari gambarnya. Pada sebelumnya kita tidak pernah menggunakan kedalaman dalam menggambar, namun karena pada nantinya kita akan menggambar banyak image, maka ada kemungkinan image-image kita akan bertabrakan dan OpenGL tidak tahu yang mana yang ada di depan, sehingga terjadi yang namanya [Z-fighting](https://en.wikipedia.org/wiki/Z-fighting). Untuk menghindarinya maka kita berikan kedalaman untuk gambar. Di sini semakin kecil Z maka gambar akan semakin di depan.
	
	Setelah menambahkan kodingan tersebut maka ketika dicoba jalankan akan ter-_load_ gambar `background.png` kita di window GLUT nya.
	
	
3. __Rendering Spritesheet__
	Berbeda dengan image biasa, spritesheet akan lebih susah di-_render_ karena kita tidak me-_render_ satu image semua melainkan sepotong-sepotong.
	![spritesheet.png](https://i.ibb.co/zXZxJ90/spritesheet.png)
	Sekarang mari kita mencoba melakukan rendering spritesheet ini. Disini kita harus membuat satu class baru yang secara garis besarnya akan menampung batasan koordinat dari setiap animasi karakter dalam spritesheet.
	```cpp
	class SpritePlayer {
	public:
		double x0, x1, y0, y1;
		SpritePlayer(double x0, double x1, double y0, double y1) {
			this->x0 = x0;
			this->x1 = x1;
			this->y0 = y0;
			this->y1 = y1;
		}
	};
	```
	Karena satu object `SpritePlayer` hanya akan menampung koordinat dari satu gambar dari banyak gambar yang ada di spritesheet, maka sebaiknya kita membuat vector dari `SpritePlayer` saja.
	```cpp
	std::vector<SpritePlayer*> *spritesheet = new std::vector<SpritePlayer*>;
	```
	Dan jangan lupa untuk meng-_include_ vector.
	```cpp
	#include <vector>
	```
	
	Maka sekarang kita siap untuk melakukan load `spritesheet.png` kita. Cara load masih sama seperti ketika melakukan load `background.png` yaitu dengan memanggil function `LoadTexture`.
	```cpp
	bool LoadAllImage() {
		...
		if (!LoadTexture(1, "spritesheet.png")) return false;
		...
	}
	```
	Hanya saja karena kita harus memotong spritesheetnya dan menyimpan koordinat setiap potongan di dalam vector yang telah kita buat tadi. Disini kita harus tahu berapa ukuran spritesheet kita yaitu memiliki 4 karakter ke kanan dan 4 ke bawah, maka kita akan membaginya menjadi 4x4.
	```cpp
	bool LoadAllImage() {
		...
		if (!LoadTexture(1, "spritesheet.png")) return false;
		
		int size_x = 4, size_y = 4;
		for (int i = 0; i < size_y; i++) {
			for (int j = 0; j < size_x; j++) {
				double x0 = (double) j / size_x;
				double x1 = (double)(j + 1) / size_x;
				double y0 = (double)i / size_y;
				double y1 = (double)(i + 1) / size_y;
				spritesheet->push_back(new SpritePlayer(x0, x1, y0, y1));
			}
		}
		...
	}
	```
	Sampai di sini kita sudah membagi menjadi 16 potongan dan masing-masing karakter telah disimpan koordinatnya. Maka sekaranng kita akan mencoba melakukan rendering nya.
	```cpp
	void DrawPlayer() {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, identifiers[1]);

		glBegin(GL_QUADS);

		SpritePlayer *player = spritesheet->at(0);
		glTexCoord2f(player->x0, player->y1); glVertex3i(100, 100, 50);
		glTexCoord2f(player->x1, player->y1); glVertex3i(150, 100, 50);
		glTexCoord2f(player->x1, player->y0); glVertex3i(150, 150, 50);
		glTexCoord2f(player->x0, player->y0); glVertex3i(100, 150, 50);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	```
	Di sini karena kita belum sampai ke tahap animasi, maka kita cukup mencoba mengambil salah satu gambar saja yaitu gambar di index ke-0. Kita menggambarnya dengan ukuran 50x50 dan tidak _full screen_. Serta untuk `z` nya kita beri 50 agar dia lebih depan daripada texture `background.png` yang ada di `z=100`. 
	
Untuk potongan kodingan lengkapnya dapat dilihat di file Main.cpp yang ada di _repository_ ini.