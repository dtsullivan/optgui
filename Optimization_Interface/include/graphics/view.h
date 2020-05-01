// TITLE:   Optimization_Interface/include/graphics/view.h
// AUTHORS: Daniel Sullivan, Miki Szmuk
// LAB:     Autonomous Controls Lab (ACL)
// LICENSE: Copyright 2018, All Rights Reserved

// Renders graphical representations of constraints and controls

#ifndef VIEW_H_
#define VIEW_H_

#include <QGraphicsView>
#include <QToolButton>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QTableWidget>
#include <QHeaderView>
#include <QGestureEvent>
#include <QDoubleSpinBox>

#include "algorithm.h"

#include "include/graphics/canvas.h"
#include "include/window/menu_panel.h"
#include "include/globals.h"
#include "include/controls/controller.h"

namespace optgui {

const qreal DOT_SIZE = 14;

class View : public QGraphicsView {
    Q_OBJECT

 public:
    explicit View(QWidget *parent);
    ~View();

 protected:
    bool viewportEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

 private slots:
    void openMenu();
    void closeMenu();
    void openExpertMenu();
    void closeExpertMenu();
    void setZoom(qreal value);
    void setState(STATE button_type);
    void setPorts();
    void execute();
    void stageTraj();
    void unstageTraj();
    void setSkyeFlyParams();
    void setFinaltime(qreal final_time);
    void duplicateSelected();
    void setClearance(qreal clearance);
    void constrainWpIdx(int value);
    void constrainAccel();
    void setFeedbackMessage(int code);
  private:
    void initialize();
    void initializeMenuPanel();
    void initializeExpertPanel();
    void clearMarkers();
    void expandView();
    bool pinchZoom(QGestureEvent *event);
    qreal currentStepScaleFactor_;  // pinch zoom factor
    qreal initialZoom_;  // initial scale factor at beginning of pinch
    Controller *controller_;
    QToolButton *menu_button_;
    MenuPanel *menu_panel_;
    QLabel *user_msg_label_;
    QToolButton *expert_menu_button_;
    MenuPanel *expert_panel_;
    STATE state_;
    Canvas *canvas_;
    QVector<QGraphicsItem*> *temp_markers_;
    QPen dot_pen_;
    QBrush dot_brush_;
    QTableWidget *skyefly_params_table_;
    quint32 a_min_row;
    quint32 a_max_row;
    quint32 wp_idx_row;
    QTableWidget *model_params_table_;

    // keep track of all widgets to delete them
    QVector<QWidget *> panel_widgets_;
    QDoubleSpinBox *zoom_slider_;
    // keep track of all toggle buttons to set them to toggled
    // or untoggled
    QVector<MenuButton *> toggle_buttons_;

    FEEDBACK_CODE user_feedback_code_;
    QMutex user_feedback_lock_;

    // Create buttons for menu panels
    void initializeMessageBox(MenuPanel *panel);
    void initializeZoom(MenuPanel *panel);
    void initializeWaypointButton(MenuPanel *panel);
    void initializeEraserButton(MenuPanel *panel);
    void initializePlaneButton(MenuPanel *panel);
    void initializePolygonButton(MenuPanel *panel);
    void initializeFinalPointButton(MenuPanel *panel);
    void initializeEllipseButton(MenuPanel *panel);
    void initializeFlipButton(MenuPanel *panel);
    void initializeExecButton(MenuPanel *panel);
    void initializeStageButton(MenuPanel *panel);
    void initializeFinaltime(MenuPanel *panel);
    void initializeDuplicateButton(MenuPanel *panel);
    // expert panel skyefly params
    void initializeSkyeFlyParamsTable(MenuPanel *panel);
    // expert panel constraint_model params not in skyefly
    void initializeModelParamsTable(MenuPanel *panel);

    bool isObstaclesOverlap(EllipseGraphicsItem* ellipse);
    void checkValidObstacles(EllipseGraphicsItem *ellipse);
};

}  // namespace optgui

#endif  // VIEW_H_
