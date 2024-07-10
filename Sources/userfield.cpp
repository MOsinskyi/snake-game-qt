#include "Headers/userfield.h"
#include "Headers/fontmanager.h"

UserField::UserField()
{
    setFixedSize(Width, Heigth);

    scoreText = "Score: 0";
    pauseStatusText = "Pause - SPACE";
}

void UserField::changePauseText(QString pauseStatus)
{
    pauseStatusText = pauseStatus + " - SPACE";
    repaint();
}

void UserField::changeScoreText(QString newScore)
{
    scoreText = "Score: " + newScore;
    repaint();
}

void UserField::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter canvas;

    canvas.begin(this);

    const QRect user_field = QRect(0, 0, width() - 1, height() - 1);

    canvas.setFont(scoreTextFont);
    canvas.drawText(user_field, Qt::AlignLeft | Qt::AlignVCenter, scoreText);
    canvas.drawText(user_field, Qt::AlignRight | Qt::AlignVCenter, pauseStatusText);

    canvas.end();
}
