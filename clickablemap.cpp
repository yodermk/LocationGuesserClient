#include "clickablemap.h"

ClickableMap::ClickableMap(QWidget *parent)
  : QLabel(parent)
{

}

ClickableMap::~ClickableMap()
{

}

void ClickableMap::mousePressEvent(QMouseEvent *event)
{
    emit clicked(event);
}
