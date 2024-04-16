#ifndef SUDOKUPRESENTER_H
#define SUDOKUPRESENTER_H

#include <QObject>
#include <QSet>
#include "model/SudokuModel.h"


/**
 * @brief The SudokuPresenter class represents the presenter of the Sudoku application.
 */
class SudokuPresenter : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for SudokuPresenter.
     * @param model The model to use (default is nullptr).
     */
    explicit SudokuPresenter(SudokuModel *model = nullptr);
    /**
     * @brief calculate the possibilities of numbers for a cell.
     * @param row
     * @param col
     * @return all the possibilities for the cell.
     */
    QSet<int> calculatePossibilities(int row, int col);
    /**
     * @brief Get the Sudoku grid.
     * @return The Sudoku grid.
     */
    QVector<QVector<int>> getSudokuGrid() const { return _model->getSudokuGrid(); }
    /**
     * @brief Set the Sudoku grid.
     * @param sudokuGrid The Sudoku grid to set.
     */
    void setSudokuGrid(QVector<QVector<int>> sudokuGrid);
    /**
     * @brief Load the initial Sudoku grid from all the grids.
     * @param nGrille The index of the grid to load.
     */
    void setInitialSudokuGrid(int nGrille);
    /**
     * @brief Set the difficulty level of the Sudoku grid.
     * @param currentDifficultyIndex The index of the difficulty level.
     */
    void setSudokuGridDifficulty(int currentDifficultyIndex);
    /**
     * @brief Get the size of the Sudoku grids.
     * @return The size of the Sudoku grids.
     */
    int getSizeSudoGrids();
    /**
     * @brief Count the filled numbers in the Sudoku grid.
     * @return The count of filled numbers.
     */
    int getProgression();
    /**
     * @brief Count the filled numbers in the Sudoku grid.
     * @return The count of filled numbers.
     */
    QVector<int> countRemainingNumbers();

private:
    SudokuModel *_model; /**< The model of the Sudoku application. */

signals :
    /**
     * @brief Signal for the victory.
     */
    void victory();
};

#endif // SUDOKUPRESENTER_H
