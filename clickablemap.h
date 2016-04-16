#ifndef CLICKABLEMAP_H
#define CLICKABLEMAP_H

#include <QLabel>
#include <QMouseEvent>

class ClickableMap : public QLabel
{
Q_OBJECT
public:
    explicit ClickableMap(QWidget* parent=0);
    ~ClickableMap();

signals:
    void clicked(QMouseEvent *event);
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKABLEMAP_H
