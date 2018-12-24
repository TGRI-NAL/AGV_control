#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QScrollBar>
#include <QPointF>
#include <QPoint>
#include <QPainter>
#include <QtMath>
#include <QQuaternion>
#include <QMouseEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QPointer>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QWheelEvent>
#include <QImageReader>
#include <QMatrix>
#include <QFileDialog>
#include <QUndoStack>
#include <QUndoCommand>
#include <QAction>
#include <QInputDialog>
#include <QProgressDialog>
#include <QMenu>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTableWidgetItem>
#include <QPalette>
#include <QThread>
#include <QSettings>

#include "navimarkeritem.h"
#include "teachgoaldialog.h"
#include "listdialog.h"
#include "goaleditdialog.h"
#include "externalcommdialog.h"

enum MODE_TYPE {SLAM = 50, NAVI, TEACHPOINT, EDITMAP, XROCKER, RESETNODE, RESTARTAGV, SHUTDOWNAGV};
enum ACTION_TYPE {NAVIGOAL = 60, DELAYACTION, EXTERNALCOMACTION, NOACTION};
enum NAVIMODE_TYPE {Normal = 100, SetInitPose, AddGoal, EditGoal, StartAction};
enum NAVISTATE {Null = 110, Pending, Active, Preempted, Succeeded, Aborted
                , Rejected, Preempting, Recalling, Recalled, Lost};
enum EDITMAP_TYPE {NoType = 130, Occupancy, Unoccupancy, Unknown};
enum EDITMAP_TOOL {NoTool = 140, Pen, Line, Rectangle, Ellipse};

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:

    struct Map {
        QString mapName;
        QPixmap mapPixmap;
        float width = 0;
        float height = 0;
        float resolution = 0;
        QPointF originPosition;
        QQuaternion originOrientation;
    };

    struct Tf {
        QPointF odomPosition;
        QPointF footprintPosition;
        QPointF robotPosition;
        QQuaternion odomOrientation;
        QQuaternion footprintOrientation;
        QQuaternion robotOrientation;
        float yawEulerAngles;
        float covariance[5];
        QPoint redPoint;
    };

    struct ActionItem {
        ACTION_TYPE type;
        int order;
        QString remark;
        QPointF point;
        QQuaternion quat;
        NaviMarkerItem *marker;
        float disTolerance = 0.0;
        float angleTolerance = 0.0;
        float reachTolerance = 0.0;
        int delayMs;
        QList<float> valueList;
    };

    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    MODE_TYPE mode;
    NAVIMODE_TYPE naviMode;
    NAVISTATE naviState;
    VEL_TYPE velType;

private slots:
    void tcpConnectStateChange();
    void readData();
    void on_connectBtn_clicked();
    void on_zoomOutBtn_clicked();
    void on_zoomInBtn_clicked();
    void on_modeCB_currentIndexChanged(const QString &arg1);
    void on_initPoseBtn_toggled(bool checked);
    void on_saveMapBtn_clicked();
    void on_listMapBtn_clicked();
    void on_addGoalBtn_toggled(bool checked);
    void on_clearGoalBtn_clicked();
    void on_actionListWidget_itemSelectionChanged();
    void on_deleteGoalBtn_clicked();
    void on_teachGoalBtn_clicked();
    void on_actionBtn_clicked();
    void on_loadMap4EditBtn_clicked();
    void on_widthSlider_valueChanged(int value);
    void on_occupancyBtn_toggled(bool checked);
    void on_unoccupancyBtn_toggled(bool checked);
    void on_unknownBtn_toggled(bool checked);
    void on_saveBtn_clicked();
    void on_redoBtn_clicked();
    void on_undoBtn_clicked();
    void on_rectShapeBtn_toggled(bool checked);
    void on_lineShapeBtn_toggled(bool checked);
    void on_ellipseShapeBtn_toggled(bool checked);
    void on_penBtn_toggled(bool checked);
    void on_hollowCheckBox_stateChanged(int arg1);
    void on_actionListWidget_customContextMenuRequested(const QPoint &pos);
    void on_actionListWidget_itemDoubleClicked(QListWidgetItem *item);
    bool on_writeScriptBtn_clicked();
    void on_readScriptBtn_clicked();
    void on_startScriptBtn_clicked();
    void on_stopScriptBtn_clicked();
    void on_resetStatusBtn_clicked();
    void on_shutdownBtn_clicked();
    void on_rebootBtn_clicked();
    void on_poseUpdateBtn_clicked();
    void on_xrockerJoystickBtn_clicked();
    void on_mappingJoystickBtn_clicked();

public slots:
    void updateMarkerValue(int, QPointF, float);
    void updateGoalValue(int, QPointF, float, float, float, float, QString);
    void updateVel(VEL_TYPE);
    void updateVelPercentage(int);
    void cloneGoal(int, QPointF, float, float, float, float, QString);
    void updateMarkerEditStatus(EDIT_STATUS);
    void actionListMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
    void addTeachGoal(QPointF, QQuaternion, bool);
    void loadMapByService(QString);
    void loadScript(QString);
    void onPublishEditedMap(QImage, QString);
    void teachGoalDestroyed();
    void changeSemicircleSide(bool);
    void startFromActionList();
    void goOrigin();
    void poseUpdate();
    void abortMovebase();
    void setTeleopMode(TELEOP_TYPE);
    void setKeyPriorityFlag(bool);
    void updateProgressDialog(int);
    void deleteMap(QString);
    void deleteScript(QString);
    void externalComm(EXTERNAL_TYPE, int, int, int);

