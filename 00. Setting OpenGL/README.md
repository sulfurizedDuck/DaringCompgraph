### Setting OpenGL di Windows dan Visual Studio 2015

Pada dasarnya Visual Studio 2015 tidak memiliki library OpenGL bawaan, sehingga kita harus menambahkan library OpenGL itu manual ke Visual Studio 2015. Jika PC Anda belum terinstall VS2015 dapat di download di [sini](vs2015-community-edition). Jika sudah terdownload maka silakan download juga library OpenGL di [sini](opengl-lib).

Setelah download librarynya maka extract dan kita akan menemukan tiga folder di dalam, yaitu `bin`, `include`, dan `lib`. Kita akan memindahkan ketiga folder ini ke library VS2015 yang terletak di `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC`.

1. Semua isi folder `bin` dicopy ke `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin`.
2. Semua isi folder `include` dicopy ke `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include`.
3. Semua isi folder `lib` dicopy ke `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib`.

Jika sudah dicopy semua, setiap project yang kita buat menggunakan VS2015 sudah dapat menggunakan library bawaan OpenGL dan GLUT. Mari mencoba buat satu project kosong baru dan cobalah memasukkan potongan code ini ke dalam satu file cpp.

```cpp
#include <stdio.h>
#include <GL/glut.h>

void display() {

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("OpenGL Program");
	glutDisplayFunc(display);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutMainLoop();

	return 0;
}
```

Lalu cobalah jalanin dengan menekan tombol `F5`. Jika project berjalan tanpa ada error maka itu menandakan VS2015 kita sudah dapat menggunakan library OpenGL.

[vs2015-community-edition]: https://www.kunal-chowdhury.com/2015/07/download-visualstudio-2015.html#topic2
[opengl-lib]: https://tinyurl.com/opengl-lib-vs