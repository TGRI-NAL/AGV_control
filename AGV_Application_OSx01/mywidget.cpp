#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget),
    scaleFactor(1.0),
    preFactor(1.0),
    scaleSize(0, 0),
    mode(MODE_TYPE::SLAM),
    naviMode(NAVIMODE_TYPE::Normal),
    naviState(NAVISTATE::Null),
    velType(VEL_TYPE::Stop),
    velPercentage(25),
    velSliderValue(1),
    mapTimerInterval(1000),
    mapTimerTimes(5),
    myPointDiameter(1),
    myPenColor(Qt::black),
    progressValue(1),
    Rstate(-1),
    isTransactionsMap(false),
    isHollow(false),
    isEditing(false),
    editMapType(EDITMAP_TYPE::NoType),
    editMapTool(EDITMAP_TOOL::NoTool),
    currentAction(ACTION_TYPE::NOACTION),
    teleopMode(TELEOP_TYPE::LINEAR),
    loadStaticMapFlag(false),
    readScriptActionJsonAryFlag(false),
    keyPriorityFlag(true)
{
    ui->setupUi(this);

    mapScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(mapScene);
    ui->graphicsView->show();
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    mapScene->installEventFilter(this);

    ui->actionListWidget->installEventFilter(this);

    mapPixmapItem = new QGraphicsPixmapItem;
    robotPixmapItem = new QGraphicsPixmapItem;
    robotPixmapItem->setPixmap(QPixmap("robot5x5.bmp"));

    naviDirLine = new QGraphicsLineItem;
    naviDirLine->setPen(QPen(Qt::red, 3));

    mapServiceTimer = new QTimer;
    mapServiceTimer->setInterval(mapTimerInterval);
    connect(mapServiceTimer, &QTimer::timeout, this, &MyWidget::handleMapServiceTimeout);

    enableUiTimer = new QTimer;
    enableUiTimer->setInterval(7000);
    connect(enableUiTimer, &QTimer::timeout, this, &MyWidget::handleEnableUiTimeout);

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::stateChanged, this, &MyWidget::tcpConnectStateChange);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MyWidget::readData);
    tcpConnectStateChange();

    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->actionListWidget->model(), &QAbstractItemModel::rowsMoved, this, &MyWidget::actionListMoved);

    velCmdTimer = new QTimer;
    velCmdTimer->setInterval(200);
    connect(velCmdTimer, &QTimer::timeout, this, &MyWidget::handleVelCmdTimeout);

    ui->deleteGoalBtn->setEnabled(false);
    listDlg = new ListDialog;
    connect(listDlg, &ListDialog::loadMap, this, &MyWidget::loadMapByService);
    connect(listDlg, &ListDialog::loadScript, this, &MyWidget::loadScript);
    connect(listDlg, &ListDialog::deleteMap, this, &MyWidget::deleteMap);
    connect(listDlg, &ListDialog::deleteScript, this, &MyWidget::deleteScript);

    initMapEditActions();

    progressTimer = new QTimer;
    progressTimer->setInterval(100);
    connect(progressTimer, &QTimer::timeout, this, &MyWidget::handleProgressTimeout);

    tempLineItem = new QGraphicsLineItem;
    tempRectItem = new QGraphicsRectItem;
    tempEllipseItem = new QGraphicsEllipseItem;

    readSettings();
}

MyWidget::~MyWidget()
{
    writeSettings();
    on_clearGoalBtn_clicked();
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        onUnsubscribeMap();
        onUnsubscribeTf();
        onUnsubscribeAmclPose();
        onUnsubscribeMovebaseStatus();
        onUnadvertiseRobotModeFlag();
        onUnsubscribeRstate();

        tcpSocket->disconnectFromHost();
    }

    delete mapServiceTimer;
    delete velCmdTimer;
    delete progressTimer;
    delete enableUiTimer;
    delete listDlg;
    delete mapPixmapItem;
    delete robotPixmapItem;
    delete tempLineItem;
    delete tempRectItem;
    delete tempEllipseItem;
    delete naviDirLine;
    delete mapScene;
    delete tcpSocket;
    delete ui;
}

void MyWidget::enableUi(bool flag)
{
    ui->naviPage->setEnabled(flag);
    ui->mappingPage->setEnabled(flag);
    ui->xrockerPage->setEnabled(flag);
    ui->mapEditPage->setEnabled(flag);
    ui->networkLayout->setEnabled(flag);
    ui->connectBtn->setEnabled(flag);
    ui->ipEdit->setEnabled(flag);
    ui->portEdit->setEnabled(flag);
    ui->modeCB->setEnabled(flag);
    ui->zoomInBtn->setEnabled(flag);
    ui->zoomOutBtn->setEnabled(flag);
    ui->initPoseBtn->setEnabled(flag);
    ui->resetStatusBtn->setEnabled(flag);
    ui->rebootBtn->setEnabled(flag);
    ui->shutdownBtn->setEnabled(flag);
}

void MyWidget::readScriptActionJsonAry(QJsonArray actionJsonAry)
{
    for(int i=0; i< actionJsonAry.size(); i++){
        QJsonObject actionItemJson = actionJsonAry.at(i).toObject();
        int type = actionItemJson.take("actionType").toInt();
        QJsonArray paraJsonAry = actionItemJson.take("para").toArray();
        int order = i;
        if(type == 1){
            QPointF point;
            QQuaternion quat;
            quat.setX(0.0);
            quat.setY(0.0);
            float disTolerance = 0.0, angleTolerance = 0.0, reachTolerance = 0.0;
            int searchTagId = -1;
            for(int j=0; j<paraJsonAry.size(); j++){
                switch (j) {
                case 0:
                    point.setX(paraJsonAry.at(j).toDouble());
                    break;
                case 1:
                    point.setY(paraJsonAry.at(j).toDouble());
                    break;
                case 2:
                    quat.setZ(paraJsonAry.at(j).toDouble());
                    break;
                case 3:
                    quat.setScalar(paraJsonAry.at(j).toDouble());
                    break;
                case 4:
                    disTolerance = paraJsonAry.at(j).toDouble();
                    break;
                case 5:
                    angleTolerance = paraJsonAry.at(j).toDouble();
                    break;
                case 6:
                    reachTolerance = paraJsonAry.at(j).toDouble();
                    break;
                case 7:
                    searchTagId = (int)paraJsonAry.at(j).toDouble();
                    break;
                default:
                    break;
                }
            }

            int xPos = scaleFactor*((point.x() - m_map.originPosition.x() ) / m_map.resolution + 0.5);
            int yPos = scaleFactor*((point.y() - m_map.originPosition.y() ) / m_map.resolution + 0.5);

            ActionItem *action = new ActionItem;
            action->type = ACTION_TYPE::NAVIGOAL;
            action->order = order;
            action->point.setX(point.x());
            action->point.setY(point.y());
            action->quat = quat;
            action->disTolerance = disTolerance;
            action->angleTolerance = angleTolerance;
            action->reachTolerance = reachTolerance;
            NaviMarkerItem *markerItem = new NaviMarkerItem(order);
            markerItem->setPos(xPos, yPos);
            markerItem->setScale(scaleFactor/2);
            markerItem->theta = qDegreesToRadians(quat.toEulerAngles().z());
            action->marker = markerItem;
            mapScene->addItem(action->marker);
            actionList.append(action);
            connect(markerItem, &NaviMarkerItem::updateMarkerValue, this, &MyWidget::updateMarkerValue);
            connect(markerItem, &NaviMarkerItem::updateMarkerEditStatus, this, &MyWidget::updateMarkerEditStatus);
            connect(this, &MyWidget::updateNaviMarkerEditable, markerItem, &NaviMarkerItem::updateNaviMarkerEditable);
        }
        else if(type == 4){
            int delay = (int)paraJsonAry.first().toDouble();
            ActionItem *action = new ActionItem;
            action->type = ACTION_TYPE::DELAYACTION;
            action->order = order;
            action->delayMs = delay;
            actionList.append(action);
        }
        else if(type == 10){
            ActionItem *action = new ActionItem;
            action->type = ACTION_TYPE::EXTERNALCOMACTION;
            action->order = order;
            action->valueList.append((float)paraJsonAry.at(0).toDouble());
            action->valueList.append((float)paraJsonAry.at(1).toDouble());
            actionList.append(action);
        }
    }

    updateActionListWidget();
    updateMapImg();
    ui->actionListWidget->setCurrentRow(0);

    ui->scriptNameLineEdit->setText(readScriptName);

    QMessageBox *mbox = new QMessageBox;
    mbox->setAttribute(Qt::WA_DeleteOnClose);
    mbox->setIcon(QMessageBox::Information);
    mbox->setWindowTitle("OK");
    mbox->setText(QString(tr("Load <%1> script from robot OK !")).arg(readScriptName));
    mbox->show();
    QTimer::singleShot(2000, mbox, SLOT(close()));

    QThread::msleep(300);

    onSubscribeRstate(1000);
    onSubscribeAmclPose();
    onSubscribeMovebaseStatus();
    onSubscribeFeedbackMsg();

    ui->actionListWidget->setCurrentRow(-1);
}

void MyWidget::tcpConnectStateChange()
{
    if(tcpSocket->state() == QAbstractSocket::UnconnectedState){
        tcpSocket->flush();
        ui->connectBtn->setText("Disconnected");
        ui->connectBtn->setStyleSheet("background-color: rgb(255, 0, 0);");
        enableUi(true);
    }
    else if(tcpSocket->state() == QAbstractSocket::ConnectedState){

        ui->connectBtn->setText("Connected");
        ui->connectBtn->setStyleSheet("background-color: rgb(0, 200, 0);");
        enableUi(false);
        enableUiTimer->setInterval(10000);
        enableUiTimer->start();

        onSubscribeRstate(1000);

        onAdvertiseCmdVel();
        onAdvertiseActionScript();
        onAdvertiseAskScript();
        onAdvertiseActionCommand();
        onAdvertiseKeyPriority();

        if(ui->modeCB->currentText() == "Mapping"){
            onUnsubscribeAmclPose();
            onUnsubscribeMovebaseStatus();

            mapServiceTimer->stop();

            onSubscribeTf();
            onSubscribeMap();

            onPublishRobotModeFlag(MODE_TYPE::SLAM);
            ui->zoomInBtn->setEnabled(true);
            ui->zoomOutBtn->setEnabled(true);
        }
        else if(ui->modeCB->currentText() == "Navigation"){
            onUnsubscribeTf();
            onUnsubscribeMap();

            onSubscribeAmclPose();
            onSubscribeMovebaseStatus();
            onSubscribeReplyScript();
            onSubscribeFeedbackMsg();

            onPublishRobotModeFlag(MODE_TYPE::NAVI);
        }
        else if(ui->modeCB->currentText() == "Map Editing"){
            onUnsubscribeTf();
            onUnsubscribeMap();
            onUnsubscribeAmclPose();
            onUnsubscribeMovebaseStatus();

            mapServiceTimer->stop();
            onPublishRobotModeFlag(MODE_TYPE::EDITMAP);
        }
        else if(ui->modeCB->currentText() == "XBOX360-Joystick"){
            onUnsubscribeTf();
            onUnsubscribeMap();
            onUnsubscribeAmclPose();
            onUnsubscribeMovebaseStatus();

            mapServiceTimer->stop();
            onPublishRobotModeFlag(MODE_TYPE::XROCKER);
        }
    }
}

void MyWidget::writeSettings()
{
    QSettings settings;
    settings.beginGroup("MyWidget");
    settings.setValue("size", this->size());
    settings.setValue("pos", this->pos());
    settings.setValue("fullScreen", this->isFullScreen());
    settings.setValue("ip", ui->ipEdit->text());
    settings.setValue("port", ui->portEdit->text());
    settings.setValue("mode", ui->modeCB->currentIndex());
    settings.setValue("teleopMode", teleopMode);
    defaultDisTolerance = ui->disToleranceDSB->value();
    defaultAngleTolerance = ui->angleToleranceDSB->value();
    settings.setValue("defaultDisTolerance", defaultDisTolerance);
    settings.setValue("defaultAngleTolerance", defaultAngleTolerance);
    settings.endGroup();
}

void MyWidget::readSettings()
{
    QSettings settings;
    settings.beginGroup("MyWidget");
    this->resize(settings.value("size").toSize());
    this->move(settings.value("pos").toPoint());
    if(settings.value("fullScreen").toBool()){
        this->setWindowState(Qt::WindowFullScreen);
        this->showFullScreen();
    }
    if(settings.value("ip").toString().isEmpty())
        ui->ipEdit->setText("192.168.0.1");
    else
        ui->ipEdit->setText(settings.value("ip").toString());
    if(settings.value("port").toString().isEmpty())
        ui->portEdit->setText("9090");
    else
        ui->portEdit->setText(settings.value("port").toString());
    ui->modeCB->setCurrentIndex(settings.value("mode").toInt());
    teleopMode = (TELEOP_TYPE)settings.value("teleopMode").toInt();
    defaultDisTolerance = settings.value("defaultDisTolerance").toFloat();
    ui->disToleranceDSB->setValue(defaultDisTolerance);
    defaultAngleTolerance = settings.value("defaultAngleTolerance").toFloat();
    ui->angleToleranceDSB->setValue(defaultAngleTolerance);
    settings.endGroup();
}

void MyWidget::on_connectBtn_clicked()
{
    ui->startScriptBtn->setText("Start");
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        bool ok;
        tcpSocket->connectToHost(ui->ipEdit->text(), ui->portEdit->text().toInt(&ok, 10));
    }
    else{
        mapServiceTimer->stop();
        onUnsubscribeRstate();
        onUnsubscribeMap();
        onUnsubscribeTf();
        onUnsubscribeAmclPose();
        onUnsubscribeMovebaseStatus();
        tcpSocket->disconnectFromHost();
    }
}

void MyWidget::on_zoomOutBtn_clicked()
{
    if(!m_map.mapPixmap.isNull())
        if(scaleFactor > 0.5)
            scaleImage(1.0/1.2);
}

void MyWidget::on_zoomInBtn_clicked()
{
    if(!m_map.mapPixmap.isNull())
        if(scaleFactor < 7.0 )
            scaleImage(1.2);
}

