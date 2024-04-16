#ifndef LEADERBOARDMODEL_H
#define LEADERBOARDMODEL_H

#include <QString>
#include <QTime>

class LeaderboardModel
{
public:
    /**
     * @brief Constructor for LeaderboardModel.
     */
    LeaderboardModel();
    /**
     * @brief Updates the leaderboard.
     * @param playerName The name of the player.
     * @param playerTime The time of the player.
     * @param playerDifficulty The difficulty of the game.
     */
    void updateLeaderboard(const QString& playerName, const QTime& playerTime, int playerDifficulty);
};

#endif // LEADERBOARDMODEL_H
