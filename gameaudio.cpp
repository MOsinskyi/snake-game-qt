#include "gameaudio.h"

GameAudio::GameAudio() {
    eatSound = new SoundAsset;
    deadSound = new SoundAsset;

    eatSound->getPlayer()->setAudioOutput(eatSound->getOutput());
    eatSound->getPlayer()->setSource(QUrl("qrc:/sounds/eatSound.wav"));
    eatSound->getOutput()->setVolume(0.2);

    deadSound->getPlayer()->setAudioOutput(deadSound->getOutput());
    deadSound->getPlayer()->setSource(QUrl("qrc:/sounds/deadSound.wav"));
    deadSound->getOutput()->setVolume(0.2);
}

SoundAsset::SoundAsset()
{
    player = new QMediaPlayer;
    output = new QAudioOutput;
}

void GameAudio::playEatSound()
{
    eatSound->getPlayer()->play();
}

void GameAudio::playDeadSound()
{
    deadSound->getPlayer()->play();
}

QMediaPlayer *SoundAsset::getPlayer() const
{
    return player;
}

QAudioOutput *SoundAsset::getOutput() const
{
    return output;
}




