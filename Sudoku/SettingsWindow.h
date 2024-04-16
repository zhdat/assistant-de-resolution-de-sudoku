#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
class SettingsWindow;
}

/**
 * @brief The SettingsWindow class represents the settings window of the application.
 * It allows the user to change the music and sound effect volume, as well as the difficulty level.
 */
class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for SettingsWindow.
     * @param parent The parent widget (default is nullptr).
     */
    explicit SettingsWindow(QWidget *parent = nullptr);
    /**
     * @brief Destructor for SettingsWindow.
     */
    ~SettingsWindow();
    /**
     * @brief Sets the music volume.
     */
    void setMusicVolume(int volume);
    /**
     * @brief Sets the sound effect volume.
     */
    void setSoundEffectVolume(int volume);
    /**
     * @brief Sets the difficulty level.
     */
    void setDifficulty(int difficultyIndex);

private slots:
    /**
     * @brief Slot for handling the return home button click event.
     */
    void returnHome();
    /**
     * @brief Slot for handling the music volume slider value change event.
     */
    void changeMusicLabel();
    /**
     * @brief Slot for handling the sound effect volume slider value change event.
     */
    void changeSoundEffectLabel();
    /**
     * @brief Slot for handling the difficulty level combo box value change event.
     */
    void difficultyChanged();

private:
    Ui::SettingsWindow *ui; /**< The UI object for the settings window. */
    /**
     * @brief Sets the font for the application.
     */
    void setFont();

};

#endif // SETTINGSWINDOW_H
