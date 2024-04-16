#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "MainWindow.h"
#include "LeaderboardWindow.h"
#include "SettingsWindow.h"
#include "Tools.h"
#include <QFontDatabase>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{

    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &LoginWindow::on_playButton_clicked);
    connect(ui->difficultyComboBox, &QComboBox::currentTextChanged, this, &LoginWindow::difficultyChanged);
    connect(ui->quitButton, &QPushButton::clicked, this, &QApplication::quit);

    setFont();
    Tools tool;
    this->setStyleSheet(tool.changeTheme());
    _musicVolume = 20;
    _soundEffectVolume = 50;

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::setFont(){

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

    fontId = QFontDatabase::addApplicationFont(":/Fonts/Variable/Pally-Variable.ttf");
    if (fontId != -1) { // Vérifie si la police a été chargée avec succès
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont customFont(fontFamily);
        customFont.setPixelSize(78);
        ui->label->setFont(customFont); // Appliquer la police personnalisée à toute l'application

    } else {
        qWarning() << "Failed to load font";
    }

}

void LoginWindow::setDifficulty(int difficultyIndex){
    ui->difficultyComboBox->setCurrentIndex(difficultyIndex);
}

void LoginWindow::on_playButton_clicked()
{
    ui->errorLabel->setText("");
    // Récupérer le pseudo de l'utilisateur
    QString pseudo = ui->pseudoLineEdit->text();
    if (pseudo != ""){
        // Créer une instance de MainWindow
        MainWindow *mainWindow = new MainWindow();

        // Passez le pseudo à la fenêtre principale si nécessaire
        mainWindow->setDifficulty(ui->difficultyComboBox->currentIndex());
        mainWindow->setPseudo(pseudo);
        mainWindow->initializeView();
        mainWindow->setMusicVolume(_musicVolume);
        mainWindow->setSoundEffectVolume(_soundEffectVolume);

        mainWindow->show();

        // Fermer la fenêtre de connexion
        close();

    }else {
        ui->errorLabel->setText(tr("You should pick a pseudo !"));
    }

}

void LoginWindow::on_leaderboardButton_clicked(){

    qDebug() << "OUVERTURE DU LEADERBOARD";
    LeaderboardWindow *leaderboardWindow = new LeaderboardWindow();
    leaderboardWindow->setDifficulty(ui->difficultyComboBox->currentIndex());
    leaderboardWindow->show();
    close();
}

void LoginWindow::on_settingsButton_clicked(){
    SettingsWindow *settingsWindow = new SettingsWindow();
    settingsWindow->setMusicVolume(_musicVolume);
    settingsWindow->setSoundEffectVolume(_soundEffectVolume);
    settingsWindow->setDifficulty(ui->difficultyComboBox->currentIndex());
    settingsWindow->show();
    close();
}


void LoginWindow::difficultyChanged(){
    int index = ui->difficultyComboBox->currentIndex();
    QString comboBoxStyle;
    switch (index) {
    case EASY:
        comboBoxStyle += "QComboBox { background-color: #8AC435; color: black; }";
        break;
    case MEDIUM:
        comboBoxStyle += "QComboBox { background-color: #FFA629; color: black; }";
        break;
    case HARD:
        comboBoxStyle += "QComboBox { background-color: #F24822; color: black; }";
        break;
    default:
        comboBoxStyle += "QComboBox { background-color: #921F06; color: black; }";
        break;
    }

    ui->difficultyComboBox->setStyleSheet(comboBoxStyle);
}

void LoginWindow::setMusicVolume(int volume){
    _musicVolume = volume;
}

void LoginWindow::setSoundEffectVolume(int volume){
    _soundEffectVolume = volume;
}

