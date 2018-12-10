#include "CANIMAL.h"
#include "CGAME.h"
#include "console.h"

mutex mu;

void initBird(vector<string>& birdWav)
{
	std::string birdWav0 = "Harbor-seagulls.wav",
		birdWav1 = "Birds-chirping-sound-effect.wav",
		birdWav2 = "Blackbird-singing-in-the-garden.wav",
		birdWav3 = "House-sparrow-sounds.wav";

	birdWav.push_back(birdWav0);
	birdWav.push_back(birdWav1);
	birdWav.push_back(birdWav2);
	birdWav.push_back(birdWav3);
}

void initDino(vector<string>& dinoWav)
{
	std::string dinoWav0 = "Dinosaur-growl-1.wav",
		dinoWav1 = "Dinosaur-vocalisation-or-growl-1.wav",
		dinoWav2 = "Dinosaur-vocalisation-or-growl-1.wav";

	dinoWav.push_back(dinoWav0);
	dinoWav.push_back(dinoWav1);
	dinoWav.push_back(dinoWav2);
}

//---------------

void CANIMAL::Draw() { TextColor(14); }

void CANIMAL::Tell(vector<string>&) { }

void CANIMAL::move() { 
	if (mX < 88) {
		mX++;
	}
	else {
		mX = 30;
	}
}

void CANIMAL::clr() { TextColor(7); }

//---------------

CBIRD::CBIRD()
{
	mX = 30;
	mY = 10;
}

void CBIRD::Draw()
{
	mu.lock();
	gotoXY(mX, mY); cout << char(223) << char(254) << char(223);
	mu.unlock();
}

void CBIRD::Tell(vector<string>& birdWav)
{
	srand(time(NULL));
	random = rand() % 4 + 0;

	sound.setVolume(35.f);

	std::string wavPath = path + birdWav[random];

	if (!buffer.loadFromFile(wavPath))
		return; // error

	sound.setBuffer(buffer);
	sound.play();
}

void CBIRD::move()
{
	CANIMAL::move();
}

void CBIRD::clr()
{
	mu.lock();
	gotoXY(mX, mY); cout << "   ";
	mu.unlock();
}

//---------------

CDINOSAUR::CDINOSAUR()
{
	mX = 30;
	mY = 13;
}

void CDINOSAUR::Draw()
{
	mu.lock(); 
	gotoXY(mX, mY + 2); cout << (char)223 << " " << (char)223;
	gotoXY(mX, mY + 1); cout << (char)219 << (char)219 << (char)219;
	gotoXY(mX + 2, mY); cout << (char)220 << (char)220;
	mu.unlock();
}

void CDINOSAUR::Tell(vector<string>& dinoWav)
{
	srand(time(NULL));
	random = rand() % 3 + 0;

	sound.setVolume(50.f);

	std::string wavPath = path + dinoWav[random];

	if (!buffer.loadFromFile(wavPath))
		return; // error

	sound.setBuffer(buffer);
	sound.play();
}

void CDINOSAUR::move()
{
	CANIMAL::move();
}

void CDINOSAUR::clr()
{
	mu.lock();
	gotoXY(mX, mY + 2); cout << "   ";
	gotoXY(mX, mY + 1); cout << "   ";
	gotoXY(mX + 2, mY);	cout << "  ";
	mu.unlock();
}

//---------------