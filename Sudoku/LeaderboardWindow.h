#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QDialog>

namespace Ui {
class LeaderboardWindow;
}

/**
 * @brief The LeaderboardWindow class represents the leaderboard window of the application.
 * It displays the top 5 scores for each difficulty level.
 */
class LeaderboardWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for LeaderboardWindow.
     * @param parent The parent widget (default is nullptr).
     */
    explicit LeaderboardWindow(QWidget *parent = nullptr);
    /**
     * @brief Destructor for LeaderboardWindow.
     */
    ~LeaderboardWindow();
    /**
     * @brief Sets the difficulty level.
     * @param difficulty The difficulty level to set.
     */
    void setDifficulty(int difficulty);

private slots:
    /**
     * @brief Slot for handling the return home button click event.
     */
    void difficultyChanged();
    /**
     * @brief Slot for handling the return home button click event.
     */
    void returnHome();

private:
    Ui::LeaderboardWindow *ui; /**< The UI object for the leaderboard window. */
    int _difficulty; /**< The difficulty level. */

    /**
     * @brief Loads the leaderboard for the specified difficulty level.
     * @param difficulty The difficulty level.
     */
    void loadLeaderboard(int difficulty);
    /**
     * @brief Sets the font for the application.
     */
    void setFont();

};

#endif // LEADERBOARDWINDOW_H
