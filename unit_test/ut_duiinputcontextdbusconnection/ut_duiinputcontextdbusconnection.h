#ifndef UT_DUIINPUTCONTEXTDBUSCONNECTION_H
#define UT_DUIINPUTCONTEXTDBUSCONNECTION_H

#include <QtTest/QtTest>
#include <QObject>
#include <QDBusAbstractAdaptor>
#include <QDBusInterface>

#include "duiinputcontextdbusconnection.h"
#include "duiinputmethodbase.h"


class DuiApplication;
class QGraphicsScene;
class DuiInputContext;

// input method base stub that dbus connection calls
class TargetStub: public DuiInputMethodBase
{
public:
    TargetStub(DuiInputContextConnection *icConnection, QObject *parent = 0);
    virtual ~TargetStub();

    virtual void show();
    virtual void hide();
    virtual void setPreedit(const QString &preeditString);
    virtual void reset();
    virtual void mouseClickedOnPreedit(const QPoint &pos, const QRect &preeditRect);
    virtual void update();
    virtual void visualizationPriorityChanged(bool enabled);
    virtual void appOrientationChanged(int angle);
    virtual void redirectKey(int keyType, int keyCode, const QString &text);

    void resetCallCounts();
    int showCallCount();
    int hideCallCount();
    int setPreeditCallCount();
    int resetCallCount();
    int mouseClickedOnPreeditCallCount();
    int updateCallCount();
    int visualizationPriorityChangedCallCount();
    int appOrientationChangedCallCount();
    int redirectKeyCallCount();

private:
    int m_showCallCount;
    int m_hideCallCount;
    int m_setPreeditCallCount;
    int m_resetCallCount;
    int m_mouseClickedOnPreeditCallCount;
    int m_updateCallCount;
    int m_visualizationPriorityChangedCallCount;
    int m_appOrientationChangedCallCount;
    int m_redirectKeyCallCount;
};

// test class
class Ut_DuiInputContextDBusConnection : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    // communication interface to input context
    void testNoReplyDBusCalls();

    // communication interface exposed to dbus
    void testShowOnFocus();
    void testHideOnLostFocus();
    void testMouseClickedOnPreedit();
    void testSetPreedit();
    void testReset();
    void testAppOrientationChanged();
    void testRedirectKey();

private:
    void handleMessages();

private:
    DuiApplication *app;
    DuiInputContextDBusConnection *m_subject;
    TargetStub *m_inputMethod;
    QGraphicsScene *m_scene;
    QDBusInterface *m_clientInterface;
    DuiInputContext *m_inputContext;
};



#endif
