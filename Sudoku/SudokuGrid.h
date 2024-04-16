#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <QPainter>
#include <QWidget>
#include "presenter/SudokuPresenter.h"
#include "MainWindow.h"

/**
 * @brief The SudokuGrid class represents the grid of the Sudoku game.
 */
class SudokuGrid : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for SudokuGrid.
     * @param parent The parent widget (default is nullptr).
     */
    explicit SudokuGrid(QWidget *parent = nullptr);
    /**
     * @brief Updates the grid.
     */
    void updateGrid(QVector<QVector<int>> grid);

protected:
    /**
     * @brief Paints the Sudoku grid.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QVector<int>> _sudokuGrid; /**< The Sudoku grid. */

};

#endif // SUDOKUGRID_H
