#ifndef TOOLS_H
#define TOOLS_H

#include <QVector>
#include <QString>
#include <QTime>
#include <QSoundEffect>
#include <QMediaPlayer>

enum Difficulty {
    EASY,
    MEDIUM,
    HARD,
    INSANE
};

/**
 * @brief The Tools class represents a set of tools.
 */
class Tools
{
private:
    QString _primaryColor; /**< The primary color of the current theme. */
    QString _accentColor; /**< The accent color of the current theme. */
    QString _complementaryColor; /**< The complementary color of the current theme. */
    QString _complementaryaccentColor; /**< The complementary accent color of the current theme. */
    QString _textColor; /**< The text color of the current theme. */
    QSoundEffect *_soundEffect; /**< The sound effect object. */
    QMediaPlayer *_music; /**< The music player object. */
    QMediaPlaylist *_playlist; /**< The playlist object. */

public:
    /**
     * @brief Constructor for Tools.
     */
    Tools();
    /**
     * @brief read a text file to get all sudoku grids of a difficulty.
     * @param fileName The name of the file.
     * @return The sudoku grids.
     */
    QVector<QString> readTextFile(const QString& fileName);
    /**
     * @brief Reads the theme from the file.
     * @return The theme.
     */
    QVector<QString> readTheme();
    /**
     * @brief Writes the data to a text file.
     * @param fileName The name of the file.
     * @param data The data to write.
     */
    void writeTextFile(const QString& fileName, const QVector<QString>& data);
    /**
     * @brief Writes the theme to the file.
     * @param data The theme data.
     */
    void writeTheme(const QVector<QString>& data);
    /**
     * @brief Reads the leaderboard from the file.
     * @return The leaderboard.
     */
    QVector<QVector<QString>> readTextLeaderboard(const QString& fileName);
    /**
     * @brief Reads the leaderboard.
     * @return The leaderboard.
     */
    QVector<QVector<QString>> readLeaderboard();
    /**
     * @brief Writes the leaderboard to the file.
     * @param fileName The name of the file.
     * @param data The data to write.
     */
    void writeTextLeaderboard(const QString& fileName, const QVector<QVector<QString>>& data);
    /**
     * @brief Writes the leaderboard.
     * @param leaderboard The leaderboard data.
     */
    void writeLeaderboard(const QVector<QVector<QString>>& leaderboard);
    /**
     * @brief apply default theme for all the annexe windows
     * @return The theme.
     */
    QString changeTheme();
    /**
     * @brief play a sound effect.
     * @param link The link of the sound effect.
     * @param volume The volume of the sound effect.
     */
    void playSound(QString link, int volume);
    /**
     * @brief play music.
     * @param link
     * @param volume
     */
    void playMusic(QString link, int volume);
    /**
     * @brief stop music.
     */
    void stopMusic();

    /**
     * @brief change the volume of the music.
     * @param volume
     */
    void changeVolume(int volume);

};

#endif // TOOLS_H
