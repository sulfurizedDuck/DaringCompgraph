### Sound Management

Pada materi kali ini kita akan membahas tentang cara memanipulasi musik/suara pada framework kita. Pada framework sudah ada class `cSound`. Kita akan memanfaatkan class ini untuk menggunakan suara.

Mari kita membuka file `cSound.cpp`. Di function `Load` sudah ada satu musik di functionnya, yaitu musik `Sounds/03_-_Lode_Runner_-_NES_-_In-Game.ogg`. Untuk cara melakukan load musik lainnya dapat menggunakan cara pemanggilannya juga.

__cSound.cpp__
```cpp
...
bool cSound::Load()
{
	system->createStream("Sounds/03_-_Lode_Runner_-_NES_-_In-Game.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	//system->createStream("Sounds/ambient1.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	return true;
}
...
```

Pemanggilan `system->createStream()` berfungsi untuk melakukan load musik ke dalam framework kita. Parameter yang perlu diperhatikan adalah _path_ menuju file musik dan _identifier_ `sound_id` agar ketika kita ingin _play_ satu musik spesifik kita akan menggunakan `sound_id` untuk memberitahu framework. Untuk nilai `sound_id` di define di file `cSound.h`.

__cSound.h__
```cpp
...
//Sound array size
#define NUM_SOUNDS 15

//Sound identifiers
#define	SOUND_AMBIENT1      0
#define	SOUND_AMBIENT2      1
...
```

`NUM_SOUNDS` adalah size dari file musik kita. Jika kita memiliki 10 musik berbeda yang harus di load, maka `NUM_SOUNDS` nilainya minimal harus 10. Sedangkan untuk `SOUND_AMBIENT1` dan `SOUND_AMBIENT2` adalah indexnya. Setiap kita memiliki musik baru yang akan kita load, kita dapat melakukan `define` _sound identifier_ baru sebelum melanjutkannya dengan memanggil `system->createStream()` di `cSound.cpp`.

Secara default function `Load` di `cSound.cpp` tidak dipanggil di framework, maka jika kita ingin menggunakan musik maka kita harus memanggilnya manual. Mari kita meletakkannya di bawah function `Load` milik `cAssetManager` di file `cGame.cpp`.

__cGame.cpp__
```cpp
...
bool cGame::Init()
{
	...
	//Texture initialization
	if (!cAssetManager::getInstance().Load())printf("Some images may missing");
	
	// Sound initialization
	if (!cSound::getInstance().Load()) printf("Some sounds may missing");

	...
	return true;
}
...
```

Setelah itu maka kita sudah dapat play/pause/stop musik. Mari kita coba di `cMenuScene`, ketika memulai maka kita langsung memainkan musik tersebut.

__cMenuScene.cpp__
```cpp
...
void cMenuScene::Init()
{
	...
	cSound::getInstance().Play(SOUND_AMBIENT1);
}
...
```

Maka sekarang kita dapat mendengar musik kita berjalan. Namun jika kita berpindah scene dengan tombol enter, musik kita tidak berhenti. Mari kita membuatnya berhenti jika berpindah scene dengan function `StopAll`.

__cMenuScene.cpp__
```cpp
...
void cMenuScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	...
	if (key == 13) {
		cSound::getInstance().StopAll();
		cGame::getInstance().UpdateScene(new cLevel1Scene());
	}
}
...
```

Sekarang jika kita berpindah scene maka musik kita juga sudah berhenti.

Mari kita mencoba untuk melakukan _pause_ sound. Kita akan mencoba apabila menekan tombol `Esc`, maka `SOUND_AMBIENT1` kita akan di _pause_, sedangkan jika kita menekan tombol `Space`, maka `SOUND_AMBIENT1` kita akan di _resume_.

Jika kita melihat function `Play`, maka kita akan tahu bahwa `SOUND_AMBIENT1` dipasang pada _channel_ yang bernama `ambient1Channel`. Namun pembahasan tentang _channel_ kita abaikan dulu dan akan dibahas nantinya. Nah, untuk melakukan _pause_ dan _resume_, kita akan memanfaatkan _channel_ ini. Mari kita ubah kodingan di `cMenuScene.cpp` kita menjadi seperti di bawah ini.

__cMenuScene.cpp__
```cpp
...
void cMenuScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	...
	if (key == 13) {
		cSound::getInstance().StopAll();
		cGame::getInstance().UpdateScene(new cLevel1Scene());
	}
	else if (key == 27) {	// esc = 27
		cSound::getInstance().ambient1Channel->setPaused(true);
	}
	else if (key == 32) {	// spasi = 32
		cSound::getInstance().ambient1Channel->setPaused(false);
	}
}
...
```

