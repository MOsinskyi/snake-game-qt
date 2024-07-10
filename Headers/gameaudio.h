#ifndef GAMEAUDIO_H
#define GAMEAUDIO_H

#include <QtMultimedia>

class SoundAsset{
public:
    SoundAsset();
    QMediaPlayer *getPlayer() const;
    QAudioOutput *getOutput() const;

private:
    QMediaPlayer *player;
    QAudioOutput *output;
};

class GameAudio
{
public:
    GameAudio();

    void playEatSound();
    void playDeadSound();
private:
    SoundAsset *eatSound;
    SoundAsset *deadSound;
};

#endif // GAMEAUDIO_H
