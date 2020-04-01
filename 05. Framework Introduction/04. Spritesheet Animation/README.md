### Spritesheet Animation

Pada materi sebelumnya kita telah membahas tentang cara memasukkan spritesheet ke dalam framework kita. Sekarang kita akan membahas tentang animasi pada spritesheet. Dari sisi kodingan, kita akan melanjutkan dari hasil materi sebelumnya yang telah menggunakan `spritesheet_person`.

Untuk cara animasi berjalan, maka kita mengintip sedikit dari `cPlayer.cpp`. Pada function `Init`, kita dapat mengetahui bahwa kita akan membuat object `cAnimControl` yang mendefinisikan ada jenis animasi apa saja dan dimulai dan diakhiri di index ke berapa.

```cpp
void cPlayer::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_forward", 0, 1, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_backward", 5, 6, 0.2f);
	animControl->AddAnim("NoLoop", "jump", 2, 2, 0.2f);
	animControl->AddAnim("NoLoop", "idle", 4, 4, 0.2f);
}
```

Di sini ada empat animasi dasar untuk `cPlayer`, yaitu 
- `walk_forward`, yang dimulai dari spritesheet index 0 dan diakhiri index 1.
- `walk_backward`, yang dimulai dari spritesheet index 5 dan diakhiri index 6.
- `jump`, yang dimulai dari spritesheet index 2 dan diakhiri index 2.
- `idle`, yang dimulai dari spritesheet index 4 dan diakhiri index 4.

Urutan hasil potongan setiap sprite tergantung dari cara slicing ketika kita melakukan _load texture_ spritesheet nya ke project. Ini dapat dilihat di `cAssetManager.cpp` function `cAssetManager::Load()`. Jika dilihat dari pattern looping nya, kita dapat simpulkan setiap sprite disimpan dengan urutan dari atas ke bawah (vertikal) lalu maka ke kanan.

![labeled-spritesheet-player][labeled-spritesheet-player]

Sprite yang kita load `spritesheet_person` yang kita load disimpan dengan cara sama juga.

![labeled-spritesheet-person][labeled-spritesheet-person]

Namun ini akan menyebabkan kesulitan karena animasi kita lebih cocok dari kiri ke kanan lalu ke bawah, sehingga kita akan mengubah urutannya terlebih dahulu di `cAssetManager.cpp` bagian load `SPRITESHEET_PERSON` kita menjadi seperti di bawah.

```cpp
bool cAssetManager::Load()
{
	...
	int size_x, size_y;
	res = LoadImage(SPRITESHEET_PERSON, "Textures/Spritesheets/spritesheet_person.png", GL_RGBA);
	if (!res) return false;
	size_x = 4;
	size_y = 4;
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			double x0, x1, y0, y1;
			x0 = (double) j / size_x;
			x1 = (double) (j + 1) / size_x;
			y0 = (double) i / size_y;
			y1 = (double) (i + 1) / size_y;
			person->push_back(new cSprite(GetID(SPRITESHEET_PERSON), x0, y0, x1, y1));
		}
	}

	return true;
}
```

Maka urutannya akan seperti di bawah.

![labeled-spritesheet-person-new][labeled-spritesheet-person-new]

Sekarang kita akan membuat object `cAnimControl` untuk mendefinisikan list animasi yang dapat dilakukan oleh `cPerson` kita. Buka file `cPerson.cpp` dan mengisi kodingan berikut di function `Init`.

```cpp
void cPerson::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_south", 0, 3, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_north", 4, 7, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_west", 8, 11, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_east", 12, 15, 0.2f);
	animControl->AddAnim("NoLoop", "idle", 0, 0, 0.2f);
}
```

Pada `cAnimControl` terdapat dua jenis loop yang dapat digunakan yaitu `StraightLoop` dan `NoLoop`, dimana `StraightLoop` akan melakukan looping animasi dari index awal lagi jika index animasi telah sampai ke akhir. Sedangkan `NoLoop` melakukan animasi sekali putaran saja; jika sudah sampai index akhir maka sprite akan diam di index akhir saja.

Untuk mencoba maka mari kita tambahkan kodingan berikut pada function `Update`.

```cpp
void cPerson::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);

	if (keys['w'] || keys['W']) {
		if (animControl->ActiveName() != "walk_north")
			animControl->SetActiveAnim("walk_north");
	} 
	else if (keys['a'] || keys['A']) {
		if (animControl->ActiveName() != "walk_west")
			animControl->SetActiveAnim("walk_west");
	}
	else if (keys['s'] || keys['S']) {
		if (animControl->ActiveName() != "walk_south")
			animControl->SetActiveAnim("walk_south");
	}
	else if (keys['d'] || keys['D']) {
		if (animControl->ActiveName() != "walk_east")
			animControl->SetActiveAnim("walk_east");
	}
}
```

Setelah menambahkan ini, jika menjalankan project maka ketika kita menekan antara tombol `w`, `a`, `s`, atau `d` maka `cPerson` kita akan menjalankan animasi berjalan sesuai arah yang telah kita tentukan.

Sedikit penjelasan tentang kodingan:
- `animControl->UpdateAnim(tpf)` harus dipanggil untuk merealisasikan update animasi setiap tpf (time per frame). Konsep _time per frame_ ini akan dibahas di materi berikutnya.
- `animControl->ActiveName()` bertujuan untuk mengetahui animasi mana yang sedang berjalan sekarang.
- `animControl->SetActiveAnim(animationName);` bertujuan mengganti jenis animasi menjadi animasi lain sesuai nama yang telah kita berikan di function `Init`.

Namun, `cPerson` kita tetap menjalankan animasi yang sama meskipun kita telah melepas tombol. Jika kita ingin membuat menjadi diam ketika tidak ditekan apa-apa maka tambahkan sedikit kodingan lagi di function `Update`.

```cpp
void cPerson::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);

	if (keys['w'] || keys['W']) {
		if (animControl->ActiveName() != "walk_north")
			animControl->SetActiveAnim("walk_north");
	} 
	else if (keys['a'] || keys['A']) {
		if (animControl->ActiveName() != "walk_west")
			animControl->SetActiveAnim("walk_west");
	}
	else if (keys['s'] || keys['S']) {
		if (animControl->ActiveName() != "walk_south")
			animControl->SetActiveAnim("walk_south");
	}
	else if (keys['d'] || keys['D']) {
		if (animControl->ActiveName() != "walk_east")
			animControl->SetActiveAnim("walk_east");
	}
	else {
		if (animControl->ActiveName() != "idle")
			animControl->SetActiveAnim("idle");
	}
}
```

Jika sudah maka `cPerson` kita akan memiliki animasi yang sudah dapat berjalan.

Seperti biasa, untuk kodingan mana saja yang berubah dapat dilihat di folder Modified File. File yang tidak ada di folder tersebut berarti tidak berubah dari framework awal.

[labeled-spritesheet-player]: https://i.ibb.co/Yfk5dsm/spritesheet-players.png
[labeled-spritesheet-person]: https://i.ibb.co/tzRVf7f/spritesheet-person.png
[labeled-spritesheet-person-new]: https://i.ibb.co/25xsV8p/spritesheet-person-new.png