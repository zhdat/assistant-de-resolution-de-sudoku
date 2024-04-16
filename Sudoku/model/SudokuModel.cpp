#include "SudokuModel.h"
#include "Tools.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

SudokuModel::SudokuModel()
{
}

void SudokuModel::loadSudokuFromFile(const QString &filePath)
{
    // Implémentation de la méthode loadSudokuFromFile
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier" << filePath;
        return;
    }

    QTextStream in(&file);
    int numGrids = 0;
    in >> numGrids; // Lire le nombre de grilles
    //qDebug() << numGrids;
    in.readLine();  // Lire la fin de ligne après le nombre de grilles
    _sudokuGrids =  QVector<QVector<QVector<int>>>();



    QString sudokuText = in.readAll(); // Lire toutes les grilles en une seule chaîne

    for (int gridIndex = 0; gridIndex < numGrids; ++gridIndex) {
        QVector<QVector<int>> sudokuGrid;
        sudokuGrid.resize(9); // Initialiser la grille avec des zéros
        sudokuGrid.fill(QVector<int>(9, 0));

        int startIndex = gridIndex * 82; // Chaque grille a 9x9 = 81 caractères
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                QChar ch = sudokuText.at(startIndex + i * 9 + j);
                if (ch.isDigit()) {
                    sudokuGrid[i][j] = ch.digitValue();
                }
            }
        }
        _sudokuGrids.append(sudokuGrid);
    }

    file.close();
}

void SudokuModel::setSudokuGridDifficulty(int difficultyLevel){
    qDebug() << "Difficulté : " << difficultyLevel;
    if (difficultyLevel == EASY){
        loadSudokuFromFile(":/Easy.txt");
        qDebug() << "EASY";
    } else if (difficultyLevel == MEDIUM){
        loadSudokuFromFile(":/Medium.txt");
        qDebug() << "MEDIUM";
    } else if (difficultyLevel == HARD){
        loadSudokuFromFile(":/Hard.txt");
        qDebug() << "HARD";
    } else {
        loadSudokuFromFile(":/Insane.txt");
        qDebug() << "INSANE";
    }
}

void SudokuModel::setInitialSudokuGrid(int nGrille){
    _sudokuGrid = _sudokuGrids[nGrille];
    qDebug() << "Sudoku Grid: " << nGrille;
        for (int i = 0; i < _sudokuGrid.size(); ++i) {
            qDebug() << _sudokuGrid[i];
        }
    _progression = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int number = _sudokuGrid[row][col];
            if (number == 0) {
                _progression++;
            }
        }
    }
}

int SudokuModel::getSizeSudoGrids()
{
    return _sudokuGrids.size();
}

QSet<int> SudokuModel::calculatePossibilities(int rowButton, int columnButton)
{
    QSet<int> possibilities;
        // Ajouter les chiffres de 1 à 9 à l'ensemble des possibilités
    possibilities << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9;

        // Vérifier les chiffres déjà utilisés dans la ligne
    for (int c = 0; c < 9; ++c) {
        possibilities.remove(_sudokuGrid[rowButton][c]);
    }

        // Vérifier les chiffres déjà utilisés dans la colonne
    for (int r = 0; r < 9; ++r) {
        possibilities.remove(_sudokuGrid[r][columnButton]);
    }

        // Vérifier les chiffres déjà utilisés dans la région
    int startRow = (rowButton / 3) * 3;
    int startCol = (columnButton / 3) * 3;
    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            possibilities.remove(_sudokuGrid[r][c]);
        }
    }

    return possibilities;
}

QVector<int> SudokuModel::countFilledNumbers()
{
    QVector<int> counts(10, 0); // Initialiser le vecteur de comptage à 0

    // Parcourir la grille de Sudoku actuelle
    for (const QVector<int>& row : _sudokuGrid) {
        for (int number : row) {
            if (number >= 1 && number <= 9) {
                // Incrémenter le compteur pour ce chiffre
                counts[number]++;
            }
        }
    }

    return counts;
}

QVector<int> SudokuModel::countRemainingNumbers()
{
    QVector<int> remainingCounts(10, 9); // Initialiser le vecteur avec 9 pour chaque chiffre possible

    // Obtenir les occurrences de chaque chiffre déjà rempli
    QVector<int> filledCounts = countFilledNumbers();

    // Soustraire les occurrences déjà remplies des totaux possibles
    for (int i = 1; i <= 9; ++i) {
        remainingCounts[i] -= filledCounts[i];
    }

    return remainingCounts;
}

void SudokuModel::setSudokuGrid(QVector<QVector<int>> sudokuGrid)
{
    _sudokuGrid = sudokuGrid;
    _progression = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int number = _sudokuGrid[row][col];
            if (number == 0) {
                _progression++;
            }
        }
    }
}

