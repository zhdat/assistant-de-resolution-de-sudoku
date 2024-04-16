#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H

#include <QObject>
#include <QTimer>
#include <QTime>


/**
 * @brief The SudokuModel class represents the model of the Sudoku application.
 */
class SudokuModel : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for SudokuModel.
     */
    explicit SudokuModel();
    /**
     * @brief Get all the Sudoku grids from a difficulty.
     * @return The Sudoku grids.
     */
    QVector<QVector<QVector<int>>> getSudokuGrids() const { return _sudokuGrids; }
    /**
     * @brief Get the Sudoku grid.
     * @return The Sudoku grid.
     */
    QVector<QVector<int>> getSudokuGrid() const { return _sudokuGrid; }
    /**
     * @brief Get the progression of the Sudoku grid.
     * @return The progression of the Sudoku grid.
     */
    int getProgression() const {return _progression;}
    /**
     * @brief Set the Sudoku grid.
     * @param sudokuGrid The Sudoku grid to set.
     */
    void setSudokuGrid(QVector<QVector<int>> sudokuGrid);
    /**
     * @brief Load a Sudoku grids from a file.
     * @param filePath The path of the file.
     */
    void loadSudokuFromFile(const QString &filePath);
    /**
     * @brief Set the difficulty level of the Sudoku grid.
     * @param difficultyLevel The difficulty level to set.
     */
    void setSudokuGridDifficulty(int difficultyLevel);
    /**
     * @brief Load the initial Sudoku grid from all the grids.
     * @param nGrille The index of the grid to load.
     */
    void setInitialSudokuGrid(int nGrille);
    /**
     * @brief Get the size of the Sudoku grids.
     * @return The size of the Sudoku grids.
     */
    int getSizeSudoGrids();
    /**
     * @brief Calculate the possibilities of numbers for a cell.
     * @param rowButton The row of the cell.
     * @param columnButton The column of the cell.
     * @return All the possibilities for the cell.
     */
    QSet<int> calculatePossibilities(int rowButton, int columnButton);
    /**
     * @brief Count the filled numbers in the Sudoku grid.
     * @return The count of filled numbers.
     */
    QVector<int> countFilledNumbers();
    /**
     * @brief Count the remaining numbers in the Sudoku grid.
     * @return The count of remaining numbers.
     */
    QVector<int> countRemainingNumbers();

private:
    QVector<QVector<QVector<int>>> _sudokuGrids; /**< all the Sudoku grids from a difficulty. */
    QVector<QVector<int>> _sudokuGrid; /**< The Sudoku grid. */
    int _progression; /**< The progression of the Sudoku grid. */
};

#endif // SUDOKUMODEL_H
