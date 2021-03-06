/* * This file is part of Maliit framework *
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#include "miminputcontextdirectconnection.h"

#include "mimdirectserverconnection.h"

#include <QtCore>
#include <QtGui/QKeyEvent>

MImInputContextDirectConnection *MImInputContextDirectConnection::instance()
{
    static MImInputContextDirectConnection singleton;

    return &singleton;
}

MImInputContextDirectConnection::MImInputContextDirectConnection(QObject *parent)
    : MInputContextConnection(parent)
    , mServerConnection(0)
{
}

void MImInputContextDirectConnection::connectTo(MImDirectServerConnection *serverConnection)
{
    if (!serverConnection) {
        qCritical() << __PRETTY_FUNCTION__ << "serverConnection cannot be NULL";
        return;
    }

    if (serverConnection != mServerConnection) {
        mServerConnection = serverConnection;
        serverConnection->connectTo(this);
    }
}

void MImInputContextDirectConnection::sendPreeditString(const QString &string,
                                                        const QList<Maliit::PreeditTextFormat> &preeditFormats,
                                                        int replacementStart,
                                                        int replacementLength,
                                                        int cursorPos)
{
    Q_EMIT mServerConnection->updatePreedit(string, preeditFormats,
                                            replacementStart, replacementLength, cursorPos);
}

void MImInputContextDirectConnection::sendCommitString(const QString &string, int replaceStart,
                                                       int replaceLength, int cursorPos)
{
    Q_EMIT mServerConnection->commitString(string, replaceStart, replaceLength, cursorPos);
}

void MImInputContextDirectConnection::sendKeyEvent(const QKeyEvent &keyEvent,
                                                   Maliit::EventRequestType requestType)
{
    const int type = static_cast<int>(keyEvent.type());
    const int key = static_cast<int>(keyEvent.key());
    const int modifiers = static_cast<int>(keyEvent.modifiers());

    /* TODO: make this API take the QEvent, so we don't have to do convert the argument here
    in a way that matches the conversion done in MInputContext::keyEvent() */
    Q_EMIT mServerConnection->keyEvent(type, key, modifiers,
                                       keyEvent.text().toUtf8().data(),
                                       keyEvent.isAutoRepeat(), keyEvent.count(),
                                       requestType);
}

void MImInputContextDirectConnection::notifyImInitiatedHiding()
{
    Q_EMIT mServerConnection->imInitiatedHide();
}

void MImInputContextDirectConnection::invokeAction(const QString &action, const QKeySequence &sequence)
{
    Q_EMIT mServerConnection->invokeAction(action, sequence);
}

void MImInputContextDirectConnection::setRedirectKeys(bool enabled)
{
    Q_EMIT mServerConnection->setRedirectKeys(enabled);
}

void MImInputContextDirectConnection::setDetectableAutoRepeat(bool enabled)
{
    Q_EMIT mServerConnection->setDetectableAutoRepeat(enabled);
}

void MImInputContextDirectConnection::setGlobalCorrectionEnabled(bool enabled)
{
    Q_EMIT mServerConnection->setGlobalCorrectionEnabled(enabled);
}

void MImInputContextDirectConnection::setSelection(int start, int length)
{
    Q_EMIT mServerConnection->setSelection(start, length);
}

void MImInputContextDirectConnection::updateInputMethodArea(const QRegion &region)
{
    Q_EMIT mServerConnection->updateInputMethodArea(region.boundingRect());
}

void MImInputContextDirectConnection::notifyExtendedAttributeChanged(int id,
                                                                     const QString &target,
                                                                     const QString &targetItem,
                                                                     const QString &attribute,
                                                                     const QVariant &value)
{
    Q_EMIT mServerConnection->extendedAttributeChanged(id, target, targetItem,
                                                       attribute, value);
}

void MImInputContextDirectConnection::notifyExtendedAttributeChanged(const QList<int> &clientIds,
                                                                     int id,
                                                                     const QString &target,
                                                                     const QString &targetItem,
                                                                     const QString &attribute,
                                                                     const QVariant &value)
{
    Q_UNUSED(clientIds);

    Q_EMIT mServerConnection->extendedAttributeChanged(id, target, targetItem,
                                                       attribute, value);
}

void MImInputContextDirectConnection::pluginSettingsLoaded(int clientId, const QList<MImPluginSettingsInfo> &info)
{
    Q_UNUSED(clientId);

    Q_EMIT mServerConnection->pluginSettingsReceived(info);
}
