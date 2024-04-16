#include "SudokuPresenter.h"
#include "QDebug"
SudokuPresenter::SudokuPresenter(SudokuModel *model)
{
    _model = model;
}

QSet<int> SudokuPresenter::calculatePossibilities(int row, int col){
    return _model->calculatePossibilities(row, col);
}

void SudokuPresenter::setSudokuGrid(QVector<QVector<int>> sudokuGrid){
    _model->setSudokuGrid(sudokuGrid);
}

void SudokuPresenter::setInitialSudokuGrid(int nGrille){
    _model->setInitialSudokuGrid(nGrille);
}

void SudokuPresenter::setSudokuGridDifficulty(int currentDifficultyIndex){
    _model->setSudokuGridDifficulty(currentDifficultyIndex);
}

int SudokuPresenter::getSizeSudoGrids(){
    return _model->getSizeSudoGrids();
}

int SudokuPresenter::getProgression(){
    int progression = _model->getProgression();
    if (progression == 0){
        emit victory();
    }
    return progression;
}

QVector<int> SudokuPresenter::countRemainingNumbers(){
    return _model->countRemainingNumbers();
}
