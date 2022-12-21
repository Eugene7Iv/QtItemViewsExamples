#include "pixelator.h"
#include <QHeaderView>
#include <QLabel>
#include <QSpinBox>
#include <QDir>
#include <QMenu>
#include <QMenuBar>
#include <QCoreApplication>
#include <QBoxLayout>
#include <QFileDialog>
#include "PixelDelegate.h"

Pixelator::Pixelator(QWidget *parent)
    : QMainWindow(parent)
{
    currentPath = QDir::homePath();
    model = new ImageModel(this);

    QWidget* centralWidget = new QWidget;

    view = new QTableView;
    view->setShowGrid(false);
    view->horizontalHeader()->hide();
    view->verticalHeader()->hide();
    view->horizontalHeader()->setMinimumSectionSize(1);
    view->verticalHeader()->setMinimumSectionSize(1);
    view->setModel(model);

    PixelDelegate* delegate = new PixelDelegate(this);
    view->setItemDelegate(delegate);

    QLabel* pixelSizeLabel = new QLabel(tr("Pixel size:"));
    QSpinBox* pixelSizeSpinBox = new QSpinBox;
    pixelSizeSpinBox->setMinimum(4);
    pixelSizeSpinBox->setMaximum(32);
    pixelSizeSpinBox->setValue(12);

    connect(pixelSizeSpinBox, qOverload<int>(& QSpinBox::valueChanged),
        delegate, &PixelDelegate::setPixelSize);

    connect(pixelSizeSpinBox, qOverload<int>(&QSpinBox::valueChanged),
        this, &Pixelator::updateView);

    QMenu* fileMenu = new QMenu(tr("&File"), this);
    QAction* openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcuts(QKeySequence::Open);

    QAction* quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcuts(QKeySequence::Quit);

    menuBar()->addMenu(fileMenu);
    menuBar()->addSeparator();

    connect(openAction, &QAction::triggered, this, &Pixelator::chooseImage);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    QHBoxLayout* controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(pixelSizeLabel);
    controlsLayout->addWidget(pixelSizeSpinBox);
    controlsLayout->addStretch(1);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addLayout(controlsLayout);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);

    setWindowTitle(tr("Pixelator"));
    resize(640, 480);
}

Pixelator::~Pixelator()
{}

void Pixelator::updateView()
{
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
}

void Pixelator::chooseImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Choose an image"), currentPath, "*");

    if (!fileName.isEmpty())
        openImage(fileName);
}

void Pixelator::openImage(const QString& fileName)
{
    QImage image;

    if (image.load(fileName)) {
        model->setImage(image);
        if (!fileName.startsWith(":/")) {
            currentPath = fileName;
            setWindowTitle(tr("%1 - Pixelator").arg(currentPath));
        }

        updateView();
    }
}