#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTextEdit>
#include <QUrl>
#include <QGraphicsDropShadowEffect>
#include <QList>
#include <QFontDatabase>
#include "LoginWindow.h"
#include "Tools.h"
#include "model/LeaderboardModel.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _model = new SudokuModel();
    _presenter = new SudokuPresenter(_model);

    timer = new PersonnalTimer();

    tool = new Tools();

    // Connecter les menus
    connect(ui->actionPurple, &QAction::triggered, this, &MainWindow::changeToPurpleTheme);
    connect(ui->actionBlue, &QAction::triggered, this, &MainWindow::changeToBlueTheme);
    connect(ui->actionDark, &QAction::triggered, this, &MainWindow::changeToDarkTheme);
    connect(ui->difficultyComboBox, &QComboBox::currentTextChanged, this, &MainWindow::difficultyChanged);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);
    connect(ui->newgameButton, &QPushButton::clicked, this, &MainWindow::newGame);
    connect(ui->button_delete, &QPushButton::clicked, this, &MainWindow::on_button_delete_clicked);
    connect(ui->action_New_Game, &QAction::triggered, this, &MainWindow::newGame);
    connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);
    connect(ui->action_Menu, &QAction::triggered, this, &MainWindow::goToMenu);
    connect(ui->actionEasy, &QAction::triggered, this, &MainWindow::handleDifficultyAction);
    connect(ui->actionMedium, &QAction::triggered, this, &MainWindow::handleDifficultyAction);
    connect(ui->actionHard, &QAction::triggered, this, &MainWindow::handleDifficultyAction);
    connect(ui->actionInsane, &QAction::triggered, this, &MainWindow::handleDifficultyAction);
    connect(timer, &PersonnalTimer::timeChanged, this, &MainWindow::updateTime);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::handleAboutAction);
    connect(ui->action_Pause, &QAction::triggered, this, &MainWindow::handlePauseAction);
    connect(ui->action_Resume, &QAction::triggered, this, &MainWindow::handleResumeAction);
    connect(_presenter, &SudokuPresenter::victory, this, &MainWindow::victory);
    connect(ui->actionReduce_Music_Volume, &QAction::triggered, this, &MainWindow::reduceMusicVolume);
    connect(ui->action_Increase_Music_Volume, &QAction::triggered, this, &MainWindow::increaseMusicVolume);
    connect(ui->actionReduce_Sound_Effect_Volume, &QAction::triggered, this, &MainWindow::reduceSoundEffectVolume);
    connect(ui->actionIncrease_Sound_Effect_Volume, &QAction::triggered, this, &MainWindow::increaseSoundEffectVolume);

    ui->menubar->setNativeMenuBar(false);

    if (!tool->readTheme().isEmpty()) {
        setThemeAttributes(tool->readTheme());
        changeTheme();
    } else {
        _primaryColor = "#E4CCFF";
        _accentColor = "#D0A7FF";
        _complementaryColor = "#c2d7b2";
        _complementaryaccentColor = "#b3c9a4";
        _textColor = "black";
    }
    setWindowIcon(QIcon(":/images/icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeView(){
    applyCustomFontToAllElements();
    newGame();
    connectButtons();
    connectSolutionButtons();
}


void MainWindow::setMusicVolume(int volume){
    _musicVolume = volume;
    qDebug() << "volume de la musique : " << volume;
    tool->playMusic("qrc:/sound/OST.wav", _musicVolume);
}

void MainWindow::setSoundEffectVolume(int volume){
    _soundEffectVolume = volume;
    qDebug() << "volume des sfx : " << volume;
}

void MainWindow::setPseudo(QString pseudo){
    _pseudo = pseudo;
    ui->pseudoLabel->setText(QString(tr("Hello %1 !")).arg(pseudo));
}

void MainWindow::setDifficulty(int difficultyIndex){
    _currentDifficultyIndex = difficultyIndex;
    ui->difficultyComboBox->setCurrentIndex(difficultyIndex);
}

void MainWindow::setThemeAttributes(const QVector<QString>& data) {
    if (data.size() >= 5) {
        _primaryColor = data[0];
        _accentColor = data[1];
        _complementaryColor = data[2];
        _complementaryaccentColor = data[3];
        _textColor = data[4];
    } else {
        qDebug() << "ERROR: Insufficient data provided to set theme attributes";
    }
}

void MainWindow::changeToTheme(const QString& primaryColor, const QString& accentColor, const QString& complementaryColor, const QString& complementaryAccentColor, const QString& textColor)
{
    _primaryColor = primaryColor;
    _accentColor = accentColor;
    _complementaryColor = complementaryColor;
    _complementaryaccentColor = complementaryAccentColor;
    _textColor = textColor;

    displaySudokuGrids();
    changeTheme();

}

void MainWindow::changeToPurpleTheme()
{
    changeToTheme("#E4CCFF", "#D0A7FF", "#c2d7b2", "#b3c9a4", "black");
}

void MainWindow::changeToBlueTheme()
{
    changeToTheme("#BDE3FF", "#6DA9D5", "#ffcbbd", "#e2afa2", "black");
}

void MainWindow::changeToDarkTheme()
{
    changeToTheme("#1E1E1E", "#343434", "#909090", "#6a6a6a", "white");
}


void MainWindow::changeTheme(){
    qApp->setStyleSheet("");

    QVector<QString> colors;
    colors << _primaryColor << _accentColor << _complementaryColor << _complementaryaccentColor << _textColor;
    tool->writeTheme(colors);

    ui->centralwidget->setStyleSheet(QString("QWidget {background-color: %1;} * {color:%2} "
                                             "QPushButton{padding-left:10px; padding-right:10px}")
                                         .arg(_primaryColor, _textColor));

    ui->progressFrame->setStyleSheet(QString("QFrame {background-color: %1; border-radius:20px}")
                                         .arg(_accentColor, _primaryColor));
    ui->helperFrame->setStyleSheet(
        QString("QFrame#helperFrame {background-color:%1;border-radius:20px}"
                "QPushButton {background-color:%1; border-radius:5px}"
                "QFrame {background-color:%2;border-radius:20px}")
            .arg(_accentColor, _primaryColor));
    ui->numbersFrame->setStyleSheet(
        QString(
            "QFrame {background-color: %1; border-radius:20px} "
            "QPushButton {background-color: %2; border-radius:5px}"
            "QLabel{border: 1 solid %4; border-radius:8px; background-color:%3; margin-left:25px;}")
            .arg(_accentColor, _primaryColor, _complementaryColor, _complementaryaccentColor));
    ui->menubar->setStyleSheet(
        QString("QMenuBar {background-color: %1; color: %2}").arg(_accentColor, _textColor));
    ui->buttonFrame->setStyleSheet(QString("QFrame {background-color: %1; border-radius:20px}"
                                           "QComboBox{color:%2}")
                                       .arg(_accentColor, _textColor));

    if (QString::compare(_primaryColor,"#1E1E1E") == 0){
        ui->buttonFrame->setStyleSheet("QFrame {background-color: #343434; border-radius:20px}"
                                       "QPushButton {border-radius: 6px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #1E1E1E, stop: 1 #000000); min-width: 80px;}"
                                       "QPushButton:pressed {background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #000000, stop: 1 #1E1E1E);}"
                                       "QComboBox{color:black}");
        ui->button_delete->setIcon(QIcon(":/images/backspace_white.png"));
    } else{
        ui->buttonFrame->setStyleSheet(QString("QFrame {background-color: %1; border-radius:20px}"
                                               "QPushButton {border-radius: 6px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f6f7fa, stop: 1 %2); min-width: 80px;}"
                                               "QPushButton:pressed {background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 %2, stop: 1 #f6f7fa);}")
                                           .arg(_accentColor, _primaryColor));
        ui->button_delete->setIcon(QIcon(":/images/backspace.png"));
    }

    QList<QFrame *> allChildren = ui->centralwidget->findChildren<QFrame *>();

    for (QObject *child : allChildren) {
        if (QLabel *label = qobject_cast<QLabel*>(child)) {
            // on passe les labels qui sont considérés comme des QFrame
        } else if (QFrame *frame = qobject_cast<QFrame*>(child)) {
            QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect;
            shadow_effect->setOffset(1, 1);
            shadow_effect->setColor(Qt::darkGray);
            shadow_effect->setBlurRadius(2);
            frame->setGraphicsEffect(shadow_effect);
        }
    }
}


void MainWindow::resetGame(){
    _presenter->setInitialSudokuGrid(_gridIndex);
    _sudokuGrid =_presenter->getSudokuGrid();
    displaySudokuGrids();
    ui->widget_2->updateGrid(_sudokuGrid);
    ui->gridLabel->setText(QString(tr("Grid #%1")).arg(_gridIndex));
    setupProgressionBar();

    for (int num = 1; num <= 9; ++num) {
        QString buttonName = QString("button_nb_%1").arg(num);
        QPushButton *numButton = findChild<QPushButton *>(buttonName);
        if (numButton) {
            numButton->setEnabled(true);
            numButton->setStyleSheet(""); // Réinitialiser le style par défaut
        }
    }
    timer->resetTimer();
    updateRemainingNumbersLabels();
}

void MainWindow::newGame(){
    _currentDifficultyIndex = ui->difficultyComboBox->currentIndex();
    _lastClickedGridButton = nullptr;
    _presenter->setSudokuGridDifficulty(_currentDifficultyIndex);

    // generate a random grid
    int maxSize = _presenter->getSizeSudoGrids();
    qDebug() << maxSize;
    _gridIndex = QRandomGenerator::global()->bounded(maxSize);
    _presenter->setInitialSudokuGrid(_gridIndex);
    _sudokuGrid = _presenter->getSudokuGrid();
    _initialSudokuGrid = _sudokuGrid;
    displaySudokuGrids();
    ui->widget_2->updateGrid(_sudokuGrid);

    ui->gridLabel->setText(QString(tr("Grid #%1")).arg(_gridIndex));
    setupProgressionBar();

    for (int num = 1; num <= 9; ++num) {
        QString buttonName = QString("button_nb_%1").arg(num);
        QPushButton *numButton = findChild<QPushButton *>(buttonName);
        if (numButton) {
            numButton->setEnabled(true);
            numButton->setStyleSheet(""); // Réinitialiser le style par défaut
        }
    }
    changeTheme();
    timer->resetTimer();
    updateRemainingNumbersLabels();


}

void MainWindow::displaySudokuGrids()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int number = _sudokuGrid[row][col]; // Assuming there is only one grid
            int initialNumber = _initialSudokuGrid[row][col];
            QString buttonName = QString("button_%1_%2").arg(row).arg(col);
            QPushButton *button = findChild<QPushButton *>(buttonName);
            if (button) {
                if (number != 0 ) {
                    button->setText(QString::number(number));
                    button->setStyleSheet(
                        QString("background-color: %1; color: %2; border-radius:5px;")
                            .arg(_accentColor, _textColor));
                    button->setCursor(Qt::ArrowCursor);
                } else {
                    // Modifier le style de la case si elle est vide
                    button->setText("-");
                    button->setStyleSheet(
                        QString("background-color: %1; color: %2; border-radius:5px;")
                            .arg(_complementaryColor, _textColor));
                    // Connecter le clic sur la case à votre gestionnaire de clic
                    connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
                }
                if (initialNumber == 0 && number != 0){
                    connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
                    button->setStyleSheet(
                        QString("background-color: %1; color: %2; border-radius:5px;")
                            .arg(_complementaryColor, _textColor));
                }
            }
        }
    }
}

