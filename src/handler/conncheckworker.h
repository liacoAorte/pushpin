/*
 * Copyright (C) 2016 Fanout, Inc.
 *
 * This file is part of Pushpin.
 *
 * $FANOUT_BEGIN_LICENSE:APACHE2$
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * $FANOUT_END_LICENSE$
 */

#ifndef CONNCHECKWORKER_H
#define CONNCHECKWORKER_H

#include <QByteArray>
#include "deferred.h"
#include "cidset.h"

class ZrpcRequest;
class ZrpcManager;
class StatsManager;

class ConnCheckWorker : public Deferred
{
	Q_OBJECT

public:
	ConnCheckWorker(ZrpcRequest *req, ZrpcManager *proxyControlClient, StatsManager *stats, QObject *parent = 0);

private:
	ZrpcRequest *req_;
	CidSet cids_;
	CidSet missing_;

	void respondError(const QByteArray &condition);
	void doFinish();

private slots:
	void proxyConnCheck_finished(const DeferredResult &result);
};

#endif