void MyWidget::on_modeCB_currentIndexChanged(const QString &arg1)
{
    if(!m_map.mapPixmap.isNull()){
        on_clearGoalBtn_clicked();
        resetMapView();
    }

    ui->mainHorizontalLayout->setStretch(1, 2);
    if(arg1 == "Mapping"){
        ui->stackedWidget->setCurrentIndex(0);
        tcpConnectStateChange();
        mapNameReg = "";
    }
    else if(arg1 == "Navigation"){
        ui->loadMapNameLineEdit->setText("");
        ui->scriptNameLineEdit->setText("");
        ui->statusLineEdit->setText("Null");
        ui->stackedWidget->setCurrentIndex(1);
        tcpConnectStateChange();
    }
    else if(arg1 == "Map Editing"){
        ui->loadMapName4EditLineEdit->setText("");
        ui->stackedWidget->setCurrentIndex(2);
        tcpConnectStateChange();
    }
    else if(arg1 == "XBOX360-Joystick"){
        ui->stackedWidget->setCurrentIndex(3);
        tcpConnectStateChange();
    }
    else
        ui->modeCB->setCurrentIndex(1);

    on_clearGoalBtn_clicked();
    ui->actionListWidget->setCurrentRow(-1);
}

void MyWidget::on_saveMapBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    if(ui->mapNameLineEdit->text().isEmpty()){
        QMessageBox mb;
        mb.setStyleSheet("");
        mb.setIcon(QMessageBox::Warning);
        mb.setWindowTitle("Error");
        mb.setText(tr("Empty map name!"));
        mb.exec();
    }
    else
        onCallServiceSaveMap();
}

void MyWidget::on_listMapBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;

    listDlg->clearList();
    listDlg->setListType(LIST_TYPE::LISTMAP);
    listDlg->show();
    onCallServiceListMap();
}

void MyWidget::on_initPoseBtn_toggled(bool checked)
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        ui->initPoseBtn->setChecked(false);
        naviMode = NAVIMODE_TYPE::Normal;
        changeCursor();
        return;
    }
    if(checked){
        ui->addGoalBtn->setChecked(false);
        naviMode = NAVIMODE_TYPE::SetInitPose;
        emit updateNaviMarkerEditable(false);
    }
    else{
        naviMode = NAVIMODE_TYPE::Normal;
        emit updateNaviMarkerEditable(true);
    }
    changeCursor();
}

void MyWidget::on_addGoalBtn_toggled(bool checked)
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState){
        ui->addGoalBtn->setChecked(false);
        naviMode = NAVIMODE_TYPE::Normal;
        changeCursor();
        return;
    }

    if(checked){
        ui->initPoseBtn->setChecked(false);
        naviMode = NAVIMODE_TYPE::AddGoal;
        ui->actionListWidget->setCurrentRow(-1);
        emit updateNaviMarkerEditable(false);
    }
    else{
        naviMode = NAVIMODE_TYPE::Normal;
        emit updateNaviMarkerEditable(true);
    }
    changeCursor();
}

void MyWidget::on_teachGoalBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;

    modeBeforeTeach = MODE_TYPE::NAVI;
    mode = MODE_TYPE::TEACHPOINT;
    keyPriorityFlag = true;
    TeachGoalDialog *dlg;
    if(ui->actionListWidget->currentRow() == -1)
        dlg = new TeachGoalDialog(velSliderValue, teleopMode, false);
    else
        dlg = new TeachGoalDialog(velSliderValue, teleopMode, true);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModal(true);
    dlg->setJoystickLevel(2);
    onPublishKeyPriority(false);
    onSubscribeSensorButtonCmdVel();
    connect(dlg, &TeachGoalDialog::updateVel, this, &MyWidget::updateVel);
    connect(dlg, &TeachGoalDialog::updateVelPercentage, this, &MyWidget::updateVelPercentage);
    connect(dlg, &TeachGoalDialog::addTeachGoal, this, &MyWidget::addTeachGoal);
    connect(dlg, &TeachGoalDialog::destroyed, this, &MyWidget::teachGoalDestroyed);
    connect(dlg, &TeachGoalDialog::goOrigin, this, &MyWidget::goOrigin);
    connect(dlg, &TeachGoalDialog::poseUpdate, this, &MyWidget::poseUpdate);
    connect(dlg, &TeachGoalDialog::abortMovebase, this, &MyWidget::abortMovebase);
    connect(dlg, &TeachGoalDialog::setTeleopMode, this, &MyWidget::setTeleopMode);
    connect(dlg, &TeachGoalDialog::setKeyPriorityFlag, this, &MyWidget::setKeyPriorityFlag);
    connect(this, &MyWidget::updateAmclPose2TeachDlg, dlg, &TeachGoalDialog::updateAmclPoseValue);
    dlg->move(this->pos().x()+this->size().width()/2-dlg->size().width()/2, this->pos().y()+this->size().height()/2-dlg->size().height()/2);
    dlg->show();
}

void MyWidget::on_actionBtn_clicked()
{
    externalCommDialog *dlg = new externalCommDialog();
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModal(true);
    dlg->move(this->pos().x()+this->size().width()/2-dlg->size().width()/2, this->pos().y()+this->size().height()/2-dlg->size().height()/2);
    connect(dlg, &externalCommDialog::externalComm, this, &MyWidget::externalComm);
    dlg->show();
}

void MyWidget::on_deleteGoalBtn_clicked()
{
    if(ui->actionListWidget->currentRow() != -1){
        for(int i=0; i<actionList.count(); i++){
            if(actionList.at(i)->order == ui->actionListWidget->currentRow()){
                if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
                    NaviMarkerItem *marker = actionList.at(i)->marker;
                    if(mapScene->items().contains(marker))
                        mapScene->removeItem(marker);
                    delete marker;
                    actionList.removeOne(actionList.at(i));
                    break;
                }
                else{
                    actionList.removeOne(actionList.at(i));
                }
            }
        }
        for(int i=0; i<actionList.count(); i++)
            if(actionList.at(i)->order > ui->actionListWidget->currentRow())
                actionList.at(i)->order--;
        ui->actionListWidget->setCurrentRow(-1);
        updateActionListWidget();
        updateMapImg();
    }
}

void MyWidget::on_clearGoalBtn_clicked()
{
    for(int i=0; i<actionList.count(); i++){
        if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
            NaviMarkerItem *marker = actionList.at(i)->marker;
            if(mapScene->items().contains(marker))
                mapScene->removeItem(marker);
            delete marker;
        }
    }

    qDeleteAll(actionList);
    actionList.clear();
    ui->actionListWidget->clear();
    updateMapImg();
}

void MyWidget::on_loadMap4EditBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    listDlg->clearList();
    listDlg->setListType(LIST_TYPE::LISTMAP);
    listDlg->show();
    onCallServiceListMap();
}

void MyWidget::on_redoBtn_clicked()
{
    redoAction->trigger();
}

void MyWidget::on_undoBtn_clicked()
{
    undoAction->trigger();
}

void MyWidget::on_actionListWidget_itemSelectionChanged()
{
    if(ui->actionListWidget->currentRow() != -1 && naviMode != NAVIMODE_TYPE::StartAction)
        ui->deleteGoalBtn->setEnabled(true);
    else
        ui->deleteGoalBtn->setEnabled(false);

    bool isGoalSelected = false;
    for(int i=0; i<actionList.count(); i++)
        if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
            if(actionList.at(i)->order == ui->actionListWidget->currentRow()){
                actionList.at(i)->marker->isFocus = true;
                isGoalSelected = true;
            }
            else
                actionList.at(i)->marker->isFocus = false;
        }
    if(isGoalSelected){
        for(int i=0; i<actionList.count(); i++)
            if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL)
                actionList.at(i)->marker->isOneGoalSelected = true;
    }
    else
        for(int i=0; i<actionList.count(); i++)
            if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL)
                actionList.at(i)->marker->isOneGoalSelected = false;
    updateMapImg();
}

void MyWidget::on_actionListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    for(int i=0; i<actionList.count(); i++){
        if(actionList.at(i)->order == ui->actionListWidget->currentRow()){
            switch (actionList.at(i)->type) {
            case ACTION_TYPE::NAVIGOAL:{
                goalEditDialog *goalEditDlg = new goalEditDialog(actionList.at(i)->marker->order, actionList.at(i)->point, actionList.at(i)->quat,
                                                                 actionList.at(i)->disTolerance, actionList.at(i)->angleTolerance, actionList.at(i)->reachTolerance, actionList.at(i)->remark);
                goalEditDlg->setMapInfo(m_map.resolution, m_map.width, m_map.height, m_map.originPosition.x(), m_map.originPosition.y());
                goalEditDlg->setAttribute(Qt::WA_DeleteOnClose);
                goalEditDlg->setModal(true);
                connect(goalEditDlg, &goalEditDialog::updateGoalValue, this, &MyWidget::updateGoalValue);
                connect(goalEditDlg, &goalEditDialog::cloneGoal, this, &MyWidget::cloneGoal);
                goalEditDlg->move(this->pos().x()+this->size().width()/2-goalEditDlg->size().width()/2, this->pos().y()+this->size().height()/2-goalEditDlg->size().height()/2);
                goalEditDlg->show();
                break;
            }
            case ACTION_TYPE::DELAYACTION:{
                externalCommDialog *dlg = new externalCommDialog(EXTERNAL_TYPE::DELAYMS, actionList.at(i)->order, 0, actionList.at(i)->delayMs);
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                dlg->setModal(true);
                dlg->move(this->pos().x()+this->size().width()/2-dlg->size().width()/2, this->pos().y()+this->size().height()/2-dlg->size().height()/2);
                connect(dlg, &externalCommDialog::externalComm, this, &MyWidget::externalComm);
                dlg->show();
                break;
            }
            case ACTION_TYPE::EXTERNALCOMACTION:{
                externalCommDialog *dlg = new externalCommDialog(EXTERNAL_TYPE::EXTERNALCOMM, actionList.at(i)->order, actionList.at(i)->valueList.at(0), actionList.at(i)->valueList.at(1));
                dlg->setAttribute(Qt::WA_DeleteOnClose);
                dlg->setModal(true);
                dlg->move(this->pos().x()+this->size().width()/2-dlg->size().width()/2, this->pos().y()+this->size().height()/2-dlg->size().height()/2);
                connect(dlg, &externalCommDialog::externalComm, this, &MyWidget::externalComm);
                dlg->show();
                break;
            }
            default:
                break;
            }
            break;
        }
    }
}

void MyWidget::on_actionListWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->actionListWidget->itemAt(pos)){
        QListWidgetItem *item = ui->actionListWidget->itemAt(pos);
        if(item->text().contains("Goal")){
            if(ui->startScriptBtn->text() == "Start"){
                QPoint globalPos = ui->actionListWidget->mapToGlobal(pos);
                QMenu menu;
                QAction *act = new QAction("Start from here", this);
                act->setObjectName(QString("%1").arg(ui->actionListWidget->currentRow()));
                connect(act, &QAction::triggered, this, &MyWidget::startFromActionList);
                menu.addAction(act);
                menu.exec(globalPos);
            }
        }
    }
}

void MyWidget::startFromActionList()
{
    QObject *obj = QObject::sender();
    bool ok;
    int startRow = obj->objectName().toInt(&ok);
    ui->startScriptBtn->setText("Pause");
    onPublishActionCommand(1, ui->scriptNameLineEdit->text(), startRow);
}

void MyWidget::on_occupancyBtn_toggled(bool checked)
{
    if(checked){
        ui->unoccupancyBtn->setChecked(false);
        ui->unknownBtn->setChecked(false);
        editMapType = EDITMAP_TYPE::Occupancy;
        myPenColor = qRgb(0,0,0);
        if(editMapTool != EDITMAP_TOOL::NoTool)
            isEditing = true;
        else
            isEditing = false;
    }
    else
        if(!(ui->occupancyBtn->isChecked()
             && ui->unoccupancyBtn->isChecked()
             && ui->unknownBtn->isChecked())){
            editMapType = EDITMAP_TYPE::NoType;
            isEditing = false;
            setCursor(Qt::ArrowCursor);
        }
}

void MyWidget::on_unoccupancyBtn_toggled(bool checked)
{
    if(checked){
        ui->occupancyBtn->setChecked(false);
        ui->unknownBtn->setChecked(false);
        editMapType = EDITMAP_TYPE::Unoccupancy;
        myPenColor = qRgb(255,255,255);
        if(editMapTool != EDITMAP_TOOL::NoTool)
            isEditing = true;
        else
            isEditing = false;
    }
    else
        if(!(ui->occupancyBtn->isChecked()
             && ui->unoccupancyBtn->isChecked()
             && ui->unknownBtn->isChecked())){
            editMapType = EDITMAP_TYPE::NoType;
            isEditing = false;
            setCursor(Qt::ArrowCursor);
        }
}

void MyWidget::on_unknownBtn_toggled(bool checked)
{
    if(checked){
        ui->occupancyBtn->setChecked(false);
        ui->unoccupancyBtn->setChecked(false);
        editMapType = EDITMAP_TYPE::Unknown;
        myPenColor = qRgb(32, 80, 100);
        if(editMapTool != EDITMAP_TOOL::NoTool)
            isEditing = true;
        else
            isEditing = false;
    }
    else
        if(!(ui->occupancyBtn->isChecked()
             && ui->unoccupancyBtn->isChecked()
             && ui->unknownBtn->isChecked())){
            editMapType = EDITMAP_TYPE::NoType;
            isEditing = false;
            setCursor(Qt::ArrowCursor);
        }
}

void MyWidget::on_penBtn_toggled(bool checked)
{
    if(checked){
        ui->lineShapeBtn->setChecked(false);
        ui->rectShapeBtn->setChecked(false);
        ui->ellipseShapeBtn->setChecked(false);
        editMapTool = EDITMAP_TOOL::Pen;
        if(editMapType != EDITMAP_TYPE::NoType)
            isEditing = true;
        else
            isEditing = false;
    }
    else
        if(!(ui->penBtn->isChecked()
             && ui->lineShapeBtn->isChecked()
             && ui->rectShapeBtn->isChecked()
             && ui->ellipseShapeBtn->isChecked())){
            editMapTool = EDITMAP_TOOL::NoTool;
            isEditing = false;
            setCursor(Qt::ArrowCursor);
        }
}

void MyWidget::on_lineShapeBtn_toggled(bool checked)
{
    if(checked){
        ui->penBtn->setChecked(false);
        ui->rectShapeBtn->setChecked(false);
        ui->ellipseShapeBtn->setChecked(false);
        editMapTool = EDITMAP_TOOL::Line;
        if(editMapType != EDITMAP_TYPE::NoType)
            isEditing = true;
        else
            isEditing = false;
    }
    else
        if(!(ui->penBtn->isChecked()
             && ui->lineShapeBtn->isChecked()
             && ui->rectShapeBtn->isChecked()
             && ui->ellipseShapeBtn->isChecked())){
            editMapTool = EDITMAP_TOOL::NoTool;
            isEditing = false;
            setCursor(Qt::ArrowCursor);
        }
}

