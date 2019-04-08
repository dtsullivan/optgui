// TITLE:   Optimization_Interface/globals.h
// AUTHORS: Daniel Sullivan, Miki Szmuk
// LAB:     Autonomous Controls Lab (ACL)
// LICENSE: Copyright 2018, All Rights Reserved

// Global constants

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <QGraphicsItem>

namespace interface {
    enum STATE {
        IDLE,
        ERASER,
        FLIP,
        ELLIPSE,
        POLYGON,
        PLANE,
        WAYPOINT,
        EXEC
    };

    enum GRAPHICS_TYPE {
        ELLIPSE_GRAPHIC = QGraphicsItem::UserType + 1,
        POLYGON_GRAPHIC = QGraphicsItem::UserType + 2,
        PLANE_GRAPHIC = QGraphicsItem::UserType + 3,
        WAYPOINTS_GRAPHIC = QGraphicsItem::UserType + 4,
        HANDLE_GRAPHIC = QGraphicsItem::UserType + 5,
    };
}  // namespace interface

#endif  // GLOBALS_H_