private:
    Ui::MyWidget *ui;
    QTcpSocket *tcpSocket;
    int port;
    QHostAddress *serverIP;
    QByteArray allData;
    int naviGoalid = 0;
    int multiGoalNaviStep = 0;
    float velPercentage;
    int velSliderValue;
    int mapTimerInterval;
    int mapTimerTimes;
    Map m_map;
    Tf m_tf;
    QSize scaleSize;
    double scaleFactor;
    double preFactor;
    QTimer *mapServiceTimer;
    QGraphicsScene *mapScene;
    QGraphicsPixmapItem *mapPixmapItem;
    QGraphicsPixmapItem *robotPixmapItem;
    QGraphicsLineItem *naviDirLine;
    QList<ActionItem*> actionList;
    QTimer *velCmdTimer;
    QTimer *progressTimer;
    QTimer *enableUiTimer;
    QString mapNameReg;
    QImage mapImg;
    ListDialog *listDlg;
    QProgressDialog *progressDlg;
    int progressValue;
    bool isLeftSide = true;
    int Rstate;
    ACTION_TYPE currentAction;
    MODE_TYPE modeBeforeTeach;
    TELEOP_TYPE teleopMode;
    bool loadStaticMapFlag;
    QString readScriptName;
    QJsonArray scriptActionJsonAry;
    bool readScriptActionJsonAryFlag;
    bool keyPriorityFlag;
    float defaultDisTolerance;
    float defaultAngleTolerance;

    void parseMapJsonData(QByteArray data);
    void parseMapServiceJsonData(QByteArray data);
    void parseTfJsonData(QByteArray data);
    void parseAmclPoseJsonData(QByteArray data);
    void parseMovebaseStatusJsonData(QByteArray data);
    void parseSaveMapServiceResponseJsonData(QByteArray data);
    void parseListMapServiceResponseJsonData(QByteArray data);
    void parseRstate(QByteArray data);
    void parseListScriptServiceResponseJsonData(QByteArray data);
    void parseReplyScript(QByteArray data);
    void parseFeedbackMsg(QByteArray data);
    void parseSensorButtonCmdVel(QByteArray data);
    void writeSettings();
    void readSettings();
    void updateMapImg();
    void updateEditMapImg();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void handleMapServiceTimeout();
    void handleEnableUiTimeout();
    void handleVelCmdTimeout();
    void updateActionListWidget();
    void changeCursor();
    void resetMapView();
    void setProgressDialog();
    void handleProgressTimeout();
    void enableUi(bool);
    void readScriptActionJsonAry(QJsonArray);

    QUndoStack *undoStack;
    QAction *undoAction;
    QAction *redoAction;
    QList<QGraphicsItem *> onceAddItemList;
    int myPointDiameter;
    QColor myPenColor;
    bool isHollow;
    EDITMAP_TYPE editMapType;
    EDITMAP_TOOL editMapTool;
    bool isEditing;
    bool startEditing;
    bool isTransactionsMap;
    QPointF lastPoint;
    QGraphicsLineItem *tempLineItem;
    QGraphicsRectItem *tempRectItem;
    QGraphicsEllipseItem *tempEllipseItem;

    void initMapEditActions();
    void drawLineTo(const QPointF &endPoint);
    void setCustomCursor(int diameter, QColor color);
    void saveEditedMap(QString);

    //Advertise
    void onAdvertiseCmdVel();
    void onAdvertiseRobotModeFlag();
    void onAdvertiseActionScript();
    void onAdvertiseAskScript();
    void onAdvertiseActionCommand();
    void onAdvertiseKeyPriority();

    //Unadvertise
    void onUnadvertiseRobotModeFlag();

    //publish
    void onPublishVelCmd();
    void onPublishInitPose(bool, QPoint, QQuaternion);
    void onPublishRobotModeFlag(MODE_TYPE);
    void onPublishActionScript();
    void onPublishAskScript(QString);
    void onPublishActionCommand(int, QString, int);
    void onPublishPeripheralCmd(int);
    void onPublishKeyPriority(bool);

    //subscribe
    void onSubscribeMap();
    void onSubscribeTf();
    void onSubscribeAmclPose();
    void onSubscribeMovebaseStatus();
    void onSubscribeRstate(int);
    void onSubscribeReplyScript();
    void onSubscribeFeedbackMsg();
    void onSubscribeSensorButtonCmdVel();

    //unsubscribe
    void onUnsubscribeMap();
    void onUnsubscribeTf();
    void onUnsubscribeAmclPose();
    void onUnsubscribeMovebaseStatus();
    void onUnsubscribeRstate();
    void onUnsubscribeReplyScript();
    void onUnsubscribeFeedbackMsg();
    void onUnsubscribeSensorButtonCmdVel();

    //service
    void onCallServiceStaticMap();
    void onCallServiceSaveMap();
    void onCallServiceLoadMap(QString);
    void onCallServiceListMap();
    void onCallServiceDeleteMap(QString);
    void onCallServiceSaveEditedMap(QString);
    void onCallServiceListScript();
    void onCallServiceDeleteScript(QString);
    void onCallServiceUpdatePose();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void updateAmclPose2TeachDlg(QPointF, QQuaternion);
    void updateNaviMarkerEditable(bool);
};

class EditMapStack : public QUndoCommand
{
public:
    EditMapStack(QList<QGraphicsItem *>, QGraphicsScene *graphicsScene, QUndoCommand *parent = 0);
    ~EditMapStack();

    void undo() override;
    void redo() override;

private:
    QGraphicsScene *myGraphicsScene;
    QList<QGraphicsItem *> newItmeList;
};

#endif // MYWIDGET_H
