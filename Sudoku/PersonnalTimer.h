#ifndef PERSONNALTIMER_H
#define PERSONNALTIMER_H

#include <QTimer>
#include <QTime>
#include <QObject>

/**
 * @brief The PersonnalTimer class represents a timer.
 */
class PersonnalTimer : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Constructor for PersonnalTimer.
     * @param parent The parent widget (default is nullptr).
     */
    PersonnalTimer();

    /**
     * @brief Resets the timer.
     */
    void resetTimer();

    /**
     * @brief Stop the timer.
     */
    void stopTimer();

signals:
    /**
     * @brief Signal emitted when the time has changed.
     * @param time The new time.
     */
    void timeChanged(QTime);

private slots:
    /**
     * @brief Updates the time.
     */
    void updateTime();

private:
    QTimer *timer; /**< The timer object. */
    QTime elapsedTime; /**< The elapsed time. */
};

#endif // PERSONNALTIMER_H
