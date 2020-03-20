### GLUT Basic Operation

Basic operation GLUT mencakup beberapa _event listener_ yang biasa digunakan yaitu listener untuk mouse dan keyboard.
1.  __Listener Mouse__
	Listener mouse akan berisi perintah apa saja yang harus dilakukan jika mouse diklik. Cara pakainya ada di bawah ini.
	``` cpp
	void FunctionMouse(int button, int state, int x, int y) {
		// apa yang terjadi jika mouse diklik akan diletakkan di sini.
	}

	int main(int argc, char **argv) {
		...
		glutMouseFunc(FunctionMouse);
		...
	}
	```
	Untuk parameter dalam function mouse ada empat dan fungsinya antara lain:
	- `int button` akan menampung informasi tentang mouse mana yang diklik. 0 untuk mouse kiri, 2 untuk mouse kanan, dan 1 untuk mouse tengah.
	- `int state` akan menampung informasi tentang keadaan klik apakah sedang ditekan atau dilepas. 0 kalau sedang ditekan dan 1 kalau sedang dilepas.
	- `int x` dan `int y` menampung koordinat mouse berada ketika mouse ditekan/dilepas.
	
	Untuk mencobanya dapat mengisi FunctionMouse seperti berikut
	```cpp
	void FunctionMouse(int button, int state, int x, int y) {
		// apa yang terjadi jika mouse diklik akan diletakkan di sini.
		printf("%d %d %d %d\n", button, state, x, y);
	}
	```
	Lalu silakan menjalankan project dan menekan mouse di area dalam window dan lihat hasilnya di console.

2. __Listener Keyboard__
	Listener keyboard akan berisi perintah apa saja yang harus dilakukan jika keyboard ditekan. 
	``` cpp
	void FunctionKeyboard(unsigned char key, int x, int y) {
		// apa yang terjadi jika keyboard ditekan akan diletakkan di sini.
	}

	int main(int argc, char **argv) {
		...
		glutKeyboardFunc(FunctionKeyboard);
		...
	}
	```
	Untuk parameter dalam function keyboard ada tiga dan fungsinya antara lain:
	- `unsigned char key` akan menampung informasi tentang key apa yang sedang ditekan.
	- `int x` dan `int y` menampung koordinat mouse berada ketika keyboard sedang ditekan.
	
	Untuk mencobanya dapat mengisi FunctionKeyboard seperti berikut
	```cpp
	void FunctionKeyboard(unsigned char key, int x, int y) {
		printf("%c %d %d\n", key, x, y);
	}
	```
	Lalu silakan menjalankan project dan menekan mouse di area dalam window dan lihat hasilnya di console.
	
	Namun jika dicoba untuk menekan key yang lebih special seperti arrow key maka console tidak akan print apa-apa karena event Keyboard tidak meng-_cover_ mereka. Maka keyboard special harus menggunakan listener yang akan dibahas di bawah.

3. __Listener Special Key__
	Untuk _special key_ akan menggunakan event listener yang berbeda dengan keyboard biasa.
	``` cpp
	void FunctionSpecialKeyboard(int key, int x, int y) {
		// apa yang terjadi jika special key ditekan akan diletakkan di sini.
	}

	int main(int argc, char **argv) {
		...
		glutSpecialFunc(FunctionSpecialKeyboard);
		...
	}
	```
	Untuk parameter dalam function keyboard ada tiga dan fungsinya antara lain:
	- `int key` akan menampung informasi tentang key apa yang sedang ditekan.
	- `int x` dan `int y` menampung koordinat mouse berada ketika keyboard sedang ditekan.
	
	Untuk mencobanya dapat mengisi FunctionMouse seperti berikut
	```cpp
	void FunctionSpecialKeyboard(int key, int x, int y) {
		printf("%d %d %d\n", key, x, y);
	}
	```
	Lalu silakan menjalankan project dan menekan mouse di area dalam window dan lihat hasilnya di console.
	Hasil dari key akan berupa angka dan angka itu adalah ASCII Code dari special key yang sedang ditekan.