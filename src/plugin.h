/*
 * This file is part of oauth2 plugin
 *
 * Copyright (C) 2010 Nokia Corporation.
 * Copyright (C) 2012 Canonical Ltd.
 *
 * Contact: Alberto Mardegan <alberto.mardegan@canonical.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef SIGNON_PLUGIN_OAUTH2_MAIN
#define SIGNON_PLUGIN_OAUTH2_MAIN

#include <QtCore>

#include <SignOn/AuthPluginInterface>
#include <SignOn/SessionData>
#include <SignOn/Error>

class OAuth2PluginTest;
class QNetworkAccessManager;

namespace OAuth2PluginNS {

class BasePlugin;

/*!
 * @class Plugin
 * OAuth authentication plugin.
 */
class PluginPrivate;
class Plugin: public AuthPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(AuthPluginInterface);
    friend class ::OAuth2PluginTest;
public:
    Plugin(QObject *parent = 0);
    ~Plugin();

public Q_SLOTS:
    QString type() const;
    QStringList mechanisms() const;
    void cancel();
    void process(const SignOn::SessionData &inData, const QString &mechanism = 0);
    void userActionFinished(const SignOn::UiSessionData &data);
    void refresh(const SignOn::UiSessionData &data);

private:
    BasePlugin *impl;
    QNetworkAccessManager *m_networkAccessManager;
};

} //namespace OAuth2PluginNS

#endif // SIGNON_PLUGIN_OAUTH2_MAIN