void MainWindow::handleButtonClick()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    //on gère les cases vides
    if (button->text() == "-") {
        if (_lastClickedGridButton){
            _lastClickedGridButton->setStyleSheet(
                QString("background-color: %1; color: %2; border-radius:5px;")
                    .arg(_complementaryColor, _textColor));
        }

        tool->playSound("qrc:/sound/click1.wav", _soundEffectVolume);
        button->setStyleSheet(QString("background-color: %1; color: %2; border-radius:5px;")
                                  .arg(_complementaryaccentColor, _textColor));

        _lastClickedGridButton = button;
        QString objectName = button->objectName();
        int row = objectName.section('_', 1, 1).toInt();
        int col = objectName.section('_', 2, 2).toInt();

        QSet<int> possibilities = _presenter->calculatePossibilities(row, col);

        // Réinitialiser le style des boutons représentant les chiffres possibles
        for (int num = 1; num <= 9; ++num) {
            QString buttonName = QString("button_nb_%1").arg(num);
            QPushButton *numButton = findChild<QPushButton *>(buttonName);
            if (numButton) {
                numButton->setEnabled(true);
                numButton->setStyleSheet(""); // Réinitialiser le style par défaut
            }
        }

        // Désactiver tous les boutons représentant les chiffres possibles
        for (int num = 1; num <= 9; ++num) {
            QString buttonName = QString("button_nb_%1").arg(num);
            QPushButton *numButton = findChild<QPushButton *>(buttonName);
            if (numButton && !possibilities.contains(num)) {
                numButton->setDisabled(true);
                numButton->setStyleSheet("background-color: gray; color: darkgrey; border-radius:5px");
            }
        }
    }

    // on gère les cases déjà complétés mais que l'on veut modifier
    QString objectName = button->objectName();
    int row = objectName.section('_', 1, 1).toInt();
    int col = objectName.section('_', 2, 2).toInt();
    if(button->text() != "-" && _initialSudokuGrid[row][col] == 0){
        if (_lastClickedGridButton){
            _lastClickedGridButton->setStyleSheet(
                QString("background-color: %1; color: %2; border-radius:5px;")
                    .arg(_complementaryColor, _textColor));
        }
        tool->playSound("qrc:/sound/click1.wav", _soundEffectVolume);
        button->setStyleSheet(QString("background-color: %1; color: %2; border-radius:5px;")
                                  .arg(_complementaryaccentColor, _textColor));
        _lastClickedGridButton = button;
        for (int num = 1; num <= 9; ++num) {
            QString buttonName = QString("button_nb_%1").arg(num);
            QPushButton *numButton = findChild<QPushButton *>(buttonName);
            if (numButton) {
                numButton->setDisabled(true);
                numButton->setStyleSheet("background-color: gray; color: darkgray; border-radius:5px");
            }
        }
    }
}

