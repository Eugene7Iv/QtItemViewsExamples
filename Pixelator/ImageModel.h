#pragma once
#include <QAbstractTableModel>
#include <QImage>

class ImageModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	ImageModel(QObject* parent = nullptr);

	void setImage(const QImage& image);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
	QImage modelImage;
};

