/* * This file is part of Maliit framework *
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 * All rights reserved.
 *
 * Contact: maliit-discuss@lists.maliit.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * and appearing in the file LICENSE.LGPL included in the packaging
 * of this file.
 */

#ifndef GUI_UTILS_H__
#define GUI_UTILS_H__

#include <QtGlobal>
#include <QInputContext>
#include <tr1/functional>
#include <vector>

namespace MaliitTestUtils {

    class RemoteWindow : public QWidget
    {
    public:
        explicit RemoteWindow(QWidget *p = 0, Qt::WindowFlags f = 0);

        void paintEvent(QPaintEvent *);
    };

    template <typename T>
    class EventSpyInputContext : public QInputContext, public std::vector<T>
    {
    public:
        typedef std::tr1::function<T (const QEvent *event)> TransformFunction;

        EventSpyInputContext(TransformFunction newTransform) : transform(newTransform) {}

        virtual QString identifierName() { return QString::fromLatin1("EventSpyInputContext"); }
        virtual bool isComposing() const { return false; }
        virtual QString language() { return QString::fromLatin1("EN"); }
        virtual void reset() {}

    protected:
        virtual bool filterEvent(const QEvent *event) {
            this->push_back(transform(event));
            return true;
        }

    private:
        const TransformFunction transform;
    };
}

// For cases where we need to run code _before_ QApplication is created
#define MALIIT_TESTUTILS_GUI_MAIN_WITH_SETUP(TestObject, setupFunc) \
int main(int argc, char *argv[]) \
{ \
    setupFunc();\
    QApplication app(argc, argv);\
    Q_UNUSED(app);\
    TestObject tc;\
    return QTest::qExec(&tc, argc, argv);\
}

#endif // UTILS_H__