void MyWidget::on_rectShapeBtn_toggled(bool checked)
{
    if(checked){
        ui->penBtn->setChecked(false);
        ui->lineShapeBtn->setChecked(false);
        ui->ellipseShapeBtn->setChecked(false);
        editMapTool = EDITMAP_TOOL::Rectangle;
        if(editMapType != EDITMAP_TYPE::NoType)
            isEditing = true;
        else
            isEditing = false;
    }
    else
        if(!(ui->penBtn->isChecked()
             && ui->lineShapeBtn->isChecked()
             && ui->rectShapeBtn->isChecked()
             && ui->ellipseShapeBtn->isChecked())){
            editMapTool = EDITMAP_TOOL::NoTool;
            isEditing = false;
            setCursor(Qt::ArrowCursor);
        }
}

void MyWidget::on_ellipseShapeBtn_toggled(bool checked)
{
    if(checked){
        ui->penBtn->setChecked(false);
        ui->lineShapeBtn->setChecked(false);
        ui->rectShapeBtn->setChecked(false);
        editMapTool = EDITMAP_TOOL::Ellipse;
        if(editMapType != EDITMAP_TYPE::NoType)
            isEditing = true;
        else
            isEditing = false;
    }
    else
        if(!(ui->penBtn->isChecked()
             && ui->lineShapeBtn->isChecked()
             && ui->rectShapeBtn->isChecked()
             && ui->ellipseShapeBtn->isChecked())){
            editMapTool = EDITMAP_TOOL::NoTool;
            isEditing = false;
            setCursor(Qt::ArrowCursor);
        }
}

void MyWidget::on_widthSlider_valueChanged(int value)
{
    ui->widthLineEdit->setText(QString::number(value, 10));
    myPointDiameter = value;
}

void MyWidget::on_hollowCheckBox_stateChanged(int isChecked)
{
    if(isChecked)
        isHollow = true;
    else
        isHollow = false;
}

void MyWidget::on_saveBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;

    if(m_map.mapPixmap.isNull())
        return;
    bool ok;
    QString saveNameTxt = QInputDialog::getText(this, tr("Edited Map Save"),
                                                tr("Map name:"), QLineEdit::Normal,
                                                QString("%1-%2").arg(m_map.mapName).arg(QDateTime::currentDateTime().toString("yyMMdd_hhmmss")), &ok);
    if (ok && !saveNameTxt.isEmpty()){
        saveEditedMap(saveNameTxt);
    }
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    if(mode != MODE_TYPE::SLAM)
        return;
    if(event->key() == Qt::Key_W)
        velType = VEL_TYPE::Forward;
    else if(event->key() == Qt::Key_X)
        velType = VEL_TYPE::Backward;
    else if(event->key() == Qt::Key_A)
        velType = VEL_TYPE::Left;
    else if(event->key() == Qt::Key_D)
        velType = VEL_TYPE::Right;
}

void MyWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(mode != MODE_TYPE::SLAM)
        return;
    if(event->key() == Qt::Key_W || event->key() == Qt::Key_X
            || event->key() == Qt::Key_A  || event->key() == Qt::Key_D ){
        if(!event->isAutoRepeat())
            velType = VEL_TYPE::Stop;
        onPublishVelCmd();
    }
}

void MyWidget::updateMarkerValue(int order, QPointF pos, float thetaValue)
{
    for(int i=0; i<actionList.count(); i++){
        if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
            if(actionList.at(i)->marker->order == order){
                actionList.at(i)->marker->setPos(pos);
                float x = (pos.y()/scaleFactor+0.5) * m_map.resolution + m_map.originPosition.x();
                float y = (pos.x()/scaleFactor+0.5) * m_map.resolution + m_map.originPosition.y();
                actionList.at(i)->point.setX(x);
                actionList.at(i)->point.setY(y);

                QQuaternion quat = QQuaternion::fromEulerAngles(0.0, 0.0, qRadiansToDegrees(thetaValue));
                actionList.at(i)->quat = quat;
                actionList.at(i)->marker->theta = thetaValue;

                updateActionListWidget();
                ui->actionListWidget->setCurrentRow(actionList.at(i)->order);
                break;
            }
        }
    }
}

void MyWidget::updateGoalValue(int order, QPointF pos, float thetaValue, float disTolerance, float angleTolerance, float reachTolerance, QString remark)
{
    for(int i=0; i<actionList.count(); i++){
        if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
            if(actionList.at(i)->marker->order == order){

                actionList.at(i)->point.setX(pos.x());
                actionList.at(i)->point.setY(pos.y());

                float x = ( (pos.y()-m_map.originPosition.y()) / m_map.resolution - 0.5 ) * scaleFactor;
                float y = ( (pos.x()-m_map.originPosition.x()) / m_map.resolution - 0.5 ) * scaleFactor;

                actionList.at(i)->marker->setPos(QPointF(x, y));
                actionList.at(i)->disTolerance = disTolerance;
                actionList.at(i)->angleTolerance = angleTolerance;
                actionList.at(i)->reachTolerance = reachTolerance;
                actionList.at(i)->remark = remark;

                QQuaternion quat = QQuaternion::fromEulerAngles(0.0, 0.0, qRadiansToDegrees(thetaValue));
                actionList.at(i)->quat = quat;
                actionList.at(i)->marker->theta = thetaValue;

                updateActionListWidget();
                ui->actionListWidget->setCurrentRow(actionList.at(i)->order);
                break;
            }
        }
    }
}

void MyWidget::cloneGoal(int goalOrder, QPointF pos, float thetaValue, float disTolerance, float angleTolerance, float reachTolerance, QString remark)
{
    float mark_x = ( (pos.y()-m_map.originPosition.y()) / m_map.resolution - 0.5 ) * scaleFactor;
    float mark_y = ( (pos.x()-m_map.originPosition.x()) / m_map.resolution - 0.5 ) * scaleFactor;
    QQuaternion quat = QQuaternion::fromEulerAngles(0.0, 0.0, qRadiansToDegrees(thetaValue));

    ActionItem *action = new ActionItem;
    int actionOrder = -1;
    if(goalOrder == -1)
        action->order = actionList.count();
    else{
        for(int i=0; i<actionList.count(); i++){
            if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
                if(actionList.at(i)->marker->order == goalOrder)
                    actionOrder = actionList.at(i)->order;
            }
        }
        for(int i=0; i<actionList.count(); i++){
            if(actionList.at(i)->order > actionOrder)
                actionList.at(i)->order = actionList.at(i)->order + 1;
        }
        action->order = actionOrder + 1;
    }
    action->type = ACTION_TYPE::NAVIGOAL;
    action->point.setX(pos.x());
    action->point.setY(pos.y());
    action->quat = quat;
    action->disTolerance = disTolerance;
    action->angleTolerance = angleTolerance;
    action->reachTolerance = reachTolerance;
    action->remark = remark;
    NaviMarkerItem *markerItem = new NaviMarkerItem(actionList.count());
    markerItem->setPos(QPointF(mark_x, mark_y));
    markerItem->setScale(scaleFactor/2);
    markerItem->theta = thetaValue;
    action->marker = markerItem;
    mapScene->addItem(action->marker);
    actionList.append(action);
    connect(markerItem, &NaviMarkerItem::updateMarkerValue, this, &MyWidget::updateMarkerValue);
    connect(markerItem, &NaviMarkerItem::updateMarkerEditStatus, this, &MyWidget::updateMarkerEditStatus);
    connect(this, &MyWidget::updateNaviMarkerEditable, markerItem, &NaviMarkerItem::updateNaviMarkerEditable);
    updateActionListWidget();
    if(actionOrder == -1)
        ui->actionListWidget->setCurrentRow(actionList.count() - 1);
    else
        ui->actionListWidget->setCurrentRow(actionOrder + 1);
}

void MyWidget::updateMarkerEditStatus(EDIT_STATUS status)
{
    if(status == EDIT_STATUS::OnEdit)
        naviMode = NAVIMODE_TYPE::EditGoal;
    else
        naviMode = NAVIMODE_TYPE::Normal;
}

void MyWidget::updateProgressDialog(int value)
{
    progressDlg->setValue(value);
    if(progressValue > 100){
        progressDlg->close();
        isTransactionsMap = false;
    }
}

void MyWidget::handleMapServiceTimeout()
{
    static int times = 0;
    if(times < 1){
        enableUi(false);
        tcpSocket->flush();
        tcpSocket->readAll();
        allData.clear();
    }
    else if (times == 2)
        loadStaticMapFlag = true;
    else if(times > 2 && times < mapTimerTimes){
        if(loadStaticMapFlag){
            onCallServiceStaticMap();
            loadStaticMapFlag = false;
        }
        else{
            times--;
            readData();
        }
    }
    else if(times >= mapTimerTimes + 2){
        mapServiceTimer->stop();
        tcpSocket->flush();
        times = 0;
        enableUi(true);

        if(mode == MODE_TYPE::NAVI){
            onSubscribeRstate(1000);
            onSubscribeAmclPose();
            onSubscribeMovebaseStatus();
            onSubscribeReplyScript();
            onSubscribeFeedbackMsg();
        }
        if(readScriptActionJsonAryFlag){
            readScriptActionJsonAryFlag = false;
            readScriptActionJsonAry(scriptActionJsonAry);
        }

        return;
    }
    times++;
}

void MyWidget::handleEnableUiTimeout()
{
    enableUiTimer->stop();
    enableUi(true);
}

void MyWidget::handleVelCmdTimeout()
{
    if(velType == VEL_TYPE::Stop || teleopMode == TELEOP_TYPE::LINEAR)
        velCmdTimer->stop();
    onPublishVelCmd();
}

void MyWidget::handleProgressTimeout()
{
    progressValue++;
    progressDlg->setValue(progressValue);
    if(progressValue > 100){
        progressTimer->stop();
        progressDlg->close();
        isTransactionsMap = false;
    }
}

void MyWidget::readData()
{
    static QTime preTime = QTime::currentTime();
    QByteArray data;
    data = tcpSocket->readAll();
    QJsonParseError readError;
    QJsonDocument readJsonDoc = QJsonDocument::fromJson(data, &readError);

    if(readError.error == QJsonParseError::NoError){

        if(data.contains("Rstate"))
            parseRstate(data);
        else{
            if(mode == MODE_TYPE::SLAM){
                if(data.contains("save_map_service"))
                    parseSaveMapServiceResponseJsonData(data);
                else if(data.contains("transforms"))
                    parseTfJsonData(data);
                else if (data.contains("map"))
                    parseMapJsonData(allData);
            }
            else if (mode == MODE_TYPE::NAVI || mode == MODE_TYPE::TEACHPOINT){
                if(data.contains("list_map_service"))
                    parseListMapServiceResponseJsonData(data);
                else if(data.contains("list_script_service"))
                    parseListScriptServiceResponseJsonData(data);
                else if(data.contains("/replyScript"))
                    parseReplyScript(data);
                else if(data.contains("/amcl_pose"))
                    parseAmclPoseJsonData(data);
                else if(data.contains("/move_base/status"))
                    parseMovebaseStatusJsonData(data);
                else if(data.contains("/feedbackMsg"))
                    parseFeedbackMsg(data);
                else if(data.contains("/Sensor_Button_cmd_vel"))
                    parseSensorButtonCmdVel(data);
            }
            else if (mode == MODE_TYPE::EDITMAP){
                if(data.contains("list_map_service"))
                    parseListMapServiceResponseJsonData(data);
            }
        }
    }
    else{
        if(preTime.msecsTo(QTime::currentTime()) > mapTimerInterval){
            if(allData.contains("static_map") && allData.contains("service_response") && allData.contains("map_load_time")){
                parseMapServiceJsonData(allData);
                loadStaticMapFlag = true;
            }
            else if(allData.contains("topic") && allData.contains("publish") && allData.contains("replyScript")){
                parseReplyScript(allData);
            }
            else if(mode == MODE_TYPE::SLAM && allData.contains("topic") && allData.contains("publish") && allData.contains("map")){
                parseMapJsonData(allData);
            }
            allData.clear();
        }
        allData.append(data);
        preTime = QTime::currentTime();

        QJsonParseError readErrorAll;
        QJsonDocument readJsonDocAll = QJsonDocument::fromJson(allData, &readErrorAll);
        if(readErrorAll.error == QJsonParseError::NoError){
            if(allData.contains("topic") && allData.contains("publish") && allData.contains("replyScript")){
                parseReplyScript(allData);
                allData.clear();
            }
            else if(allData.contains("static_map") && allData.contains("service_response") && allData.contains("map_load_time")){
                parseMapServiceJsonData(allData);
                allData.clear();
                loadStaticMapFlag = true;
            }
            else if(mode == MODE_TYPE::SLAM &&  allData.contains("topic") && allData.contains("publish") && allData.contains("map")){
                parseMapJsonData(allData);
                allData.clear();
            }
        }
    }
}
void MyWidget::parseMapJsonData(QByteArray data)
{
    QString mapData;
    bool isCompleted = true;
    while(data.indexOf("}{") != -1){
        int pos = data.indexOf("}{")+1;
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data.mid(0, pos), &error);
        if (error.error != QJsonParseError::NoError){
            isCompleted = false;
            break;
        }
        mapData += jsonDoc.object().value("data").toString();
        data = data.mid(pos, data.size()-pos);
    }
    if(!data.isEmpty()){
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
        if (error.error != QJsonParseError::NoError)
            isCompleted = false;
        mapData += jsonDoc.object().value("data").toString();
    }

    if(isCompleted){
        QJsonParseError error;
        QJsonDocument dataJsonDoc = QJsonDocument::fromJson(mapData.toLatin1(), &error);

        if(dataJsonDoc.isObject()){
            QJsonObject dataJsonObj = dataJsonDoc.object();
            if(dataJsonObj.contains("msg")) {
                QJsonObject msgJsonObj = dataJsonObj.take("msg").toObject();
                if(msgJsonObj.contains("info")){
                    QJsonObject infoJsonObj = msgJsonObj.take("info").toObject();
                    m_map.width = infoJsonObj.take("width").toDouble();
                    m_map.height = infoJsonObj.take("height").toDouble();
                    m_map.resolution = infoJsonObj.take("resolution").toDouble();


                    if(infoJsonObj.contains("origin")){
                        QJsonObject originJsonObj = infoJsonObj.take("origin").toObject();
                        if(originJsonObj.contains("position")){
                            QJsonObject positionJsonObj = originJsonObj.take("position").toObject();
                            m_map.originPosition.setX( positionJsonObj.take("x").toDouble());
                            m_map.originPosition.setY( positionJsonObj.take("y").toDouble());
                        }
                        if(originJsonObj.contains("orientation")){
                            QJsonObject orientationJsonObj = originJsonObj.take("orientation").toObject();
                            m_map.originOrientation.setX( orientationJsonObj.take("z").toDouble());
                            m_map.originOrientation.setY( orientationJsonObj.take("w").toDouble());
                        }
                    }
                }

                if(msgJsonObj.contains("data")){

                    QJsonArray dataJsonAry = msgJsonObj.take("data").toArray();
                    QImage img(m_map.height, m_map.width, QImage::Format_Indexed8);
                    img.setColorCount(256);
                    QRgb rgb;
                    for(int i = 0; i < 256; i++){
                        if(i == 50)
                            rgb = qRgb(32, 80, 100);
                        else
                            rgb = qRgb(i, i, i);
                        img.setColor(i, rgb);
                    }

                    for(int i = 0; i < m_map.height; i++){
                        for(int j = 0; j < m_map.width; j++){
                            int n = i*m_map.width + j;
                            if(dataJsonAry.at(n) == 100)
                                img.setPixel(i, j, 0);
                            else if(dataJsonAry.at(n) == 0)
                                img.setPixel(i, j, 255);
                            else
                                img.setPixel(i, j, 50);
                        }
                    }

                    m_map.mapPixmap = QPixmap::fromImage(img);
                    ui->graphicsView->resetTransform();
                    scaleSize = m_map.mapPixmap.size();
                    updateMapImg();

                    ui->mappingWidthLineEdit->setText(QString("%1").arg(m_map.width));
                    ui->mappingHeightLineEdit->setText(QString("%1").arg(m_map.height));
                    ui->mappingResLineEdit->setText(QString("%1").arg(m_map.resolution));
                }
            }
        }
    }
}

