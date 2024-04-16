#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

/**
 * @brief The LoginWindow class represents the login window of the application.
 * It handles user input for starting a new game, viewing leaderboards,
 * accessing settings, and quitting the application.
 */
class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for LoginWindow.
     * @param parent The parent widget (default is nullptr).
     */
    explicit LoginWindow(QWidget *parent = nullptr);
    /**
     * @brief Destructor for LoginWindow.
     */
    ~LoginWindow();
    /**
     * @brief Sets the font for the application.
     */
    void setFont();
    /**
     * @brief Sets the volume for the music.
     * @param volume The volume level to set.
     */
    void setMusicVolume(int volume);
    /**
     * @brief Sets the volume for the sound effects.
     * @param volume The volume level to set.
     */
    void setSoundEffectVolume(int volume);
    /**
     * @brief Sets the difficulty level.
     * @param difficultyIndex The index representing the difficulty level.
     */
    void setDifficulty(int difficultyIndex);


public slots:
    /**
     * @brief Slot for handling the play button click event.
     */
    void on_playButton_clicked();
    /**
     * @brief Slot for handling the quit button click event.
     */
    void difficultyChanged();
    /**
     * @brief Slot for handling the leaderboard button click event.
     */
    void on_leaderboardButton_clicked();
    /**
     * @brief Slot for handling the settings button click event.
     */
    void on_settingsButton_clicked();

private:
    Ui::LoginWindow *ui; /**< The user interface for the login window. */
    int _musicVolume; /**< The volume level for the music. */
    int _soundEffectVolume; /**< The volume level for the sound effects. */
};

#endif // LOGINWINDOW_H
