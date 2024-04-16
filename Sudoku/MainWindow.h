#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QTime>
#include "presenter/SudokuPresenter.h"
#include "model/SudokuModel.h"
#include "Tools.h"
#include "PersonnalTimer.h"

class SudokuGrid;


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class represents the main window of the Sudoku application.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor for MainWindow.
     * @param parent The parent widget (default is nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

    /**
     * @brief Sets the pseudo of the user.
     * @param pseudo The pseudo to set.
     */
    void setPseudo(QString pseudo);

    /**
     * @brief Sets the difficulty level.
     * @param difficultyIndex The index representing the difficulty level.
     */
    void setDifficulty(int difficultyIndex);

    /**
     * @brief Sets the volume for background music.
     * @param volume The volume level to set.
     */
    void setMusicVolume(int volume);

    /**
     * @brief Sets the volume for sound effects.
     * @param volume The volume level to set.
     */
    void setSoundEffectVolume(int volume);

    /**
     * @brief Initializes the view components.
     */
    void initializeView();

public slots:
    /**
     * @brief Changes the theme to a purple color scheme.
     */
    void changeToPurpleTheme();

    /**
     * @brief Changes the theme to a blue color scheme.
     */
    void changeToBlueTheme();

    /**
     * @brief Changes the theme to a dark color scheme.
     */
    void changeToDarkTheme();

    /**
     * @brief Slot called when the difficulty level is changed.
     */
    void difficultyChanged();

    /**
     * @brief Resets the game to its initial state.
     */
    void resetGame();

    /**
     * @brief Starts a new game with the current difficulty level.
     */
    void newGame();

    /**
     * @brief Slot called when the delete button is clicked.
     */
    void on_button_delete_clicked();

    /**
     * @brief Updates the elapsed time on the UI.
     * @param elapsedTime The elapsed time to display.
     */
    void updateTime(QTime elapsedTime);

    /**
     * @brief popup a window and play a sound when the player has won
     */
    void victory();

private:
    // Private member variables
    Ui::MainWindow *ui; /**< The UI object for MainWindow. */
    SudokuPresenter *_presenter; /**< The presenter object for Sudoku. */
    SudokuModel *_model; /**< The model object for Sudoku. */
    QVector<QVector<int>> _sudokuGrid; /**< The Sudoku grid data. */
    QVector<QVector<int>> _initialSudokuGrid; /**< The initial Sudoku grid data. */
    QPushButton *_buttons; /**< Pointer to QPushButton. */
    QPushButton *_lastClickedGridButton = nullptr; /**< Pointer to the last clicked grid button. */
    int _gridIndex; /**< The index of the current grid. */
    int _currentDifficultyIndex; /**< The index representing the current difficulty level. */
    int _musicVolume; /**< The volume level for background music. */
    int _soundEffectVolume; /**< The volume level for sound effects. */
    QString _primaryColor; /**< The primary color of the theme. */
    QString _accentColor; /**< The accent color of the theme. */
    QString _complementaryColor; /**< The complementary color of the theme. */
    QString _complementaryaccentColor; /**< The complementary accent color of the theme. */
    QString _textColor; /**< The text color of the theme. */
    QString _pseudo; /**< The pseudo of the user. */
    PersonnalTimer *timer; /**< The timer object for measuring elapsed time. */
    QTime _elapsedTime; /**< The elapsed time during gameplay. */
    Tools *tool; /**< The tools object for utility functions. */

    /**
     * @brief Calculates the possibilities for a given button.
     * @param button The button for which possibilities are calculated.
     * @return A set of possible numbers for the button.
     */
    QSet<int> calculatePossibilities(QPushButton *button);

    /**
     * @brief Displays the Sudoku grids based on current data.
     */
    void displaySudokuGrids();

    /**
     * @brief Connects buttons to appropriate slots.
     */
    void connectButtons();

    /**
     * @brief Connects solution buttons to appropriate slots.
     */
    void connectSolutionButtons();

    /**
     * @brief Sets up the progression bar for the game.
     */
    void setupProgressionBar();

    /**
     * @brief Updates the progression bar based on game progress.
     */
    void updateProgressionBar();

    /**
     * @brief Changes the theme colors according to specified parameters.
     * @param primaryColor The primary color of the theme.
     * @param accentColor The accent color of the theme.
     * @param complementaryColor The complementary color of the theme.
     * @param complementaryAccentColor The complementary accent color of the theme.
     * @param textColor The text color of the theme.
     */
    void changeToTheme(const QString &primaryColor, const QString &accentColor, const QString &complementaryColor,
                       const QString &complementaryAccentColor, const QString &textColor);

    /**
     * @brief Changes the theme according to the current settings.
     */
    void changeTheme();

    /**
     * @brief Displays the elapsed time on the UI.
     */
    void displayTime();

    /**
     * @brief Sets the theme attributes based on provided data.
     * @param data The vector containing theme attribute data.
     */
    void setThemeAttributes(const QVector <QString> &data);

    /**
     * @brief Updates the labels showing the remaining numbers.
     */
    void updateRemainingNumbersLabels();

    /**
     * @brief Handles key press events.
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief Handles key press events for entering numbers.
     * @param number The number pressed.
     */
    void handleKeyPress(int number);

    void applyCustomFontToAllElements();

private slots:

    /**
     * @brief Handles the click event of the Sudoku grid buttons.
     */
    void handleButtonClick();

    /**
     * @brief Handles the click event of the solution buttons.
     * @param number The number corresponding to the solution button clicked.
     */
    void handleSolutionButtonClick(int number);

    /**
     * @brief Handles the action triggered by changing difficulty level.
     */
    void handleDifficultyAction();

    /**
     * @brief Navigates back to the login menu.
     */
    void goToMenu();

    /**
     * @brief Handles the action triggered by the About option.
     */
    void handleAboutAction();

    /**
     * @brief Handles the action triggered by the Pause option.
     */
    void handlePauseAction();

    /**
     * @brief Handles the action triggered by the Resume option.
     */
    void handleResumeAction();

    void reduceMusicVolume();
    void increaseMusicVolume();
    void reduceSoundEffectVolume();
    void increaseSoundEffectVolume();


};
#endif // MAINWINDOW_H