void MyWidget::parseMapServiceJsonData(QByteArray data)
{
    QString mapData;
    bool isCompleted = true;
    while(data.indexOf("}{") != -1){
        int pos = data.indexOf("}{")+1;
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data.mid(0, pos), &error);
        if (error.error != QJsonParseError::NoError){
            isCompleted = false;
            break;
        }
        mapData += jsonDoc.object().value("data").toString();
        data = data.mid(pos, data.size()-pos);
    }
    if(!data.isEmpty()){
        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
        if (error.error != QJsonParseError::NoError)
            isCompleted = false;
        mapData += jsonDoc.object().value("data").toString();
    }

    if(isCompleted){
        QJsonParseError error;
        QJsonDocument dataJsonDoc = QJsonDocument::fromJson(mapData.toLatin1(), &error);

        if(dataJsonDoc.isObject()){
            QJsonObject dataJsonObj = dataJsonDoc.object();
            if(dataJsonObj.contains("values")) {
                QJsonObject valuesJsonObj = dataJsonObj.take("values").toObject();
                if(valuesJsonObj.contains("map")) {
                    QJsonObject mapJsonObj = valuesJsonObj.take("map").toObject();
                    if(mapJsonObj.contains("info")){
                        QJsonObject infoJsonObj = mapJsonObj.take("info").toObject();
                        m_map.width = infoJsonObj.take("width").toDouble();
                        m_map.height = infoJsonObj.take("height").toDouble();
                        m_map.resolution = infoJsonObj.take("resolution").toDouble();

                        if(infoJsonObj.contains("origin")){
                            QJsonObject originJsonObj = infoJsonObj.take("origin").toObject();
                            if(originJsonObj.contains("position")){
                                QJsonObject positionJsonObj = originJsonObj.take("position").toObject();
                                m_map.originPosition.setX( positionJsonObj.take("x").toDouble());
                                m_map.originPosition.setY( positionJsonObj.take("y").toDouble());
                            }
                            if(originJsonObj.contains("orientation")){
                                QJsonObject orientationJsonObj = originJsonObj.take("orientation").toObject();
                                m_map.originOrientation.setX( orientationJsonObj.take("x").toDouble());
                                m_map.originOrientation.setY( orientationJsonObj.take("y").toDouble());
                                m_map.originOrientation.setZ( orientationJsonObj.take("z").toDouble());
                                m_map.originOrientation.setScalar(orientationJsonObj.take("w").toDouble());
                            }
                        }
                    }
                    if(mapJsonObj.contains("data")){
                        if(m_map.mapName == mapNameReg && !m_map.mapPixmap.isNull())
                            return;
                        m_map.mapName = mapNameReg;
                        QJsonArray dataJsonAry = mapJsonObj.take("data").toArray();
                        QImage img((int)m_map.height, (int)m_map.width, QImage::Format_Indexed8);
                        img.setColorCount(256);
                        QRgb rgb;
                        for(int i = 0; i < 256; i++){
                            if(i == 50)
                                rgb = qRgb(32, 80, 100);
                            else
                                rgb = qRgb(i, i, i);
                            img.setColor(i, rgb);
                        }

                        for(int i = 0; i < (int)m_map.height; i++){
                            for(int j = 0; j < (int)m_map.width; j++){
                                int n = i*(int)m_map.width + j;
                                if(dataJsonAry.at(n) == 100)
                                    img.setPixel(i, j, 0);
                                else if(dataJsonAry.at(n) == 0)
                                    img.setPixel(i, j, 255);
                                else
                                    img.setPixel(i, j, 50);
                            }
                        }
                        m_map.mapPixmap = QPixmap::fromImage(img);
                        if(mode == MODE_TYPE::NAVI){
                            ui->loadMapNameLineEdit->setText(mapNameReg);
                            ui->graphicsView->resetTransform();
                            scaleSize = m_map.mapPixmap.size();
                            scaleFactor = 1.0;
                            updateMapImg();
                        }
                        if(mode == MODE_TYPE::EDITMAP && !isTransactionsMap){
                            ui->loadMapName4EditLineEdit->setText(mapNameReg);
                            updateEditMapImg();
                        }
                    }
                }
            }
        }
    }
}

void MyWidget::parseTfJsonData(QByteArray tfData)
{
    if(tfData.contains("laser"))
        return;

    QJsonParseError error;
    QJsonDocument tfJsonDoc = QJsonDocument::fromJson(tfData, &error);

    if(tfJsonDoc.isObject()){
        QJsonObject tfJsonObj = tfJsonDoc.object();
        if(tfJsonObj.contains("msg")) {
            QJsonObject msgJsonObj = tfJsonObj.take("msg").toObject();
            if(msgJsonObj.contains("transforms")){
                QJsonArray transformsJsonAry = msgJsonObj.take("transforms").toArray();

                for(int i=0; i<transformsJsonAry.size(); i++){
                    QString frame_id_str = "", child_frame_id_str = "";
                    QJsonObject transformsJsonObj = transformsJsonAry.at(i).toObject();
                    if(transformsJsonObj.contains("child_frame_id")){
                        child_frame_id_str = transformsJsonObj.take("child_frame_id").toString();
                    }
                    if(transformsJsonObj.contains("header")){
                        QJsonObject headerJsonObj = transformsJsonObj.take("header").toObject();
                        if(headerJsonObj.contains("frame_id"))
                            frame_id_str = headerJsonObj.take("frame_id").toString();
                    }
                    if(transformsJsonObj.contains("transform")){
                        QJsonObject transformJsonObj = transformsJsonObj.take("transform").toObject();
                        if(transformJsonObj.contains("translation")){
                            QJsonObject translationJsonObj = transformJsonObj.take("translation").toObject();
                            if(child_frame_id_str == "odom"){
                                m_tf.odomPosition.setX(translationJsonObj.take("x").toDouble());
                                m_tf.odomPosition.setY(translationJsonObj.take("y").toDouble());
                                if(transformJsonObj.contains("rotation")){
                                    QJsonObject rotationJsonObj = transformJsonObj.take("rotation").toObject();
                                    m_tf.odomOrientation.setX(rotationJsonObj.take("x").toDouble());
                                    m_tf.odomOrientation.setY(rotationJsonObj.take("y").toDouble());
                                    m_tf.odomOrientation.setZ(rotationJsonObj.take("z").toDouble());
                                    m_tf.odomOrientation.setScalar(rotationJsonObj.take("w").toDouble());
                                }
                            }
                            else if(child_frame_id_str == "base_link"){
                                m_tf.footprintPosition.setX(translationJsonObj.take("x").toDouble());
                                m_tf.footprintPosition.setY(translationJsonObj.take("y").toDouble());
                                if(transformJsonObj.contains("rotation")){
                                    QJsonObject rotationJsonObj = transformJsonObj.take("rotation").toObject();
                                    m_tf.footprintOrientation.setX(rotationJsonObj.take("x").toDouble());
                                    m_tf.footprintOrientation.setY(rotationJsonObj.take("y").toDouble());
                                    m_tf.footprintOrientation.setZ(rotationJsonObj.take("z").toDouble());
                                    m_tf.footprintOrientation.setScalar(rotationJsonObj.take("w").toDouble());
                                }
                            }
                        }
                    }
                    if(!(m_tf.odomPosition.isNull() || m_tf.footprintPosition.isNull())){
                        m_tf.robotPosition = m_tf.odomPosition + m_tf.footprintPosition;
                    }
                    if(!(m_tf.odomOrientation.isNull() || m_tf.footprintOrientation.isNull())){
                        m_tf.yawEulerAngles = (m_tf.odomOrientation.toEulerAngles() + m_tf.footprintOrientation.toEulerAngles()).z();
                        if(m_tf.yawEulerAngles < -180.0)
                            m_tf.yawEulerAngles += 360.0;
                    }
                    updateMapImg();
                }
            }
        }
    }
}

void MyWidget::parseAmclPoseJsonData(QByteArray amclPoseData)
{
    QJsonParseError error;
    QJsonDocument amclPoseJsonDoc = QJsonDocument::fromJson(amclPoseData, &error);

    if(amclPoseJsonDoc.isObject()){
        QJsonObject amclPoseJsonObj = amclPoseJsonDoc.object();
        if(amclPoseJsonObj.contains("msg")) {
            QJsonObject msgJsonObj = amclPoseJsonObj.take("msg").toObject();
            if(msgJsonObj.contains("pose")){
                QJsonObject poseWithCovarianceJsonObj = msgJsonObj.take("pose").toObject();
                if(poseWithCovarianceJsonObj.contains("pose")){
                    QJsonObject poseJsonObj = poseWithCovarianceJsonObj.take("pose").toObject();
                    if(poseJsonObj.contains("position")){
                        QJsonObject positionJsonObj = poseJsonObj.take("position").toObject();
                        m_tf.robotPosition.setX(positionJsonObj.take("x").toDouble());
                        m_tf.robotPosition.setY(positionJsonObj.take("y").toDouble());
                    }

                    if(poseJsonObj.contains("orientation")){
                        QJsonObject orientationJsonObj = poseJsonObj.take("orientation").toObject();
                        m_tf.robotOrientation.setX(orientationJsonObj.take("x").toDouble());
                        m_tf.robotOrientation.setY(orientationJsonObj.take("y").toDouble());
                        m_tf.robotOrientation.setZ(orientationJsonObj.take("z").toDouble());
                        m_tf.robotOrientation.setScalar(orientationJsonObj.take("w").toDouble());

                        m_tf.yawEulerAngles = m_tf.robotOrientation.toEulerAngles().z();
                        if(m_tf.yawEulerAngles < -180.0)
                            m_tf.yawEulerAngles += 360.0;
                    }
                    if(mode == MODE_TYPE::TEACHPOINT)
                        emit updateAmclPose2TeachDlg(m_tf.robotPosition, m_tf.robotOrientation);
                    if(mode == MODE_TYPE::NAVI || mode == MODE_TYPE::TEACHPOINT){
                        if(!(naviMode == NAVIMODE_TYPE::SetInitPose || naviMode == NAVIMODE_TYPE::AddGoal
                             || naviMode == NAVIMODE_TYPE::EditGoal)){
                            updateMapImg();
                        }
                    }
                }
            }
        }
    }
}

void MyWidget::parseMovebaseStatusJsonData(QByteArray statusData)
{
    QJsonParseError error;
    QJsonDocument dataJsonDoc = QJsonDocument::fromJson(statusData, &error);

    if(dataJsonDoc.isObject()){
        QJsonObject dataJsonObj = dataJsonDoc.object();
        if(dataJsonObj.contains("msg")) {
            QJsonObject msgJsonObj = dataJsonObj.take("msg").toObject();
            if(msgJsonObj.contains("status_list")){
                QJsonArray statuslistJsonAry = msgJsonObj.take("status_list").toArray();
                QJsonObject statuslistJsonObj = statuslistJsonAry.last().toObject();
                if(statuslistJsonObj.contains("status")) {
                    int statusValue = statuslistJsonObj.take("status").toInt();
                    static int preStateValue = -1;
                    if(preStateValue != statusValue){
                        switch (statusValue) {
                        case 0:
                            ui->statusLineEdit->setText("Pending");
                            break;
                        case 1:
                            ui->statusLineEdit->setText("Active");
                            break;
                        case 2:
                            ui->statusLineEdit->setText("Preempted");
                            break;
                        case 3:
                            ui->statusLineEdit->setText("Succeeded");
                            break;
                        case 4:
                            ui->statusLineEdit->setText("Aborted");
                            break;
                        case 5:
                            ui->statusLineEdit->setText("Rejected");
                            break;
                        case 6:
                            ui->statusLineEdit->setText("Preempting");
                            break;
                        case 7:
                            ui->statusLineEdit->setText("Recalling");
                            break;
                        case 8:
                            ui->statusLineEdit->setText("Recalled");
                            break;
                        case 9:
                            ui->statusLineEdit->setText("Lost");
                            break;
                        default:
                            break;
                        }
                        preStateValue = statusValue;
                    }
                }
                else{
                    naviState = NAVISTATE::Null;
                    ui->statusLineEdit->setText("Null");
                }
            }
        }

    }
}

void MyWidget::parseSaveMapServiceResponseJsonData(QByteArray data)
{
    QJsonParseError error;
    QJsonDocument dataJsonDoc = QJsonDocument::fromJson(data, &error);
    if(dataJsonDoc.isObject()){
        QJsonObject dataJsonObj = dataJsonDoc.object();
        if(dataJsonObj.contains("result")) {
            bool result = dataJsonObj.take("result").toBool();
            if(result){
                QMessageBox mb;
                mb.setStyleSheet("");
                mb.setIcon(QMessageBox::Information);
                mb.setWindowTitle("OK");
                mb.setText(QString(tr("Save map %1 completed!").arg(ui->mapNameLineEdit->text())));
                mb.exec();
            }
        }
    }
}

void MyWidget::parseListMapServiceResponseJsonData(QByteArray data)
{
    QJsonParseError error;
    QJsonDocument dataJsonDoc = QJsonDocument::fromJson(data, &error);
    if(dataJsonDoc.isObject()){
        QJsonObject dataJsonObj = dataJsonDoc.object();
        if(dataJsonObj.contains("values")) {
            QJsonObject valueJsonObj =  dataJsonObj.take("values").toObject();
            QString str = valueJsonObj.take("output").toString();
            QStringList lines = str.split( "\n", QString::SkipEmptyParts );
            if(listDlg->isVisible())
                listDlg->setList(lines);
        }
    }
}

