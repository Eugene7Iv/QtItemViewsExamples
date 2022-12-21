#pragma once
#include <QtWidgets/QMainWindow>
#include <QTableView>
#include <QAbstractItemDelegate>
#include <QAbstractTableModel>
#include "ImageModel.h"

class Pixelator : public QMainWindow
{
    Q_OBJECT

public:
    Pixelator(QWidget *parent = nullptr);
    ~Pixelator();

    void openImage(const QString& fileName);

private slots:
    void updateView();
    void chooseImage();

private:
    QTableView* view = nullptr;
    ImageModel* model = nullptr;

    QString currentPath = "";
};
