#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <Headers/gamefield.h>
#include <Headers/userfield.h>

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);

private:
    // Main window size
    enum Size
    {
        Width = 320,
        Height = 344
    };

    GameField *gameField;
    UserField *userField;

    QGridLayout *layout;
    QWidget *centralWidget;
};
#endif // GAMEWINDOW_H