void MyWidget::parseRstate(QByteArray data)
{
    QJsonParseError error;
    QJsonDocument dataJsonDoc = QJsonDocument::fromJson(data, &error);
    if(dataJsonDoc.isObject()){
        QJsonObject dataJsonObj = dataJsonDoc.object();
        if(dataJsonObj.contains("msg")) {
            QJsonObject msgJsonObj = dataJsonObj.take("msg").toObject();
            int value = msgJsonObj.take("data").toInt();
            if(value != Rstate){
                Rstate = value;
                if(Rstate == 111){
                    onSubscribeTf();
                    onSubscribeMap();
                }
                else if(Rstate == 132){
                    onSubscribeAmclPose();
                    onSubscribeMovebaseStatus();
                }
            }
        }
    }
}

void MyWidget::parseListScriptServiceResponseJsonData(QByteArray data)
{
    QJsonParseError error;
    QJsonDocument dataJsonDoc = QJsonDocument::fromJson(data, &error);
    if(dataJsonDoc.isObject()){
        QJsonObject dataJsonObj = dataJsonDoc.object();
        if(dataJsonObj.contains("values")) {
            QJsonObject valueJsonObj =  dataJsonObj.take("values").toObject();
            QString str = valueJsonObj.take("output").toString();
            QStringList lines = str.split( "\n", QString::SkipEmptyParts );
            if(listDlg->isVisible()){
                listDlg->setList(lines);
            }
        }
    }
}

void MyWidget::parseReplyScript(QByteArray data)
{
    QJsonParseError error;
    QJsonDocument dataJsonDoc = QJsonDocument::fromJson(data, &error);
    if(dataJsonDoc.isObject()){
        QJsonObject dataJsonObj = dataJsonDoc.object();
        if(dataJsonObj.contains("msg")) {

            on_clearGoalBtn_clicked();
            QJsonObject msgJsonObj = dataJsonObj.take("msg").toObject();
            QString scriptName = msgJsonObj.take("scriptName").toString();
            ui->scriptNameLineEdit->setText(scriptName);
            readScriptName = scriptName;

            QString mapName = msgJsonObj.take("mapName").toString();
            mapName.remove(mapName.size()-6, 6);
            ui->loadMapNameLineEdit->setText(mapName);

            scriptActionJsonAry = msgJsonObj.take("actionArray").toArray();
            readScriptActionJsonAryFlag = true;

            if(m_map.mapName != mapName){
                m_map.mapName = mapName;
                mapNameReg = mapName;
                loadMapByService(mapName);
            }
            else{
                readScriptActionJsonAry(scriptActionJsonAry);
            }
            if(ui->statusLineEdit->text() != "Active")
                ui->startScriptBtn->setText("Start");
        }
    }
}

void MyWidget::parseFeedbackMsg(QByteArray data)
{
    QJsonParseError error;
    QJsonDocument dataJsonDoc = QJsonDocument::fromJson(data, &error);
    if(dataJsonDoc.isObject()){
        QJsonObject dataJsonObj = dataJsonDoc.object();
        if(dataJsonObj.contains("msg")) {
            QJsonObject msgJsonObj = dataJsonObj.take("msg").toObject();

            QString currentAction = msgJsonObj.take("action").toString();
            int currentIndex = msgJsonObj.take("currentIndex").toInt();

            if(currentAction.isEmpty()){
                ui->startScriptBtn->setText("Start");
                ui->actionListWidget->setCurrentRow(-1);
            }

            if(currentIndex >= 0)
                ui->actionListWidget->setCurrentRow(currentIndex);
            else
                ui->actionListWidget->setCurrentRow(-1);

            if(currentAction == "Succeeded" || currentAction == "Failed"){
                if(mode == MODE_TYPE::NAVI){
                    ui->startScriptBtn->setText("Start");
                    ui->actionListWidget->setCurrentRow(-1);
                }
            }
        }
    }
}

void MyWidget::parseSensorButtonCmdVel(QByteArray data)
{
    Q_UNUSED(data);
    if(keyPriorityFlag){
        updateVel(VEL_TYPE::Stop);
    }
}

void MyWidget::onAdvertiseCmdVel()
{
    QJsonObject rosJson;
    rosJson.insert("op", "advertise");
    rosJson.insert("topic", "/cmd_vel");
    rosJson.insert("type", "geometry_msgs/Twist");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onAdvertiseRobotModeFlag()
{
    QJsonObject rosJson;
    rosJson.insert("op", "advertise");
    rosJson.insert("topic", "/Robot_Mode_Flag");
    rosJson.insert("type", "std_msgs/Byte");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnadvertiseRobotModeFlag()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unadvertise");
    rosJson.insert("topic", "/Robot_Mode_Flag");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onPublishVelCmd()
{
    static float linearVel = 0.0;
    static float angularVel = 0.0;
    static float velPercentageReg = 25.0;

    float linearLimit = 0.90*(velPercentage/100.0);
    float angularLimit = 0.5*(velPercentage/100.0);
    float linearStep = 0.10;
    float angularStep = 0.08;

    switch (velType) {
    case VEL_TYPE::Forward:
        if(teleopMode == TELEOP_TYPE::JOG)
            angularVel = 0.0;
        if(linearVel < (linearLimit + linearStep))
            linearVel = linearVel + linearStep;
        break;
    case VEL_TYPE::Backward:
        if(teleopMode == TELEOP_TYPE::JOG)
            angularVel = 0.0;
        if(linearVel > -(linearLimit + linearStep))
            linearVel = linearVel - linearStep;
        break;
    case VEL_TYPE::Left:
        if(teleopMode == TELEOP_TYPE::JOG)
            linearVel = 0.0;
        if(angularVel < (angularLimit + angularStep))
            angularVel = angularVel + angularStep;
        break;
    case VEL_TYPE::Right:
        if(teleopMode == TELEOP_TYPE::JOG)
            linearVel = 0.0;
        if(angularVel > -(angularLimit + angularStep))
            angularVel = angularVel - angularStep;
        break;
    case VEL_TYPE::Stop:
        linearVel = 0.0;
        angularVel = 0.0;
        break;
    default:
        break;
    }

    if(velPercentageReg != velPercentage){
        velPercentageReg = velPercentage;
        if(linearVel != 0){
            if(linearVel > 0)
                while(linearVel > linearLimit)
                    linearVel -= linearStep;
            else
                while(linearVel < -linearLimit)
                    linearVel += linearStep;
        }
        if(angularVel != 0){
            if(angularVel > 0)
                while(angularVel > angularLimit)
                    angularVel -= angularStep;
            else
                while(angularVel < -angularLimit)
                    angularVel += angularStep;
        }
    }

    if(teleopMode == TELEOP_TYPE::JOG){
        if( (fabs(linearVel) > linearLimit*1.01) || (fabs(angularVel) > angularLimit*1.01) )
            return;
    }
    else if (teleopMode == TELEOP_TYPE::LINEAR){
        if(fabs(linearVel) > linearLimit*1.01){
            if(linearVel < 0.0)
                linearVel = linearVel + linearStep;
            else
                linearVel = linearVel - linearStep;
        }
        else if (fabs(angularVel) > angularLimit*1.01)
            if(angularVel < 0.0)
                angularVel = angularVel + angularStep;
            else
                angularVel = angularVel - angularStep;
    }

    QJsonObject rosJson, msgJson, linearJson, angularJson;
    linearJson.insert("x", linearVel);
    linearJson.insert("y", 0.0);
    linearJson.insert("z", 0.0);
    angularJson.insert("x", 0.0);
    angularJson.insert("y", 0.0);
    angularJson.insert("z", angularVel);
    msgJson.insert("linear", linearJson);
    msgJson.insert("angular", angularJson);
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    if(mode == MODE_TYPE::SLAM)
        rosJson.insert("topic", "/cmd_vel");
    else
        rosJson.insert("topic", "/key_cmd_vel");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onPublishInitPose(bool isOrigin, QPoint pos, QQuaternion quat)
{
    float x = 0.0, y = 0.0;
    if(!isOrigin){
        x = (pos.y()/scaleFactor+0.5) * m_map.resolution + m_map.originPosition.x();
        y = (pos.x()/scaleFactor+0.5) * m_map.resolution + m_map.originPosition.y();
    }

    static int seqInitPose = 0;
    seqInitPose++;

    QJsonObject headerJson, stampJson;
    headerJson.insert("seq", seqInitPose);
    stampJson.insert("secs", QDateTime::currentDateTime().toMSecsSinceEpoch()*1000);
    stampJson.insert("nsecs", 0);
    headerJson.insert("stamp", stampJson);
    headerJson.insert("frame_id", "");

    QJsonObject posesonJson, positionJson, orientationJson;
    positionJson.insert("x", x);
    positionJson.insert("y", y);
    positionJson.insert("z", 0.0);
    posesonJson.insert("position", positionJson);
    orientationJson.insert("x", quat.x());
    orientationJson.insert("y", quat.y());
    orientationJson.insert("z", quat.z());
    orientationJson.insert("w", quat.scalar());
    posesonJson.insert("orientation", orientationJson);

    QJsonArray covarianceJson;
    for(int i=0; i<36; i++){
        if(i == 0)
            covarianceJson.append(0.25);
        else if(i == 7)
            covarianceJson.append(0.25);
        else if(i == 35)
            covarianceJson.append(0.06853891945200942);
        else
            covarianceJson.append(0.0);
    }
    m_tf.covariance[0] = 0.25;
    m_tf.covariance[1] = 0.0;
    m_tf.covariance[2] = 0.0;
    m_tf.covariance[3] = 0.25;
    m_tf.covariance[4] = 0.06853891945200942;

    QJsonObject poseJson;
    poseJson.insert("pose", posesonJson);
    poseJson.insert("covariance", covarianceJson);

    QJsonObject msgJson;
    msgJson.insert("header", headerJson);
    msgJson.insert("pose", poseJson);

    QJsonObject rosJson;
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/initialpose");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
    scaleImage(1.0);
}

void MyWidget::onPublishRobotModeFlag(MODE_TYPE type)
{
    mode = type;
    QJsonObject msgJson;
    if(type == MODE_TYPE::SLAM)
        msgJson.insert("data", (qint8)1);
    else if(type == MODE_TYPE::NAVI)
        msgJson.insert("data", (qint8)3);
    else if(type == MODE_TYPE::TEACHPOINT)
        msgJson.insert("data", (qint8)4);
    else if(type == MODE_TYPE::XROCKER)
        msgJson.insert("data", (qint8)2);
    else if(type == MODE_TYPE::EDITMAP)
        msgJson.insert("data", (qint8)5);
    else if(type == MODE_TYPE::RESETNODE)
        msgJson.insert("data", (qint8)11);
    else if(type == MODE_TYPE::RESTARTAGV)
        msgJson.insert("data", (qint8)12);
    else if(type == MODE_TYPE::SHUTDOWNAGV)
        msgJson.insert("data", (qint8)13);

    QJsonObject rosJson;
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/Robot_Mode_Flag");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onPublishEditedMap(QImage image, QString name)
{
    isTransactionsMap = true;
    onCallServiceSaveEditedMap(name);

    QJsonObject msgJson;
    QJsonObject headerJson, stampJson;
    headerJson.insert("seq", 0);
    stampJson.insert("secs", QDateTime::currentDateTime().toMSecsSinceEpoch()*1000);
    stampJson.insert("nsecs", 0);
    headerJson.insert("stamp", stampJson);
    headerJson.insert("frame_id", "map");

    QJsonObject infoJson, mapLoadTimeJson, originJson, positionJson, orientationJson;
    mapLoadTimeJson.insert("secs", QDateTime::currentDateTime().toMSecsSinceEpoch()*1000);
    mapLoadTimeJson.insert("nsecs", 0);
    infoJson.insert("map_load_time", mapLoadTimeJson);
    infoJson.insert("resolution", m_map.resolution);
    infoJson.insert("width", m_map.width);
    infoJson.insert("height", m_map.height);

    positionJson.insert("x", m_map.originPosition.x());
    positionJson.insert("y", m_map.originPosition.y());
    positionJson.insert("z", 0);
    originJson.insert("position", positionJson);

    orientationJson.insert("x", m_map.originOrientation.x());
    orientationJson.insert("y", m_map.originOrientation.y());
    orientationJson.insert("z", m_map.originOrientation.z());
    orientationJson.insert("w", m_map.originOrientation.scalar());
    originJson.insert("orientation", orientationJson);
    infoJson.insert("origin", originJson);

    int progressSize = image.height() * image.width();
    QJsonArray dataJsonAry;
    for(int i = 0; i < image.height(); i++){
        for(int j = 0; j < image.width(); j++){
            if(image.pixelColor(j, image.height()-1-i).black() == 0)
                dataJsonAry.append(0);
            else if(image.pixelColor(j, image.height()-1-i).black() == 255)
                dataJsonAry.append(100);
            else
                dataJsonAry.append(-1);
        }
    }

    msgJson.insert("header", headerJson);
    msgJson.insert("info", infoJson);
    msgJson.insert("data", dataJsonAry);

    QJsonObject rosJson;
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/map");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
    setProgressDialog();
}

void MyWidget::onPublishActionCommand(int cmdType, QString name, int startLine)
{
    QJsonObject msgJson;
    msgJson.insert("cmdType", (qint8)cmdType);
    msgJson.insert("scriptName", name);
    msgJson.insert("startLine", startLine);

    QJsonObject rosJson;
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/actionCommand");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onPublishPeripheralCmd(int value)
{
    QJsonObject msgJson;
    msgJson.insert("actionTypeID", 3);
    msgJson.insert("statusID", value);

    QJsonObject rosJson;
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/peripheralCommand");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();

    QThread::msleep(500);
}

void MyWidget::onPublishKeyPriority(bool flag)
{
    QJsonObject msgJson;
    msgJson.insert("data", flag);

    QJsonObject rosJson;
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/key_priority");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onPublishActionScript()
{
    QJsonObject msgJson;
    QJsonArray actionItemJsonAry;
    for(int i=0; i<actionList.count(); i++){
        for(int j=0; j<actionList.count(); j++){
            if(actionList.at(j)->order == i){
                QJsonObject actionItemJson;
                QJsonArray actionItemParaJsonAry;
                switch(actionList.at(j)->type) {
                case ACTION_TYPE::NAVIGOAL:
                    actionItemParaJsonAry.append(actionList.at(j)->point.x());
                    actionItemParaJsonAry.append(actionList.at(j)->point.y());
                    actionItemParaJsonAry.append(actionList.at(j)->quat.z());
                    actionItemParaJsonAry.append(actionList.at(j)->quat.scalar());
                    actionItemParaJsonAry.append(actionList.at(j)->disTolerance);
                    actionItemParaJsonAry.append(actionList.at(j)->angleTolerance);
                    actionItemParaJsonAry.append(actionList.at(j)->reachTolerance);
                    actionItemParaJsonAry.append(-1.0);
                    actionItemJson.insert("actionType", 1);
                    actionItemJson.insert("para", actionItemParaJsonAry);
                    break;
                case ACTION_TYPE::DELAYACTION:
                    actionItemParaJsonAry.append((float)actionList.at(j)->delayMs);
                    actionItemJson.insert("actionType", 4);
                    actionItemJson.insert("para", actionItemParaJsonAry);
                    break;
                case ACTION_TYPE::EXTERNALCOMACTION:
                    actionItemParaJsonAry.append(actionList.at(j)->valueList.at(0));
                    actionItemParaJsonAry.append(actionList.at(j)->valueList.at(1));
                    actionItemJson.insert("actionType", 10);
                    actionItemJson.insert("para", actionItemParaJsonAry);
                    break;
                default:
                    break;
                }
                actionItemJsonAry.append(actionItemJson);
            }
        }
    }

    msgJson.insert("scriptName", ui->scriptNameLineEdit->text());
    msgJson.insert("mapName", ui->loadMapNameLineEdit->text() + ".yaml");
    msgJson.insert("actionArray", actionItemJsonAry);

    QJsonObject rosJson;
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/actionScript");
    rosJson.insert("msg", msgJson);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onPublishAskScript(QString name)
{
    QJsonObject msgJson;
    msgJson.insert("data", name);

    QJsonObject rosJson;
    rosJson.insert("msg", msgJson);
    rosJson.insert("op", "publish");
    rosJson.insert("topic", "/askScript");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeMap()
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/map");
    rosJson.insert("type", "nav_msgs/OccupancyGrid");
    rosJson.insert("throttle_rate", 800);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeTf()
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/tf");
    rosJson.insert("type", "tf/tfMessage");
    rosJson.insert("throttle_rate", 600);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());

    rosJson.remove("type");
    rosJson.insert("type", "tf2_msgs/TFMessage");
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeAmclPose()
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/amcl_pose");
    rosJson.insert("type", "geometry_msgs/PoseWithCovarianceStamped");
    rosJson.insert("throttle_rate", 1000);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeMovebaseStatus()
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/move_base/status");
    rosJson.insert("type", "actionlib_msgs/GoalStatusArray");
    rosJson.insert("throttle_rate", 1000);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeRstate(int throttle_rate)
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/Rstate");
    rosJson.insert("type", "std_msgs/Char");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeReplyScript()
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/replyScript");
    rosJson.insert("type", "my_script_handler/actionList");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeFeedbackMsg()
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/feedbackMsg");
    rosJson.insert("type", "my_action_actionlib/feedbackMsg");
    rosJson.insert("throttle_rate", 1000);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onSubscribeSensorButtonCmdVel()
{
    QJsonObject rosJson;
    rosJson.insert("op", "subscribe");
    rosJson.insert("topic", "/Sensor_Button_cmd_vel");
    rosJson.insert("type", "geometry_msgs/Twist");
    rosJson.insert("throttle_rate", 500);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeMap()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/map");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeTf()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/tf");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeAmclPose()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/amcl_pose");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeMovebaseStatus()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/move_base/status");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeRstate()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/Rstate");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeReplyScript()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/replyScript");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeFeedbackMsg()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/feedbackMsg");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onUnsubscribeSensorButtonCmdVel()
{
    QJsonObject rosJson;
    rosJson.insert("op", "unsubscribe");
    rosJson.insert("topic", "/Sensor_Button_cmd_vel");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onCallServiceStaticMap()
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "static_map");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onCallServiceSaveMap()
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "save_map_service");

    QJsonObject arg;
    arg.insert("input", ui->mapNameLineEdit->text());
    rosJson.insert("args", arg);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onCallServiceSaveEditedMap(QString str)
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "save_map_service");

    QJsonObject arg;
    arg.insert("input", str);
    rosJson.insert("args", arg);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onCallServiceListScript()
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "list_script_service");

    QJsonObject arg;
    arg.insert("input", " ");
    rosJson.insert("args", arg);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onCallServiceDeleteScript(QString nameStr)
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "delete_script_service");

    QJsonObject arg;
    arg.insert("input", nameStr);
    rosJson.insert("args", arg);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onCallServiceUpdatePose()
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "request_nomotion_update");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}


