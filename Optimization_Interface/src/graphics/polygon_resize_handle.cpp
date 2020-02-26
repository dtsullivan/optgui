// TITLE:   Optimization_Interface/src/graphics/polygon_resize_handle.cpp
// AUTHORS: Daniel Sullivan, Miki Szmuk
// LAB:     Autonomous Controls Lab (ACL)
// LICENSE: Copyright 2018, All Rights Reserved

#include "include/graphics/polygon_resize_handle.h"

#include <QtMath>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "include/globals.h"

namespace optgui {

PolygonResizeHandle::PolygonResizeHandle(PolygonModelItem *model,
                                         quint32 index,
                                         QGraphicsItem *parent,
                                         qreal size)
    : QGraphicsEllipseItem(parent) {
    this->model_ = model;
    this->resize_ = false;
    this->setPen(QPen(Qt::black));
    this->setBrush(QBrush(Qt::white));
    this->size_ = size;
    this->index_ = index;
    this->setRect(-this->size_, -this->size_,
                  this->size_ * 2, this->size_ * 2);
}

void PolygonResizeHandle::setColor(const QColor color) {
    this->setBrush(QBrush(color));
}

void PolygonResizeHandle::updatePos() {
    // Translate model point to local coordinates
    this->setPos(this->parentItem()->mapFromScene(
                     this->model_->getPointAt(this->index_)));
}

void PolygonResizeHandle::updateModel(QPointF diff) {
    // Adjust model to new parent position
    QPointF currPos = this->model_->getPointAt(this->index_);
    this->model_->setPointAt(currPos + diff, this->index_);
}

void PolygonResizeHandle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->resize_ = true;
    }
}

void PolygonResizeHandle::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // scale with view
    qreal scaling_factor = this->getScalingFactor();
    qreal size = this->size_ / scaling_factor;
    QPen pen = this->pen();
    pen.setWidthF(1.0 / scaling_factor);
    this->setPen(pen);
    this->setRect(-size, -size, size * 2, size * 2);

    // paint
    QGraphicsEllipseItem::paint(painter, option, widget);
}

void PolygonResizeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->resize_ = false;
    }
}

void PolygonResizeHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (this->resize_) {
        QPointF eventPos = event->scenePos();
        this->model_->setPointAt(eventPos, this->index_);
        this->expandScene();
    }
}

int PolygonResizeHandle::type() const {
    return HANDLE_GRAPHIC;
}

QPointF PolygonResizeHandle::getPoint() {
    return this->model_->getPointAt(this->index_);
}

void PolygonResizeHandle::expandScene() {
    if (scene()) {
        // expand scene if item goes out of bounds
        QRectF newRect = this->parentItem()->sceneBoundingRect();
        QRectF rect = this->scene()->sceneRect();
        if (!rect.contains(newRect)) {
            this->scene()->setSceneRect(scene()->sceneRect().united(newRect));
            if (!this->scene()->views().isEmpty()) {
                this->scene()->views().first()->setSceneRect(
                            this->scene()->sceneRect());
            }
        }
        this->update(this->boundingRect());
    }
}

qreal PolygonResizeHandle::getScalingFactor() {
    qreal scaling_factor = 1;
    if (this->scene() && !this->scene()->views().isEmpty()) {
        scaling_factor = this->scene()->views().first()->matrix().m11();
    }
    return scaling_factor;
}

}  // namespace optgui