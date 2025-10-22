# include "PlayerAudio.h"
# include <iostream>
using namespace std;
PlayerAudio::PlayerAudio() {

	formataudio.registerBasicFormats();

}
PlayerAudio:: ~PlayerAudio() {}



void PlayerAudio::play() {
	transportSource.start(); // play
}
void PlayerAudio::pause() {
	transportSource.stop(); // pause 
}
void PlayerAudio::gotostart() {
	transportSource.setPosition(0.0);// go to start 
}
void PlayerAudio::end() {
	transportSource.setPosition(transportSource.getLengthInSeconds()); // it ends
}