void MyWidget::onCallServiceLoadMap(QString nameStr)
{
    mapServiceTimer->stop();

    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "load_map_service");

    QJsonObject arg;
    arg.insert("input", nameStr + ".yaml");
    rosJson.insert("args", arg);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();

    mapServiceTimer->start();
}

void MyWidget::onCallServiceListMap()
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "list_map_service");

    QJsonObject arg;
    arg.insert("input", " ");
    rosJson.insert("args", arg);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onCallServiceDeleteMap(QString nameStr)
{
    QJsonObject rosJson;
    rosJson.insert("op", "call_service");
    rosJson.insert("service", "delete_map_service");

    QJsonObject arg;
    arg.insert("input", nameStr);
    rosJson.insert("args", arg);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::updateMapImg()
{
    if(m_map.mapPixmap.isNull())
        return;

    static QSize preScaleSize(0, 0);
    if(preScaleSize != scaleSize){
        scaleSize = m_map.mapPixmap.size() * scaleFactor;
        preScaleSize = scaleSize;
    }

    scaleImage(1.0);
}

void MyWidget::updateEditMapImg()
{
    if(mapScene->items().contains(mapPixmapItem))
        mapScene->removeItem(mapPixmapItem);
    mapPixmapItem->setPixmap(m_map.mapPixmap);
    scaleSize = m_map.mapPixmap.size();
    mapScene->addItem(mapPixmapItem);
    ui->graphicsView->fitInView(mapScene->sceneRect(), Qt::KeepAspectRatio);
    scaleImage(1.0);
}

void MyWidget::scaleImage(double factor)
{
    if(factor != 1.0){
        scaleSize *= factor;
        scaleFactor *= factor;
    }

    if(mode != MODE_TYPE::EDITMAP){

        if(mapScene->items().contains(mapPixmapItem))
            mapScene->removeItem(mapPixmapItem);
        mapPixmapItem->setPixmap(m_map.mapPixmap.scaled(scaleSize, Qt::KeepAspectRatio));
        mapScene->addItem(mapPixmapItem);
        QRectF rect = mapScene->itemsBoundingRect();
        mapScene->setSceneRect(rect);

        if(!m_map.mapPixmap.isNull()){

            if(mapScene->items().contains(robotPixmapItem))
                mapScene->removeItem(robotPixmapItem);
            if(!m_tf.robotPosition.isNull()){

                int xPos = scaleFactor*((m_tf.robotPosition.x() - m_map.originPosition.x() ) / m_map.resolution + 0.5);
                int yPos = scaleFactor*((m_tf.robotPosition.y() - m_map.originPosition.y() ) / m_map.resolution + 0.5);

                robotPixmapItem->setTransformOriginPoint(robotPixmapItem->boundingRect().center());
                robotPixmapItem->setRotation(-m_tf.yawEulerAngles+180);
                robotPixmapItem->setScale(scaleFactor);
                int offset = robotPixmapItem->pixmap().size().width()*scaleFactor/2;
                robotPixmapItem->setPos(yPos-offset, xPos-offset);
                mapScene->addItem(robotPixmapItem);
            }

            if(mode != MODE_TYPE::SLAM){
                for(int i=0; i<actionList.count(); i++){
                    if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
                        NaviMarkerItem *marker = actionList.at(i)->marker;
                        if(mapScene->items().contains(marker))
                            mapScene->removeItem(marker);

                        int x = ( (actionList.at(i)->point.y() - m_map.originPosition.y()) / m_map.resolution - 0.5 ) * scaleFactor;
                        int y = ( (actionList.at(i)->point.x() - m_map.originPosition.x()) / m_map.resolution - 0.5 ) * scaleFactor;

                        marker->setScale(scaleFactor/2);
                        marker->setPos(x, y);
                        mapScene->addItem(marker);
                    }
                }
            }
        }
    }
    else{
        if(scaleFactor > preFactor)
            ui->graphicsView->scale(1.2, 1.2);
        else
            ui->graphicsView->scale(1.0/1.2, 1.0/1.2);
        QRectF rect = mapScene->itemsBoundingRect();
        mapScene->setSceneRect(rect);
        preFactor = scaleFactor;
    }

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);
}

void MyWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

bool MyWidget::eventFilter(QObject *obj, QEvent *event)
{
    static QPoint clickPoint;

    if( (obj == mapScene && mode == MODE_TYPE::NAVI && (naviMode == NAVIMODE_TYPE::SetInitPose || naviMode == NAVIMODE_TYPE::AddGoal))
            || (obj == mapScene && naviMode == NAVIMODE_TYPE::SetInitPose) ){

        if(m_map.mapPixmap.isNull() ){
            if(ui->initPoseBtn->isChecked())
                ui->initPoseBtn->setChecked(false);
            else if(ui->addGoalBtn->isChecked())
                ui->addGoalBtn->setChecked(false);
            return QWidget::eventFilter(obj, event);
        }

        static qreal theta = 0;
        static bool isInisdeMap = false;
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        switch (event->type()) {
        case QEvent::Enter:
            changeCursor();
            break;
        case QEvent::Leave:
            this->setCursor(Qt::ArrowCursor);
            break;
        case QEvent::GraphicsSceneMousePress:
            if (mapScene->sceneRect().contains(mouseEvent->scenePos())) {
                isInisdeMap = true;
                clickPoint = mouseEvent->scenePos().toPoint();
                theta = 0;
                naviDirLine->setLine(clickPoint.x(), clickPoint.y(), clickPoint.x(), clickPoint.y()+30);
                mapScene->addItem(naviDirLine);
            }
            break;
        case QEvent::GraphicsSceneMouseMove:{
            if(isInisdeMap){
                theta = qAtan2(mouseEvent->scenePos().toPoint().x() - clickPoint.x(),
                               mouseEvent->scenePos().toPoint().y() - clickPoint.y());
                qreal thetaForDisplay = qAtan2(mouseEvent->scenePos().toPoint().y() - clickPoint.y(),
                                               mouseEvent->scenePos().toPoint().x() - clickPoint.x());

                qreal r = 30;
                qreal x_projection = r*qCos(thetaForDisplay);
                qreal y_projection = r*qSin(thetaForDisplay);
                naviDirLine->setLine(clickPoint.x(), clickPoint.y(), clickPoint.x()+x_projection, clickPoint.y()+y_projection);
                mapScene->update();
            }
            break;
        }
        case QEvent::GraphicsSceneMouseRelease:{
            if(isInisdeMap){
                QQuaternion quat = QQuaternion::fromEulerAngles(0.0, 0.0, qRadiansToDegrees(theta));
                if(naviMode == NAVIMODE_TYPE::SetInitPose){
                    onPublishInitPose(false, clickPoint, quat);
                    if(mode == MODE_TYPE::NAVI)
                        ui->initPoseBtn->setChecked(false);
                }
                else if(naviMode == NAVIMODE_TYPE::AddGoal){
                    ui->addGoalBtn->setChecked(false);

                    float x = (clickPoint.y()/scaleFactor+0.5) * m_map.resolution + m_map.originPosition.x();
                    float y = (clickPoint.x()/scaleFactor+0.5) * m_map.resolution + m_map.originPosition.y();

                    ActionItem *action = new ActionItem;
                    action->type = ACTION_TYPE::NAVIGOAL;
                    action->order = actionList.count();
                    action->point.setX(x);
                    action->point.setY(y);
                    action->quat = quat;
                    action->disTolerance = ui->disToleranceDSB->value();
                    action->angleTolerance = ui->angleToleranceDSB->value();
                    action->reachTolerance = 0.0;
                    NaviMarkerItem *markerItem = new NaviMarkerItem(actionList.count());
                    markerItem->setPos(clickPoint);
                    markerItem->setScale(scaleFactor/2);
                    markerItem->theta = theta;
                    action->marker = markerItem;
                    mapScene->addItem(action->marker);
                    actionList.append(action);
                    connect(markerItem, &NaviMarkerItem::updateMarkerValue, this, &MyWidget::updateMarkerValue);
                    connect(markerItem, &NaviMarkerItem::updateMarkerEditStatus, this, &MyWidget::updateMarkerEditStatus);
                    connect(this, &MyWidget::updateNaviMarkerEditable, markerItem, &NaviMarkerItem::updateNaviMarkerEditable);
                    updateActionListWidget();
                }
                mapScene->removeItem(naviDirLine);
                mapScene->update();
                isInisdeMap = false;
                this->setCursor(Qt::ArrowCursor);
            }
            break;
        }
        default:
            return QWidget::eventFilter(obj, event);
            break;
        }
    }
    else if(obj == mapScene && mode == MODE_TYPE::NAVI
            && (naviMode == NAVIMODE_TYPE::Normal || naviMode == NAVIMODE_TYPE::EditGoal)){
        if(tcpSocket->state() != QAbstractSocket::ConnectedState)
            return QWidget::eventFilter(obj, event);
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        switch (mouseEvent->type()) {
        case QEvent::GraphicsSceneMousePress:{
            QTransform myTransform;
            myTransform.rotate(90);
            QGraphicsItem *clickItem = mapScene->itemAt(mouseEvent->scenePos(), myTransform);
            if(clickItem != mapPixmapItem && clickItem != robotPixmapItem){
                NaviMarkerItem *node = qgraphicsitem_cast<NaviMarkerItem *>(clickItem);
                for(int i=0; i< actionList.count(); i++){
                    if(actionList.at(i)->type == ACTION_TYPE::NAVIGOAL){
                        if(actionList.at(i)->marker->order == node->order){
                            ui->actionListWidget->setCurrentRow(actionList.at(i)->order);
                            break;
                        }
                    }
                }
            }
            else
                ui->actionListWidget->setCurrentRow(-1);
            break;
        }
        default:
            break;
        }
        return QWidget::eventFilter(obj, event);
    }
    else if(obj == mapScene && mode == MODE_TYPE::EDITMAP && isEditing){
        if(m_map.mapPixmap.isNull())
            return QWidget::eventFilter(obj, event);

        QPen pen(myPenColor, myPointDiameter, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        QBrush brush;
        if(!isHollow)
            brush = QBrush(myPenColor);
        else
            brush = QBrush(Qt::NoBrush);

        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        switch (event->type()) {

        case QEvent::GraphicsSceneMousePress:
            if ((mouseEvent->button() == Qt::LeftButton) && mapScene->sceneRect().contains(mouseEvent->scenePos())) {
                lastPoint = mouseEvent->scenePos();
                startEditing = true;
                onceAddItemList.clear();
                switch (editMapTool) {
                case EDITMAP_TOOL::Line:
                    tempLineItem->setPen(pen);
                    tempLineItem->setLine(lastPoint.x(), lastPoint.y(), lastPoint.x(), lastPoint.y());
                    mapScene->addItem(tempLineItem);
                    break;

                case EDITMAP_TOOL::Rectangle:
                    tempRectItem->setPen(pen);
                    tempRectItem->setBrush(brush);
                    tempRectItem->setRect(lastPoint.x(), lastPoint.y(), 0, 0);
                    mapScene->addItem(tempRectItem);
                    break;

                case EDITMAP_TOOL::Ellipse:
                    tempEllipseItem->setPen(pen);
                    tempEllipseItem->setBrush(brush);
                    tempEllipseItem->setRect(lastPoint.x(), lastPoint.y(), 0, 0);
                    mapScene->addItem(tempEllipseItem);
                    break;

                default:
                    break;
                }
            }
            break;

        case QEvent::GraphicsSceneMouseMove:
            switch (editMapTool) {
            case EDITMAP_TOOL::Pen:
                if ((mouseEvent->buttons() == Qt::LeftButton) && startEditing && mapScene->sceneRect().contains(mouseEvent->scenePos()))
                    drawLineTo(mouseEvent->scenePos());
                break;
            case EDITMAP_TOOL::Line:
                tempLineItem->setLine(lastPoint.x(), lastPoint.y(), mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
                mapScene->update();
                break;

            case EDITMAP_TOOL::Rectangle:
                tempRectItem->setRect(lastPoint.x(), lastPoint.y(),
                                      mouseEvent->scenePos().x()-lastPoint.x(), mouseEvent->scenePos().y()-lastPoint.y());
                mapScene->update();
                break;

            case EDITMAP_TOOL::Ellipse:
                tempEllipseItem->setRect(lastPoint.x(), lastPoint.y(),
                                         mouseEvent->scenePos().x()-lastPoint.x(), mouseEvent->scenePos().y()-lastPoint.y());
                mapScene->update();
                break;

            default:
                break;
            }
            break;

        case QEvent::GraphicsSceneMouseRelease:
            switch (editMapTool) {
            case EDITMAP_TOOL::Pen:
                if ((mouseEvent->button() == Qt::LeftButton) && startEditing && mapScene->sceneRect().contains(mouseEvent->scenePos())) {
                    drawLineTo(mouseEvent->scenePos());
                    startEditing = false;
                    QUndoCommand *stack = new EditMapStack(onceAddItemList, mapScene);
                    undoStack->push(stack);
                }
                break;
            case EDITMAP_TOOL::Line:
                if(mapScene->items().contains(tempLineItem))
                    mapScene->removeItem(tempLineItem);

                if ((mouseEvent->button() == Qt::LeftButton) && startEditing && mapScene->sceneRect().contains(mouseEvent->scenePos())) {
                    drawLineTo(mouseEvent->scenePos());
                    startEditing = false;
                    QUndoCommand *stack = new EditMapStack(onceAddItemList, mapScene);
                    undoStack->push(stack);
                }
                break;

            case EDITMAP_TOOL::Rectangle:
                if(mapScene->items().contains(tempRectItem))
                    mapScene->removeItem(tempRectItem);

                if ((mouseEvent->button() == Qt::LeftButton) && startEditing && mapScene->sceneRect().contains(mouseEvent->scenePos())) {
                    onceAddItemList.append(mapScene->addRect(lastPoint.x(), lastPoint.y(),
                                                             mouseEvent->scenePos().x()-lastPoint.x(),
                                                             mouseEvent->scenePos().y()-lastPoint.y(),
                                                             pen, brush));
                    startEditing = false;
                    QUndoCommand *stack = new EditMapStack(onceAddItemList, mapScene);
                    undoStack->push(stack);
                }
                break;

            case EDITMAP_TOOL::Ellipse:
                if(mapScene->items().contains(tempEllipseItem))
                    mapScene->removeItem(tempEllipseItem);

                if ((mouseEvent->button() == Qt::LeftButton) && startEditing && mapScene->sceneRect().contains(mouseEvent->scenePos())) {
                    onceAddItemList.append(mapScene->addEllipse(lastPoint.x(), lastPoint.y(),
                                                                mouseEvent->scenePos().x()-lastPoint.x(),
                                                                mouseEvent->scenePos().y()-lastPoint.y(),
                                                                pen, brush));
                    startEditing = false;
                    QUndoCommand *stack = new EditMapStack(onceAddItemList, mapScene);
                    undoStack->push(stack);
                }
                break;

            default:
                break;
            }
            break;

        case QEvent::Enter:
            if(editMapTool == EDITMAP_TOOL::Pen)
                setCustomCursor(myPointDiameter, myPenColor);
            else
                setCursor(Qt::CrossCursor);
            break;

        case QEvent::Leave:
            setCursor(Qt::ArrowCursor);
            break;

        default:
            return QWidget::eventFilter(obj, event);
            break;
        }
    }
    else if(obj == ui->actionListWidget){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Escape){
                ui->actionListWidget->setCurrentRow(-1);
            }
        }
    }
    else
        return QWidget::eventFilter(obj, event);
}

