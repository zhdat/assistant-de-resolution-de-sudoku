#include "model/LeaderboardModel.h"
#include "Tools.h"

LeaderboardModel::LeaderboardModel()
{
}

void LeaderboardModel::updateLeaderboard(const QString& playerName, const QTime& playerTime, int playerDifficulty) {
    // Lire le leaderboard existant
    QString leaderboardFileName = QString("leaderboard_%1.txt").arg(playerDifficulty);
       Tools tool;
       QVector<QVector<QString>> leaderboard = tool.readTextLeaderboard(leaderboardFileName);

       // Ajouter les nouvelles données du joueur au leaderboard
       QVector<QString> newEntry;
       newEntry.append(playerName);
       newEntry.append(playerTime.toString());
       newEntry.append(QString::number(playerDifficulty));
       leaderboard.append(newEntry);

       // Trier le leaderboard par temps croissant
       std::sort(leaderboard.begin(), leaderboard.end(), [](const QVector<QString>& entry1, const QVector<QString>& entry2) {
           QTime time1 = QTime::fromString(entry1[1]);
           QTime time2 = QTime::fromString(entry2[1]);
           return time1 < time2;
       });

       // Ne conserver que les cinq premiers
       while (leaderboard.size() > 5) {
           leaderboard.pop_back();
       }

       // Écrire le nouveau leaderboard dans le fichier
       tool.writeTextLeaderboard(leaderboardFileName, leaderboard);
}
