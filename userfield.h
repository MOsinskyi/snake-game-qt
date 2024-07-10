#ifndef USERFIELD_H
#define USERFIELD_H

#include <QWidget>
#include <QPainter>

class UserField : public QWidget
{
public:
    UserField();

public slots:
    void changePauseText(QString pauseStatus);
    void changeScoreText(QString newScore);

private:
    // User field size
    enum Size
    {
        Width = 300,
        Heigth = 24
    };

    QString scoreText;
    QString pauseStatusText;

    void paintEvent(QPaintEvent *event) override;

};

#endif // USERFIELD_H