QSet<int> MainWindow::calculatePossibilities(QPushButton *button)
{
    QSet<int> possibilities;
    if (button) {
        // Obtenir les coordonnées de la case correspondant au bouton
        QString objectName = button->objectName();
        int row = objectName.section('_', 1, 1).toInt();
        int col = objectName.section('_', 2, 2).toInt();
        possibilities = _presenter->calculatePossibilities(row, col);
    }
    return possibilities;
}

void MainWindow::connectSolutionButtons()
{
    for (int num = 1; num <= 9; ++num) {
        QString buttonName = QString("button_nb_%1").arg(num);
        QPushButton *numButton = findChild<QPushButton *>(buttonName);
        if (numButton) {
            connect(numButton, &QPushButton::clicked, this, [this, num]() {
                handleSolutionButtonClick(num);
            });
        }
    }
}


void MainWindow::connectButtons()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QString buttonName = QString("button_%1_%2").arg(row).arg(col);
            _buttons = findChild<QPushButton *>(buttonName);
            if (_buttons) {
                disconnect(_buttons, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
                connect(_buttons, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
            }
        }
    }
}

void MainWindow::handleSolutionButtonClick(int number)
{

    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button && _lastClickedGridButton) {
        // Obtenir les coordonnées de la case correspondant au bouton
        QString objectName = _lastClickedGridButton->objectName();
        int row = objectName.section('_', 1, 1).toInt();
        int col = objectName.section('_', 2, 2).toInt();

        // Placer le numéro dans la case de la grille
        _sudokuGrid[row][col] = number;

        tool->playSound("qrc:/sound/click2.wav", _soundEffectVolume);

        // Mettre à jour l'affichage de la grille
        _presenter->setSudokuGrid(_sudokuGrid);
        ui->widget_2->updateGrid(_sudokuGrid);
        displaySudokuGrids();
        updateProgressionBar();
        updateRemainingNumbersLabels();
    }
}