Maka jika kita menekan tombol `Esc` ataupun `Space` kita sudah dapat melihat `SOUND_AMBIENT1` kita di _pause_ dan _resume_.

Mari kita melihat lebih dalam untuk function `Play` di `cSound.cpp`.

__cSound.cpp__
```cpp
...
void cSound::Play(int sound_id)
{
	if (sound_id == SOUND_AMBIENT1) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT1], false, &ambient1Channel);
		ambient1Channel->setVolume(0.25f); //between 0 and 1
	}
	else if (sound_id == SOUND_AMBIENT2) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT2], false, &ambient2Channel);
		ambient2Channel->setVolume(0.2f); //between 0 and 1
	}
	else system->playSound(FMOD_CHANNEL_FREE, sounds[sound_id], false, 0);
}
...
```

Di sini kita dapat melihat bahwa ketika memberikan `sound_id` kita bernilai `SOUND_AMBIENT1`, maka dia akan memanggil `system->playSound()` dan ada melakukan passing _channel_ yaitu `ambient1Channel`. Begitu juga untuk `SOUND_AMBIENT2` yang melakukan passing _channel_ `ambient2Channel`. Sedangkan untuk `sound_id` yang lain tidak menggunakan _channel_ (dipassing nilai `0` yang artinya `NULL` untuk channel). Maka muncul satu pertanyaan: apa bedanya? Dan kenapa dibedakan?

Untuk _channel_ sendiri sebenarnya tidak wajib untuk dipakai. Bahkan tanpa _channel_ kita sudah dapat melakukan _play_ musik kita. Namun, jika kita tidak memberikan _channel_, maka setelah melakukan _play_ musik, musik itu sudah tidak dapat kita kontrol lagi, seperti _pause_, _stop_, atau mengatur volume musik. Mari kita melihat function `StopAll`.

__cSound.cpp__
```cpp
...
void cSound::StopAll()
{
	ambient1Channel->stop();
	ambient2Channel->stop();
}
...
```

Untuk melakukan _stop_ musik harus dari _channel_. Nah, sebenarnya tidak semua musik harus kita kontrol. Contohnya, musik seperti _sfx_ ketika peluru kita bertabrakan dengan musuh, atau ketika _player_ kita menginjak bom, maka _sfx_ tersebut hanya berjalan sekali saja dan tidak perlu di _pause_ atau _stop_. Jenis _sound_ yang ini tidak perlu _channel_ karena selain menambah kerjaan, _channel_ juga menggunakan memori komputer sehingga jika terlalu banyak _channel_ berpotensi mengurangi performa game kita nantinya.

Mari kita mencoba melakukan _play_ sound tanpa menggunakan _channel_. Di `cLevel1Scene`, ketika `cPlayer` kita bertabrakan dengan `cPerson`, maka mari kita jalankan _sfx_ `Sounds/explosion.wav`.

__cSound.h__
```cpp
...
//Sound array size
#define NUM_SOUNDS 15

//Sound identifiers
#define	SOUND_AMBIENT1      0
#define	SOUND_AMBIENT2      1
#define SOUND_EXPLOSION		2
...
```

__cSound.cpp__
```cpp
...
bool cSound::Load()
{
	system->createStream("Sounds/03_-_Lode_Runner_-_NES_-_In-Game.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	system->createStream("Sounds/explosion.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_EXPLOSION]);
	//system->createStream("Sounds/ambient1.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	return true;
}
...
```

__cLevel1Scene.cpp__
```cpp
...
void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	...
	if (IsCollide(person, player)) {
		cSound::getInstance().Play(SOUND_EXPLOSION);
		removeGameObject(person);
	}
}
...
```

Agar suara explosion hanya berjalan sekali saja, maka mari kita ganti `FMOD_LOOP_NORMAL` menjadi `FMOD_LOOP_OFF` ketika di function `Load`.

__cSound.cpp__
```cpp
...
bool cSound::Load()
{
	system->createStream("Sounds/03_-_Lode_Runner_-_NES_-_In-Game.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	system->createStream("Sounds/explosion.wav", FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &sounds[SOUND_EXPLOSION]);
	//system->createStream("Sounds/ambient1.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	return true;
}
...
```

Maka sekarang kita sudah membuat _sfx_ yang tidak menggunakan _channel_.

Seperti biasa, untuk kodingan mana saja yang berubah dapat dilihat di folder Modified File. File yang tidak ada di folder tersebut berarti tidak berubah dari framework awal.