#include "LeaderboardWindow.h"
#include "ui_LeaderboardWindow.h"
#include "Tools.h"
#include "LoginWindow.h"
#include <QFontDatabase>

LeaderboardWindow::LeaderboardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderboardWindow)
{
    ui->setupUi(this);

    connect(ui->difficultyComboBox, &QComboBox::currentTextChanged, this, &LeaderboardWindow::difficultyChanged);
    connect(ui->homeButton, &QPushButton::clicked, this, &LeaderboardWindow::returnHome);

    Tools tool;
    this->setStyleSheet(tool.changeTheme());
    setFont();

}

LeaderboardWindow::~LeaderboardWindow()
{
    delete ui;
}

void LeaderboardWindow::setFont(){

    QFont customFont;
    int fontId = QFontDatabase::addApplicationFont(":/Fonts/OTF/Supreme-Medium.otf");
    if (fontId != -1) { // Vérifie si la police a été chargée avec succès
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        customFont = QFont(fontFamily);
        customFont.setPixelSize(32);
    } else {
        qWarning() << "Failed to load font";
        return;
    }

    QList<QWidget*> widgets = findChildren<QWidget*>();
    for (QWidget* widget : widgets) {
        widget->setFont(customFont);
    }
}

void LeaderboardWindow::setDifficulty(int difficulty) {
    _difficulty = difficulty;
    ui->difficultyComboBox->setCurrentIndex(difficulty);
    loadLeaderboard(difficulty);
}

void LeaderboardWindow::loadLeaderboard(int difficulty) {
    // Construire le nom du fichier leaderboard en fonction de la difficulté
    QString leaderboardFileName = QString("leaderboard_%1.txt").arg(difficulty);

    // Lire le leaderboard depuis le fichier
    Tools tool;
    QVector<QVector<QString>> leaderboard = tool.readTextLeaderboard(leaderboardFileName);

    // Afficher les noms et les temps dans les labels
    for (int i = 0; i < leaderboard.size(); ++i) {
        QVector<QString> entry = leaderboard[i];
        QString playerName = entry[0];
        QString playerTime = entry[1];

        // Récupérer les labels existants
        QLabel *nameLabel = findChild<QLabel *>(QString("nameLabel_%1").arg(i));
        QLabel *timeLabel = findChild<QLabel *>(QString("timeLabel_%1").arg(i));

        // Mettre à jour les labels existants avec les nouvelles données
        if (nameLabel)
            nameLabel->setText(playerName);
        if (timeLabel)
            timeLabel->setText(playerTime);
    }

    // Mettre à vide les labels restants si nécessaire
    for (int i = leaderboard.size(); i < 5; ++i) {
        QLabel *nameLabel = findChild<QLabel *>(QString("nameLabel_%1").arg(i));
        QLabel *timeLabel = findChild<QLabel *>(QString("timeLabel_%1").arg(i));
        if (nameLabel)
            nameLabel->setText(" - ");
        if (timeLabel)
            timeLabel->setText(" - ");
    }
}

void LeaderboardWindow::difficultyChanged(){
    int index = ui->difficultyComboBox->currentIndex();
    if (index == EASY){
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:green;color:black} QComboBox QAbstractItemView {color:white}");
    }else if (index == MEDIUM){
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:#FFA629;color:black} QComboBox QAbstractItemView {color:white}");
    }else if (index == HARD){
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:#F24822;color:black} QComboBox QAbstractItemView {color:white}");
    }else {
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:#921F06;color:black} QComboBox QAbstractItemView {color:white}");
    }
    setDifficulty(index);
}

void LeaderboardWindow::returnHome(){
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->show();
    close();
}