void MainWindow::on_button_delete_clicked()
{
    tool->playSound("qrc:/sound/click3.wav", _soundEffectVolume);

    if (_lastClickedGridButton) {
        QString objectName = _lastClickedGridButton->objectName();
        int row = objectName.section('_', 1, 1).toInt();
        int col = objectName.section('_', 2, 2).toInt();

        // Vérifier si la case est remplie
        if (_sudokuGrid[row][col] != 0) {
            // Effacer le chiffre dans la grille Sudoku
            _sudokuGrid[row][col] = 0;

            // Effacer le texte sur le bouton correspondant
            _lastClickedGridButton->setText("-");

            // Mettre à jour l'affichage de la grille
            _presenter->setSudokuGrid(_sudokuGrid);
            ui->widget_2->updateGrid(_sudokuGrid);
            displaySudokuGrids();
            updateProgressionBar();
            updateRemainingNumbersLabels();


        }
    }
}

void MainWindow::updateRemainingNumbersLabels()
{
    QVector<int> remainingCounts = _presenter->countRemainingNumbers();

    // Mettre à jour le texte de chaque QLabel directement via l'interface utilisateur
    for (int i = 1; i <= 9; ++i) {
        QLabel* label = qobject_cast<QLabel*>(findChild<QObject*>(QString("remaining_%1").arg(i)));
        if (label) {
            QString labelText = QString::number(remainingCounts[i]);
            label->setText(labelText);
            QFont font = label->font();
            font.setPointSize(11);
            label->setFont(font);
        } else {
            qDebug() << "Erreur: QLabel remaining_" << i << " non trouvé.";
        }
    }
}


