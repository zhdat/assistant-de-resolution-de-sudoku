#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"
#include "Tools.h"
#include "LoginWindow.h"
#include <QSlider>
#include <QFontDatabase>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    connect(ui->homeButton, &QPushButton::clicked, this, &SettingsWindow::returnHome);
    connect(ui->difficultyComboBox, &QComboBox::currentTextChanged, this, &SettingsWindow::difficultyChanged);
    connect(ui->musicSlider, &QSlider::sliderReleased, this, &SettingsWindow::changeMusicLabel);
    connect(ui->sfxSlider, &QSlider::sliderReleased, this, &SettingsWindow::changeSoundEffectLabel);

    Tools tool;
    this->setStyleSheet(tool.changeTheme());
    setFont();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::setFont(){

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

void SettingsWindow::returnHome(){
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->setMusicVolume(ui->musicSlider->value());
    loginWindow->setSoundEffectVolume(ui->sfxSlider->value());
    loginWindow->setDifficulty(ui->difficultyComboBox->currentIndex());
    loginWindow->show();
    close();
}

void SettingsWindow::changeMusicLabel(){
    ui->musicLabel->setText(QString(tr("%1 %")).arg(ui->musicSlider->value()));
}

void SettingsWindow::changeSoundEffectLabel(){
    ui->sfxLabel->setText(QString(tr("%1 %")).arg(ui->sfxSlider->value()));
}

void SettingsWindow::setMusicVolume(int volume){
    ui->musicSlider->setValue(volume);
    changeMusicLabel();
}

void SettingsWindow::setSoundEffectVolume(int volume){
    ui->sfxSlider->setValue(volume);
    changeSoundEffectLabel();
}

void SettingsWindow::setDifficulty(int difficultyIndex){
    ui->difficultyComboBox->setCurrentIndex(difficultyIndex);
}

void SettingsWindow::difficultyChanged(){
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
