/*
 * This file is part of oauth2 plugin
 *
 * Copyright (C) 2010 Nokia Corporation.
 *
 * Contact: Alberto Mardegan <alberto.mardegan@nokia.com>
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

#ifndef OAUTH2PLUGIN_H
#define OAUTH2PLUGIN_H

#include <QtCore>
#include <QSslError>
#include <QNetworkRequest>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>

#include <SignOn/AuthPluginInterface>
#include <SignOn/SessionData>
#include <SignOn/Error>

#include "oauth2data.h"
#include "oauth1data.h"

class OAuth2PluginTest;
namespace OAuth2PluginNS {

    /*!
 * @class oauthPlugin
 * OAuth authentication plugin.
 */
    class OAuth2Plugin : public AuthPluginInterface
    {
        Q_OBJECT
        Q_INTERFACES(AuthPluginInterface);
        friend class ::OAuth2PluginTest;
    public:
        OAuth2Plugin(QObject *parent = 0);
        ~OAuth2Plugin();

    public Q_SLOTS:
        QString type() const;
        QStringList mechanisms() const;
        void cancel();
        void process(const SignOn::SessionData &inData, const QString &mechanism = 0);
        void userActionFinished(const SignOn::UiSessionData &data);
        void refresh(const SignOn::UiSessionData &data);
        void replyFinished(QNetworkReply*);
        void replyOAuth1RequestFinished(QNetworkReply *reply);
        void slotError(QNetworkReply::NetworkError);
        void slotSslErrors(QList<QSslError> errorList);

    private:
        void sendAuthRequest(const OAuth2PluginData &inData, const QString &mechanism);
        bool validateInput(const SignOn::SessionData &inData, const QString &mechanism);
        QByteArray getQueryString(const QVariantMap& parameters);
        const QVariantMap getRefreshTokenRequestParams(QString refresh_token);
        const QVariantMap getAssertionRequestParams(QString assertion_type, QString assertion);
        const QVariantMap getUserBasicRequestParams(QString username, QString password);
        const QVariantMap getAuthCodeRequestParams(QString code);
        void sendPostRequest(const QByteArray &queryString);
        void sendOAuth1PostRequest(const OAuth1PluginData &inData);
        const QByteArray parseReply(const QByteArray &reply, const QByteArray &find);
        const QByteArray parsePlainTextReply(const QByteArray &reply, const QByteArray &find);
        void handleError(const QByteArray &reply);
        void handleOAuth2Error(const QByteArray &reply);
        void handleOAuth2ErrorMessageContent(const QByteArray &reply);
        void handleOAuth1Error(const QByteArray &reply);
        QString getUrlString(OAuth2PluginData inData, QString type);
        QByteArray constructSignatureBaseString(const QString &aUrl, const QString &callback,
                                                const OAuth1PluginData &inData, const QString &timestamp,
                                                const QString &nonce);
        QString urlEncode(QString strData);
        QString createOAuthHeader(const QString& aUrl, OAuth1PluginData inData,
                                  const QString &callback = QString());
        QByteArray createHMACSha1(const QByteArray &keyForHash ,const QByteArray &secret);
        void handleRequestFinishedError(QNetworkReply *reply, const QByteArray &replyContent);

            private:
        class Private;
        Private *d; // Owned.
    };

} //namespace OAuth2PluginNS

#endif // OAUTH2PLUGIN_H