void MainWindow::setupProgressionBar()
{
    ui->progressBar->setMaximum(81);
    ui->progressBar->setValue(81 - _presenter->getProgression());
}

void MainWindow::updateProgressionBar()
{
    ui->progressBar->setValue(81 - _presenter->getProgression());
}

void MainWindow::updateTime(QTime elapsedTime) {
    _elapsedTime = elapsedTime;
    displayTime();

}
void MainWindow::displayTime() {
    ui->timeLabel->setText(_elapsedTime.toString("hh:mm:ss"));
}

void MainWindow::difficultyChanged(){
    int index = ui->difficultyComboBox->currentIndex();
    if (index == EASY){
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:#14AE5C}");
    }else if (index == MEDIUM){
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:#FFA629}");
    }else if (index == HARD){
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:#F24822}");
    }else {
        ui->difficultyComboBox->setStyleSheet("QComboBox{background-color:#921F06}");
    }
}


void MainWindow::handleDifficultyAction() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (!action)
        return;
    if (action == ui->actionEasy){
        setDifficulty(EASY);
    }else if (action == ui->actionMedium){
        setDifficulty(MEDIUM);
    }else if (action == ui->actionHard){
        setDifficulty(HARD);
    }else if (action == ui->actionInsane){
        setDifficulty(INSANE);
    }
}

void MainWindow::goToMenu(){
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->show();
    setDifficulty(ui->difficultyComboBox->currentIndex());
    setMusicVolume(_musicVolume);
    setSoundEffectVolume(_soundEffectVolume);
    tool->stopMusic();
    close();
}



