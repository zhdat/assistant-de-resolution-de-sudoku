#include "PersonnalTimer.h"

PersonnalTimer::PersonnalTimer()
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);
    elapsedTime = QTime(0, 0, 0);
}

void PersonnalTimer::updateTime() {
    elapsedTime = elapsedTime.addSecs(1);
    emit timeChanged(elapsedTime);
}

void PersonnalTimer::resetTimer() {
    // Arrêtez le timer si actif
    if (timer->isActive()) {
        timer->stop();
    }

    // Réinitialisez le temps écoulé
    elapsedTime = QTime(0, 0, 0);

    // Émettez le signal indiquant que le temps a changé (0:0:0)
    emit timeChanged(elapsedTime);

    // Redémarrez le timer si nécessaire
    if (!timer->isActive()) {
        timer->start(1000);
    }
}

void PersonnalTimer::stopTimer() {
    // Arrêtez le timer si actif
    if (timer->isActive()) {
        timer->stop();
    }
}