void MyWidget::actionListMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row)
{
    Q_UNUSED(parent);
    Q_UNUSED(end);
    Q_UNUSED(destination);

    if(start > row){
        for(int i=0; i<actionList.count(); i++){
            if(actionList.at(i)->order == start)
                actionList.at(i)->order = row;
            else if(actionList.at(i)->order >= row && actionList.at(i)->order < start )
                actionList.at(i)->order += 1;
        }
    }
    else if(start < row){
        for(int i=0; i<actionList.count(); i++){
            if(actionList.at(i)->order == start)
                actionList.at(i)->order = row - 1;
            else if(actionList.at(i)->order <= row - 1 && actionList.at(i)->order > start )
                actionList.at(i)->order -= 1;
        }
    }
    updateActionListWidget();
    updateMapImg();

    if(start > row)
        ui->actionListWidget->setCurrentRow(row);
    else
        ui->actionListWidget->setCurrentRow(row-1);
}

void MyWidget::updateVel(VEL_TYPE vel_type)
{
    velType = vel_type;
    if(!velCmdTimer->isActive())
        velCmdTimer->start();
}

void MyWidget::updateVelPercentage(int value)
{
    velSliderValue = value;
    if(value == 2)
        velPercentage = 70.0;
    else if(value == 3)
        velPercentage = 100.0;
    else
        velPercentage = 50.0;
}

void MyWidget::addTeachGoal(QPointF pos, QQuaternion quat, bool isAdd2End)
{
    int xPos = scaleFactor*((pos.x() - m_map.originPosition.x() ) / m_map.resolution + 0.5);
    int yPos = scaleFactor*((pos.y() - m_map.originPosition.y() ) / m_map.resolution + 0.5);

    ActionItem *action = new ActionItem;
    action->type = ACTION_TYPE::NAVIGOAL;
    action->point.setX(pos.x());
    action->point.setY(pos.y());
    action->quat = quat;
    action->disTolerance = ui->disToleranceDSB->value();
    action->angleTolerance = ui->angleToleranceDSB->value();
    action->reachTolerance = 0.0;
    NaviMarkerItem *markerItem = new NaviMarkerItem(actionList.count());
    action->marker = markerItem;
    action->marker->setPos(xPos, yPos);
    action->marker->setScale(scaleFactor/2);
    action->marker->theta = qDegreesToRadians(quat.toEulerAngles().z());
    mapScene->addItem(action->marker);
    connect(markerItem, &NaviMarkerItem::updateMarkerValue, this, &MyWidget::updateMarkerValue);
    connect(markerItem, &NaviMarkerItem::updateMarkerEditStatus, this, &MyWidget::updateMarkerEditStatus);
    connect(this, &MyWidget::updateNaviMarkerEditable, markerItem, &NaviMarkerItem::updateNaviMarkerEditable);

    int focusRow = -1;
    if(isAdd2End){
        action->order = actionList.count();
        focusRow = action->order;
    }
    else{
        action->order = ui->actionListWidget->currentRow() + 1;
        for(int i=0; i<actionList.count(); i++){
            if(actionList.at(i)->order > ui->actionListWidget->currentRow())
                actionList.at(i)->order = actionList.at(i)->order + 1;
        }
        focusRow = ui->actionListWidget->currentRow() + 1;
    }
    actionList.append(action);
    updateActionListWidget();
    updateMapImg();
    if(isAdd2End)
        ui->actionListWidget->setCurrentRow(focusRow);
    else
        ui->actionListWidget->setCurrentRow(focusRow);
    mode = MODE_TYPE::NAVI;
}

void MyWidget::loadMapByService(QString mapName)
{
    on_clearGoalBtn_clicked();

    resetMapView();

    onUnsubscribeRstate();
    onUnsubscribeAmclPose();
    onUnsubscribeMovebaseStatus();
    onUnsubscribeReplyScript();
    onUnsubscribeFeedbackMsg();

    enableUi(false);
    onCallServiceLoadMap(mapName);
    ui->loadMapNameLineEdit->setText("");
    ui->scriptNameLineEdit->setText("");
    mapNameReg = mapName;
}

void MyWidget::loadScript(QString name)
{
    on_clearGoalBtn_clicked();
    readScriptName = name;
    onPublishAskScript(readScriptName);
}

void MyWidget::deleteMap(QString name)
{
    onCallServiceDeleteMap(name);
}

void MyWidget::deleteScript(QString name)
{
    onCallServiceDeleteScript(name);
}

void MyWidget::externalComm(EXTERNAL_TYPE type, int order, int address, int value)
{
    if(order == -1){
        ActionItem *action = new ActionItem;
        if(type == EXTERNAL_TYPE::EXTERNALCOMM){
            action->type = ACTION_TYPE::EXTERNALCOMACTION;
            action->valueList.append(address);
            action->valueList.append(value);
        }
        else if(type == EXTERNAL_TYPE::DELAYMS){
            action->type = ACTION_TYPE::DELAYACTION;
            action->delayMs = value;
        }

        int focusRow = -1;
        action->order = actionList.count();
        focusRow = action->order;

        actionList.append(action);
        updateActionListWidget();
        ui->actionListWidget->setCurrentRow(focusRow);
    }
    else{
        for(int i=0; i<actionList.count(); i++){
            if(actionList.at(i)->order == order){
                if(type == EXTERNAL_TYPE::EXTERNALCOMM){
                    actionList.at(i)->valueList.replace(0, address);
                    actionList.at(i)->valueList.replace(1, value);
                }
                else if(type == EXTERNAL_TYPE::DELAYMS){
                    actionList.at(i)->delayMs = value;
                }
            }
        }
        updateActionListWidget();
        ui->actionListWidget->setCurrentRow(order);
    }
}

void MyWidget::updateActionListWidget()
{
    ui->actionListWidget->clear();
    int goalCount = 0;
    for(int i=0; i<actionList.count(); i++){
        for(int j=0; j<actionList.count(); j++){
            if(actionList.at(j)->order == i){
                if(actionList.at(j)->type == ACTION_TYPE::NAVIGOAL){
                    actionList.at(j)->marker->order = goalCount;
                    QString str;
                    str = QString("Goal %1 \t (%2, %3, %4) \t (%5, %6, %7) \t %8")
                            .arg(goalCount)
                            .arg(actionList.at(j)->point.y(), 0, 'f', 2)
                            .arg(actionList.at(j)->point.x(), 0, 'f', 2)
                            .arg(qRadiansToDegrees(actionList.at(j)->marker->theta), 0, 'f', 2)
                            .arg(actionList.at(j)->disTolerance, 0, 'f', 2)
                            .arg(actionList.at(j)->angleTolerance, 0, 'f', 2)
                            .arg(actionList.at(j)->reachTolerance, 0, 'f', 2)
                            .arg(actionList.at(j)->remark);
                    ui->actionListWidget->addItem(str);
                    QString rosStr = QString(" postion:(%1, %2, 0.0000)\n orientation:(%3, %4, %5, %6)\n tolerance:(%7, %8, %9)")
                            .arg(actionList.at(j)->point.x(), 0, 'f', 4)
                            .arg(actionList.at(j)->point.y(), 0, 'f', 4)
                            .arg(actionList.at(j)->quat.x(), 0, 'f', 4)
                            .arg(actionList.at(j)->quat.y(), 0, 'f', 4)
                            .arg(actionList.at(j)->quat.z(), 0, 'f', 4)
                            .arg(actionList.at(j)->quat.scalar(), 0, 'f', 4)
                            .arg(actionList.at(j)->disTolerance, 0, 'f', 2)
                            .arg(actionList.at(j)->angleTolerance, 0, 'f', 2)
                            .arg(actionList.at(j)->reachTolerance, 0, 'f', 2);
                    ui->actionListWidget->item(i)->setToolTip(rosStr);

                    goalCount++;
                    break;
                }
                else if(actionList.at(j)->type == ACTION_TYPE::DELAYACTION){
                    QString str = QString("Delay \t %1 ms").arg(actionList.at(j)->delayMs);
                    ui->actionListWidget->addItem(str);
                    break;
                }
                else if(actionList.at(j)->type == ACTION_TYPE::EXTERNALCOMACTION){
                    QString str = QString("External Comm. Address:%1/Value:%2")
                            .arg((int)actionList.at(j)->valueList.at(0), 4, 16, QLatin1Char('0'))
                            .arg((int)actionList.at(j)->valueList.at(1), 4, 16, QLatin1Char('0'));
                    ui->actionListWidget->addItem(str);
                    break;
                }
            }
        }
    }
}

void MyWidget::changeCursor()
{
    switch (naviMode) {
    case NAVIMODE_TYPE::StartAction:
        this->setCursor(Qt::ArrowCursor);
        break;
    case NAVIMODE_TYPE::SetInitPose:
    case NAVIMODE_TYPE::AddGoal:
        this->setCursor(Qt::CrossCursor);
        break;
    case NAVIMODE_TYPE::EditGoal:
        break;
    default:
        this->setCursor(Qt::ArrowCursor);
        break;
    }
}

void MyWidget::resetMapView()
{
    delete mapPixmapItem;
    m_map.mapPixmap = QPixmap();
    mapPixmapItem = new QGraphicsPixmapItem;
    m_map.mapName.clear();

    delete robotPixmapItem;
    robotPixmapItem = new QGraphicsPixmapItem;
    robotPixmapItem->setPixmap(QPixmap("robot5x5.bmp"));

    qDeleteAll(mapScene->items());
    preFactor = 1.0;
    scaleFactor = 1.0;
    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), scaleFactor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), scaleFactor);

    ui->zoomInBtn->setEnabled(false);
    ui->zoomOutBtn->setEnabled(false);
}

