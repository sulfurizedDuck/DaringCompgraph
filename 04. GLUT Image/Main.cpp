#pragma comment(lib, "corona")

#include <stdio.h>
#include <vector>
#include <GL\glut.h>
#include <corona.h>

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
std::vector<SpritePlayer*> *spritesheet = new std::vector<SpritePlayer*>;

GLuint identifiers[10];

// function untuk menginisialisasi gambar yang dari file menjadi image yang dapat dipakai oleh OpenGL
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

// Function untuk menggambar player
void DrawPlayer() {
	glEnable(GL_TEXTURE_2D);
	// karena menggambar background kita menggunakan index 1
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

// Function untuk menggambar background
void DrawBackground() {
	glEnable(GL_TEXTURE_2D);
	// karena menggambar background kita menggunakan index 0
	glBindTexture(GL_TEXTURE_2D, identifiers[0]);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 1); glVertex3i(0, 0, 100);
	glTexCoord2f(1, 1); glVertex3i(800, 0, 100);
	glTexCoord2f(1, 0); glVertex3i(800, 600, 100);
	glTexCoord2f(0, 0); glVertex3i(0, 600, 100);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void FunctionDisplay() {
	DrawBackground();
	DrawPlayer();

	glutSwapBuffers();
}

bool LoadAllImage() {
	// index 0 = background
	if (!LoadTexture(0, "background.png")) return false;
	// index 1 = spritesheet
	if (!LoadTexture(1, "spritesheet.png")) return false;
	
	// inisialisasi size x dan y masing-masing 4 karena gambar memiliki 4x4 karakter.
	int size_x = 4, size_y = 4;
	// looping untuk setiap karakter, kita ambil koordinat dari masing-masing karakter untuk disimpan di vector spritesheet.
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			double x0 = (double) j / size_x;
			double x1 = (double)(j + 1) / size_x;
			double y0 = (double)i / size_y;
			double y1 = (double)(i + 1) / size_y;
			spritesheet->push_back(new SpritePlayer(x0, x1, y0, y1));
		}
	}

	return true;
}

int main(int argc, char **argv) {
	// inisialisasi GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);			// menginisialisasi mode display menjadi double buffer. Untuk referensi tentang buffer dapat dilihat di http://www.swiftless.com/tutorials/opengl/smooth_rotation.html
	glutInitWindowSize(800, 600);				// melakukan inisialisasi ukuran window 800x600
	glutCreateWindow("GLUT Event Listener");	// membuat window glut dengan title/nama `GLUT Event Listener`

	glutDisplayFunc(FunctionDisplay);			// mengaplikasikan FunctionDisplay sebagai callback untuk fungsi tampilan. Apa saja yang harus ditampilkan di window akan diletakkan di function ini.

	if (!LoadAllImage()) printf("Some images may be missing\n");

	// mereset matrix menjadi identity serta mengatur ortho camera agar menyesuaikan dengan ukuran window.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, 3, -101);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutMainLoop();

	return 0;
}