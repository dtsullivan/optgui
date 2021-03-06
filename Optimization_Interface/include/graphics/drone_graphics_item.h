// TITLE:   Optimization_Interface/include/graphics/drone_graphics_item.h
// AUTHORS: Daniel Sullivan, Miki Szmuk
// LAB:     Autonomous Controls Lab (ACL)
// LICENSE: Copyright 2018, All Rights Reserved

// Graphical representation for drone

#ifndef DRONE_GRAPHICS_ITEM_H_
#define DRONE_GRAPHICS_ITEM_H_

#include <QGraphicsItem>
#include <QPainter>

#include "include/globals.h"
#include "include/models/drone_model_item.h"

namespace optgui {

class DroneGraphicsItem : public QGraphicsItem {
 public:
    explicit DroneGraphicsItem(DroneModelItem *model,
                               QGraphicsItem *parent = nullptr,
                               qreal size = 20);
    // rough area of graphic
    QRectF boundingRect() const override;

    // draw graphic
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
              QWidget *widget = nullptr) override;
    int type() const override;

    // data model
    DroneModelItem *model_;
    bool is_curr_drone_;
    bool is_staged_drone_;
    bool is_executed_drone_;

    void setIsFeasible(bool feasible);
    bool getIsFeasible();

 protected:
    // shape to paint
    QPainterPath shape() const override;

    // update model when graphic is moved
    QVariant itemChange(GraphicsItemChange change,
                       const QVariant &value) override;

 private:
    QPen pen_;
    QBrush brush_;

    // size of drone
    qreal size_;

    // for compute thread setting infeasible
    QMutex mutex_;
    bool is_feasible_;

    qreal getScalingFactor() const;
};

}  // namespace optgui

#endif  // DRONE_GRAPHICS_ITEM_H_
