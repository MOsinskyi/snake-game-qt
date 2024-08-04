#include "Headers/gameaudio.h"

GameAudio::GameAudio() {
    eatSound = new SoundAsset;
    deadSound = new SoundAsset;

    eatSound->getPlayer()->setAudioOutput(eatSound->getOutput());
    eatSound->getPlayer()->setSource(QUrl("qrc:/sounds/Sounds/eatSound.wav"));
    eatSound->getOutput()->setVolume(0.2);

    deadSound->getPlayer()->setAudioOutput(deadSound->getOutput());
    deadSound->getPlayer()->setSource(QUrl("qrc:/sounds/Sounds/deadSound.wav"));
    deadSound->getOutput()->setVolume(0.2);
}

SoundAsset::SoundAsset()
{
    player = new QMediaPlayer;
    output = new QAudioOutput;
}

void GameAudio::playEatSound()
{
    deadSound->getPlayer()->stop();
    eatSound->getPlayer()->play();
}

void GameAudio::playDeadSound()
{
    eatSound->getPlayer()->stop();
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




