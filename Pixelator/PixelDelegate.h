#pragma once
#include <QAbstractItemDelegate>

class PixelDelegate : public QAbstractItemDelegate
{
	Q_OBJECT

public:
	PixelDelegate(QObject* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

public slots:
	void setPixelSize(int size);

private:
	int pixelSize;
};

