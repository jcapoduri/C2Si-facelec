/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef client_H
#define client_H

#include "ui_wsfeform.h"
#include "wsaalogin.h"
#include "wsfemanager.h"
#include <QWidget>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QProcess>
#include <QDateTime>
#include <QMessageBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QSslSocket;
class QToolButton;
class Ui_wsfeForm;
QT_END_NAMESPACE

class client : public QWidget
{
    Q_OBJECT
public:
    client(QWidget *parent = 0);
    client(QString settingFile, bool justcae, QWidget *parent = 0);
    ~client();
    
    void justCae();
private slots:
    void updateEnabledState();

    void secureConnect();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketEncrypted();
    void sslErrors(const QList<QSslError> &errors);
    void socketErrors(const QAbstractSocket::SocketError error);

    void logedIn();

    void operationChanged(QString value);
    void doOperation();

    void validateRecipe();
    void getLastApproveRecipe();
    void getRecipeInfo();

    void logSessionData(QString data);

    void appendString(const QString &line);
    void cleanCae(QString error);
    void writeError(QString error);

signals:
    void wsaalogon(bool status);

private:
    QTimer       closeTimer;
    QSslSocket   *socket;
    wsaaLogin    *wsaa;
    wsfeManager  *wsfe;

    QToolButton *padLock;
    Ui_wsfeForm *form;
    bool executingDialog;
    bool wsaaok;

    QString token;
    QString sign;
    QString error;

    QString source, cuit;
    QString inker, pass;
    QString certConexion;
    QString x509, ptoventa, prestaserv;
    QString pedido;
    QString pedido_iva;
    QString pedido_tributo;
    QString pedido_opcional;
    int port;
    bool testing;
    int     secondsToClose;
    bool _justcae;
};

#endif
