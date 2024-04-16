#include "Tools.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QUrl>
#include <QMediaPlaylist>
#include <QMediaPlayer>

Tools::Tools()
{
    _soundEffect = new QSoundEffect();
    _music = new QMediaPlayer();
    _playlist = new QMediaPlaylist();
}

QVector<QString> Tools::readTextFile(const QString& fileName) {
    QVector<QString> values;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "opening file done !";
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            values.append(line);
        }
        file.close();
    }else{
        qDebug() << "ERROR: opening file";
    }
    return values;
}

QVector<QString> Tools::readTheme(){
    return readTextFile("Theme.txt");
}

void Tools::writeTextFile(const QString &fileName, const QVector<QString> &data)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "File opened for writing: " << fileName;
        QTextStream out(&file);
        for (const QString &value : data) {
            out << value << "\n";
        }
        file.close();
        qDebug() << "Writing to file done!";
    } else {
        qDebug() << "ERROR: Unable to open file for writing: " << fileName;
    }
}

void Tools::writeTheme(const QVector<QString>& data){
    writeTextFile("Theme.txt", data);
}


QVector<QVector<QString>> Tools::readTextLeaderboard(const QString& fileName) {
    QVector<QVector<QString>> leaderboardData;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Opening file done!";
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 3) {
                QVector<QString> entry;
                entry.append(parts[0]); // Name
                entry.append(parts[1]); // Time
                entry.append(parts[2]); // Score
                leaderboardData.append(entry);
            }
        }
        file.close();
    } else {
        qDebug() << "ERROR: Opening file";
    }
    return leaderboardData;
}

QVector<QVector<QString>> Tools::readLeaderboard(){
    return readTextLeaderboard("Leaderboard.txt");
}

void Tools::writeTextLeaderboard(const QString& fileName, const QVector<QVector<QString>>& data) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Opening file done!";
        QTextStream out(&file);
        for (const QVector<QString>& entry : data) {
            if (entry.size() == 3) {
                out << entry[0] << "," << entry[1] << "," << entry[2] << "\n";
            }
        }
        file.close();
    } else {
        qDebug() << "ERROR: Opening file";
    }
}

void Tools::writeLeaderboard(const QVector<QVector<QString>>& leaderboard){
    writeTextLeaderboard("Leaderboard.txt", leaderboard);
}

QString Tools::changeTheme(){

    QVector<QString> data = readTheme();
    if(!data.isEmpty()){
        if (data.size() >= 5) {
            _primaryColor = data[0];
            _accentColor = data[1];
            _complementaryColor = data[2];
            _complementaryaccentColor = data[3];
            _textColor = data[4];
        } else {
            qDebug() << "ERROR: Insufficient data provided to set theme attributes";
        }
    }else{
        _primaryColor = "#E4CCFF";
        _accentColor = "#D0A7FF";
        _complementaryColor = "#c2d7b2";
        _complementaryaccentColor = "#b3c9a4";
        _textColor = "black";
    }

    qDebug() << data;

    return QString("QWidget {background-color: %1;} * {color:%2}\n"
                   "QFrame {background-color: %3; border-radius:20px}\n"
                   "QPushButton {background-color: %1; border-radius:5px; padding-right:10px;padding-left:10px}\n"
                   "QPushButton:hover {background-color:green}\n"
                   "QLabel{background-color: transparent;}"
                   "QSlider{background-color:%3}"
                   "QSlider::groove:horizontal {border: 1px solid #CCCCCC;background: "
                   "#FFFFFF;height: 10px;border-radius: 5px;}"
                   "QSlider::handle:horizontal {background: #8AC435;border: 1px solid "
                   "#CCCCCC;width: 20px;margin: -5px 0;border-radius: 10px;}")
        .arg(_primaryColor, _textColor, _accentColor);
}



void Tools::playSound(QString link, int volume){

    _soundEffect->setSource(QUrl(link));
    _soundEffect->setVolume(volume);
    _soundEffect->play();

}

void Tools::playMusic(QString link, int volume){
    if (_music->state() == QMediaPlayer::PlayingState)
            _music->stop();
    _playlist->addMedia(QUrl(link));
    _playlist->setPlaybackMode(QMediaPlaylist::Loop);

    _music->setPlaylist(_playlist);
    _music->setVolume(volume);
    _music->play();
}

void Tools::stopMusic(){
    _playlist->clear();
    if (_music->state() == QMediaPlayer::PlayingState)
            _music->stop();
}

void Tools::changeVolume(int volume){
    _music->setVolume(volume);
}


