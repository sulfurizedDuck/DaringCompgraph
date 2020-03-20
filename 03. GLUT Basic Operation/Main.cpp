#include <stdio.h>
#include <GL\glut.h>

// variable global untuk menentukan titik mulai menggambar
double draw_x = -0.25;
double draw_y = -0.25;
// variable global untuk menentukan warna untuk menggambar
double r = 1.0;
double g = 0.5;
double b = 0.0;

void DrawRectangle(double x, double y) {
	double rectangleSize = 0.5;	// ukuran rectangle = 0.5

	glBegin(GL_QUADS);	// menetapkan GL_QUADS sebagai mode menggambar dari titik/vertex yang akan dilist di bawah

	glVertex2f(x, y);
	glVertex2f(x+rectangleSize, y);
	glVertex2f(x + rectangleSize, y + rectangleSize);
	glVertex2f(x, y + rectangleSize);

	glEnd();			// keluar dari mode gambar
}

void FunctionDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	// membersihkan sisa dari hasil gambar sebelumnya

	glColor3f(r, g, b);				// mengubah warna untuk penggambaran menjadi (1, 0.5, 0). Parameternya adalah (Red, Green, Blue) dan memiliki rentang antara 0 sampai 1.

	DrawRectangle(draw_x, draw_y);	// menggambar kotak dengan function yang telah dibuat di atas

	glutSwapBuffers();				// mengaplikasikan tampilan baru yang telah ditentukan di atas.
}

void FunctionMouse(int button, int state, int x, int y) {
	// apa yang terjadi jika mouse diklik akan diletakkan di sini.
	printf("%d %d %d %d\n", button, state, x, y);

	// mengubah warna RGB tergantung dari button yang diklik.
	if (button == 0) {
		r = 0.5;
		g = 1;
		b = 0.75;
	}

	glutPostRedisplay();	// untuk melakukan refresh display karena tanpa ini tampilan tidak berubah
}

void FunctionKeyboard(unsigned char key, int x, int y) {
	// apa yang terjadi jika keyboard ditekan akan diletakkan di sini.
	printf("%c %d %d\n", key, x, y);
}

void FunctionSpecialKeyboard(int key, int x, int y) {
	// apa yang terjadi jika special key ditekan akan diletakkan di sini.
	printf("%d %d %d\n", key, x, y);
}

int main(int argc, char **argv) {
	// inisialisasi GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);			// menginisialisasi mode display menjadi double buffer. Untuk referensi tentang buffer dapat dilihat di http://www.swiftless.com/tutorials/opengl/smooth_rotation.html
	glutInitWindowSize(800, 600);				// melakukan inisialisasi ukuran window 800x600
	glutCreateWindow("GLUT Event Listener");	// membuat window glut dengan title/nama `GLUT Event Listener`
	
	// Basic Function
	glutDisplayFunc(FunctionDisplay);			// mengaplikasikan FunctionDisplay sebagai callback untuk fungsi tampilan. Apa saja yang harus ditampilkan di window akan diletakkan di function ini.

	glutMouseFunc(FunctionMouse);				// mengaplikasikan FunctionMouse sebagai callback untuk menerima perintah dari mouse. Apa saja yang terjadi jika mouse di klik akan diletakkan di function ini.
	glutKeyboardFunc(FunctionKeyboard);			// mengaplikasikan FunctionKeyboard sebagai callback untuk menerima perintah dari keyboard. Apa saja yang terjadi jika keyboard ditekan akan diletakkan di function ini.
	glutSpecialFunc(FunctionSpecialKeyboard);	// mengaplikasikan FunctionSpecialKeyboard sebagai callback untuk menerima perintah dari keyboard. Apa saja yang terjadi jika special key ditekan akan diletakkan di function ini.
	
	glutMainLoop();								// berfungsi sebagai penahan window supaya window tidak berhenti. Segala kodingan yang ada di bawah glutMainLoop tidak akan berjalan.

	return 0;
}