void MyWidget::setProgressDialog()
{
    progressDlg = new QProgressDialog;
    progressDlg->setAttribute(Qt::WA_DeleteOnClose);
    progressDlg->setWindowFlags(Qt::FramelessWindowHint);
    progressDlg->setWindowFlags(Qt::WindowTitleHint);
    progressDlg->setRange(0, 100);
    progressDlg->setWindowTitle("Progress");
    progressDlg->setModal(true);
    progressDlg->setCancelButton(0);
    progressDlg->setFixedSize(progressDlg->width(), progressDlg->height());
    progressDlg->setStyleSheet("background: rgba(32, 80, 96, 100); color: white;");
    progressDlg->show();

    progressValue = 1;
    progressTimer->start();
}

void MyWidget::initMapEditActions()
{
    undoStack = new QUndoStack(this);

    undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);

    this->addAction(undoAction);
    this->addAction(redoAction);
}

void MyWidget::drawLineTo(const QPointF &endPoint)
{
    QPen pen(myPenColor, myPointDiameter, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QLineF newLine(lastPoint, endPoint);
    onceAddItemList.append(mapScene->addLine(newLine, pen));

    int rad = (myPointDiameter / 2) + 2;
    mapScene->update(QRectF(lastPoint, endPoint).normalized()
                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void MyWidget::setCustomCursor(int diameter, QColor color)
{
    diameter *= scaleFactor;
    QPixmap cursorPixmap = QPixmap(":empty.png");
    cursorPixmap.fill(Qt::transparent);
    QPainter painter(&cursorPixmap);
    painter.setPen(QPen(color, 1));
    painter.setBrush(color);
    painter.drawEllipse(cursorPixmap.width()/2-diameter/2, cursorPixmap.height()/2-diameter/2, diameter, diameter);
    painter.end();
    QCursor customCursor = QCursor(cursorPixmap);
    setCursor(customCursor);
}

void MyWidget::saveEditedMap(QString name)
{
    mapScene->clearSelection();
    mapScene->setSceneRect(mapScene->itemsBoundingRect());
    QImage image(mapScene->sceneRect().size().toSize(), QImage::Format_Grayscale8);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    mapScene->render(&painter);
    painter.end();

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            if(image.pixelColor(i,j).black() == 189)
                image.setPixel(i, j, qRgb(200, 200, 200));
        }
    }

    QTransform myTransform;
    myTransform.rotate(-90);
    image = image.transformed(myTransform);
    onPublishEditedMap(image, name);
}

void MyWidget::teachGoalDestroyed()
{
    onUnsubscribeSensorButtonCmdVel();
    onPublishKeyPriority(false);
    mode = modeBeforeTeach;
}

EditMapStack::EditMapStack(QList<QGraphicsItem *> list, QGraphicsScene *graphicsScene, QUndoCommand *parent)
{
    static int itemCount = 0;
    myGraphicsScene = graphicsScene;
    newItmeList = list;
    ++itemCount;
    setText(QObject::tr("%1 %2").arg(itemCount).arg(list.count()));
}

EditMapStack::~EditMapStack()
{

}

void EditMapStack::undo()
{
    for(int i=0; i<newItmeList.count(); i++)
        myGraphicsScene->removeItem(newItmeList.at(i));
    myGraphicsScene->update();
}

void EditMapStack::redo()
{
    for(int i=0; i<newItmeList.count(); i++)
        if(!myGraphicsScene->items().contains(newItmeList.at(i)))
            myGraphicsScene->addItem(newItmeList.at(i));
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}

void MyWidget::changeSemicircleSide(bool isLeft)
{
    isLeftSide = isLeft;
    if(mapScene->items().contains(tempEllipseItem)){
        if(isLeftSide)
            tempEllipseItem->setStartAngle(16 * 0);
        else
            tempEllipseItem->setStartAngle(16 * 180);
        tempEllipseItem->setSpanAngle(16 * 180);
        mapScene->update();
    }
}

void MyWidget::onAdvertiseActionScript()
{
    QJsonObject rosJson;
    rosJson.insert("op", "advertise");
    rosJson.insert("topic", "/actionScript");
    rosJson.insert("type", "my_script_handler/actionList");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onAdvertiseAskScript()
{
    QJsonObject rosJson;
    rosJson.insert("op", "advertise");
    rosJson.insert("topic", "/askScript");
    rosJson.insert("type", "std_msgs/String");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onAdvertiseActionCommand()
{
    QJsonObject rosJson;
    rosJson.insert("op", "advertise");
    rosJson.insert("topic", "/actionCommand");
    rosJson.insert("type", "my_action_actionlib/actionCmd");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::onAdvertiseKeyPriority()
{
    QJsonObject rosJson;
    rosJson.insert("op", "advertise");
    rosJson.insert("topic", "/key_priority");
    rosJson.insert("type", "std_msgs/Bool");

    QJsonDocument jsonDoc;
    jsonDoc.setObject(rosJson);
    tcpSocket->write(jsonDoc.toJson());
    tcpSocket->flush();
}

void MyWidget::goOrigin()
{
    onPublishActionCommand(4, ui->scriptNameLineEdit->text(), -1);
}

void MyWidget::poseUpdate()
{
    static bool isFirst = true;
    onCallServiceUpdatePose();

    if(isFirst){
        QTimer::singleShot(1000, this, SLOT(poseUpdate()));
        isFirst = false;
    }
    else
        isFirst = true;
}

void MyWidget::abortMovebase()
{
    onPublishActionCommand(2, ui->scriptNameLineEdit->text(), -1);
    onCallServiceUpdatePose();
    if(mode == MODE_TYPE::NAVI)
        ui->startScriptBtn->setText("Start");
}

void MyWidget::setTeleopMode(TELEOP_TYPE type)
{
    teleopMode = type;
}

void MyWidget::setKeyPriorityFlag(bool flag)
{
    keyPriorityFlag = flag;
    onPublishKeyPriority(!flag);
}

bool MyWidget::on_writeScriptBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return false;

    if(ui->scriptNameLineEdit->text().isEmpty() || ui->loadMapNameLineEdit->text().isEmpty())
        return false;

    onPublishActionScript();

    QMessageBox *mbox = new QMessageBox;
    mbox->setAttribute(Qt::WA_DeleteOnClose);
    mbox->setIcon(QMessageBox::Information);
    mbox->setWindowTitle("OK");
    mbox->setText(QString(tr("Write <%1> script to robot OK !")).arg(ui->scriptNameLineEdit->text()));
    mbox->show();
    QTimer::singleShot(2000, mbox, SLOT(close()));

    return true;
}

void MyWidget::on_startScriptBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    if(ui->startScriptBtn->text() == "Start"){
        QMessageBox *mb = new QMessageBox;
        mb->setIcon(QMessageBox::Question);
        mb->setText("Information");
        mb->setInformativeText("Press 'Apply' to write the current script, or 'Discard' to reload this from robot!");
        mb->setStandardButtons(QMessageBox::Apply|QMessageBox::Discard|QMessageBox::Cancel);
        mb->setDefaultButton(QMessageBox::Apply);
        int ret = mb->exec();
        mb->deleteLater();
        switch(ret){
        case QMessageBox::Apply:
            if(on_writeScriptBtn_clicked()){
                qDebug() << "Apply";
                QThread::msleep(1000);
                onPublishActionCommand(1, ui->scriptNameLineEdit->text(), -1);
                ui->startScriptBtn->setText("Pause");
            }
            break;
        case QMessageBox::Discard:
            loadScript(ui->scriptNameLineEdit->text());
            QThread::msleep(100);
            onPublishActionCommand(1, ui->scriptNameLineEdit->text(), -1);
            ui->startScriptBtn->setText("Pause");
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
    else if(ui->startScriptBtn->text() == "Resume"){
        ui->startScriptBtn->setText("Pause");
        onPublishActionCommand(1, ui->scriptNameLineEdit->text(), -1);
    }
    else if(ui->startScriptBtn->text() == "Pause"){
        ui->startScriptBtn->setText("Resume");
        onPublishActionCommand(3, ui->scriptNameLineEdit->text(), -1);
    }
    onCallServiceUpdatePose();
}

void MyWidget::on_stopScriptBtn_clicked()
{
    ui->actionListWidget->setCurrentRow(-1);
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    ui->startScriptBtn->setText("Start");
    onPublishActionCommand(2, ui->scriptNameLineEdit->text(), -1);
}

void MyWidget::on_readScriptBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;

    listDlg->clearList();
    listDlg->setListType(LIST_TYPE::LISTSCRIPT);
    listDlg->show();

    onCallServiceListScript();
}

void MyWidget::on_resetStatusBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    QMessageBox *mb = new QMessageBox;
    mb->setIcon(QMessageBox::Warning);
    mb->setText("Warring");
    mb->setInformativeText("Do you want to reset to current state?");
    mb->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    mb->setDefaultButton(QMessageBox::No);
    int ret = mb->exec();
    mb->deleteLater();
    switch(ret){
    case QMessageBox::Yes:{
        ui->loadMapNameLineEdit->setText("");
        ui->scriptNameLineEdit->setText("");
        ui->statusLineEdit->setText("Null");
        ui->mappingWidthLineEdit->setText("");
        ui->mappingHeightLineEdit->setText("");
        ui->mappingResLineEdit->setText("");
        ui->mapNameLineEdit->setText("");
        ui->loadMapName4EditLineEdit->setText("");
        on_clearGoalBtn_clicked();
        resetMapView();

        onUnsubscribeMap();
        onUnsubscribeTf();
        onUnsubscribeAmclPose();
        onUnsubscribeMovebaseStatus();
        onUnsubscribeReplyScript();
        onUnsubscribeFeedbackMsg();
        onUnsubscribeRstate();

        enableUi(false);
        onPublishRobotModeFlag(MODE_TYPE::RESETNODE);
        QTime dieTime= QTime::currentTime().addSecs(10);
        while(true){
            if(QTime::currentTime() > dieTime){
                tcpConnectStateChange();
                break;
            }
        }
        break;
    }
    case QMessageBox::No:
        break;
    default:
        break;
    }
}

void MyWidget::on_rebootBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    QMessageBox *mb = new QMessageBox;
    mb->setIcon(QMessageBox::Warning);
    mb->setText("Warring");
    mb->setInformativeText("Do you want to reboot AGV?");
    mb->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    mb->setDefaultButton(QMessageBox::No);
    int ret = mb->exec();
    mb->deleteLater();
    switch(ret){
    case QMessageBox::Yes:{
        ui->loadMapNameLineEdit->setText("");
        ui->scriptNameLineEdit->setText("");
        ui->statusLineEdit->setText("Null");
        ui->mappingWidthLineEdit->setText("");
        ui->mappingHeightLineEdit->setText("");
        ui->mappingResLineEdit->setText("");
        ui->mapNameLineEdit->setText("");
        ui->loadMapName4EditLineEdit->setText("");
        on_clearGoalBtn_clicked();
        resetMapView();

        onUnsubscribeMap();
        onUnsubscribeTf();
        onUnsubscribeAmclPose();
        onUnsubscribeMovebaseStatus();
        onUnsubscribeReplyScript();
        onUnsubscribeFeedbackMsg();
        onUnsubscribeRstate();

        onPublishRobotModeFlag(MODE_TYPE::RESTARTAGV);
        break;
    }
    case QMessageBox::No:
        break;
    default:
        break;
    }
}

void MyWidget::on_shutdownBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    QMessageBox *mb = new QMessageBox;
    mb->setIcon(QMessageBox::Warning);
    mb->setText("Warring");
    mb->setInformativeText("Do you want to shutdown AGV?");
    mb->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    mb->setDefaultButton(QMessageBox::No);
    int ret = mb->exec();
    mb->deleteLater();
    switch(ret){
    case QMessageBox::Yes:{
        onPublishRobotModeFlag(MODE_TYPE::SHUTDOWNAGV);
        QTime dieTime= QTime::currentTime().addSecs(5);
        while(true){
            if(QTime::currentTime() > dieTime){
                this->close();
                break;
            }
        }
        break;
    }
    case QMessageBox::No:
        break;
    default:
        break;
    }
}

void MyWidget::on_poseUpdateBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    poseUpdate();
}

void MyWidget::on_xrockerJoystickBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    keyPriorityFlag = true;
    TeachGoalDialog *dlg;
    if(ui->actionListWidget->currentRow() == -1)
        dlg = new TeachGoalDialog(velSliderValue, teleopMode, false);
    else
        dlg = new TeachGoalDialog(velSliderValue, teleopMode, true);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModal(true);
    dlg->setJoystickLevel(0);
    onPublishKeyPriority(false);
    onSubscribeSensorButtonCmdVel();
    connect(dlg, &TeachGoalDialog::updateVel, this, &MyWidget::updateVel);
    connect(dlg, &TeachGoalDialog::updateVelPercentage, this, &MyWidget::updateVelPercentage);
    connect(dlg, &TeachGoalDialog::destroyed, this, &MyWidget::teachGoalDestroyed);
    connect(dlg, &TeachGoalDialog::setTeleopMode, this, &MyWidget::setTeleopMode);
    connect(dlg, &TeachGoalDialog::setKeyPriorityFlag, this, &MyWidget::setKeyPriorityFlag);
    dlg->move(this->pos().x()+this->size().width()/2-dlg->size().width()/2, this->pos().y()+this->size().height()/2-dlg->size().height()/2);
    dlg->show();
}

void MyWidget::on_mappingJoystickBtn_clicked()
{
    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
        return;
    keyPriorityFlag = true;
    TeachGoalDialog *dlg;
    if(ui->actionListWidget->currentRow() == -1)
        dlg = new TeachGoalDialog(velSliderValue, teleopMode, false);
    else
        dlg = new TeachGoalDialog(velSliderValue, teleopMode, true);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModal(true);
    dlg->setJoystickLevel(0);
    onPublishKeyPriority(false);
    onSubscribeSensorButtonCmdVel();
    connect(dlg, &TeachGoalDialog::updateVel, this, &MyWidget::updateVel);
    connect(dlg, &TeachGoalDialog::updateVelPercentage, this, &MyWidget::updateVelPercentage);
    connect(dlg, &TeachGoalDialog::destroyed, this, &MyWidget::teachGoalDestroyed);
    connect(dlg, &TeachGoalDialog::setTeleopMode, this, &MyWidget::setTeleopMode);
    connect(dlg, &TeachGoalDialog::setKeyPriorityFlag, this, &MyWidget::setKeyPriorityFlag);
    dlg->move(this->pos().x()+this->size().width()/2-dlg->size().width()/2, this->pos().y()+this->size().height()/2-dlg->size().height()/2);
    dlg->show();
}
