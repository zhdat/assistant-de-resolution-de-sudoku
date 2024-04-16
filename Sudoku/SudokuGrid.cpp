#include "SudokuGrid.h"
#include "model/SudokuModel.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QFontDatabase>

SudokuGrid::SudokuGrid(QWidget *parent)
    : QWidget{parent}
{

}


void SudokuGrid::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 1));

    int cellSize = qMin(width(), height()) / 9;

    // lignes verticales
    for (int i = 0; i <= 9; ++i) {
        painter.drawLine(i * cellSize, 0, i * cellSize, 9 * cellSize);
    }

    // lignes horizontales
    for (int i = 0; i <= 9; ++i) {
        painter.drawLine(0, i * cellSize, 9 * cellSize, i * cellSize);
    }

    for (int i = 0; i <= 9; i += 3) {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(i * cellSize, 0, i * cellSize, 9 * cellSize);
        painter.drawLine(0, i * cellSize, 9 * cellSize, i * cellSize);
    }

    // les nombres
    painter.setPen(QPen(Qt::black, 1));
    QFont font = painter.font();
    font.setPointSize(cellSize / 2);
    painter.setFont(font);

    if(_sudokuGrid.isEmpty()) return;

    int fontId = QFontDatabase::addApplicationFont(":/Fonts/OTF/Supreme-Medium.otf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont customFont(fontFamily);
        customFont.setPixelSize(32);
        painter.setFont(customFont);

    } else {
        qWarning() << "Failed to load font";
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int number = _sudokuGrid[row][col];
            if (number != 0) {
                painter.drawText(col * cellSize + cellSize / 3,
                                 row * cellSize + cellSize * 2 / 3,
                                 QString::number(number));
            }
        }
    }
}

void SudokuGrid::updateGrid(QVector<QVector<int>> grid)
{
    _sudokuGrid.clear();
    _sudokuGrid = grid;
    update();
}
