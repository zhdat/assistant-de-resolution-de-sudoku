QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LeaderboardWindow.cpp \
    LoginWindow.cpp \
    PersonnalTimer.cpp \
    SettingsWindow.cpp \
    SudokuGrid.cpp \
    Tools.cpp \
    main.cpp \
    MainWindow.cpp \
    model/LeaderboardModel.cpp \
    model/SudokuModel.cpp \
    presenter/SudokuPresenter.cpp \

HEADERS += \
    LeaderboardWindow.h \
    LoginWindow.h \
    MainWindow.h \
    PersonnalTimer.h \
    SettingsWindow.h \
    SudokuGrid.h \
    Tools.h \
    model/LeaderboardModel.h \
    model/SudokuModel.h \
    presenter/SudokuPresenter.h \

FORMS += \
    LeaderboardWindow.ui \
    MainWindow.ui \
    LoginWindow.ui \
    SettingsWindow.ui

TRANSLATIONS += \
    Sudoku_en_US.ts \
    Sudoku_fr_FR.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Sudoku_fr_FR.ts