void MainWindow::applyCustomFontToAllElements()
{
    QFont customFont;
    int fontId = QFontDatabase::addApplicationFont(":/Fonts/OTF/Supreme-Medium.otf");
    if (fontId != -1) { // Vérifie si la police a été chargée avec succès
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        customFont = QFont(fontFamily);
        customFont.setPixelSize(22);
    } else {
        qWarning() << "Failed to load font";
        return;
    }

    QList<QWidget*> widgets = findChildren<QWidget*>();
    for (QWidget* widget : widgets) {
        widget->setFont(customFont);
    }
}

void MainWindow::handleAboutAction()
{
    // Créez une boîte de dialogue
    QDialog aboutDialog(this);
    aboutDialog.setWindowTitle(tr("About"));

    // Créer un widget QTextEdit pour afficher le contenu
    QTextEdit *textEdit = new QTextEdit(&aboutDialog);
    textEdit->setReadOnly(true); // Rendre le texte en lecture seule

    // Lire le contenu du fichier license.txt
    QFile file(":/license.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString licenseText = in.readAll();
        textEdit->setPlainText(licenseText);
        file.close();
    } else {
        textEdit->setPlainText("Unable to open license.txt");
    }

    // Ajouter le widget de texte à la boîte de dialogue
    QVBoxLayout *layout = new QVBoxLayout(&aboutDialog);
    layout->addWidget(textEdit);

    aboutDialog.resize(textEdit->document()->size().toSize() + QSize(600, 400));

    // Afficher la boîte de dialogue
    aboutDialog.exec();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9) {
        int number = event->key() - Qt::Key_0;
        handleKeyPress(number);
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::handleKeyPress(int number)
{
    if (_lastClickedGridButton) {
        QString objectName = _lastClickedGridButton->objectName();
        int row = objectName.section('_', 1, 1).toInt();
        int col = objectName.section('_', 2, 2).toInt();
        if (_presenter->calculatePossibilities(row, col).contains(number)) {
            _sudokuGrid[row][col] = number;
            tool->playSound("qrc:/sound/click2.wav", _soundEffectVolume);
            _presenter->setSudokuGrid(_sudokuGrid);
            ui->widget_2->updateGrid(_sudokuGrid);
            displaySudokuGrids();
            updateProgressionBar();
            updateRemainingNumbersLabels();
        } else {
            QMessageBox::warning(this,
                                 tr("Invalid Number"),
                                 tr("Please enter a valid number for this cell."));
        }
    }
}

void MainWindow::handlePauseAction()
{
    tool->stopMusic();
}

void MainWindow::handleResumeAction()
{
    tool->playMusic("qrc:/sound/OST.wav", _musicVolume);
}

void MainWindow::reduceMusicVolume()
{
    if (_musicVolume > 0) {
        _musicVolume -= 10;
        setMusicVolume(_musicVolume);
    }
    tool->changeVolume(_musicVolume);
}

void MainWindow::increaseMusicVolume()
{
    if (_musicVolume < 100) {
        _musicVolume += 10;
        setMusicVolume(_musicVolume);
    }
    tool->changeVolume(_musicVolume);
}

void MainWindow::reduceSoundEffectVolume()
{
    if (_soundEffectVolume > 0) {
        _soundEffectVolume -= 10;
        setSoundEffectVolume(_soundEffectVolume);
    }
}

void MainWindow::increaseSoundEffectVolume()
{
    if (_soundEffectVolume < 100) {
        _soundEffectVolume += 10;
        setSoundEffectVolume(_soundEffectVolume);
    }
}


void MainWindow::victory()
{
    timer->stopTimer();
    LeaderboardModel leaderboard;
    leaderboard.updateLeaderboard(_pseudo, _elapsedTime, _currentDifficultyIndex);
    tool->playSound("qrc:/sound/win.wav", _soundEffectVolume);
    QMessageBox::information(this, tr("Bravo"), tr("Vous avez gagné"));
    qDebug() << "GAGNE !!";
}
